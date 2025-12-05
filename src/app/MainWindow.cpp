#include "MainWindow.h"

MainWindow* MainWindow::instance = nullptr;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {}

MainWindow::~MainWindow() {
    instance = nullptr;
}

void MainWindow::init() {
    if (instance == nullptr) {
        instance = new MainWindow();
    }
}

MainWindow* MainWindow::getInstance() {
    return instance;
}