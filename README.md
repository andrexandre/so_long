# So_long

A simple 2D game developed using [MinilibX](https://github.com/42Paris/minilibx-linux). The player navigates through a map, collecting items and reaching the exit while avoiding obstacles

### Features

- Simple and intuitive controls
- Custom map parsing from .ber files
- Custom map creation with an in game map editor

## Usage

1. Clone the repository
```sh
git clone https://github.com/andrexandre/so_long.git ; cd so_long
```

2. Compile the library
```sh
make
```

3. Run the game
```sh
./so_long maps/test.ber
```

## Controls

- W, A, S, D or arrow keys: Move the player
- ESC or Q: Quit the game
- R: Restart the game
- E: Map editor

## Map Creation

Maps must have a `.ber` extension and follow these rules:
- Must be rectangular
- Surrounded by walls ('1')
- Must have one exit ('E')
- Must have at least one collectible ('C')
- Must have one starting position ('P')
- Only valid characters: '0' (space), '1' (wall), 'C' (collectible), 'E' (exit), 'P' (player), 'D' (Danger)

Example of a valid map:
```
1111111111111
10010000000C1
1000011111001
1P0011E000001
1111111111111
```

## Editor

You can edit the map with the mouse in game if you use `E`. The controls for the editor will be shown on the terminal

> [!NOTE]
> This project is part of the 42 School curriculum
