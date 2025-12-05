#pragma once

#include <QApplication>

class MainApplication : public QApplication {
public:
    static void init(int &argc, char **argv);
    static MainApplication* getInstance();
    
private:
    MainApplication(int &argc, char **argv);
    static MainApplication* instance;
};
