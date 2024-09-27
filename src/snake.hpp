#pragma once

#include "main.hpp"

enum stateCodeSnake
{
    right,
    left,
    up,
    down
};

class Snake
{
private:
    const SDL_Color color{0, 0, 0, 100};

    struct Block
    {
        int x1, x2, y1, y2;
    };

    std::vector<Block> len;
    int head{0}, body{1};
    bool changeDirection{false};

    short prevState{stateCodeSnake::right};
    short state{stateCodeSnake::right};

    const void add_block();
    const bool move_half_body_R();
    const bool move_half_body_L();
    const bool move_half_body_U();
    const bool move_half_body_D();

    union move
    {
        const void right(std::vector<Block> &_len, const short &_start, const short &_end)
        {
            for (size_t i = _start; i < _end; i++)
            {
                _len[i].x1 += 1;
                _len[i].x2 += 1;
            }
        }
        const void left(std::vector<Block> &_len, const short &_start, const short &_end)
        {
            for (size_t i = _start; i < _end; i++)
            {
                _len[i].x1 -= 1;
                _len[i].x2 -= 1;
            }
        }
        const void up(std::vector<Block> &_len, const short &_start, const short &_end)
        {
            for (size_t i = _start; i < _end; i++)
            {
                _len[i].y1 -= 1;
                _len[i].y2 -= 1;
            }
        }
        const void down(std::vector<Block> &_len, const short &_start, const short &_end)
        {
            for (size_t i = _start; i < _end; i++)
            {
                _len[i].y1 += 1;
                _len[i].y2 += 1;
            }
        }

        // const void downRight(Block &_body, Block &_head)
        // {
        //     _body.y1 += 1;
        //     _body.y2 += 1;
        //     _head.x1 += 1;
        //     _head.x2 += 1;
        // }
    };

    move mv;

public:
    Snake();
    ~Snake();

    const void draw(SDL_Renderer *_renderer) const;
    void change_state(const short &_state);
    const void auto_move();
    const bool check_eat(const std::tuple<int, int> &_coords);
    const short get_state() const;
    const int get_head() const;
    const int get_body() const;
};