#include "eller_algo.h"

Eller::Eller(const int r, const int c) { ResizeVectors(r, c); }

void Eller::SetSize(const int r, const int c) { ResizeVectors(r, c); }

int Eller::GetRows() { return rows_; }

int Eller::GetCols() { return cols_; }

std::vector<std::vector<int>> Eller::GetWalls() {
  std::vector<std::vector<int>> vec(rows_, std::vector<int>(cols_, 0));
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      vec[i][j] = walls_[i * cols_ + j];
    }
  }
  return vec;
}

std::vector<std::vector<int>> Eller::GetBottoms() {
  std::vector<std::vector<int>> vec(rows_, std::vector<int>(cols_, 0));
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      vec[i][j] = bottoms_[i * cols_ + j];
    }
  }
  return vec;
}

bool Eller::RandomValue() {
  std::random_device rd;
  std::default_random_engine engine(rd());
  std::uniform_int_distribution<int> dist(0, 1);
  return static_cast<bool>(dist(engine));
}

void Eller::FillEmptyValue() {
  for (int i = 0; i < cols_; ++i) {
    sideLine_[i] = DEAD;
  }
}

void Eller::AssingUniqueSets() {
  for (int i = 0; i < cols_; ++i) {
    if (sideLine_[i] == DEAD) sideLine_[i] = counter_++;
  }
}

void Eller::MergeSet(int indx, int elem) {
  int mutableSet = sideLine_[indx + 1];
  for (int i = 0; i < cols_; ++i) {
    if (sideLine_[i] == mutableSet) {
      sideLine_[i] = elem;
    }
  }
}

void Eller::DoWalls(int r) {
  int i = r, j = 0;
  for (; i < (r + cols_ - 1); ++i) {
    bool randVal = RandomValue();
    if (randVal || sideLine_[j] == sideLine_[j + 1]) {
      walls_[i] = LIVE;
    } else {
      MergeSet(i - r, sideLine_[j]);
    }
    ++j;
  }
  walls_[i] = LIVE;
}

int Eller::CalculateUniqueSet(int elem) {
  int countUnique = 0;
  for (int i = 0; i < cols_; ++i) {
    if (sideLine_[i] == elem) {
      ++countUnique;
    }
  }
  return countUnique;
}

void Eller::DoBottoms(int r) {
  int i = r, j = 0;
  for (; i < (r + cols_); ++i) {
    bool rand = RandomValue();
    if (rand && CalculateUniqueSet(sideLine_[j]) != LIVE) {
      bottoms_[i] = LIVE;
    }
    ++j;
  }
}

int Eller::CalculateBottoms(int elem, int r) {
  int countBottoms = 0;
  for (int i = 0; i < cols_; ++i) {
    if (sideLine_[i] == elem && bottoms_[r + i] == DEAD) {
      ++countBottoms;
    }
  }
  return countBottoms;
}

void Eller::CheckBottoms(int r) {
  for (int i = 0; i < cols_; ++i) {
    if (CalculateBottoms(sideLine_[i], r) == 0) {
      bottoms_[r + i] = DEAD;
    }
  }
}

void Eller::PrepareNewLine(int r) {
  for (int i = 0; i < cols_; ++i) {
    if (bottoms_[r + i] == LIVE) {
      sideLine_[i] = DEAD;
    }
  }
}

void Eller::CheckEndLine(int endLine) {
  for (int i = 0; i < cols_ - 1; ++i) {
    if (sideLine_[i] != sideLine_[i + 1]) {
      walls_[endLine + i] = DEAD;
      MergeSet(i, sideLine_[i]);
    }
    bottoms_[endLine + i] = LIVE;
  }
  bottoms_[endLine + cols_ - 1] = LIVE;
}

void Eller::AddEndLine(int endLine) {
  AssingUniqueSets();
  DoWalls(endLine);
  CheckEndLine(endLine);
}

void Eller::ResizeVectors(const int r, const int c) {
  if (r > 50 || r < 1 || c > 50 || c < 1) {
    throw std::invalid_argument("ERROR: Неверный размер матриц!");
  }
  rows_ = r;
  cols_ = c;
  walls_.resize(rows_ * cols_);
  bottoms_.resize(rows_ * cols_);
  sideLine_.resize(cols_);
}

void Eller::Generator(const int rows, const int cols) {
  ResizeVectors(rows, cols);
  int limit = rows_ * cols_ - cols_;
  walls_.clear();
  bottoms_.clear();
  FillEmptyValue();
  for (int i = 0; i < limit; i += cols_) {
    AssingUniqueSets();
    DoWalls(i);
    DoBottoms(i);
    CheckBottoms(i);
    PrepareNewLine(i);
  }
  AddEndLine(limit);
  sideLine_.clear();
  counter_ = 1;
}
