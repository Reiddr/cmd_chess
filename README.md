# cmd_chess
A repo to create a command line chess game

To build run:

- `cmake -B build`

- `cmake --build build`

### TODO

- Add a FEN notation conversion from the boardstate struct to make printing easier

- Split term_draw into its own library with an installable CMakeLists

- Add all the basic bitboard functions: flip, rotate, ect

- Add a header for the piece moves

- Shift the header code into source files

- Create functions for printing a single bitboard with pieces

- Use Makefile instead of CMakeLists for building

- Add a simple test framework as the project grows

- Enable lsp integration with bear and clang

- set up clang format command in Makefile with formatting rules following the linux kernel

- Add a simple gameplay loop
    - ask for a move
    - move the piece from/to the corresponding square

- Create a bitboard piece header and source for checking moves

- Write in game logic to restrict moves

- Update the gameplay loop to allow a full game to be played between two humans

- Start making a chess engine to evaluate positions 

- Allow play against a computer

- Split the game into a server/client architecture over tcp
    - this way a central server can run the evaluation and have multiple games going at once
    - allow clients to create games, then query games and make moves, all the chess logic can be implemented by the server

- Created a small database to store the games (SQL lite?)
    - opponents named through hostname and or time so multiple games can be started with the same opponent

- Aternatively do not split into server client, but opt for serverless peer to peer architechture
    - games could be syncronised through a handshake
