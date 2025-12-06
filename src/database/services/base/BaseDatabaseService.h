#pragma once

class BaseDatabaseService {
public:
    virtual ~BaseDatabaseService() = default;
    static const int MAX_CREATION_ATTEMPTS = 3;
};
