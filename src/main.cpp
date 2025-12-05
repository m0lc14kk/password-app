#include "app/MainApplication.h"
#include <QMainWindow>
#include <QLabel>

int main(int argc, char *argv[]) {
    MainApplication::init(argc, argv);
    MainApplication *app = MainApplication::getInstance();

    QMainWindow window;
    window.setWindowTitle("Hello World");
    window.resize(400, 300);

    QLabel *label = new QLabel("Hello World!", &window);
    label->setAlignment(Qt::AlignCenter);
    window.setCentralWidget(label);

    window.show();
    return app->exec();
}
