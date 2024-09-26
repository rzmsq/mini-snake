#pragma once

#include "main.hpp"

class Apple
{
private:
    const SDL_Color color{255, 16, 16, 100};

    int x, y, size{5};

public:
    Apple();
    ~Apple();

    const void draw(SDL_Renderer *_renderer) const;
    const std::tuple<int, int> get_coord() const;
};