#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <memory>

#include "maze.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_pushButton_clicked();

  void on_pushButton_3_clicked();

  void on_pushButton_2_clicked();

 private:
  Ui::MainWindow *ui_;
  std::unique_ptr<Maze> maze_;
};
#endif  // MAINWINDOW_H
