## Terminal-GFX
A simple retained mode graphics-API, still very much a work in progress  
Currently only supports a terminal based rendering backend using **ncurses**

### Setup
1. Install **ncurses** if needed
2. `cd` to main source directory
3. `mkdir build`
4. `cd build`
5. `cmake ..`
6. `make`
7. `cd bin`
7. `./[name-of-demo]`

### Interactive Demo App
- `e` and `t` to create an ellipse or triangle polyline respectively
- `E` and `T` to create an item as a child of the selected item
- `n` to cycle selected object
- `r` to remove selected object
- `wasd` to move selected object
- `hjkl` to scale selected object
- `H` and `L` to rotate selected object
- `i` an `o` to change line thickness of selected object

