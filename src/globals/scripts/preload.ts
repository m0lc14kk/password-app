import { contextBridge, ipcRenderer } from "electron";

contextBridge.exposeInMainWorld("electron", {
    closeWindow: (): void => ipcRenderer.send("closeWindow"),
    minimizeWindow: (): void => ipcRenderer.send("minimizeWindow"),
    maximizeWindow: (): void => ipcRenderer.send("maximizeWindow"),
    fetchPasswords: (): void => ipcRenderer.send("fetchPasswords"),
});