// Copyright Aeva 2018

#include "board.hh"

#include <string>
#include <vector>

#include "acutest.h"
#include "log.hh"

using namespace game;

void basic_board_test(void) {
  LOG << "Basic Connect 4 test"
      << "\n";
  Board board;
  board.Init();

  for (int i = 0; i < 3; i++) {
    board.MakeMove(0, Color::black);
    board.MakeMove(6, Color::red);
  }

  for (int i = 0; i < 3; i++) {
    TEST_CHECK_(board.board_[0][i] == Color::black, "expected color incorrect");
    TEST_CHECK_(board.board_[6][i] == Color::red, "expected incorrect color");
  }

  board.PrintBoard();
}

void load_board(void) {
  LOG << "Load board test"
      << "\n";
  std::string vector =
    "XXXXXXX"
    "XXXXXXX"
    "XXXRXXX"
    "XXRBXXX"
    "XRBRXXX"
    "RBBBXXX";
  LOG << "Input vector: " << vector << "\n";
  Board board;
  board.Init();
  board.LoadBoard(vector);
  board.PrintBoard();

  // check the bottom row
  TEST_CHECK(board.board_[0][0] == Color::red);
  TEST_CHECK(board.board_[1][0] == Color::black);
  TEST_CHECK(board.board_[2][0] == Color::black);
  TEST_CHECK(board.board_[3][0] == Color::black);
  TEST_CHECK(board.board_[4][0] == Color::none);
  TEST_CHECK(board.board_[5][0] == Color::none);
  TEST_CHECK(board.board_[6][0] == Color::none);
}


struct TestInput {
  std::string name;
  bool valid;
  Color winner;
  std::string board;
};

static std::vector<TestInput> TestCases = {
  {
    "Empty board", true, Color::none,
    "XXXXXXX"
    "XXXXXXX"
    "XXXXXXX"
    "XXXXXXX"
    "XXXXXXX"
    "XXXXXXX"
  }, {
    "Horizontal Red", true, Color::red,
    "XXXXXXX"
    "XXXXXXX"
    "XXXXXXX"
    "XXXXXXX"
    "XBBBXXX"
    "XRRRRXX"
  }, {
    "Vertical Black", true, Color::black,
    "XXXXXXX"
    "XXXXXXX"
    "XBXXXXX"
    "XBRXXXX"
    "XBRXXXX"
    "XBRRXXX"
  }, {
// the hardest condition to test for is the covered/uncovered win, as talked about in board.cc
// an example of a uncovered win (this is valid):
    "Red win", true, Color::red,
    "XXXXXXX"
    "XXXXXXX"
    "XXXRXXX"
    "XXRBXXX"
    "XRBRXXX"
    "RBBBXXX"
  }, {
// an example of a covered win (this is not valid):
// Black has 4 in a row, but pieces were put in on top of it! This cannot be - the game should have
// ended the moment Black connected 4 in a row.
    "Covered Win", false, Color::black,
    "XXXXXXX"
    "XXXXXXX"
    "XXXRXXX"
    "XXRRXXX"
    "RRBRXXX"
    "BBBBXXX"
  }, {
// an example of a floating piece (this is not valid):
    "Floating Piece", false, Color::none,
    "XXXXXXX"
    "XXXRXXX"
    "XXXXXXX"
    "XXRRXXX"
    "RBBRXXX"
    "XBBBXXX"
  }, {
// an example of a double color win (this is not valid):
    "Double Color", false, Color::none,
    "XXXXXXX"
    "XXXRXXX"
    "XXXRXXX"
    "XXRRXXX"
    "RBBRXXX"
    "BBBBXXX"
  }, {
// an example of an extra red piece (this is not valid):
    "Red 2 more than black", false, Color::red,
    "XXXXXXX"
    "XXXRXXX"
    "XXXRXXX"
    "XXRRXXX"
    "RBBRXXX"
    "BRBBXXX"
  },  {
// an example of black pieces more than red pieces (this is not valid):
    "Black more than red", false, Color::none,
    "XXXXXXX"
    "XXXXXXX"
    "XXXXXXX"
    "BRBXXXX"
    "RRRBXXX"
    "RBBBXXX"
  }, {
// an example of black 1 more than red and black win (this is not valid):
    "invalid black win", false, Color::black,
    "XXXXXXX"
    "XXXXBXX"
    "XXXXBXX"
    "XXXBRXX"
    "XRBBBXX"
    "RBRRRXX"
  }, {
// an example stalemate (this is valid):
    "Floating Piece", true, Color::none,
    "BBRRBBR"
    "BRBBRRB"
    "RBRBRBR"
    "BRBBRBR"
    "RRBRBRB"
    "RBRBRBR"
  }, {
// another example of covered win (this is not valid):
    "Black more than red", false, Color::black,
    "XXXXXXX"
    "XXXRXXX"
    "XXXBXXX"
    "BRRBXXX"
    "RRRBXXX"
    "RBBBXXX"
  },{
// an example of 3 red wins (this is not valid):
    "3 red wins", false, Color::red,
    "XXXXXXX"
    "XRXXXXX"
    "RRXXXXX"
    "RRRXXBB"
    "RRRRBBB"
    "RBBBXBB"
  }, {
// an example of 5 black pieces in a row (this is valid):
    "5 Black pieces in a row", true, Color::black,
    "XXXXXXX"
    "XXXXXXX"
    "XXXXXXX"
    "RXXXXXX"
    "RRRXXXX"
    "RBBBBBX"
  },
};

// this function tests both HasWinner and IsValidBoard
void full_board_test(void) {
   LOG << "Load has winner"
       << "\n";
  for (const auto& test_case : TestCases) {
    LOG << "Test case: " << test_case.name << std::endl;
    Board board;
    board.Init();
    board.LoadBoard(test_case.board);
    board.PrintBoard();
    TEST_CHECK(test_case.valid == board.IsValidBoard());
    TEST_CHECK(test_case.winner == board.HasWinner());
  }
}


TEST_LIST = {{"basic", basic_board_test},
             {"load_board", load_board},
             {"full_board_test", full_board_test},
             {NULL, NULL}};
