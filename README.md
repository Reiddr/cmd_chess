# cmd_chess
A repo to create a command line chess game

To build run:

- `cmake -B build`

- `cmake --build build`

### TODO
- split term_draw into its own library with an installable CMakeLists

- add all the basic bitboard functions: flip, rotate, ect

- add a header for the piece moves

- shift the header code into source files

- create functions for printing a single bitboard with pieces

- add a simple gameplay loop
    - ask for a move
    - move the piece from/to the corresponding square

- create a bitboard piece header and source for checking moves

- write in game logic to restrict moves

- update the gameplay loop to allow a full game to be played between two humans

- start making a chess engine to evaluate positions 

- allow play against a computer

- split the game into a server/client architecture over tcp
    - this way a central server can run the evaluation and have multiple games going at once
    - allow clients to create games, then query games and make moves, all the chess logic can be implemented by the server

