#include "../headers/snake.hpp"
#include "../headers/apple.hpp"

const int screen_width{180};
const int screen_height{200};

int main(int argc, char const *argv[])
{
    SDL_Window *window{nullptr};
    SDL_Surface *screenSurface{nullptr};
    SDL_Renderer *renderer{nullptr};
    SDL_Surface *surfaceMessage{nullptr};
    SDL_Texture *message{nullptr};

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
            SDL_Color fontColor = {255, 255, 255};

            Snake snake = Snake();
            Apple apple = Apple();

            TTF_Font *Sans = TTF_OpenFont("../OpenSans-Regular.ttf", 36);

            SDL_Rect message_rect;
            message_rect.x = 5;
            message_rect.y = 0;
            message_rect.w = 50;
            message_rect.h = 50;

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
                        if (e.key.keysym.sym == SDLK_RIGHT &&
                            snake.get_state() != stateCodeSnake::left)
                            snake.change_state(stateCodeSnake::right);
                        if (e.key.keysym.sym == SDLK_LEFT &&
                            snake.get_state() != stateCodeSnake::right)
                            snake.change_state(stateCodeSnake::left);
                        if (e.key.keysym.sym == SDLK_UP &&
                            snake.get_state() != stateCodeSnake::down)
                            snake.change_state(stateCodeSnake::up);
                        if (e.key.keysym.sym == SDLK_DOWN &&
                            snake.get_state() != stateCodeSnake::up)
                            snake.change_state(stateCodeSnake::down);
                    }
                    default:
                        break;
                    }
                }
                SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
                SDL_RenderClear(renderer);

                snake.auto_move();
                flg = snake.check_eat(apple.get_coord());
                snake.check_hit();
                snake.draw(renderer);
                apple.draw(renderer);

                if (flg)
                    apple.respawn();

                std::string scoreTxt = "Score: " + std::to_string(snake.get_score());

                surfaceMessage =
                    TTF_RenderText_Solid(Sans, scoreTxt.c_str(), fontColor);
                message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
                SDL_RenderCopy(renderer, message, NULL, &message_rect);

                SDL_RenderPresent(renderer);

                SDL_Delay(150);
            }
        }
    }

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
