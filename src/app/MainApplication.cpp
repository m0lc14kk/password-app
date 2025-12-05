#include "MainApplication.h"

MainApplication* MainApplication::instance = nullptr;

MainApplication::MainApplication(int &argc, char **argv) 
    : QApplication(argc, argv) {
}

void MainApplication::init(int &argc, char **argv) {
    if (instance == nullptr) {
        instance = new MainApplication(argc, argv);
    }
}

MainApplication* MainApplication::getInstance() {
    return instance;
}
