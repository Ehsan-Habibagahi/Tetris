# Tetris game (Unicode terminal game)
[![star](https://img.shields.io/static/v1?label=%F0%9F%8C%9F&message=If%20Useful&style=style=flat&color=1e2463)]() [![license](https://img.shields.io/badge/License-MIT-1e2463)]() 

<p align="center">
<img src="./data/tetris-2.png" width=50%>
<br/>
</p>

A C++ implementation of the classic Tetris game, built from the ground up with enhancements and additional features. This project stays true to the original while introducing fresh elements to make it remain nostalgic.

## Quick guide
### Compile with:
 `c++ *.cpp -lwinmm`
## Features
- In game sound / sound effect 🔊
- Responsive UI - press any key to update the view 💅
- Resumability: Continue from where you saved!
All the current map held and pendding tetrominos are retured
- Hold current Tetromino
- See incoming Tetromino
- Easter egg: Spoiler duck spawns on random spot. Each hit will lead to spoil of Tetromino. Hitting 5 ducks leads to loss (D-lost 🦆)
- 3 levels (Speeds increase by level grows/ Hard mode has no shadow guide)
- Mid-game pause menu
- Timer
- leaderboard seprate for each level - sorted by (Score/ time)
- Dynamic dimentions

![Screenshot](./data/Screenshot.png)

![Screenshot](./data/Screenshot2.png)


## Shortcuts

| Key | Action |
| ---- | ----- |
| `🠨` `🠪` `🠫` | Move Tetromino |
| `🠩` | Rotate |
| `Esc` | Pause |
| `H` | Hold |
| `Space` | Push down |

## Contributing
We warmly welcome and value your contributions to this project!🧸

If you have ideas for enhancements, bug fixes, or new features, feel free to fork the repository, make your changes, and submit a pull request. Your input helps make this project better for everyone.

Don’t forget to star🌟 the repository if you find it useful! Thank you for your support!
## Acknowledgments

* [Tetris Game](https://en.wikipedia.org/wiki/Tetris)
* [Gravity Guy sound](https://www.miniplay.com/game/gravity-guy) (All the in-game and menu sounds)