import { app, BrowserWindow } from "electron";
import { DesktopWindow } from "./globals/DesktopWindow";
import { ipcMain } from "electron";
import { PasswordHashing } from "./globals/PasswordHashing";
import { appDatabase } from "./globals/AppDatabase";

class MainApplication {
    private constructor() {};

    public static init(): void {
        app.on("ready", this.onAppReady);
        app.on("window-all-closed", this.onWindowAllClosed)

        this.activateInterProcessCommunication();
    }

    public static async onAppReady(): Promise<void> {
        await DesktopWindow.createWindow();
    }

    public static async onWindowAllClosed(): Promise<void> {
        if (process.platform !== "darwin") {
            app.quit();
        }
    }

    public static activateInterProcessCommunication(): void {
        ipcMain.on("closeWindow", () => {
            const window: BrowserWindow | null = DesktopWindow.instance;
            if (window) {
                window.close();
            }
        })

        ipcMain.on("maximizeWindow", () => {
            const window: BrowserWindow | null = DesktopWindow.instance;
            if (!window)
                return;

            if (window.isMaximized()) {
                window.unmaximize();
            } else {
                window.maximize();
            }
        })

        ipcMain.on("minimizeWindow", () => {
            const window: BrowserWindow | null = DesktopWindow.instance;
            if (window) {
                window.minimize()
            }
        })

        ipcMain.on("deleteAllPasswords", () => {
            appDatabase.run("DELETE FROM passwords;");
        })

        ipcMain.on("deletePassword", (_, id) => {
            const preparedQuery = appDatabase.prepare("DELETE FROM passwords WHERE id = ?");
            preparedQuery.run(id);
        })

        ipcMain.on("updatePassword", (_, id, options) => {
            const preparedQuery = appDatabase.prepare(`
                UPDATE passwords SET username = ?, password = ?, type = ? WHERE id = ?;
            `);

            preparedQuery.run(
                options.username,
                PasswordHashing.encrypt(options.password),
                options.type,
                id
            );
        });

        ipcMain.on("addPassword", (_, options) => {
            const preparedQuery = appDatabase.prepare(`
                INSERT INTO passwords(username, password, type) VALUES (?, ?, ?)
            `)

            preparedQuery.run(
                options.username,
                PasswordHashing.encrypt(options.password),
                options.type,
            );
        })

        ipcMain.handle("fetchPasswords", async () => {
            const sql = "SELECT * FROM passwords ORDER BY id";
            const finalResult: Array<{ id: number; username: string; password: string; type: number }> = [];

            return new Promise((resolve, reject) => {
                appDatabase.all(sql, [], (err, rows: any[]) => {
                    if (err) {
                        reject(false);
                        return;
                    }

                    rows.forEach(({ password, ...rest }) => {
                        finalResult.push({
                            password: PasswordHashing.decrypt(password),
                            ...rest
                        });
                    });

                    resolve(finalResult);
                });
            });
        });
    }
}

MainApplication.init();