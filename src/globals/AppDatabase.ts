import sqlite3 from "sqlite3";
import { join } from "path";
import { existsSync, writeFileSync } from "node:fs";

const filePath: string = join(process.cwd(), "databases/database.db");
if (!existsSync(filePath)) {
    writeFileSync(filePath, "");
}

const appDatabase = new sqlite3.Database(filePath);
appDatabase.exec(`
    CREATE TABLE IF NOT EXISTS passwords (
        id          INTEGER         PRIMARY KEY AUTOINCREMENT,
        username    TEXT            NOT NULL,
        password    TEXT            NOT NULL,
        type        TINYINT(4)      NOT NULL
    )
`);

export { appDatabase };
