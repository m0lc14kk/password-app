#include "DatabaseManager.h"
#include <filesystem>
#include <string>

DatabaseManager* DatabaseManager::instance = nullptr;

DatabaseManager::DatabaseManager()
    : databaseInstance(nullptr), databasePath("public/database/passwords.db") {
    openDatabase();
    if (isOpen()) {
        initializeDatabase();
    }
}

DatabaseManager::~DatabaseManager() {
    closeDatabase();
    instance = nullptr;
}

void DatabaseManager::init() {
    if (instance == nullptr) {
        instance = new DatabaseManager();
    }
}

DatabaseManager* DatabaseManager::getInstance() {
    return instance;
}

sqlite3* DatabaseManager::getDatabase() const {
    return databaseInstance;
}

bool DatabaseManager::isOpen() const {
    return databaseInstance != nullptr;
}

bool DatabaseManager::openDatabase() {
    std::filesystem::path dbFilePath(databasePath);
    std::filesystem::path dbDir = dbFilePath.parent_path();
    if (!dbDir.empty() && !std::filesystem::exists(dbDir)) {
        std::filesystem::create_directories(dbDir);
    }

    int rc = sqlite3_open(databasePath.c_str(), &databaseInstance);
    if (rc != SQLITE_OK) {
        sqlite3_close(databaseInstance);
        databaseInstance = nullptr;
        return false;
    }

    return true;
}

void DatabaseManager::closeDatabase() {
    if (databaseInstance != nullptr) {
        sqlite3_close(databaseInstance);
        databaseInstance = nullptr;
    }
}

bool DatabaseManager::initializeDatabase() {
    if (!this->isOpen()) {
        return false;
    }
    return createTables();
}

bool DatabaseManager::createTables() {
    const char* sql = R"(SELECT 1;)";

    char* errMsg = nullptr;
    int rc = sqlite3_exec(databaseInstance, sql, nullptr, nullptr, &errMsg);

    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        return false;
    }

    return true;
}
