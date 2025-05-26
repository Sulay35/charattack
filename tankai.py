import pygame
import random
import numpy as np
import pickle

WIDTH, HEIGHT = 600, 600
GRID_SIZE = 10
CELL_SIZE = WIDTH // GRID_SIZE
FPS = 10
WHITE = (255, 255, 255)
RED = (255, 0, 0)
BLUE = (0, 100, 255)
BLACK = (0, 0, 0)
GRAY = (100, 100, 100)


# Q-Learning parameters
LEARNING_RATE = 0.1
DISCOUNT = 0.95
EPSILON = 0.1  # Exploration rate

pygame.init()
# Tank Images
player_sprite = pygame.transform.scale(pygame.image.load("char.png"), (CELL_SIZE, CELL_SIZE))
agent_sprite = pygame.transform.scale(pygame.image.load("char.png"), (CELL_SIZE, CELL_SIZE))

def clamp(val, min_val=0, max_val=GRID_SIZE - 1):
    return max(min_val, min(max_val, val))


# TANK  ACTIONS
ACTIONS = ['UP', 'DOWN', 'LEFT', 'RIGHT', 'SHOOT']
class Tank:
    def __init__(self, x, y, color, sprite, is_player=False):
        self.x = x
        self.y = y
        self.color = color
        self.sprite = sprite
        self.bullet = None
        self.is_player = is_player
        self.dir = 'UP'  
        self.hits = 0

    def draw(self, win):
        rotated_sprite = self.sprite
        if self.dir == 'UP':
            rotated_sprite = pygame.transform.rotate(self.sprite, 0)
        elif self.dir == 'DOWN':
            rotated_sprite = pygame.transform.rotate(self.sprite, 180)
        elif self.dir == 'LEFT':
            rotated_sprite = pygame.transform.rotate(self.sprite, 90)
        elif self.dir == 'RIGHT':
            rotated_sprite = pygame.transform.rotate(self.sprite, -90)

        win.blit(rotated_sprite, (self.x * CELL_SIZE, self.y * CELL_SIZE))

        if self.bullet:
            pygame.draw.circle(win, self.color, (self.bullet[0] * CELL_SIZE + CELL_SIZE // 2, self.bullet[1] * CELL_SIZE + CELL_SIZE // 2), CELL_SIZE // 4)

    def move(self, direction, walls):
        self.dir = direction
        new_x, new_y = self.x, self.y
        if direction == 'UP':
            new_y = clamp(self.y - 1)
        elif direction == 'DOWN':
            new_y = clamp(self.y + 1)
        elif direction == 'LEFT':
            new_x = clamp(self.x - 1)
        elif direction == 'RIGHT':
            new_x = clamp(self.x + 1)
        if (new_x, new_y) not in walls:
            self.x, self.y = new_x, new_y

    def shoot(self):
        dx, dy = 0, 0
        if self.dir == 'UP':
            dx, dy = 0, -1
        elif self.dir == 'DOWN':
            dx, dy = 0, 1
        elif self.dir == 'LEFT':
            dx, dy = -1, 0
        elif self.dir == 'RIGHT':
            dx, dy = 1, 0
        self.bullet = (self.x + dx, self.y + dy, dx, dy)

    def update_bullet(self, walls):
        if self.bullet:
            bx, by, dx, dy = self.bullet
            bx += dx
            by += dy
            if 0 <= bx < GRID_SIZE and 0 <= by < GRID_SIZE and (bx, by) not in walls:
                self.bullet = (bx, by, dx, dy)
            else:
                self.bullet = None


def get_state(agent, player):
    return (agent.x, agent.y, player.x, player.y)

def choose_action(state, q_table):
    if random.uniform(0, 1) < EPSILON:
        return random.choice(ACTIONS)
    return max(q_table[state], key=q_table[state].get)

def reset_round(agent, player):
    agent.x, agent.y = 1, GRID_SIZE - 2
    player.x, player.y = GRID_SIZE - 2, GRID_SIZE - 2
    agent.bullet = None
    player.bullet = None
    agent.facing = 'UP'
    player.facing = 'UP'

MAP = [
    ".......#..",
    ".###..##..",
    "..#....#..",
    "..........",
    ".......###",
    "..........",
    "..#....#..",
    "..##..##..",
    "..........",
    ".##..#....",
]

def generate_walls():
    walls = set()
    for y, row in enumerate(MAP):
        for x, cell in enumerate(row):
            if cell == "#":  # '#' represents a wall
                walls.add((x, y))
    return walls

def draw_walls(win, walls):
    for (x, y) in walls:
        pygame.draw.rect(win, GRAY, (x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE))

def main():
    win = pygame.display.set_mode((WIDTH, HEIGHT))
    clock = pygame.time.Clock()

    # Tanks
    agent = Tank(1, GRID_SIZE - 2, BLUE, agent_sprite)
    # Walls
    player = Tank(GRID_SIZE - 2, GRID_SIZE - 2, RED, player_sprite, is_player=True)
    walls = generate_walls()

    # Initialize Q-table
    q_table = {}
    for x1 in range(GRID_SIZE):
        for y1 in range(GRID_SIZE):
            for x2 in range(GRID_SIZE):
                for y2 in range(GRID_SIZE):
                    q_table[(x1, y1, x2, y2)] = {a: 0 for a in ACTIONS}

    run = True
    while run:
        clock.tick(FPS)
        win.fill(BLACK)

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False

        # Player input Z, S, Q, D for movement and SPACE to shoot
        keys = pygame.key.get_pressed()
        if keys[pygame.K_z]:
            player.move('UP', walls)
        if keys[pygame.K_s]:
            player.move('DOWN', walls)
        if keys[pygame.K_q]:
            player.move('LEFT', walls)
        if keys[pygame.K_d]:
            player.move('RIGHT', walls)
        if keys[pygame.K_SPACE] and not player.bullet:
            player.shoot()

        # Agent decision
        state = get_state(agent, player)
        action = choose_action(state, q_table)

        reward = -1

        if action in ['UP', 'DOWN', 'LEFT', 'RIGHT']:
            agent.move(action, walls)
        elif action == 'SHOOT' and not agent.bullet:
            agent.shoot()

        player.update_bullet(walls)
        agent.update_bullet(walls)

        # Check hits
        if player.bullet and (player.bullet[0], player.bullet[1]) == (agent.x, agent.y):
            print("Player hit agent")
            reward = -10
            player.hits += 1
            player.bullet = None
            reset_round(agent, player)
        if agent.bullet and (agent.bullet[0], agent.bullet[1]) == (player.x, player.y):
            print("Agenr hit player")
            reward = 10
            agent.hits += 1
            agent.bullet = None
            reset_round(agent, player)

        # Round over check
        if player.hits >= 3:
            print("Player won!")
            run = False
        if agent.hits >= 3:
            print("Agent won!")
            run = False

        # Q-learning update
        new_state = get_state(agent, player)
        max_future_q = max(q_table[new_state].values())
        current_q = q_table[state][action]
        new_q = (1 - LEARNING_RATE) * current_q + LEARNING_RATE * (reward + DISCOUNT * max_future_q)
        q_table[state][action] = new_q
        print(f"State: {state}, Action: {action}, Reward: {reward}, Q-value: {q_table[state][action]}")

        # DRAW
        draw_walls(win, walls)
        agent.draw(win)
        player.draw(win)
        pygame.display.update()

    pygame.quit()

    with open("q_table.pkl", "wb") as f:
        pickle.dump(q_table, f)


if __name__ == "__main__":
    main()
