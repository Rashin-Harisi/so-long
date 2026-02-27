*This project has been created as part of the 42 curriculum by rabdolho.*

## Description
**SO_LONG** is a small 2D game developed as part of the 42 curriculum.
The goal of the project is to create a simple tile-based game using the MiniLibX (MLX) graphical library.

In this game, the player must:
* Collect all collectibles (C)
* Avoid enemies (X)
* Reach the exit (E) after collecting all items

The map is read from a .ber file and validated before the game starts. 
* The map must be rectangular.
* The map must be enclosed/surrounded by walls.
* You must verify if there is a valid path in the map.
* a map must contain 1 exit, 1 starting position and at least 1 collectible
If the map is invalid, the program exits with an error.

This project focuses on:
* Window management with MiniLibX
* 2D rendering
* Event handling (keyboard + window events)
* Path validation using BFS (queue-based flood fill)
* Memory management
* Game loop & animations


### MiniLibX (MLX)
This project uses MiniLibX, a lightweight graphical library provided by 42.

It is used for:
* Creating windows
* Rendering images (XPM textures)
* Handling keyboard input
* Managing the game loop
* Destroying graphical resources properly

On Linux, MLX requires linking with:
```bash
-lmlx -lXext -lX11 -lm
```
## Instruction

### Usage
#### Compilation
The project includes a `Makefile` that compiles the source files into an executable named `so_long`. To compile, run:
```bash
make
# OR
make bonus
```
#### Cleanup
To remove object files, run:
```bash
make fclean
```


## Resources
* <a href="https://harm-smits.github.io/42docs/libs/minilibx"> MinilibX Library </a>
* <a href="https://chatgpt.com/"> ChatGpt </a>
* <a href="https://42-cursus.gitbook.io/guide/2-rank-02/so_long" target="_blank"> So_Long Guide </a>
* <a href="https://youtu.be/bYS93r6U0zg?si=RXUH9VSV0dk94uaq" target="_blank"> Introduction to the minilibX : a simple X-Window programming API in C</a>
* <a href="https://www.geeksforgeeks.org/dsa/flood-fill-algorithm/" target="_blank">Flood Fill Algorithm</a>
