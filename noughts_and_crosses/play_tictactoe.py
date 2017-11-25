import sys
import random

number_of_games = 10000

moves = {
    0: (0, 0),
    1: (0, 1),
    2: (0, 2),
    3: (1, 0),
    4: (1, 1),
    5: (1, 2),
    6: (2, 0),
    7: (2, 1),
    8: (2, 2),
}

# generator that plays pseudo random moves
def get_next_move():
    seen = {}
    for x in range(9):
        move = random.randrange(0, 9)
        while move in seen:
            move = random.randrange(0, 9)
        seen[move] = True
        yield move


def get_token():
    token = random.randrange(0, 2)
    if token == 0:
        return 'o'
    else:
        return 'x'

# Player 1
print("Mr One")
# Select token
print(get_token())
# Player 2
print("Mr Two")


# play number_of_games"
for i in range(0, number_of_games - 1):
    for j in get_next_move():
        print(moves[j][0])
        print(moves[j][1])

    # do you want to play again?
    print("y")

# play final game
for j in get_next_move():
    print(moves[j][0])
    print(moves[j][1])

# tired now, no more games.
print("n")

