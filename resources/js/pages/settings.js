const deleteAllPasswordsButton = document.getElementById("deleteAllPasswords");
const modalDeletePassword = document.getElementById("modalDeletePassword");
const closeModalButton = document.getElementById("closeModal");
const cancelModalButton = document.getElementById("cancelButton");
const modalDeletePasswordButton = document.getElementById("deletePasswordModal");

if (deleteAllPasswordsButton) {
    deleteAllPasswordsButton.addEventListener("click", () => {
        modalDeletePassword.classList.remove("-left-full");
    })
}

if (closeModalButton) {
    closeModalButton.addEventListener("click", () => {
        modalDeletePassword.classList.add("-left-full");
    })
}

if (cancelModalButton) {
    cancelModalButton.addEventListener("click", () => {
        modalDeletePassword.classList.add("-left-full");
    })
}

if (modalDeletePasswordButton) {
    modalDeletePasswordButton.addEventListener("click", () => {
        window.electron.deleteAllPasswords();
        window.location.href = "../views/list.html";
    })
}