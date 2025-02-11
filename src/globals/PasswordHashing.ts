import crypto from 'crypto';
import { DESKTOP_HASHING_SECRET_KEY } from "./EnvironmentVariables";
import { Cipher, Decipher } from "node:crypto";

class PasswordHashing {
    private static key: Buffer = crypto.scryptSync(
        DESKTOP_HASHING_SECRET_KEY,
        'salt',
        32
    );

    private constructor() {};

    public static encrypt(password: string): string {
        const cipher: Cipher = crypto.createCipher('aes-256-cbc', this.key);
        let encrypted: string = cipher.update(password, 'utf8', 'hex');
        encrypted += cipher.final('hex');
        return encrypted;
    }

    public static decrypt(encryptedData: string): string {
        const decipher: Decipher = crypto.createDecipher('aes-256-cbc', this.key);
        let decrypted: string = decipher.update(encryptedData, 'hex', 'utf8');
        decrypted += decipher.final('utf8');
        return decrypted;
    }
}

export { PasswordHashing };