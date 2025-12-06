#pragma once

#include <sqlite3.h>
#include <string>

class DatabaseManager {
public:
    static void init();
    static DatabaseManager* getInstance();

    sqlite3* getDatabase() const;
    bool isOpen() const;
    bool initializeDatabase();
    void closeDatabase();

private:
    DatabaseManager();
    ~DatabaseManager();

    bool openDatabase();
    bool createTables();

    sqlite3* databaseInstance;
    std::string databasePath;
    static DatabaseManager* instance;
};
