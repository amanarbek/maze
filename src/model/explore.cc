#include "explore.h"

void Explore::FindPath(int rows, int cols, Matrix vertical_walls,
                       Matrix horizontal_walls, Coord start, Coord end) {
  rows_ = rows;
  cols_ = cols;
  vertical_walls_ = vertical_walls;
  horizontal_walls_ = horizontal_walls;
  waves_ = Matrix(rows, std::vector<int>(cols, 0));
  MarkWavePoint(Point(start), 1);  // Начальная точка
  int value = 1;
  bool exit_flag = false;
  while (!exit_flag) {
    if (value > rows * cols) throw std::range_error("Error: Нет пути!\n");
    exit_flag = true;
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        Point p({j, i});
        if (IsUnmarked(p)) exit_flag = false;
        if (!IsUnmarked(p) && (GetWaveValue(p) == value)) МarkNeighbors(p);
      }
    }
    if (waves_[end.second][end.first] > 0) break;
    ++value;
  }
  path_.clear();
  Point current = end;
  exit_flag = true;
  do {
    auto step_back = WayBack(current);
    current = step_back.first;
    exit_flag = step_back.second;
  } while (exit_flag);
}

std::pair<Explore::Point, bool> Explore::WayBack(Point p) {
  path_.push_front({p.x_, p.y_});
  for (auto i : GetNeighbors(p)) {
    if (GetWaveValue(p) == GetWaveValue(i) + 1) {
      return {i, true};
    }
  }
  return {p, false};
};

void Explore::МarkNeighbors(Point p) {
  int value = GetWaveValue(p) + 1;
  for (auto i : GetNeighbors(p)) {
    if (IsUnmarked(i)) {
      MarkWavePoint(i, value);
    }
  }
};

bool Explore::IsInMaze(Point p) {
  return (((p.x_ - 0) | (cols_ - p.x_ - 1)) >= 0) &&
         (((p.y_ - 0) | (rows_ - p.y_ - 1)) >= 0);
}

std::list<Explore::Point> Explore::GetNeighbors(Point p) {
  std::list<Point> neighbors;
  District d(p);

  if (IsInMaze(d.top_) && !IsPointWithBottomWall(d.top_)) {
    neighbors.push_back(d.top_);
  }

  if (IsInMaze(d.bottom_) && !IsPointWithBottomWall(p)) {
    neighbors.push_back(d.bottom_);
  }

  if (IsInMaze(d.left_) && !IsPointWithRightWall(d.left_)) {
    neighbors.push_back(d.left_);
  }

  if (IsInMaze(d.right_) && !IsPointWithRightWall(p)) {
    neighbors.push_back(d.right_);
  }

  return neighbors;
}
