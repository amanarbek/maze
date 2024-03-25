#ifndef A1_MAZE_VIEW_MAZE_H
#define A1_MAZE_VIEW_MAZE_H

#include <QFile>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMessageBox>
#include <QMouseEvent>
#include <QTextStream>
#include <cmath>
#include <vector>

#include "../model/download.h"
#include "../model/eller_algo.h"
#include "../model/explore.h"

class Maze : public QGraphicsView {
 public:
  using Matrix = std::vector<std::vector<int>>;
  using Coord = std::pair<int, int>;
  using Coords = std::vector<Coord>;
  using Path = std::list<Coord>;

  Maze(QWidget *parent = nullptr);
  ~Maze();

  void LoadMaze(const QString &path);
  void SetWalls(int rows, int cols);
  void DrawMaze();
  void Save(const QString &path);

 private:
  void ClearVec(QVector<QGraphicsEllipseItem *> &vec);
  void ClearVec(QVector<QGraphicsLineItem *> &vec);
  void ClearScene();
  void DrawWay();
  void mousePressEvent(QMouseEvent *event) override;
  QGraphicsScene *scene_;
  int rows_;
  int cols_;
  float size_cellv_;
  float size_cellh_;
  Matrix vertical_walls_;
  Matrix horizontal_walls_;
  QVector<QGraphicsEllipseItem *> dots_;
  QVector<QGraphicsLineItem *> path_dots_;
  Coords coords_;
  Download downloader_;
  Explore explorer_;
  Eller eller_;
  Path path_;
};

#endif  // A1_MAZE_VIEW_MAZE_H