#include "snake.hpp"
#include "move_func.cpp"

Snake::Snake()
{
    Block head = Block();
    head.x1 = {80};
    head.x2 = {90};
    head.y1 = {100};
    head.y2 = {110};
    len.push_back(head);
}

Snake::~Snake()
{
}

const void Snake::draw(SDL_Renderer *_renderer) const
{
    for (size_t i = 0; i < len.size(); i++)
        boxRGBA(_renderer, this->len[i].x1, this->len[i].y1, this->len[i].x2, this->len[i].y2,
                this->color.r, this->color.g, this->color.b, this->color.a);
}

void Snake::change_state(const short &_state)
{
    if (state != _state)
    {
        prevState = state;
        state = _state;
    }
}

const void Snake::auto_move()
{
    switch (state)
    {
    case stateCodeSnake::right:
    {
        if (prevState == stateCodeSnake::down)
        {
            if (len.size() > 1 && len[1].y1 != len[0].y1)
            {
                for (size_t i = 1; i < len.size(); i++)
                {
                    mv.down(len, i, len.size());
                    mv.right(len, 0, len.size()-1);
                }
                break;
            }
        }
        else if (prevState == stateCodeSnake::up)
        {
            if (len.size() > 1 && len[1].y1 != len[0].y1)
            {
                for (size_t i = 1; i < len.size(); i++)
                {
                    mv.up(len, i);
                    len[0].x1 += 1;
                    len[0].x2 += 1;
                }
                break;
            }
        }
        mv.right(len, 0, len.size());
        break;
    }
    case stateCodeSnake::left:
    {
        if (prevState == stateCodeSnake::down)
        {
            if (len.size() > 1 && len[1].y1 != len[0].y1)
            {
                for (size_t i = 1; i < len.size(); i++)
                {
                    mv.down(len, i, len.size());
                    len[0].x1 -= 1;
                    len[0].x2 -= 1;
                }
                break;
            }
        }
        else if (prevState == stateCodeSnake::up)
        {
            if (len.size() > 1 && len[1].y1 != len[0].y1)
            {
                for (size_t i = 1; i < len.size(); i++)
                {
                    mv.up(len, i);
                    len[0].x1 -= 1;
                    len[0].x2 -= 1;
                }
                break;
            }
        }
        mv.left(len, 0);
        break;
    }
    case stateCodeSnake::up:
    {
        if (prevState == stateCodeSnake::left)
        {
            if (len.size() > 1 && len[1].x1 != len[0].x1)
            {
                for (size_t i = 1; i < len.size(); i++)
                {
                    mv.left(len, i);
                    len[0].y1 -= 1;
                    len[0].y2 -= 1;
                }
                break;
            }
        }
        else if (prevState == stateCodeSnake::right)
        {
            if (len.size() > 1 && len[1].x1 != len[0].x1)
            {
                for (size_t i = 1; i < len.size(); i++)
                {
                    mv.right(len, i, len.size());
                    len[0].y1 -= 1;
                    len[0].y2 -= 1;
                }
                break;
            }
        }
        mv.up(len, 0);
        break;
    }
    case stateCodeSnake::down:
    {
        if (prevState == stateCodeSnake::left)
        {
            if (len.size() > 1 && len[1].x1 != len[0].x1)
            {
                for (size_t i = 1; i < len.size(); i++)
                {
                    mv.left(len, i);
                    len[0].y1 += 1;
                    len[0].y2 += 1;
                }
                break;
            }
        }
        else if (prevState == stateCodeSnake::right)
        {
            if (len.size() > 1 && len[1].x1 != len[0].x1)
            {
                for (size_t i = 1; i < len.size(); i++)
                {
                    mv.right(len, i, len.size());
                    len[0].y1 += 1;
                    len[0].y2 += 1;
                }
                break;
            }
        }
        mv.down(len, 0, len.size());
        break;
    }
    default:
        break;
    }
}

const void Snake::add_block()
{
    Block body = Block();
    switch (state)
    {
    case stateCodeSnake::right:
    {
        body.x1 = len.back().x1 - 12;
        body.x2 = len.back().x2 - 12;
        body.y1 = len.back().y1;
        body.y2 = len.back().y2;
        break;
    }
    case stateCodeSnake::left:
    {
        body.x1 = len.back().x1 + 12;
        body.x2 = len.back().x2 + 12;
        body.y1 = len.back().y1;
        body.y2 = len.back().y2;
        break;
    }
    case stateCodeSnake::up:
    {
        body.x1 = len.back().x1;
        body.x2 = len.back().x2;
        body.y1 = len.back().y1 + 12;
        body.y2 = len.back().y2 + 12;
        break;
    }
    case stateCodeSnake::down:
    {
        body.x1 = len.back().x1;
        body.x2 = len.back().x2;
        body.y1 = len.back().y1 - 12;
        body.y2 = len.back().y2 - 12;
        break;
    }
    default:
        break;
    }

    len.push_back(body);
}

const bool Snake::check_eat(const std::tuple<int, int> &_coords)
{
    if ((std::get<0>(_coords) - 5) <= len.front().x2 && (std::get<0>(_coords) + 5) >= len.front().x1 &&
        (std::get<1>(_coords) - 5) <= len.front().y2 && (std::get<1>(_coords) + 5) >= len.front().y1)
    {
        this->add_block();
        return true;
    }
    return false;
}

const short Snake::get_state() const
{
    return this->state;
}

const int Snake::get_head() const
{
    return this->head;
}
const int Snake::get_body() const
{
    return this->body;
}