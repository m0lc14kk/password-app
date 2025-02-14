const modalDeletePassword = document.getElementById("modalDeletePassword");
const closeModalButton = document.getElementById("closeModal");
const cancelModalButton = document.getElementById("cancelButton");
const modalDeletePasswordButton = document.getElementById("deletePasswordModal");
const sectionElement = document.getElementById("management");
const urlOptions = window.location.search;
let passwordId = false;

const copyToClipboard = async (element) => {
    try {
        await window.navigator.clipboard.writeText(document.getElementById(element)?.value || "");
    } catch {}
};

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
        if (typeof passwordId !== "number") return;

        window.electron.deletePassword(passwordId);
        window.location.href = "../views/list.html";
    })
}

const main = () => {
    for (const [key, value] of urlOptions.slice(1).split("&").map((pair) => pair.split("="))) {
        if (key === "id") passwordId = +value;
    }

    if (Number.isNaN(passwordId)) {
        sectionElement.innerHTML = `
            <h1 class="bg-transparent">
                INVALID PASSWORD
            </h1>
    
            <p class="text-[#909090] font-semibold bg-transparent">
                This password is invalid.
            </p>
            
            <a href="list.html" class="bg-[#202020] hover:bg-[#272727] transition-all duration-150 rounded-md py-6 px-6 flex items-center w-full lg:w-[50%] mt-4">
                <img src="../assets/icons/list.svg" alt="list" width="40" height="40" class="bg-transparent select-none" />
    
                <div class="bg-transparent flex flex-col pl-4 text-gray-300">
                    <h1 class="text-lg font-semibold tracking-wide bg-transparent">
                        PASSWORDS
                    </h1>
    
                    <p class="text-sm text-[#909090] font-semibold bg-transparent">
                        Get back to list of your passwords.
                    </p>
                </div>
            </a>
        `;
        return;
    }

    viewPassword()
}

const viewPassword = () => {
    const passwordInformation = localStorage.getItem(`${passwordId}`);

    if (!passwordInformation) {
        sectionElement.innerHTML = `
            <h1 class="bg-transparent">
                PASSWORD NOT FOUND
            </h1>
    
            <p class="text-[#909090] font-semibold bg-transparent">
                This password does not exist.
            </p>
            
            <a href="list.html" class="bg-[#202020] hover:bg-[#272727] transition-all duration-150 rounded-md py-6 px-6 flex items-center w-full lg:w-[50%] mt-4">
                <img src="../assets/icons/list.svg" alt="list" width="40" height="40" class="bg-transparent select-none" />
    
                <div class="bg-transparent flex flex-col pl-4 text-gray-300">
                    <h1 class="text-lg font-semibold tracking-wide bg-transparent">
                        PASSWORDS
                    </h1>
    
                    <p class="text-sm text-[#909090] font-semibold bg-transparent">
                        Get back to list of your passwords.
                    </p>
                </div>
            </a>
        `;
        return;
    }

    const { username, password, type } = JSON.parse(passwordInformation);

    sectionElement.innerHTML = `
        <h1 class="bg-transparent">DETAILS</h1>
        <p class="text-[#909090] font-semibold bg-transparent">Details about selected password.</p>
        
        <ul id="errors" class="bg-[#321414] rounded-sm border-[#90909030] border p-3 flex flex-col mt-4 max-lg:w-full lg:w-[50%] gap-y-2 hidden">
            <li class="bg-transparent flex items-center justify-between">
                <h3 class="bg-transparent font-semibold text-[#AA909060]">
                    ERRORS
                </h3>

                <button id="closeErrors" class="p-[2px] rounded-sm border border-[#90909030] bg-[#201010] cursor-pointer select-none">
                    <img src="../assets/icons/close.svg" alt="close" width="16" height="16" class="bg-transparent select-none" />
                </button>
            </li>

            <li class="bg-transparent w-full">
                <ul class="bg-transparent flex flex-col gap-y-[2px] pl-2]">
                    <li class="bg-transparent text-[#909090] font-semibold hidden" id="usernameError">
                        You must provide a username or an email address.
                    </li>
                    <li class="bg-transparent text-[#909090] font-semibold hidden" id="passwordError">
                        You must provide a password.
                    </li>
                </ul>
            </li>
        </ul>
    
        <label for="username" class="text-[#909090] font-semibold bg-transparent pt-4 flex items-center gap-x-1 pb-2">
            <button type="button" onclick="copyToClipboard('username')" class="bg-transparent">
                <img src="../assets/icons/copy.svg" alt="copy" width="24" height="24" class="bg-transparent select-none cursor-pointer" />
            </button> 
            USERNAME
        </label>
        <input name="username" type="text" value="${username}" class="bg-transparent p-2 outline-none border-[#90909030] border rounded-md font-medium max-lg:w-full w-[50%]" maxlength="64" minlength="3" id="username" />
    
        <label for="password" class="text-[#909090] font-semibold bg-transparent pt-4 flex items-center gap-x-1 pb-2">
            <button type="button" onclick="copyToClipboard('password')" class="bg-transparent">
                <img src="../assets/icons/copy.svg" alt="copy" width="24" height="24" class="bg-transparent select-none cursor-pointer" />
            </button>
            PASSWORD
        </label>
        <input name="password" type="text" value="${password}" class="bg-transparent p-2 outline-none border-[#90909030] border rounded-md font-medium max-lg:w-full w-[50%]" maxlength="64" minlength="3" id="password" />
    
    
        <p class="text-[#909090] font-semibold bg-transparent pt-4 pb-2">
            TYPE
        </p>
    
        <div class="grid max-lg:w-full w-[50%] grid-cols-2 gap-[2px]">
            <div class="bg-transparent flex items-center justify-start gap-x-2">
                <input type="radio" id="type-instagram" name="type" value="0" class="cursor-pointer appearance-none border-2 border-[#909090] rounded-sm bg-[#101010] w-4 h-4 checked:bg-[#6868DF] checked:border-[#6868DF] duration-150" ${type === 0 ? "checked" : ""} />
                <label for="type-instagram" class="text-[#909090] font-semibold bg-transparent">
                    Instagram
                </label>
            </div>

            <div class="bg-transparent flex items-center justify-start gap-x-2">
                <input type="radio" id="type-github" name="type" value="1" class="cursor-pointer appearance-none border-2 border-[#909090] rounded-sm bg-[#101010] w-4 h-4 checked:bg-[#6868DF] checked:border-[#6868DF] duration-150" ${type === 1 ? "checked" : ""} />
                <label for="type-github" class="text-[#909090] font-semibold bg-transparent">
                    GitHub
                </label>
            </div>

            <div class="bg-transparent flex items-center justify-start gap-x-2">
                <input type="radio" id="type-facebook" name="type" value="2" class="cursor-pointer appearance-none border-2 border-[#909090] rounded-sm bg-[#101010] w-4 h-4 checked:bg-[#6868DF] checked:border-[#6868DF] duration-150" ${type === 2 ? "checked" : ""} />
                <label for="type-facebook" class="text-[#909090] font-semibold bg-transparent">
                    Facebook
                </label>
            </div>

            <div class="bg-transparent flex items-center justify-start gap-x-2">
                <input type="radio" id="type-other" name="type" value="3" class="cursor-pointer appearance-none border-2 border-[#909090] rounded-sm bg-[#101010] w-4 h-4 checked:bg-[#6868DF] checked:border-[#6868DF] duration-150" ${type === 3 ? "checked" : ""} />
                <label for="type-other" class="text-[#909090] font-semibold bg-transparent">
                    Other
                </label>
            </div>
        </div>
    
        <div class="bg-transparent flex max-lg:flex-col max-lg:w-full w-[50%] gap-2 pt-4">
            <button id="deletePassword" class="bg-[#702121] duration-150 hover:bg-[#993030] text-center rounded-sm cursor-pointer py-1 w-full font-semibold">
                Delete Password
            </button>
            
            <button id="savePassword" class="bg-[#4040BF] duration-150 hover:bg-[#6868DF] text-center rounded-sm cursor-pointer py-1 w-full font-semibold">
                Save Password
            </button>
        </div>
    `;

    const errorsContainer = document.getElementById("errors");
    const usernameError = document.getElementById("usernameError");
    const passwordError = document.getElementById("passwordError");

    const closeErrors = document.getElementById("closeErrors");

    if (closeErrors) {
        closeErrors.addEventListener("click", () => {
            errorsContainer.classList.add("hidden");
        });
    }

    document.getElementById("deletePassword").addEventListener("click", () => {
        modalDeletePassword.classList.remove("-left-full");
    });

    document.getElementById("savePassword").addEventListener("click", () => {
        const username = document.getElementById("username")?.value || "";
        const password = document.getElementById("password")?.value || "";

        if (!password || !username) {
            usernameError.classList[!username ? "remove" : "add"]("hidden");
            passwordError.classList[!password ? "remove" : "add"]("hidden");
            errorsContainer.classList.remove("hidden");
            return;
        }

        window.electron.updatePassword(passwordId, {
            username,
            password,
            type: document.querySelector('input[name="type"]:checked')?.value || 3,
        })

        window.location.href = "../views/list.html";
    });
}

main();