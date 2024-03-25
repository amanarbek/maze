#include "download.h"

Download::Download(int r, int c) {
  rows_ = r;
  cols_ = c;
  ResizeMatrices();
}

void Download::SetSizes(int r, int c) {
  if (r > 50 || r < 1 || c > 50 || c < 1) {
    throw std::invalid_argument("EROOR: Неправильные размеры матриц!\n");
  }
  rows_ = r;
  cols_ = c;
  ResizeMatrices();
}

void Download::SetMatrices(Matrix w, Matrix b) {
  walls_ = w;
  bottoms_ = b;
}

void Download::SetWalls(std::fstream &file) {
  char c;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      file.get(c);
      if (c == ' ' || c == '\n') {
        --j;
        continue;
      } else {
        if (c == '1') {
          walls_[i][j] = LIVE;
        } else if (c == '0') {
          walls_[i][j] = DEAD;
        } else {
          throw std::invalid_argument(
              "ERROR: Поврежденный или неправильный файл!\n");
        }
      }
    }
  }
}

void Download::SetBottoms(std::fstream &file) {
  char c;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      file.get(c);
      if (c == ' ' || c == '\n') {
        --j;
        continue;
      } else {
        if (c == '1') {
          bottoms_[i][j] = LIVE;
        } else if (c == '0') {
          bottoms_[i][j] = DEAD;
        } else {
          throw std::invalid_argument(
              "Error: Поврежденный или неправильный файл!\n");
        }
      }
    }
  }
}

void Download::ResizeMatrices() {
  walls_.resize(rows_);
  bottoms_.resize(rows_);

  for (int i = 0; i < rows_; ++i) {
    walls_[i].resize(cols_);
    bottoms_[i].resize(cols_);
  }
}

void Download::DownloadMazeInFile(const std::string &path) {
  std::ofstream out;
  out.open(path);
  if (out.is_open()) {
    out << rows_ << " " << cols_ << std::endl;
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        out << walls_[i][j];
        if (j != (cols_ - 1)) out << " ";
      }
      out << std::endl;
    }
    out << std::endl;
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        out << bottoms_[i][j];
        if (j != (cols_ - 1)) out << " ";
      }
      if (i != (rows_ - 1)) out << std::endl;
    }
    out.close();
  } else {
    throw std::invalid_argument("ERROR: Ошибка открытия файла для записи.");
  }
}

void Download::UploadMazeFromFile(const std::string &path) {
  int r, c;
  std::string s;
  std::stringstream ss;
  std::fstream file;
  file.open(path);
  if (file.is_open()) {
    getline(file, s);
    ss << s;
    ss >> r;
    ss.ignore();
    ss >> c;
    SetSizes(r, c);
    SetWalls(file);
    getline(file, s);
    SetBottoms(file);
    file.close();
  } else {
    throw std::invalid_argument("ERROR: Ошибка чтения файла!");
  }
}
