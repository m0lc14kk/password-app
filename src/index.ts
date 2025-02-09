import { app, BrowserWindow } from "electron";
import { DesktopWindow } from "./globals/DesktopWindow";
import { ipcMain } from "electron";

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
    }
}

MainApplication.init();