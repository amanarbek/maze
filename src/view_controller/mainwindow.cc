#include "mainwindow.h"

#include <QGraphicsScene>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);
  maze_ = std::make_unique<Maze>(ui_->graphicsView);
}

MainWindow::~MainWindow() { delete ui_; }

void MainWindow::on_pushButton_clicked() {
  QString path =
      QFileDialog::getOpenFileName(this, "Open", QString(), "maze(*.txt)");
  try {
    maze_->LoadMaze(path);
  } catch (const std::exception& e) {
    QMessageBox::critical(nullptr, "Ошибка", e.what());
  }
}

void MainWindow::on_pushButton_3_clicked() {
  QString path =
      QFileDialog::getSaveFileName(this, "Save maze", QString(), "Maze(*.txt)");
  maze_->Save(path);
}

void MainWindow::on_pushButton_2_clicked() {
  int rows = ui_->spinBox_2->value();
  int cols = ui_->spinBox_3->value();
  maze_->SetWalls(rows, cols);
  maze_->DrawMaze();
}
