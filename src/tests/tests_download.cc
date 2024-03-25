#include <gtest/gtest.h>

#include "../model/download.h"
#include "../model/eller_algo.h"

TEST(TestDownload, SetSizesGetRowsGetCols) {
  Download duplo;
  int originalRows = 3;
  int originalCols = 5;
  duplo.SetSizes(3, 5);

  EXPECT_EQ(originalRows, duplo.GetRows());
  EXPECT_EQ(originalCols, duplo.GetCols());
}

TEST(TestDownload, SetMatricesGetWallsMGetBottomsM) {
  Download pollo;
  Download::Matrix originalM1(2, std::vector<int>(2));
  Download::Matrix originalM2(2, std::vector<int>(2));
  originalM1[0][0] = 1;
  originalM1[0][1] = 1;
  originalM1[1][0] = 0;
  originalM1[1][1] = 0;

  originalM2[0][0] = 0;
  originalM2[0][1] = 0;
  originalM2[1][0] = 1;
  originalM2[1][1] = 1;
  pollo.SetMatrices(originalM1, originalM2);

  Download::Matrix walls = pollo.GetWallsMatrix();
  Download::Matrix bottoms = pollo.GetBottomsMatrix();

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      EXPECT_EQ(originalM1[i][j], walls[i][j]);
      EXPECT_EQ(originalM2[i][j], bottoms[i][j]);
    }
  }
}

TEST(TestDownload, UploadMazeFromFile) {
  Download duplo;
  duplo.UploadMazeFromFile("./tests/for_testing/for_test_upload_maze.txt");
  Download::Matrix walls = duplo.GetWallsMatrix();
  Download::Matrix bottoms = duplo.GetBottomsMatrix();

  EXPECT_EQ(3, duplo.GetRows());
  EXPECT_EQ(3, duplo.GetCols());

  EXPECT_EQ(walls[0][0], 0);
  EXPECT_EQ(walls[0][1], 0);
  EXPECT_EQ(walls[0][2], 1);
  EXPECT_EQ(walls[1][0], 1);
  EXPECT_EQ(walls[1][1], 1);
  EXPECT_EQ(walls[1][2], 1);
  EXPECT_EQ(walls[2][0], 1);
  EXPECT_EQ(walls[2][1], 0);
  EXPECT_EQ(walls[2][2], 1);

  EXPECT_EQ(bottoms[0][0], 0);
  EXPECT_EQ(bottoms[0][1], 0);
  EXPECT_EQ(bottoms[0][2], 1);
  EXPECT_EQ(bottoms[1][0], 0);
  EXPECT_EQ(bottoms[1][1], 0);
  EXPECT_EQ(bottoms[1][2], 0);
  EXPECT_EQ(bottoms[2][0], 1);
  EXPECT_EQ(bottoms[2][1], 1);
  EXPECT_EQ(bottoms[2][2], 1);
}

TEST(TestDownload, DownloadMazeToFile) {
  Download duplo;
  Eller el;
  el.Generator(3, 3);
  duplo.SetSizes(3, 3);
  duplo.SetMatrices(el.GetWalls(), el.GetBottoms());

  duplo.DownloadMazeInFile("./tests/for_testing/for_test_download_maze.txt");
  const std::vector<std::vector<int>> &walls = el.GetWalls();

  Eller dl;
  duplo.UploadMazeFromFile("./tests/for_testing/for_test_download_maze.txt");
  const std::vector<std::vector<int>> &walls2 = duplo.GetWallsMatrix();

  EXPECT_EQ(walls[0][0], walls2[0][0]);
  EXPECT_EQ(walls[0][1], walls2[0][1]);
  EXPECT_EQ(walls[0][2], walls2[0][2]);

  EXPECT_EQ(walls[1][0], walls2[1][0]);
  EXPECT_EQ(walls[1][1], walls2[1][1]);
  EXPECT_EQ(walls[1][2], walls2[1][2]);

  EXPECT_EQ(walls[2][0], walls2[2][0]);
  EXPECT_EQ(walls[2][1], walls2[2][1]);
  EXPECT_EQ(walls[2][2], walls2[2][2]);
}