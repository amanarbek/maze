#include <gtest/gtest.h>

#include "../model/download.h"
#include "../model/eller_algo.h"
#include "../model/explore.h"

TEST(ExploreTest, FindPath) {
  Explore explorer;
  int rows = 5;
  int cols = 5;
  Explore::Matrix vertical_walls(rows, std::vector<int>(cols - 1, 0));
  Explore::Matrix horizontal_walls(rows - 1, std::vector<int>(cols, 0));
  Explore::Coord start = {0, 0};
  Explore::Coord end = {rows - 1, cols - 1};
  explorer.FindPath(rows, cols, vertical_walls, horizontal_walls, start, end);

  EXPECT_EQ(explorer.GetPath().size(), 9);

  EXPECT_EQ(explorer.GetPath().front(), start);

  EXPECT_EQ(explorer.GetPath().back(), end);
}

TEST(ExploreTest, WayBack) {
  Download duplo;
  duplo.UploadMazeFromFile("./presets/preset0.txt");
  Explore explorer;
  int rows = duplo.GetRows();
  int cols = duplo.GetCols();
  Explore::Matrix vertical_walls = duplo.GetWallsMatrix();
  Explore::Matrix horizontal_walls = duplo.GetBottomsMatrix();
  Explore::Coord start = {0, 0};
  Explore::Coord end = {3, 1};
  explorer.FindPath(rows, cols, vertical_walls, horizontal_walls, start, end);

  Explore::Point point1(Explore::Coord(2, 1));
  auto result1 = explorer.WayBack(point1);
  EXPECT_TRUE(result1.second);
}

TEST(ExploreTest, МarkNeighbors) {
  Download duplo;
  duplo.UploadMazeFromFile("./presets/preset0.txt");
  Explore explorer;
  int rows = duplo.GetRows();
  int cols = duplo.GetCols();
  Explore::Matrix vertical_walls = duplo.GetWallsMatrix();
  Explore::Matrix horizontal_walls = duplo.GetBottomsMatrix();
  Explore::Coord start = {0, 0};
  Explore::Coord end = {0, 3};
  explorer.FindPath(rows, cols, vertical_walls, horizontal_walls, start, end);

  Explore::Path path = explorer.GetPath();

  Explore::Coord second = {0, 1};
  Explore::Coord third = {0, 2};

  for (auto it = path.rbegin(); it != path.rend(); ++it) {
    if (it->first == second.first && it->first == second.second) {
      EXPECT_EQ(*it, second);
    }
    if (it->first == third.first && it->first == third.second) {
      EXPECT_EQ(*it, third);
    }
  }
}

TEST(ExploreTest, IsInMaze) {
  Explore explorer;
  int rows = 5;
  int cols = 5;
  Explore::Matrix vertical_walls(rows, std::vector<int>(cols - 1, 0));
  Explore::Matrix horizontal_walls(rows - 1, std::vector<int>(cols, 0));
  Explore::Coord start = {0, 0};
  Explore::Coord end = {rows - 1, cols - 1};
  explorer.FindPath(rows, cols, vertical_walls, horizontal_walls, start, end);

  EXPECT_TRUE(explorer.IsInMaze(Explore::Point({{2, 3}})));
  EXPECT_TRUE(explorer.IsInMaze(Explore::Point({{0, 0}})));
  EXPECT_TRUE(explorer.IsInMaze(Explore::Point({{4, 4}})));

  EXPECT_FALSE(explorer.IsInMaze(Explore::Point({{-1, 2}})));
  EXPECT_FALSE(explorer.IsInMaze(Explore::Point({{2, -1}})));
  EXPECT_FALSE(explorer.IsInMaze(Explore::Point({{5, 2}})));
  EXPECT_FALSE(explorer.IsInMaze(Explore::Point({{2, 5}})));
}

TEST(ExploreTest, GetWaveValue) {
  Explore explorer;
  int rows = 5;
  int cols = 5;
  Explore::Matrix vertical_walls(rows, std::vector<int>(cols - 1, 0));
  Explore::Matrix horizontal_walls(rows - 1, std::vector<int>(cols, 0));
  Explore::Coord start = {0, 0};
  Explore::Coord end = {rows - 1, cols - 1};
  explorer.FindPath(rows, cols, vertical_walls, horizontal_walls, start, end);

  explorer.MarkWavePoint(Explore::Point({{1, 1}}), 1);
  explorer.MarkWavePoint(Explore::Point({{2, 2}}), 2);
  explorer.MarkWavePoint(Explore::Point({{3, 3}}), 3);

  EXPECT_EQ(explorer.GetWaveValue(Explore::Point({{1, 1}})), 1);
  EXPECT_EQ(explorer.GetWaveValue(Explore::Point({{2, 2}})), 2);
  EXPECT_EQ(explorer.GetWaveValue(Explore::Point({{3, 3}})), 3);

  EXPECT_EQ(explorer.GetWaveValue(Explore::Point({{0, 0}})), 1);
  EXPECT_EQ(explorer.GetWaveValue(Explore::Point({{4, 4}})), 9);
  EXPECT_EQ(explorer.GetWaveValue(Explore::Point({{0, 4}})), 5);
}

TEST(ExploreTest, IsUnmarked) {
  Explore explorer;
  int rows = 5;
  int cols = 5;
  Explore::Matrix vertical_walls(rows, std::vector<int>(cols - 1, 0));
  Explore::Matrix horizontal_walls(rows - 1, std::vector<int>(cols, 0));
  Explore::Coord start = {0, 0};
  Explore::Coord end = {rows - 1, cols - 1};
  explorer.FindPath(rows, cols, vertical_walls, horizontal_walls, start, end);

  explorer.MarkWavePoint(Explore::Point({{1, 1}}), 1);
  explorer.MarkWavePoint(Explore::Point({{2, 2}}), 2);
  explorer.MarkWavePoint(Explore::Point({{3, 3}}), 3);

  EXPECT_FALSE(explorer.IsUnmarked(Explore::Point({{1, 1}})));
  EXPECT_FALSE(explorer.IsUnmarked(Explore::Point({{2, 2}})));
  EXPECT_FALSE(explorer.IsUnmarked(Explore::Point({{3, 3}})));
}

TEST(ExploreTest, GetNeighbors) {
  Explore explorer;
  int rows = 5;
  int cols = 5;
  Explore::Matrix vertical_walls(rows, std::vector<int>(cols - 1, 0));
  Explore::Matrix horizontal_walls(rows - 1, std::vector<int>(cols, 0));
  Explore::Coord start = {0, 0};
  Explore::Coord end = {rows - 1, cols - 1};
  explorer.FindPath(rows, cols, vertical_walls, horizontal_walls, start, end);

  Explore::Point interiorPoint = {{2, 2}};
  std::list<Explore::Point> interiorNeighbors =
      explorer.GetNeighbors(interiorPoint);
  EXPECT_EQ(interiorNeighbors.size(), 4);

  Explore::Point boundaryPoint = {{0, 0}};
  std::list<Explore::Point> boundaryNeighbors =
      explorer.GetNeighbors(boundaryPoint);
  EXPECT_EQ(boundaryNeighbors.size(), 2);

  Explore::Point cornerPoint = {{4, 4}};
  std::list<Explore::Point> cornerNeighbors =
      explorer.GetNeighbors(cornerPoint);
  EXPECT_EQ(cornerNeighbors.size(), 2);
}

TEST(ExploreTest, MarkWavePoint) {
  Explore explorer;
  int rows = 5;
  int cols = 5;
  Explore::Matrix vertical_walls(rows, std::vector<int>(cols - 1, 0));
  Explore::Matrix horizontal_walls(rows - 1, std::vector<int>(cols, 0));
  Explore::Coord start = {0, 0};
  Explore::Coord end = {rows - 1, cols - 1};
  explorer.FindPath(rows, cols, vertical_walls, horizontal_walls, start, end);

  Explore::Point interiorPoint = {{2, 2}};
  int waveValue = 3;
  explorer.MarkWavePoint(interiorPoint, waveValue);
  EXPECT_EQ(explorer.GetWaveValue(interiorPoint), waveValue);

  Explore::Point boundaryPoint = {{0, 0}};
  waveValue = 1;
  explorer.MarkWavePoint(boundaryPoint, waveValue);
  EXPECT_EQ(explorer.GetWaveValue(boundaryPoint), waveValue);

  Explore::Point cornerPoint = {{4, 4}};
  waveValue = 2;
  explorer.MarkWavePoint(cornerPoint, waveValue);
  EXPECT_EQ(explorer.GetWaveValue(cornerPoint), waveValue);
}

TEST(ExploreTest, IsPointWithBottomWall) {
  Explore explorer;
  int rows = 3;
  int cols = 3;
  Explore::Matrix vertical_walls(rows, std::vector<int>(cols - 1, 0));
  Explore::Matrix horizontal_walls(rows - 1, std::vector<int>(cols, 0));
  Explore::Coord start = {0, 0};
  Explore::Coord end = {rows - 1, cols - 1};
  explorer.FindPath(rows, cols, vertical_walls, horizontal_walls, start, end);

  Explore::Point pointWithBottomWall = {{3, 0}};
  EXPECT_FALSE(explorer.IsPointWithBottomWall(pointWithBottomWall));

  Explore::Point pointWithoutBottomWall = {{0, 1}};
  EXPECT_FALSE(explorer.IsPointWithBottomWall(pointWithoutBottomWall));
}

TEST(ExploreTest, IsPointWithRightWall) {
  Download duplo;
  duplo.UploadMazeFromFile("./presets/preset0.txt");
  Explore explorer;
  int rows = duplo.GetRows();
  int cols = duplo.GetCols();
  Explore::Matrix vertical_walls = duplo.GetWallsMatrix();
  Explore::Matrix horizontal_walls = duplo.GetBottomsMatrix();
  Explore::Coord start = {0, 0};
  Explore::Coord end = {0, 3};
  explorer.FindPath(rows, cols, vertical_walls, horizontal_walls, start, end);

  Explore::Point pointWithRightWall = {{0, 1}};
  vertical_walls[pointWithRightWall.y_][pointWithRightWall.x_] = 1;

  EXPECT_TRUE(explorer.IsPointWithRightWall(pointWithRightWall));

  Explore::Point pointWithoutRightWall = {{1, 1}};
  EXPECT_FALSE(explorer.IsPointWithRightWall(pointWithoutRightWall));
}

TEST(ExploreTest, GetPath) {
  Explore explorer;
  int rows = 5;
  int cols = 5;
  Explore::Matrix vertical_walls(rows, std::vector<int>(cols - 1, 0));
  Explore::Matrix horizontal_walls(rows - 1, std::vector<int>(cols, 0));
  Explore::Coord start = {0, 0};
  Explore::Coord end = {rows - 1, cols - 1};

  explorer.FindPath(rows, cols, vertical_walls, horizontal_walls, start, end);

  const Explore::Path &pathReference = explorer.GetPath();

  EXPECT_EQ(pathReference.size(), 9);
}
