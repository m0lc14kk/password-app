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
    
        <div class="bg-transparent flex max-lg:flex-col max-lg:w-full w-[50%] gap-2 pt-4">
            <button id="deletePassword" class="bg-[#702121] duration-150 hover:bg-[#993030] text-center rounded-sm cursor-pointer py-1 w-full font-semibold">
                Delete Password
            </button>
            
            <button id="savePassword" class="bg-[#4040BF] duration-150 hover:bg-[#6868DF] text-center rounded-sm cursor-pointer py-1 w-full font-semibold">
                Save Password
            </button>
        </div>
    `;

    document.getElementById("deletePassword").addEventListener("click", () => {
        modalDeletePassword.classList.remove("-left-full");
    });

    document.getElementById("savePassword").addEventListener("click", () => {
        window.electron.updatePassword(passwordId, {
            username: document.getElementById("username")?.value || "",
            password: document.getElementById("password")?.value || "",
            type: document.getElementById("type")?.value || 3,
        })

        window.location.href = "../views/list.html";
    });
}

main();