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
        state = _state;
}

const void Snake::auto_move()
{
    switch (state)
    {
    case stateCodeSnake::right:
    {
        mv.right(len);
        break;
    }
    case stateCodeSnake::left:
    {
        mv.left(len);
        break;
    }
    case stateCodeSnake::up:
    {
        mv.up(len);
        break;
    }
    case stateCodeSnake::down:
    {
        mv.down(len);
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
        body.x1 = len[len.size() - 1].x1 - 10;
        body.x2 = len[len.size() - 1].x2 - 10;
        body.y1 = len[len.size() - 1].y1;
        body.y2 = len[len.size() - 1].y2;
        break;
    }
    case stateCodeSnake::left:
    {
        body.x1 = len[len.size() - 1].x1 + 10;
        body.x2 = len[len.size() - 1].x2 + 10;
        body.y1 = len[len.size() - 1].y1;
        body.y2 = len[len.size() - 1].y2;
        break;
    }
    case stateCodeSnake::up:
    {
        body.x1 = len[len.size() - 1].x1;
        body.x2 = len[len.size() - 1].x2;
        body.y1 = len[len.size() - 1].y1 + 10;
        body.y2 = len[len.size() - 1].y2 + 10;
        break;
    }
    case stateCodeSnake::down:
    {
        body.x1 = len[len.size() - 1].x1;
        body.x2 = len[len.size() - 1].x2;
        body.y1 = len[len.size() - 1].y1 - 10;
        body.y2 = len[len.size() - 1].y2 - 10;
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