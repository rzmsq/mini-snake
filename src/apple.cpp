#include "apple.hpp"

Apple::Apple()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib_x(3, 187);
    std::uniform_int_distribution<> distrib_y(3, 197);
    this->x = {distrib_x(gen)};
    this->y = {distrib_y(gen)};
}

Apple::~Apple()
{
}

const void Apple::draw(SDL_Renderer *_renderer) const
{
    filledCircleRGBA(_renderer, this->x, this->y, this->size, this->color.r, this->color.g, this->color.b, this->color.a);
}

const std::tuple<int, int> Apple::get_coord() const
{
    return std::make_tuple(this->x, this->y);
}