#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <fstream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

class Download {
 public:
  enum Set {
    DEAD,
    LIVE,
  };

  using Matrix = std::vector<std::vector<int>>;
  using Coord = std::pair<int, int>;
  using Path = std::list<Coord>;

  Download() = default;
  Download(int r, int c);
  ~Download() = default;
  void SetSizes(int r, int c);
  int GetRows() { return rows_; }
  int GetCols() { return cols_; }
  void SetMatrices(Matrix w, Matrix b);
  Matrix GetWallsMatrix() const { return walls_; }
  Matrix GetBottomsMatrix() const { return bottoms_; }

  void DownloadMazeInFile(const std::string &path);
  void UploadMazeFromFile(const std::string &path);

 private:
  void SetWalls(std::fstream &file);
  void SetBottoms(std::fstream &file);
  void ResizeMatrices();

  int rows_;
  int cols_;
  Matrix walls_;
  Matrix bottoms_;
};

#endif  //  DOWNLOAD_H