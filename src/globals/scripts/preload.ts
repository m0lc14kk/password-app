import { contextBridge, ipcRenderer } from "electron";

contextBridge.exposeInMainWorld("electron", {
    closeWindow: (): void => ipcRenderer.send("closeWindow"),
    minimizeWindow: (): void => ipcRenderer.send("minimizeWindow"),
    maximizeWindow: (): void => ipcRenderer.send("maximizeWindow"),
    fetchPasswords: (): Promise<any[]> => ipcRenderer.invoke("fetchPasswords"),
    addPassword: (options: {
        password: string,
        username: string,
        type: number
    }) => ipcRenderer.send("addPassword", options),

    updatePassword: (id: number, options: {
        password: string,
        username: string,
        type: number
    }) => ipcRenderer.send("updatePassword", id, options),

    deletePassword: (id: number) => ipcRenderer.send("deletePassword", id),
    deleteAllPasswords: () => ipcRenderer.send("deleteAllPasswords"),
});