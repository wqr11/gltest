#include <QtWidgets/QApplication>
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QtWidgets/QMainWindow>
#include <memory>

#include "./gui/widget.h"

int main(int argc, char **argv)
{
    qDebug() << "[APPLICATION] STARTING";

    QApplication app(argc, argv);

    QMainWindow w;

    std::unique_ptr<TwglWidget> twgl_widget = std::make_unique<TwglWidget>(&w);

    w.setCentralWidget(twgl_widget.get());

    w.show();

    return app.exec();
}
