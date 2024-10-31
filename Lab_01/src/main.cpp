#include <SDL2/SDL.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

bool init(SDL_Window** window, SDL_Renderer** renderer, const int windowWidth, const int windowHeight) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    *window = SDL_CreateWindow(
        "Lab_01",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        windowWidth,
        windowHeight,
        SDL_WINDOW_SHOWN
    );

    if (*window == nullptr) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return false;
    }

    *renderer = SDL_CreateRenderer(
        *window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if (*renderer == nullptr) {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void close(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

struct Point {
    float x, y;

    Point() = default;
    
    Point(float x, float y) {
        this->x = x;
        this->y = y;
    }

    ~Point() = default;
};

std::vector<Point> createPolygon(int sides, float radius) {
    std::vector<Point> points;

    for (int i = 0; i < sides; ++i) {
        float angle = 2.0f * M_PI * i / sides;
        points.emplace_back(radius * cos(angle), radius * sin(angle));
    }

    return points;
}

Point rotatePoint(const Point& p, float angle) {
    float cosA = cos(angle);
    float sinA = sin(angle);
    
    return {p.x * cosA - p.y * sinA, p.x * sinA + p.y * cosA};
}

void drawPolygon(SDL_Renderer* renderer, const std::vector<Point>& points, float scale, float rotation, Point offset) {
    std::vector<Point> transformedPoints;

    for (const auto& p : points) {
        Point rotated = rotatePoint(p, rotation);
        transformedPoints.emplace_back(rotated.x * scale + offset.x, rotated.y * scale + offset.y);
    }

    for (size_t i = 0; i < transformedPoints.size(); ++i) {
        const Point& p1 = transformedPoints[i];
        const Point& p2 = transformedPoints[(i + 1) % transformedPoints.size()];
        SDL_RenderDrawLine(renderer, static_cast<int>(p1.x), static_cast<int>(p1.y), static_cast<int>(p2.x), static_cast<int>(p2.y));
    }
}

int main(int argc, char* argv[]) {

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (!init(&window, &renderer, WINDOW_WIDTH, WINDOW_HEIGHT)) {
        std::cout << "Failed to initialize" << std::endl;
        return 1;
    }
    
    const int sides = atoi(argv[1]);
    const float radius = atof(argv[2]);
    std::vector<Point> polygon = createPolygon(sides, radius);
    
    Point center(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    float scale = 1.0f;
    float rotation = 0.0f;
    float distance = 2.0f;

    bool rotate = false;
    bool scaleUp = false;
    bool scaleDown = false;

    bool movingInSquarePath = false;
    int squarePathStep = 0;
    float squarePathSpeed = 2.0f;

    bool running = true;
    SDL_Event event;
    
    while (running) {

        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT) {

                running = false;

            } else if (event.type == SDL_KEYDOWN) {

                switch (event.key.keysym.sym) {
                    case SDLK_RETURN:
                        rotate = !rotate;
                        break;
                    case SDLK_RSHIFT:
                        scaleUp = true;
                        break;
                    case SDLK_RCTRL: 
                        scaleDown = true;
                        break;
                    case SDLK_RALT: 
                        movingInSquarePath = true;
                        break;
                }

            } else if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_RSHIFT: 
                        scaleUp = false; 
                        break;
                    case SDLK_RCTRL: 
                        scaleDown = false;
                        break;
                    case SDLK_RALT: 
                        movingInSquarePath = false; 
                        break;
                }
            }

        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

        if (!movingInSquarePath) {
            if (currentKeyStates[SDL_SCANCODE_UP]) { 
                center.y = std::max(0.0f, center.y - distance); 
            }

            if (currentKeyStates[SDL_SCANCODE_DOWN]) {
                center.y = std::min(static_cast<float>(WINDOW_HEIGHT), center.y + distance);
            }

            if (currentKeyStates[SDL_SCANCODE_LEFT]) {
                center.x = std::max(0.0f, center.x - distance);
            }

            if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
                center.x = std::min(static_cast<float>(WINDOW_WIDTH), center.x + distance);
            }
        }

        if (movingInSquarePath) {
            switch (squarePathStep) {
                case 0: // Вправо
                    if (center.x + distance < WINDOW_WIDTH / 2 - radius) {
                        // std::cout << "I'm right" << std::endl;
                        center.x += squarePathSpeed;
                    } else {
                        squarePathStep = 1; // Поворот вниз
                    }
                    break;
                case 1: // Вниз
                    if (center.y + distance < WINDOW_HEIGHT / 2 - radius) {
                        center.y += squarePathSpeed;
                    } else {
                        squarePathStep = 2; // Поворот влево
                    }
                    break;
                case 2: // Влево
                    if (center.x - distance > radius + WINDOW_WIDTH / 2) {
                        // std::cout << "I'm left" << std::endl;
                        center.x -= squarePathSpeed;
                    } else {
                        squarePathStep = 3; // Поворот вверх
                    }
                    break;
                case 3: // Вверх
                    if (center.y - distance > radius + WINDOW_HEIGHT / 2) {
                        center.y -= squarePathSpeed;
                    } else {
                        squarePathStep = 0; // Возврат к движению вправо
                    }
                    break;
            }
        }

        if (rotate) {
            rotation += 0.01f;
        }

        if (scaleUp) {
            scale += 0.1f;
        }

        if (scaleDown) {
            scale = std::max(0.1f, scale - 0.1f);
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        drawPolygon(renderer, polygon, scale, rotation, center);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    close(window, renderer);

    return 0;
}