#ifndef ELLER_ALGO_H
#define ELLER_ALGO_H

#include <iostream>
#include <random>
#include <vector>

class Eller {
 public:
  enum Set {
    DEAD,
    LIVE,
  };

  Eller() = default;
  Eller(const int r, const int c);
  ~Eller() = default;

  void SetSize(const int r, const int c);
  int GetRows();
  int GetCols();
  std::vector<std::vector<int>> GetWalls();
  std::vector<std::vector<int>> GetBottoms();

  void Generator(const int rows, const int cols);

 private:
  bool RandomValue();
  void FillEmptyValue();
  void AssingUniqueSets();
  void MergeSet(int indx, int elem);
  void DoWalls(int r);
  int CalculateUniqueSet(int elem);
  void DoBottoms(int r);
  int CalculateBottoms(int elem, int r);
  void CheckBottoms(int r);
  void PrepareNewLine(int r);
  void CheckEndLine(int endLine);
  void AddEndLine(int endLine);
  void ResizeVectors(const int r, const int c);

  int rows_ = 0, cols_ = 0;
  std::vector<int> walls_, bottoms_, sideLine_;
  unsigned counter_ = 1;
};

#endif  // ELLER_ALGO_H
