#include "EncryptionManager.h"
#include <QByteArray>
#include <QCryptographicHash>

std::string EncryptionManager::encrypt(const std::string& data) {
    QCryptographicHash hash(QCryptographicHash::Sha256);
    hash.addData(QByteArray::fromRawData(data.c_str(), data.size()));
    return hash.result().toStdString();
}

std::string EncryptionManager::decrypt(const std::string& data) {
    QCryptographicHash hash(QCryptographicHash::Sha256);
    hash.addData(QByteArray::fromRawData(data.c_str(), data.size()));
    return hash.result().toStdString();
}
