#include "game.hpp"
#include "matrix.hpp"
#include <Arduino.h>
#include <util/delay.h>

#ifdef SNAKE

typedef uint8_t idx_t;

/**
 * \brief Direction on the board that the snake's body can turn towards
 */
enum dir_t {
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3
};

/**
 * Snake object tracking the head and tail of the snake, forming a linked list
 * over the board
 */
struct snake_t {
    idx_t head;
    idx_t tail;
    uint8_t facing;
};

struct tile_t {
    bool apple : 1;
    bool body : 1;
    uint8_t body_dir : 2;
};

tile_t *board = nullptr;
snake_t snake = {0};
uint8_t apple_x = 8, apple_y = 8;

struct input_t {
    bool b1 : 1;
    bool b2 : 1;
    bool b3 : 1;
};

input_t input = {1};

static idx_t translate(uint8_t x, uint8_t y, uint8_t const dir) {
    if(dir & 1) {
        x = (dir == EAST) ? x + 1 : x - 1; 
    } else {
        y = (dir == NORTH) ? y + 1 : y - 1;
    }

    return y * 16 + x;
}

void reset(void) {
    memset(board, 0, 256);
    memset(matrix::screen_buf, 0, 32);

    snake.head = 1;
    snake.tail = 0;

    board[snake.tail].body = true;
    board[snake.tail].body_dir = EAST;
    board[snake.head].body = true;
    board[snake.head].body_dir = EAST;
    matrix::set(0, 0);
    matrix::set(1, 0);

    board[8 * 16 + 8].apple = true;
    apple_x = apple_y = 8; 
}

bool update_input(void) {
  if(digitalRead(17) == LOW) {
        if(input.b3) {
            input.b3 = false;
            snake.facing = (snake.facing == WEST) ? NORTH : snake.facing + 1;
            return true;
        }
    } else {
        input.b3 = true;
    }
    
    if(digitalRead(15) == LOW) {
        if(input.b1) {
            input.b1 = false;
            snake.facing = (snake.facing == NORTH) ? WEST : snake.facing - 1;
            return true;
        }
    } else {
        input.b1 = true;
    }

    return false;
}

void play(void) {
    tile_t board_alloc[256] = {0};
    board = board_alloc;
    bool blinked = false;

    reset();

    uint8_t count = 0;
    for(;;) {
        if(!update_input() && count != 100) {
            _delay_us(10);
            count += 1;
            continue;
        }
        count = 0;

        board[snake.head].body_dir = snake.facing;
        uint8_t y = snake.head / 16;
        uint8_t x = snake.head % 16;
        if(snake.facing & 1) {
            x = (snake.facing == EAST) ? x + 1 : x - 1; 
        } else {
            y = (snake.facing == NORTH) ? y + 1 : y - 1;
        }
        snake.head = y * 16 + x;
         
        if(x < 16 && y < 16 && !board[snake.head].body) {
            if(board[snake.head].apple) {
                board[snake.head].apple = false;
                idx_t new_apple = random(0, 255);
                apple_x = new_apple % 16;
                apple_y = new_apple / 16;
                board[new_apple].apple = true;
            } else {
                uint8_t tail_x = snake.tail % 16;
                uint8_t tail_y = snake.tail / 16;
                matrix::unset(tail_x, tail_y);
                board[snake.tail].body = false;
                snake.tail = translate(tail_x, tail_y, board[snake.tail].body_dir);
            }
            
            matrix::set(x, y);
            board[snake.head].body = true;
        } else {
            reset();
        }
        
        if(blinked) {
            matrix::unset(apple_x, apple_y);
        } else {
            matrix::set(apple_x, apple_y);
        }

        blinked = !blinked;

    }

}

#endif
