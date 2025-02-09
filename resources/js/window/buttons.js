const closeWindow = document.getElementById("closeWindow");
const maximizeWindow = document.getElementById("maximizeWindow");
const minimizeWindow = document.getElementById("minimizeWindow");
if (!window.electron) window.electron = {};

if (window.electron) {
    closeWindow?.addEventListener("click", () => {
        if (typeof window.electron.closeWindow === "function") {
            window.electron.closeWindow();
        }
    });

    maximizeWindow?.addEventListener("click", () => {
        if (typeof window.electron.maximizeWindow === "function") {
            window.electron.maximizeWindow();
        }
    });

    minimizeWindow?.addEventListener("click", () => {
        if (typeof window.electron.minimizeWindow === "function") {
            window.electron.minimizeWindow();
        }
    });
}