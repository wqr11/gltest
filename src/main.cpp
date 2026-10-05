#include <QtCore/QObject>
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QMainWindow>
#include <memory>

#include "./gui/widget.h"

int main(int argc, char **argv) {
  qDebug() << "[APPLICATION] STARTING";

  QApplication app(argc, argv);

  // main widgets
  QWidget *window = new QWidget;

  // twgl
  std::unique_ptr<TwglWidget> twgl_widget =
      std::make_unique<TwglWidget>(window);

  QHBoxLayout *windowLayout = new QHBoxLayout(window);
  windowLayout->setContentsMargins(0, 0, 0, 0);

  // left panel
  QWidget *leftWindowPanel = new QWidget;
  leftWindowPanel->setMinimumWidth(120);
  leftWindowPanel->setMaximumWidth(240);

  QVBoxLayout *leftWindowPanelLayout = new QVBoxLayout;
  QPushButton *btn1 = new QPushButton("set texture");

  QFileDialog *fileDialog = new QFileDialog(window);

  QObject::connect(btn1, &QPushButton::clicked, btn1, [fileDialog]() {
    qDebug() << "[ BUTTON ] CLICKED!";
    fileDialog->open();
  });

  QObject::connect(fileDialog, &QFileDialog::filesSelected, fileDialog,
                   [](const QList<QString> &files) { qDebug() << files; });

  leftWindowPanelLayout->addWidget(btn1);
  leftWindowPanel->setLayout(leftWindowPanelLayout);

  // Add widgets to windowLayout
  windowLayout->addWidget(leftWindowPanel);
  windowLayout->addWidget(twgl_widget.get());

  window->setLayout(windowLayout);
  window->show();

  return app.exec();
}
