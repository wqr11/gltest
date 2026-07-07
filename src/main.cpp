#include <QApplication>
#include <QButtonGroup>
#include <QPushButton>
#include <QMainWindow>
#include <QLabel>
#include <QObject>
#include <QTimer>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QMainWindow w;

    w.setMinimumSize(240, 240);
    w.show();

    QButtonGroup bg(nullptr);

    QPushButton b1(&w);
    QPushButton b2(&w);
    QPushButton b3(&w);

    QLabel l1(&w);

    l1.show();

    b1.setText(QString::fromStdWString(L"Randomize!"));
    b1.show();

    QObject::connect(&b1, &QPushButton::clicked, &w, [&]()
                     {
            l1.setText(QString("IN PROCESS"));

    QTimer::singleShot(2000, [&]()
                       { l1.setText(QString("COMPLETED")); }); }, Qt::ConnectionType::AutoConnection);

    return app.exec();
}