#include "maze.h"

Maze::Maze(QWidget *parent) : QGraphicsView(parent) {
  rows_ = cols_ = 1;
  size_cellh_ = size_cellv_ = 0.0;
  vertical_walls_ = horizontal_walls_ = {{0}};
  scene_ = new QGraphicsScene(this);
  DrawMaze();
}

Maze::~Maze() {
  ClearScene();
  delete scene_;
  scene_ = nullptr;
}

void Maze::LoadMaze(const QString &path) {
  downloader_.UploadMazeFromFile(path.toUtf8().constData());
  rows_ = downloader_.GetRows();
  cols_ = downloader_.GetCols();
  vertical_walls_ = downloader_.GetWallsMatrix();
  horizontal_walls_ = downloader_.GetBottomsMatrix();
  DrawMaze();
}

void Maze::ClearVec(QVector<QGraphicsEllipseItem *> &vec) {
  for (int i = 0; i < vec.size(); i++) {
    delete vec[i];
    vec[i] = nullptr;
  }
  vec.clear();
}

void Maze::ClearVec(QVector<QGraphicsLineItem *> &vec) {
  for (int i = 0; i < vec.size(); i++) {
    delete vec[i];
    vec[i] = nullptr;
  }
  vec.clear();
}

void Maze::ClearScene() {
  ClearVec(dots_);
  ClearVec(path_dots_);
  scene_->clear();
  coords_.clear();
}

void Maze::SetWalls(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  eller_.Generator(rows, cols);
  vertical_walls_ = eller_.GetWalls();
  horizontal_walls_ = eller_.GetBottoms();
}

void Maze::DrawMaze() {
  ClearScene();
  setScene(scene_);
  size_cellv_ = 500.0 / rows_;
  size_cellh_ = 500.0 / cols_;
  QPen penBlack(Qt::black, 2);
  for (int row = 0; row < rows_; ++row) {
    for (int col = 0; col < cols_; ++col) {
      if (vertical_walls_[row][col] == 1) {
        scene_->addLine((col + 1) * size_cellh_, row * size_cellv_,
                        (col + 1) * size_cellh_, (row + 1) * size_cellv_,
                        penBlack);
      }
      if (horizontal_walls_[row][col] == 1)
        scene_->addLine(col * size_cellh_, (row + 1) * size_cellv_,
                        (col + 1) * size_cellh_, (row + 1) * size_cellv_,
                        penBlack);
    }
  }
  scene_->addRect(0, 0, cols_ * size_cellh_, rows_ * size_cellv_, penBlack);
}

void Maze::Save(const QString &path) {
  downloader_.SetSizes(rows_, cols_);
  downloader_.SetMatrices(vertical_walls_, horizontal_walls_);
  downloader_.DownloadMazeInFile(path.toUtf8().constData());
}

void Maze::DrawWay() {
  auto [start_x, start_y] = path_.front();
  path_.pop_front();
  auto [next_x, next_y] = path_.front();
  path_.pop_front();
  size_cellv_ = 500.0 / rows_;
  size_cellh_ = 500.0 / cols_;
  QPen pen(Qt::red, 2);
  QGraphicsLineItem *line;
  while (true) {
    if (start_x - next_x == -1 || start_x - next_x == 1) {
      line = scene_->addLine(start_x * size_cellh_ + (size_cellh_ / 2),
                             start_y * size_cellv_ + (size_cellv_ / 2),
                             next_x * size_cellh_ + (size_cellh_ / 2),
                             next_y * size_cellv_ + (size_cellv_ / 2), pen);
    } else {
      line = scene_->addLine(start_x * size_cellh_ + (size_cellh_ / 2),
                             start_y * size_cellv_ + (size_cellv_ / 2),
                             next_x * size_cellh_ + (size_cellh_ / 2),
                             next_y * size_cellv_ + (size_cellv_ / 2), pen);
    }
    path_dots_.append(line);
    if (path_.empty()) {
      dots_[1]->setBrush(Qt::yellow);
      break;
    }
    auto [x, y] = path_.front();
    path_.pop_front();
    start_x = next_x;
    start_y = next_y;
    next_x = x;
    next_y = y;
  }
}

void Maze::mousePressEvent(QMouseEvent *event) {
  if (dots_.size() == 2) {
    coords_.clear();
    ClearVec(dots_);
    ClearVec(path_dots_);
  }
  int x = event->pos().x() / size_cellh_;
  int y = event->pos().y() / size_cellv_;
  if (y < rows_ && x < cols_) {
    float ellipse_width = 0.5 * size_cellh_;
    float ellipse_height = 0.5 * size_cellv_;
    float x_offset = (size_cellh_ - ellipse_width) / 2;
    float y_offset = (size_cellv_ - ellipse_height) / 2;
    QPen pen(Qt::blue, 2);
    QGraphicsEllipseItem *dot = scene_->addEllipse(
        x * size_cellh_ + x_offset, y * size_cellv_ + y_offset, ellipse_width,
        ellipse_height, pen);
    dot->setBrush(Qt::blue);
    dots_.append(dot);
    coords_.push_back({x, y});
    if (dots_.size() == 2 && (coords_[0].first != coords_[1].first ||
                              coords_[0].second != coords_[1].second)) {
      try {
        explorer_.FindPath(rows_, cols_, vertical_walls_, horizontal_walls_,
                           coords_[0], coords_[1]);
        path_ = explorer_.GetPath();
        DrawWay();
      } catch (const std::exception &e) {
        coords_.clear();
        ClearVec(dots_);
        ClearVec(path_dots_);
        QMessageBox::critical(nullptr, "Ошибка", e.what());
      }
    }
  }
}