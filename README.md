Connect 4 is a very common game played by kids. The game is simple enough; players take turns putting in red or black pieces until four pieces are connected in a in a row, column or diagonal. For more information, see: https://en.wikipedia.org/wiki/Connect_Four

Your tasks:

1) Preform a code review on the .hh and .cc files. What do you notice? What would you change?
2) Implement game/board.cc's HasWinner() function. 
3) Implement game/board.cc's IsValidBoard() function
4) Add test cases in test/basic.cc:full_board_test to verify the two above functions

Project specific comments:
We provide make files for this project. The project should build out of the box assuming make and gcc are installed. 

Assuming your toolchain is set up: 

To build everything, try: `make all`
To run the basic test cases, try `make test_basic`

Take a look at the comments, especially in board.cc and basic.cc - this will provide insight into what we define a "winner" and a "valid board" as. The HasWinner function is fairly straight forward; the IsValid function is tricky. 

test/basic.cc also contains some code that will help you develop and debug some of your functions.


---
Credit must be given to acutest, the unit testing framework used.
Source can be found here: https://github.com/mity/acutest
