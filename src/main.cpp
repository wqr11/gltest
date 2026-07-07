#include <QApplication>
#include <QOpenGLWidget>
#include <QMainWindow>
#include <memory>

#include "TwglWidget.h"

using namespace std;

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QMainWindow w;

    unique_ptr<TwglWidget> twgl_widget = make_unique<TwglWidget>(&w);

    w.setCentralWidget(twgl_widget.get());

    w.show();

    return app.exec();
}