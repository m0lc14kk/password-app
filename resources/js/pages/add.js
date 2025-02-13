const addPasswordButton = document.getElementById("addPassword");

if (addPasswordButton) {
    addPasswordButton.addEventListener("click", () => {
        const username = document.getElementById("username").value;
        const password = document.getElementById("password").value;
        const selectedType = document.querySelector('input[name="type"]:checked').value;

        window.electron.addPassword({
            username, password, type: selectedType
        });

        window.location.href = "../views/list.html";
    });
}