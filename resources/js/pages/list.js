const passwordsContainer = document.getElementById("passwords");
const typeIdToIcon = [
    "instagram",
    "github",
    "facebook",
    "other"
]

let allPasswords = [];

window.electron.fetchPasswords().then((passwords) => {
    allPasswords = passwords;

    for (const { password, username, type, id } of passwords) {
        passwordsContainer.innerHTML += `
            <a href="./manage.html?id=${id}" class="bg-[#202020] hover:bg-[#272727] transition-all duration-150 rounded-md py-6 px-6 flex items-center w-full lg:w-[50%]">
                <img src="../assets/icons/media/${typeIdToIcon[type]}.svg" alt="list" width="40" height="40" class="bg-transparent select-none" />

                <div class="bg-transparent flex flex-col pl-4 text-gray-300">
                    <h1 class="text-lg font-semibold tracking-wide bg-transparent">
                        ${username}
                    </h1>

                    <p class="text-sm text-[#909090] font-semibold bg-transparent">
                        Password: ${password}
                    </p>
                </div>
            </a>`;
    }
}).catch((error) => {
    console.error("Error fetching passwords:", error);
});