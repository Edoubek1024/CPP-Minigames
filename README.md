# C++ Minigames
This repository contains several C++ files with minigames:

- [Connect 4](https://github.com/Edoubek1024/CPP-Minigames/tree/main?tab=readme-ov-file#connect-4)

- [Tic-Tac-Toe](https://github.com/Edoubek1024/CPP-Minigames/tree/main?tab=readme-ov-file#tic-tac-toe)

- [Snake](https://github.com/Edoubek1024/CPP-Minigames/tree/main?tab=readme-ov-file#snake)

- [2048](https://github.com/Edoubek1024/CPP-Minigames/tree/main?tab=readme-ov-file#2048)

- [Minesweeper](https://github.com/Edoubek1024/CPP-Minigames/tree/main?tab=readme-ov-file#minesweeper)

## Connect 4
This project is a console-based implementation of a Connect Four game that supports 2-4 players. Players take turns dropping their "chips" into columns on the board, with the goal of being the first to connect four (get it?) chips in a row, column, or diagonal.

This game starts by prompting the user for the amount of players playing. Then, each player is allowed to choose their username and skin. The skin is simply a unique character used to represent their chips on the board. After all players have entered their details, the game begins and each player can choose a column to place a chip or allow a random one to be chosen. Upon finishing the game, a scoreboard is shown and players are presented with a prompt that allows them to replay the game and possibly increase their scores.


## Tic Tac Toe
This project is a console-based implementation of a Tic Tac Toe game for 2 players. Players take turns placing their markers (X or O) on a 3 by 3 grid, aiming to align three in a row horizontally, vertically, or diagonally to win.

This game starts by prompting the user to choose which piece will move first. Then, the game begins and each player must place their piece in an open slot on the board until one gets 3 in a row or the board is filled and no one wins, which is considered a "cat's game."


## Snake
This project is a implementation of a classic snake game using the SFML (version 3.0.0) library. Players can move around a snake in order to collect apples and increase in size as much as they can. The game ends when the snake runs into its tail or the walls of the window.

This game starts immediately with the snake moving. The snake will always be moving but its direction of movement can be controlled by the player using the WASD keys or the ↑←↓→ keys in order to move up, left, down, or right respectively. The snake increases in size by one pixel every time it eats an apple. Upon hitting its tail or a wall, the display window will close.
<p align="center">
  <img src="https://github.com/user-attachments/assets/ea6d5279-a1a7-449f-86b5-c75770f765ac" width="450" />
</p>


## 2048
This project is an implementation of the original 2048 game using the SFML (version 3.0.0) library. Players can move blocks in one of four directions at a time to combine them and hopefully achieve the coveted 2048 block or higher.

This game starts immediately with two 2 blocks to be moved. The user can can make moves by using the WASD keys or the ↑←↓→ keys in order to move up, left, down, or right respectively. When moving in a corresponding direction, all blocks will move towards that direction. If two blocks bump into each other on the way to their destination, they will combine to form a block with a value twice the original. Once a valid move is made, a new 2 or 4 block will spawn in any available spaces. The game ends when the player can no longer make any valid moves, meaning the grid is full and there are no adjacent blocks with the same value.

<p align="center">
  <img src="https://github.com/user-attachments/assets/a7fa4ea5-5c33-4fc1-9678-1901f6a20ebe" width="400" />
</p>


## Minesweeper
This project is an implementation of the minesweeper game using the SFML (version 3.0.0) library. Players can check squares with the risk of accidentally hitting a mine. The player wins if they can find all spaces not containing a mine based on the numerical hints found. The player loses if they hit a mine.

This game starts as soon as the player chooses their first square by left clicking. The player can then proceed to right click on squares they think contain a mine, placing a flag there so that they don't click on it. Dug up squares appear grey in color while undug squares appear green. Once a square has been dug up, there can be a hint underneath, revealing how many mines are in the surrounding eight blocks. These hints range from one to eight and can only be uncovered once an undug square is clicked. If a player hits a mine, all mine positions will be shown and the game will terminate.
<p align="center">
  <img src="https://github.com/user-attachments/assets/d9876b64-0db0-45e1-b461-e981c21071d6" width="800" />
</p>
