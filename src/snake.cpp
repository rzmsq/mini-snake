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
        changeDirection = false;
    }
}

const void Snake::auto_move()
{
    bool isChangeDirect{false};
    switch (state)
    {
    case stateCodeSnake::right:
    {
        if (prevState == stateCodeSnake::down)
        {
            if (len.size() > 1 && len[this->body].y1 != len[0].y1)
            {
                mv.down(len, this->body, len.size());
                mv.right(len, 0, this->body);
                break;
            }
            isChangeDirect = move_half_body_R();
        }
        else if (prevState == stateCodeSnake::up)
        {
            if (len.size() > 1 && len[this->body].y1 != len[0].y1)
            {
                mv.up(len, this->body, len.size());
                mv.right(len, 0, this->body);
                break;
            }
            isChangeDirect = move_half_body_R();
        }
        if (!isChangeDirect)
            mv.right(len, 0, len.size());
        else
            mv.right(len, this->body-1, len.size());
        break;
    }
    case stateCodeSnake::left:
    {
        if (prevState == stateCodeSnake::down)
        {
            if (len.size() > 1 && len[this->body].y1 != len[0].y1)
            {
                mv.down(len, this->body, len.size());
                mv.left(len, 0, this->body);
                break;
            }
            isChangeDirect = move_half_body_L();
        }
        else if (prevState == stateCodeSnake::up)
        {
            if (len.size() > 1 && len[this->body].y1 != len[0].y1)
            {
                mv.up(len, this->body, len.size());
                mv.left(len, 0, this->body);
                break;
            }
            isChangeDirect = move_half_body_L();
        }
        if (!isChangeDirect)
            mv.left(len, 0, len.size());
        else
            mv.left(len, this->body-1, len.size());
        break;
    }
    case stateCodeSnake::up:
    {
        if (prevState == stateCodeSnake::left)
        {
            if (len.size() > 1 && len[this->body].x1 != len[0].x1)
            {
                mv.left(len, this->body, len.size());
                mv.up(len, 0, this->body);
                break;
            }
            isChangeDirect = move_half_body_U();
        }
        else if (prevState == stateCodeSnake::right)
        {
            if (len.size() > 1 && len[this->body].x1 != len[0].x1)
            {
                mv.right(len, this->body, len.size());
                mv.up(len, 0, this->body);
                break;
            }
            isChangeDirect = move_half_body_U();
        }
        if (!isChangeDirect)
            mv.up(len, 0, len.size());
        else
            mv.up(len, this->body-1, len.size());
        break;
    }
    case stateCodeSnake::down:
    {
        if (prevState == stateCodeSnake::left)
        {
            if (len.size() > 1 && len[this->body].x1 != len[0].x1)
            {
                mv.left(len, this->body, len.size());
                mv.down(len, 0, this->body);
                break;
            }
            isChangeDirect = move_half_body_D();
        }
        else if (prevState == stateCodeSnake::right)
        {
            if (len.size() > 1 && len[this->body].x1 != len[0].x1)
            {
                mv.right(len, this->body, len.size());
                mv.down(len, 0, this->body);
                break;
            }
            isChangeDirect = move_half_body_D();
        }
        if (!isChangeDirect)
            mv.down(len, 0, len.size());
        else
            mv.down(len, this->body-1, len.size());
        break;
    }
    default:
        break;
    }
}

const bool Snake::move_half_body_R()
{
    if (this->body != len.size() - 1 && !this->changeDirection)
    {
        if (len.size() > 1 && len[this->body].y1 == len[0].y1)
        {
            mv.right(len, 0, this->body);
            this->body += this->body < len.size() - 1 ? 1 : 0;
            return true;
        }
    }
    else
    {
        this->changeDirection = true;
        this->body = 1;
    }
    return false;
}

const bool Snake::move_half_body_U()
{
    if (this->body != len.size() - 1 && !this->changeDirection)
    {
        if (len.size() > 1 && len[this->body].x1 == len[0].x1)
        {
            mv.up(len, 0, this->body);
            this->body += this->body < len.size() - 1 ? 1 : 0;
            return true;
        }
    }
    else
    {
        this->changeDirection = true;
        this->body = 1;
    }
    return false;
}

const bool Snake::move_half_body_D()
{
    if (this->body != len.size() - 1 && !this->changeDirection)
    {
        if (len.size() > 1 && len[this->body].x1 == len[0].x1)
        {
            mv.down(len, 0, this->body);
            this->body += this->body < len.size() - 1 ? 1 : 0;
            return true;
        }
    }
    else
    {
        this->changeDirection = true;
        this->body = 1;
    }
    return false;
}

const bool Snake::move_half_body_L()
{
    if (this->body != len.size() - 1 && !this->changeDirection)
    {
        if (len.size() > 1 && len[this->body].y1 == len[0].y1)
        {
            mv.left(len, 0, this->body);
            this->body += this->body < len.size() - 1 ? 1 : 0;
            return true;
        }
    }
    else
    {
        this->changeDirection = true;
        this->body = 1;
    }
    return false;
}

const void Snake::add_block()
{
    Block body = Block();
    switch (state)
    {
    case stateCodeSnake::right:
    {
        body.x1 = len[len.size()-1].x1 - 12;
        body.x2 = len[len.size()-1].x2 - 12;
        body.y1 = len[len.size()-1].y1;
        body.y2 = len[len.size()-1].y2;
        break;
    }
    case stateCodeSnake::left:
    {
        body.x1 = len[len.size()-1].x1 + 12;
        body.x2 = len[len.size()-1].x2 + 12;
        body.y1 = len[len.size()-1].y1;
        body.y2 = len[len.size()-1].y2;
        break;
    }
    case stateCodeSnake::up:
    {
        body.x1 = len[len.size()-1].x1;
        body.x2 = len[len.size()-1].x2;
        body.y1 = len[len.size()-1].y1 + 12;
        body.y2 = len[len.size()-1].y2 + 12;
        break;
    }
    case stateCodeSnake::down:
    {
        body.x1 = len[len.size()-1].x1;
        body.x2 = len[len.size()-1].x2;
        body.y1 = len[len.size()-1].y1 - 12;
        body.y2 = len[len.size()-1].y2 - 12;
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