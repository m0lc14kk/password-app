#pragma once

#include <QMainWindow>

class MainWindow : public QMainWindow {
public:
    static void init();
    static MainWindow* getInstance();

private:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    static MainWindow* instance;
};
