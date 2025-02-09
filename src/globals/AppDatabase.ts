import Database from "better-sqlite3";
import { join } from "path";

const appDatabase = new Database(join(process.cwd(), "databases/database.db"));
appDatabase.exec(`
    CREATE TABLE IF NOT EXISTS passwords (
        id          INT UNSIGNED NOT NULL PRIMARY KEY AUTO_INCREMENT,
        username    VARCHAR(255) NOT NULL,
        password    VARCHAR(255) NOT NULL,
        type        TINYINT(4) UNSIGNED NOT NULL
    )
`);

export { appDatabase };