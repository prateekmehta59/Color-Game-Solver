// Copyright Aeva 2018

#include "board.hh"
#include "log.hh"

#include <sstream>
#include <string>
#include <iostream>
#include <list>

namespace game {

Board::Board() {}
Board::~Board() {}

void Board::Init() {
  for (int i = 0; i < width_; i++) {
    for (int j = 0; j < height_; j++) {
      board_[i][j] = Color::none;
    }
  }
}

namespace {

// little lambda to convert a Color enum to its string representation
auto ColorToString = [](Color color) {
  // Use the ANSI sequence to change red output to red
  if (color == Color::red) {
    return "\033[31mR\033[0;0m";
  }
  if (color == Color::black) {
    return "B";
  }
  if (color == Color::none) {
    return " ";
  }
  return "X";
};

auto CharToColor = [](const char& ch){
  if (ch == 'R') {
    return Color::red;
  }
  if (ch == 'B') {
    return Color::black;
  }
  return Color::none;
};

}

void Board::PrintBoard() {
  LOG << "| - - - - - - - - - - - - - |" << "\n";
  for (int i = height_ - 1; i >= 0; i--) {
    std::stringstream ss;
    ss << "| ";
    for (int j = 0; j < width_; j++) {
      ss << ColorToString(board_[j][i]) << " | ";
    }
    LOG << ss.str() << "\n";
  }
  LOG << "| - - - - - - - - - - - - - |" << "\n";
}

// Returns row that the piece will fall to, -1 otherwise
int Board::IsValidMove(int column) const {
  if (column < 0 && column > width_ - 1) return -1;
  for (int i = 0; i < height_; i++) {
    if (board_[column][i] == Color::none) {
      return i;
    }
  }
  return -1;
}

// todo(user): implement this!
// The conditions for a valid board
// 1) Red/Black either have the same number of pieces, or red has one more piece than black
//      Red can have one more piece, because red always goes first.
// 2) There are no floating pieces - you cannot have a piece with nothing under it
// 3) Only one, or no winners. Red and black cannot both have 4 in a row.
// 4) There are no "covered" wins - that the top piece in one of the columns must have completed the
//      4 in a row. See grader.cc for examples of covered and uncovered wins. 
// In general, the board must be in a state that can be achieved by starting with an empty board
// before placing one piece at a time into the board, without having a winner until the final piece
// is placed.
int max_height;
bool doubleColor;

int array_height[4];
int array_width[4];


bool Board::IsValidBoard() const {
	
	//  1
	int count_red = 0;
	int count_black = 0;
	for (int i = 0; i < width_; i++) {
	    for (int j = 0; j < height_; j++) {
	      if (board_[i][j] == Color::red){
			count_red++;
			}
	      else if (board_[i][j] == Color::black){
			count_black++;
			}
	    }
	}

	if ((count_red == count_black) || (count_red == count_black+1))
		LOG << "OK" << std::endl;
	else
		return false;

  	LOG << "Count_RED: " << count_red << std::endl;
	LOG << "Count_BLACK: " << count_black << std::endl;


	// 2

	for (int i = 0; i < width_; i++) {
	    for (int j = 0; j < height_; j++) {
	      if (board_[i][j] != Color::none){
	      	if (j>0){
				if(board_[i][j-1] == Color::none){
					LOG << "OOPS" << std::endl;
					return false;
				}
			}
		  }
	    }
	}

	// 3

	Board proxy(*this);
	Color color = proxy.HasWinner();

	if(doubleColor){
		LOG << "DOUBLE COLOR FOUND" << std::endl;
		return false;
	}


	// 4
	// int maxH = 0;
	// for (int i = 0; i < width_; i++) {
	//     for (int j = 0; j < height_; j++) {
	//     	if (board_[i][j] != Color::none){
	//     		if (maxH<=j+1){
	//     			maxH = j+1;
	//     		}
	//     	} 
	//     }
	// }
	// LOG << "-------------------- " << maxH  << std::endl;

	
	// Board proxy(*this);
	// Color color = proxy.HasWinner();
	std::list<int> mylist (array_width,array_width+4);
	if(color == Color::red || color == Color::black) {
		//LOG << "-------------------- " << max_height  << std::endl;
		// for (int y=0;y<4;y++)
	 //    	LOG << "YYYYYYY          " << array_height[y] << std::endl;
  //   	for (int y=0;y<4;y++)
  //   		LOG << "XXXXXXX          " << array_width[y] << std::endl;

    	//int array_maxH[4] = {0,0,0,0};
    	
    	int count = 0;
    	std::list<int>::iterator it;
		for (it = mylist.begin(); it != mylist.end(); ++it){
		    //LOG << "-------------------- " << *it  << std::endl;
		    int maxH = 0;
		    for (int j = 0; j < height_; j++) {
	     		if (board_[*it][j] != Color::none){
	     			if (maxH<=j+1){
	     				maxH = j+1;
	     			}
	     		}	     		
	     	}
	     	if (maxH == array_height[count]+1){
	     		return true;
	     	}
	     	//array_maxH[count] = maxH;
	     	count++;
		}
		return false;

 	}


  return true;
}


// Returns a boolean that indicates whether or not the move was completed
bool Board::MakeMove(int column, Color color) {
  ASSERT(column > -1 && column < width_, "Column out of bounds");

  int row = IsValidMove(column);
  if (row < 0) {
    return false;
  }

  board_[column][row] = color;
  return true;
}

void Board::LoadBoard(std::string board){
  ASSERT(board.length() == 42, "String length not 42, degenerate string lengths not accepted");
  int element = 41;
  for(int j = 0; j < height_; j++){
    for(int i = width_ - 1; i > -1; i--){
      board_[i][j] = CharToColor(board.at(element));
      element--;
    }
  }
}

bool Board::IsGameOver() {
  if (HasWinner() != Color::none) {
    return true;
  }

  int moves = 0;
  for (int i = 0; i < width_; i++) {
    for (int j = 0; j < height_; j++) {
      if (board_[i][j] != Color::none) {
        moves++;
      }
    }
  }
  if (moves == width_ * height_) {
    return true;
  }
  return false;
}

int x[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int y[] = { -1, 0, 1, -1, 1, -1, 0, 1 };


bool Board::patternSearch(int row, int col, Color color)
{
    // Consider every point as starting point and search
    // given word
	if (board_[row][col] != color)
      return false;
 
    int len = 4;
    int R = width_;
    int C = height_;
    
 
    // Search word in all 8 directions starting from (row,col)
    for (int dir = 0; dir < 8; dir++)
    {
        // Initialize starting point for current direction
        int k, rd = row + x[dir], cd = col + y[dir];
 		int h = 0;
 		int array_height1[4] = {0,0,0,0};
 		int array_width1[4] =  {0,0,0,0};

 		array_height1[0] = col;
        array_width1[0] = row;
        
 		int count = 1;
        // First character is already checked, match remaining
        // characters
        for (k = 1; k < len; k++)
        {
            // If out of bound break
            if (rd >= R || rd < 0 || cd >= C || cd < 0)
                break;
 
            // If not matched,  break
            if (board_[rd][cd] != color)
                break;
 
            //  Moving in particular direction
            array_height1[count] = cd;
            array_width1[count] = rd;

            rd += x[dir], cd += y[dir];
            
            count++;
            // if (cd>=h){
            // 	h = cd;
            // }
        }
 
        // If all character matched, then value of must
        // be equal to length of word
        if (k == len){

        	std::copy(array_height1, array_height1+4, array_height);
        	std::copy(array_width1, array_width1+4, array_width);
        	//max_height = h;
            return true;
        }
    }
    return false;

}

/*bool Board::Getmaxheight(){
	if(HasWinner() == Color::red){
		LOG << "------------------- " << max_height << std::endl;
	}
	return true;
}*/

// todo(user) implement this!
// If there are no winners or two winners, return Color::none
Color Board::HasWinner() { 

	bool isRed = false;
	bool isBlack = false;
	doubleColor = false;

	for (int row = 0; row < width_; row++){
       for (int col = 0; col < height_; col++){
          if (patternSearch(row, col, Color::red)){
             isRed = true;
             //LOG << "pattern red " << (sizeof(array_height)/sizeof(*array_height)) << std::endl;
			 //return Color::red; 
          }
          if (patternSearch(row, col, Color::black)){
             isBlack = true;
             //LOG << "pattern black " << (sizeof(array_height)/sizeof(*array_height)) << std::endl;
			 //return Color::black; 
          }
       }
	}
	if (isBlack && isRed){
		doubleColor = true;
		return Color::none; 
	}
	if (isRed){
		// LOG << "pattern red " << sizeof(array_height) << std::endl;
		// for (int y=0;y<4;y++)
  //   		LOG << "YYYYYYY          " << array_height[y] << std::endl;
		return Color::red; 
	}
	if(isBlack){
		// LOG << "pattern black " << sizeof(array_height) << std::endl;
		// for (int y=0;y<4;y++)
  //   		LOG << "YYYYYYY          " << array_height[y] << std::endl;
		return Color::black; 
	}
	return Color::none; 
	}

}  // namespace game

