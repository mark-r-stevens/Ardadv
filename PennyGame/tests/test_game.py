import pytest

from pennygame.game import apply_move, is_valid_move


def test_is_valid_move_accepts_1_or_2_within_pile():
    assert is_valid_move(1, 5)
    assert is_valid_move(2, 5)


def test_is_valid_move_rejects_other_values_or_too_many():
    assert not is_valid_move(0, 5)
    assert not is_valid_move(3, 5)
    assert not is_valid_move(2, 1)


def test_apply_move_updates_pile_size():
    assert apply_move(5, 2) == 3


def test_apply_move_raises_for_invalid_move():
    with pytest.raises(ValueError):
        apply_move(1, 2)
