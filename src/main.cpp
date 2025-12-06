#include "app/MainApplication.h"
#include "app/MainWindow.h"
#include <QLabel>
#include <QMainWindow>

int main(int argc, char* argv[]) {
    MainApplication::init(argc, argv);
    MainApplication* app = MainApplication::getInstance();

    MainWindow::init();
    MainWindow* window = MainWindow::getInstance();
    window->setWindowTitle("Hello World");
    window->resize(400, 300);

    QLabel* label = new QLabel("Hello World!", window);
    label->setAlignment(Qt::AlignCenter);
    window->setCentralWidget(label);

    window->show();
    return app->exec();
}
