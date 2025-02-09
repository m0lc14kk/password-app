const incrementButton = document.getElementById("incrementButton");
const decrementButton = document.getElementById("decrementButton");
const passwordsAmountInput = document.getElementById("passwordsAmount");
const generatePasswords = document.getElementById("generatePasswords");
const generatedPasswords = document.getElementById("generatedPasswords");

const incrementLengthButton = document.getElementById("incrementLengthButton");
const decrementLengthButton = document.getElementById("decrementLengthButton");
const passwordsLengthInput = document.getElementById("passwordsLengthInput");

const allowedLowercaseLetters = document.getElementById("lowercaseLettersOption");
const allowedUppercaseLetters = document.getElementById("uppercaseLettersOption");
const allowedNumbers = document.getElementById("numbersOption");
const allowedSpecialCharacters = document.getElementById("specialCharactersOption");

const copyToClipboard = (element) => {
    try {
        window.navigator.clipboard.writeText(element);
    } catch {};
};

if (incrementButton) {
    incrementButton.addEventListener("click", () => {
        const currentAmount = +(passwordsAmountInput?.value || 0);
        if (currentAmount < 20) {
            passwordsAmountInput.value = currentAmount + 1;
        }
    })
}

if (decrementButton) {
    decrementButton.addEventListener("click", () => {
        const currentAmount = +(passwordsAmountInput?.value || 0);
        if (currentAmount > 1) {
            passwordsAmountInput.value = currentAmount - 1;
        }
    })
}

if (passwordsAmountInput) {
    passwordsAmountInput.addEventListener("input", () => {
        const currentAmount = +(passwordsAmountInput?.value || 0);
        passwordsAmountInput.value = Math.min(20, Math.max(currentAmount, 1));
    })
}

if (incrementLengthButton) {
    incrementLengthButton.addEventListener("click", () => {
        const currentAmount = +(passwordsLengthInput?.value || 0);
        if (currentAmount < 255) {
            passwordsLengthInput.value = currentAmount + 1;
        }
    })
}

if (decrementLengthButton) {
    decrementLengthButton.addEventListener("click", () => {
        const currentAmount = +(passwordsLengthInput?.value || 0);
        if (currentAmount > 8) {
            passwordsLengthInput.value = currentAmount - 1;
        }
    })
}

if (passwordsLengthInput) {
    passwordsLengthInput.addEventListener("input", () => {
        const currentAmount = +(passwordsLengthInput?.value || 0);
        passwordsLengthInput.value = Math.min(255, Math.max(currentAmount, 8));
    })
}

if (generatePasswords) {
    generatePasswords.addEventListener("click", () => {
        const currentAmount = +(passwordsAmountInput?.value || 0);

        generatedPasswords.innerHTML = "";

        const randomCharacters = [];

        if (allowedNumbers?.checked || false) randomCharacters.push(..."0123456789".split(""));
        if (allowedLowercaseLetters?.checked || false) randomCharacters.push(..."abcdefghijklmnopqrstuvwxyz".split(""));
        if (allowedUppercaseLetters.checked || false) randomCharacters.push(..."abcdefghijklmnopqrstuvwxyz".toUpperCase().split(""));
        if (allowedSpecialCharacters?.checked || false) randomCharacters.push(..."!@#$%&^*".split(""));

        if (randomCharacters.length === 0) {
            generatedPasswords.innerHTML = `<p class="bg-transparent font-medium text-[#909090]">Invalid options of a password generation. Select at least one option to generate your password.</p>`;
            return;
        };

        for (let i = 0; i < currentAmount; i++) {
            let generatedPassword = "";

            for (let j = 0; j < 16; j++)
                generatedPassword += randomCharacters[Math.floor(Math.random() * randomCharacters.length)];

            generatedPasswords.innerHTML += `<li class="bg-transparent" onclick="copyToClipboard(${generatedPassword})">
                ${generatedPassword}
            </li>`;
        };
    })
}
