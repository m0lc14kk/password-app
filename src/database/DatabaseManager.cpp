#include "DatabaseManager.h"
#include <filesystem>
#include <fstream>
#include <sstream>
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

    std::filesystem::path sqlFilePath("public/queries/BaseQueries.sql");
    if (!std::filesystem::exists(sqlFilePath)) {
        return true;
    }

    std::ifstream file(sqlFilePath);
    if (!file.is_open()) {
        return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string sqlContent = buffer.str();
    file.close();

    char* errorMessage = nullptr;
    int rc = sqlite3_exec(databaseInstance, sqlContent.c_str(), nullptr, nullptr, &errorMessage);

    if (rc != SQLITE_OK) {
        if (errorMessage) {
            sqlite3_free(errorMessage);
        }

        return false;
    }

    return true;
}
