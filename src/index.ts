import { app, BrowserWindow, ipcRenderer } from "electron";
import { DesktopWindow } from "./globals/DesktopWindow";
import { ipcMain } from "electron";
import { PasswordHashing } from "./globals/PasswordHashing";
import { appDatabase } from "./globals/AppDatabase";

class MainApplication {
    private constructor() {};

    public static init(): void {
        app.on("ready", this.onAppReady);

        this.activateInterProcessCommunication();
    }

    public static async onAppReady(): Promise<void> {
        await DesktopWindow.createWindow();
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

        ipcMain.on("fetchPasswords", () => {
            const result: Array<{
                id: number,
                username: string,
                password: string,
                type: number
            }> = appDatabase.prepare("SELECT * FROM passwords").all() as any[];

            ipcRenderer.send("fetchPasswordsResult", result.map(({ password, ...rest }) => ({
                password: PasswordHashing.decrypt(password),
                ...rest
            })));
        });
    }
}

MainApplication.init();