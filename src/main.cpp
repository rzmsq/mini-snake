#include "snake.hpp"
#include "apple.hpp"

const int screen_width{180};
const int screen_height{200};

int main(int argc, char const *argv[])
{
    SDL_Window *window{nullptr};
    SDL_Surface *screenSurface{nullptr};
    SDL_Renderer *renderer{nullptr};

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << '\n';
    else if (TTF_Init() < 0)
        std::cerr << "TTF could not initialize! TTF_Error: " << TTF_GetError() << '\n';
    else
    {
        window = SDL_CreateWindow("mini-snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (window == NULL)
            std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << '\n';
        else
        {
            const SDL_Color bgColor = {128, 128, 128};
            Snake snake = Snake();
            Apple apple = Apple();

            SDL_Event e;
            bool quit{false}, flg{false};
            while (!quit)
            {
                while (SDL_PollEvent(&e))
                {
                    switch (e.type)
                    {
                    case SDL_QUIT:
                        quit = true;
                        break;
                    case SDL_KEYDOWN:
                    {
                        if (e.key.keysym.sym == SDLK_RIGHT)
                            snake.change_state(stateCodeSnake::right);
                        if (e.key.keysym.sym == SDLK_LEFT)
                            snake.change_state(stateCodeSnake::left);
                        if (e.key.keysym.sym == SDLK_UP)
                            snake.change_state(stateCodeSnake::up);
                        if (e.key.keysym.sym == SDLK_DOWN)
                            snake.change_state(stateCodeSnake::down);
                    }
                    default:
                        break;
                    }
                }
                SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
                SDL_RenderClear(renderer);

                snake.auto_move();
                if (!flg)
                    flg = snake.check_eat(apple.get_coord());
                snake.draw(renderer);
                apple.draw(renderer);

                SDL_RenderPresent(renderer);

                SDL_Delay(25);
            }
        }
    }

    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
