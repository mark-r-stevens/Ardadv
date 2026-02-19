"""Command-line Penny Game implementation."""

from __future__ import annotations


def is_valid_move(move: int, pennies_left: int) -> bool:
    """Return True when a move is legal for the current game state."""
    return move in (1, 2) and move <= pennies_left


def apply_move(pennies_left: int, move: int) -> int:
    """Apply a legal move and return the updated penny count."""
    if not is_valid_move(move, pennies_left):
        raise ValueError(f"Illegal move: {move} with {pennies_left} pennies left")
    return pennies_left - move


def take_turn(player_name: str, pennies_left: int) -> int:
    """Prompt the current player for a move and return a legal choice."""
    while True:
        raw = input(f"{player_name}, take 1 or 2 pennies ({pennies_left} left): ").strip()
        if raw not in {"1", "2"}:
            print("Please enter 1 or 2.")
            continue

        move = int(raw)
        if not is_valid_move(move, pennies_left):
            print(f"You cannot take {move}; only {pennies_left} remaining.")
            continue

        return move


def main() -> None:
    """Run a two-player Penny Game in the terminal."""
    pennies_left = 13
    players = ["Player 1", "Player 2"]
    turn = 0

    print("Welcome to PennyGame!")
    while pennies_left > 0:
        player = players[turn % 2]
        move = take_turn(player, pennies_left)
        pennies_left = apply_move(pennies_left, move)

        if pennies_left == 0:
            print(f"{player} wins!")
            return

        print(f"{pennies_left} pennies remain.\n")
        turn += 1


if __name__ == "__main__":
    main()
