import crypto from 'crypto';
import { DESKTOP_HASHING_SECRET_KEY } from "./EnvironmentVariables";

class PasswordHashing {
    private static key: Buffer = crypto.scryptSync(DESKTOP_HASHING_SECRET_KEY, 'salt', 32);

    private constructor() {}

    public static encrypt(plainText: string): string {
        const iv: Buffer = crypto.randomBytes(16);
        const cipher = crypto.createCipheriv('aes-256-cbc', this.key, iv);
        let encrypted: string = cipher.update(plainText, 'utf8', 'hex');
        encrypted += cipher.final('hex');

        return iv.toString('hex') + ':' + encrypted;
    }

    public static decrypt(encryptedData: string): string {
        const [ivHex, encrypted] = encryptedData.split(':');
        const iv: Buffer = Buffer.from(ivHex, 'hex');

        const decipher = crypto.createDecipheriv('aes-256-cbc', this.key, iv);
        let decrypted: string = decipher.update(encrypted, 'hex', 'utf8');
        decrypted += decipher.final('utf8');

        return decrypted;
    }
}

export { PasswordHashing };