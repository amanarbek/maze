#include <QApplication>

#include "view_controller/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.setFixedSize(761, 520);
  w.show();
  return a.exec();
}
