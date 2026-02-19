# PennyGame

A starter implementation of a two-player Penny Game where players alternately take 1 or 2 pennies from a shared pile.

## Rules

- The game starts with a pile of pennies (default: 13).
- Each player takes turns removing **1** or **2** pennies.
- The player who takes the final penny wins.

## Quick start

```bash
cd PennyGame
python -m pennygame.game
```

Or, after installing the project:

```bash
pip install -e .
pennygame
```

## Roadmap

- [x] Core game loop and win condition
- [x] Input validation for legal moves
- [ ] Add a simple AI opponent
- [ ] Add richer terminal UI and score tracking
