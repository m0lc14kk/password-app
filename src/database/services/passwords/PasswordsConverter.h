#pragma once

#include "../../models/passwords/Password.h"
#include "../../models/passwords/RawPassword.h"

class PasswordsConverter {
public:
    static RawPassword convertToRawPassword(const Password& password);
    static Password convertToPassword(const RawPassword& rawPassword);
};
