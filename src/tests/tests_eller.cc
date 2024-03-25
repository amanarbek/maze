#include <gtest/gtest.h>

#include "../model/download.h"
#include "../model/eller_algo.h"

TEST(TestEller, GetWalls) {
  Eller eller;
  eller.Generator(2, 3);
  const std::vector<std::vector<int>> &walls = eller.GetWalls();

  EXPECT_EQ(walls.size(), 2);
  EXPECT_EQ(walls[0].size(), 3);
  EXPECT_EQ(walls[1].size(), 3);
}

TEST(TestEller, GetBottoms) {
  Eller eller;
  eller.Generator(2, 3);
  const std::vector<std::vector<int>> &bottoms = eller.GetBottoms();

  EXPECT_EQ(bottoms.size(), 2);
  EXPECT_EQ(bottoms[0].size(), 3);
  EXPECT_EQ(bottoms[1].size(), 3);
}

TEST(TestEller, Generator) {
  Eller eller;
  eller.Generator(10, 10);

  Download duplo1(10, 10);
  duplo1.SetMatrices(eller.GetWalls(), eller.GetBottoms());
  duplo1.DownloadMazeInFile("./tests/for_testing/for_test_download_maze.txt");
  Download::Matrix bottoms = eller.GetBottoms();

  Download duplo2;
  duplo2.UploadMazeFromFile("./tests/for_testing/for_test_download_maze.txt");
  Download::Matrix bottoms2 = duplo2.GetBottomsMatrix();

  EXPECT_EQ(bottoms[0][0], bottoms2[0][0]);
  EXPECT_EQ(bottoms[0][1], bottoms2[0][1]);
  EXPECT_EQ(bottoms[0][2], bottoms2[0][2]);

  EXPECT_EQ(bottoms[1][0], bottoms2[1][0]);
  EXPECT_EQ(bottoms[1][1], bottoms2[1][1]);
  EXPECT_EQ(bottoms[1][2], bottoms2[1][2]);

  EXPECT_EQ(bottoms[2][0], bottoms2[2][0]);
  EXPECT_EQ(bottoms[2][1], bottoms2[2][1]);
  EXPECT_EQ(bottoms[2][2], bottoms2[2][2]);
}
