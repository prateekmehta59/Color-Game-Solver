// Copyright Aeva 2018
#pragma once

#include <string> 

namespace game {

enum class Color { none, red, black };

class Board {
 public:
  static constexpr int width_ = 7;
  static constexpr int height_ = 6;

  Color board_[width_][height_];

  Board();
  ~Board();

  void Init();
  void PrintBoard();
  int IsValidMove(int column) const;
  bool IsValidBoard() const;
  bool MakeMove(int column, Color color);
  void LoadBoard(std::string board);
  bool IsGameOver();
  bool patternSearch(int row, int col, Color color);
  //bool Getmaxheight();

  Color HasWinner();

};

}  // namespace game
