#include "snake.hpp"
#include "move_func.cpp"

Snake::Snake()
{
    Block head = Block();
    head.x1 = {80};
    head.x2 = {90};
    head.y1 = {100};
    head.y2 = {110};
    body.push_back(head);
}

Snake::~Snake()
{
}

const void Snake::draw(SDL_Renderer *_renderer) const
{
    for (size_t i = 0; i < body.size(); i++)
        boxRGBA(_renderer, this->body[i].x1, this->body[i].y1, this->body[i].x2, this->body[i].y2,
                this->color.r, this->color.g, this->color.b, this->color.a);
}

const void Snake::change_state(const short &_state)
{
    state = _state;
}

const void Snake::auto_move()
{
    switch (state)
    {
    case stateCodeSnake::right:
    {
        mv.right(body);
        break;
    }
    case stateCodeSnake::left:
    {
        mv.left(body);
        break;
    }
    case stateCodeSnake::up:
    {
        mv.up(body);
        break;
    }
    case stateCodeSnake::down:
    {
        mv.down(body);
        break;
    }
    default:
        break;
    }
}

const void Snake::add_block()
{
    Block newBody = Block();
    newBody.x1 = body[body.size() - 1].x1;
    newBody.x2 = body[body.size() - 1].x2;
    newBody.y1 = body[body.size() - 1].y1;
    newBody.y2 = body[body.size() - 1].y2;

    body.push_back(newBody);
}

const bool Snake::check_eat(const std::tuple<int, int> &_coords)
{
    if ((std::get<0>(_coords) - 5) <= body.front().x2 &&
        (std::get<0>(_coords) + 5) >= body.front().x1 &&
        (std::get<1>(_coords) - 5) <= body.front().y2 &&
        (std::get<1>(_coords) + 5) >= body.front().y1)
    {
        this->add_block();
        return true;
    }
    return false;
}

const void Snake::check_hit()
{
    if (body.size() > 2)
    {
        for (size_t i = 1; i < body.size(); i++)
        {
            if ((body[0].x2 <= body[i].x2 &&
                 body[0].x1 >= body[i].x1 &&
                 body[0].y2 <= body[i].y2 &&
                 body[0].y1 >= body[i].y1))
            {
                std::cerr << "hit\n";
            }
        }
    }
    if (body[0].x2 <= 0 || body[0].x2 >= 190 ||
        body[0].y2 <= 0 || body[0].y2 >= 210)
    {
        std::cerr << "hit\n";
    }
}

const int Snake::get_state() const
{
    return this->state;
}