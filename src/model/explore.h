#ifndef A1_MAZE_1_MODEL_LEE_ALGORITHM_H
#define A1_MAZE_1_MODEL_LEE_ALGORITHM_H

#include <iostream>
#include <list>
#include <utility>
#include <vector>

class Explore {
 public:
  using Matrix = std::vector<std::vector<int>>;
  using Coord = std::pair<int, int>;
  using Path = std::list<Coord>;

  struct Point {
    Point() = default;
    Point(Coord p) : x_(p.first), y_(p.second){};

    bool operator==(Point other) {
      return other.x_ == this->x_ && other.y_ == this->y_;
    }

    bool operator!=(Point other) { return !(other == *this); }

    int x_;
    int y_;
  };

  struct District {
    District(int x, int y) {
      this->top_ = Point(std::pair<int, int>({x, y - 1}));
      this->bottom_ = Point(std::pair<int, int>({x, y + 1}));
      this->left_ = Point(std::pair<int, int>({x - 1, y}));
      this->right_ = Point(std::pair<int, int>({x + 1, y}));
    };
    District(Point p) {
      top_ = Point({p.x_, p.y_ - 1});
      bottom_ = Point({p.x_, p.y_ + 1});
      left_ = Point({p.x_ - 1, p.y_});
      right_ = Point({p.x_ + 1, p.y_});
    };
    Point top_;
    Point bottom_;
    Point right_;
    Point left_;
  };

  Explore() = default;

  void FindPath(int rows, int cols, Matrix vertical_walls,
                Matrix horizontal_walls, Coord start, Coord end);

  std::pair<Point, bool> WayBack(Point p);

  void МarkNeighbors(Point p);

  bool IsInMaze(Point p);

  int GetWaveValue(Point p) { return waves_[p.y_][p.x_]; }

  bool IsUnmarked(Point p) { return waves_[p.y_][p.x_] == 0; }

  std::list<Point> GetNeighbors(Point p);

  void MarkWavePoint(Point p, int value) { waves_[p.y_][p.x_] = value; }

  bool IsPointWithBottomWall(Point p) {
    return horizontal_walls_[p.y_][p.x_] == 1;
  }

  int IsPointWithRightWall(Point p) { return vertical_walls_[p.y_][p.x_] == 1; }

  const Path GetPath() const { return path_; }

 private:
  int rows_;
  int cols_;
  Matrix vertical_walls_;
  Matrix horizontal_walls_;
  Point start_;
  Point end_;
  Matrix waves_;
  Path path_;
};

#endif  // A1_MAZE_1_MODEL_LEE_ALGORITHM_H