# Dungeon Whack

A simple dungeon exploration game written in C using the Raylib library.

## Description

This is a top-down dungeon crawler where the player explores a procedurally generated dungeon, battling enemies and navigating through mazes. The game features a simple UI and a retro-style visual aesthetic.  The player can move using the arrow keys, rotate using Q and E, and toggle the inventory with C.  Enemies move randomly and are represented by colored circles.

## Features

* Top-down perspective
* Procedurally generated dungeon levels
* Random enemy placement and movement
* Simple inventory UI (inventory, equipment, character sheet, minimap, spells)
* Compass UI element dynamically updates with player direction
* Retro-style graphics

## Technologies Used

* C
* Raylib

## Installation

1. Clone the repository: `git clone <repository_url>`
2. Make sure you have Raylib installed.  (Instructions depend on your operating system.  Refer to the Raylib documentation for details).
3. Compile the code using a C compiler (like GCC) with the Raylib library linked:  `gcc *.c -o dungeon_whack -lraylib -lm`

## Usage

* **Movement:** Use the arrow keys (W, A, S, D) to move the player.
* **Rotation:** Use Q and E keys to rotate the player's view.
* **Inventory:** Press C to toggle the inventory UI.
* **Enemy Movement:** Press Z to trigger random enemy movement (for testing purposes).

## Controls

| Action        | Key(s) |
|----------------|--------|
| Move Up        | W      |
| Move Down      | S      |
| Move Left      | A      |
| Move Right     | D      |
| Rotate Left    | Q      |
| Rotate Right   | E      |
| Toggle Inventory | C      |
| Random Enemy Movement | Z      |


## License

MIT License

Copyright (c) [Your Name/Year]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
