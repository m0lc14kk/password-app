CREATE TABLE IF NOT EXISTS accounts (
    id VARCHAR(36) NOT NULL,
    name VARCHAR(255) NOT NULL,
    encryptedSecurityPin VARCHAR(255) NOT NULL,
    avatarId INT NOT NULL,
    role INT NOT NULL,

    PRIMARY KEY (id),
    CHECK (role IN (0, 1))
);

CREATE TABLE IF NOT EXISTS passwords (
    id VARCHAR(36) NOT NULL,
    accountId VARCHAR(36) NOT NULL,
    title VARCHAR(255) NOT NULL,
    username VARCHAR(255) NOT NULL,
    url VARCHAR(255),
    encryptedPassword VARCHAR(255) NOT NULL,
    encryptedSecurityPin VARCHAR(255) NOT NULL,

    PRIMARY KEY (id),
    FOREIGN KEY (accountId) REFERENCES accounts (id) ON DELETE CASCADE
);
