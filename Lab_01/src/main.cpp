#include "/home/dmitriimrsh/Projects/Labs/CG-Labs/Lab_01/src/headers/SDL_functions.hpp"
#include "/home/dmitriimrsh/Projects/Labs/CG-Labs/Lab_01/src/headers/Point.hpp"

#include <cstdlib>
#include <cmath>
#include <vector>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

std::vector<Point> createPolygon(int sides, float radius) {
    std::vector<Point> points;

    for (int i = 0; i < sides; ++i) {
        float angle = 2.0f * M_PI * i / sides;
        points.emplace_back(radius * cos(angle), radius * sin(angle));
    }

    return points;
}

void drawPolygon(SDL_Renderer* renderer, const std::vector<Point>& points, float scale, float rotation, Point offset) {
    std::vector<Point> transformedPoints;

    for (const auto& p : points) {
        Point rotated = Point::rotatePoint(p, rotation);
        transformedPoints.emplace_back(rotated.getX() * scale + offset.getX(), rotated.getY() * scale + offset.getY());
    }

    for (size_t i = 0; i < transformedPoints.size(); ++i) {
        Point& p1 = transformedPoints[i];
        Point& p2 = transformedPoints[(i + 1) % transformedPoints.size()];

        SDL_RenderDrawLine(
            renderer, 
            static_cast<int>(p1.getX()), 
            static_cast<int>(p1.getY()), 
            static_cast<int>(p2.getX()),
            static_cast<int>(p2.getY())
        );
    }
}

int main(int argc, char* argv[]) {
    SDL_Window* window;
    SDL_Renderer* renderer;

    if (!init(&window, &renderer, WINDOW_WIDTH, WINDOW_HEIGHT)) {
        std::cout << "Failed to initialize" << std::endl;
        return 1;
    }
    
    const int sides = atoi(argv[1]);
    const float radius = atof(argv[2]);

    std::vector<Point> polygon = createPolygon(sides, radius);
    
    Point center(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    float currentRadius = radius;

    float scale = 1.0f;
    float rotation = 0.0f;
    float distance = 2.0f;
    float scaleChangeFor = 0.1f;

    bool rotate = false;
    bool scaleUp = false;
    bool scaleDown = false;

    Point startOfClosedPath;
    bool movingClosedPath = false;
    int closedPathState = 0;
    float closedPathWidth;
    float closedPathHeight;
    float closedPathDistance = 2.0f;

    bool running = true;
    SDL_Event event;
    
    while (running) {

        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT) {

                running = false;

            } else if (event.type == SDL_KEYDOWN) {

                switch (event.key.keysym.sym) {
                    case SDLK_RSHIFT:
                        scaleUp = true;
                        break;
                    case SDLK_RCTRL: 
                        scaleDown = true;
                        break;
                }

            } else if (event.type == SDL_KEYUP) {

                switch (event.key.keysym.sym) {
                    case SDLK_RETURN:
                        rotate = !rotate;
                        break;
                    case SDLK_RALT: 
                        movingClosedPath = !movingClosedPath;

                        if (movingClosedPath == true) {
                            startOfClosedPath.setX(center.getX());
                            startOfClosedPath.setY(center.getY());
                            closedPathWidth = WINDOW_WIDTH - center.getX();
                            closedPathHeight = WINDOW_HEIGHT - center.getY();
                        }

                        break;
                    case SDLK_RSHIFT: 
                        scaleUp = false; 
                        break;
                    case SDLK_RCTRL: 
                        scaleDown = false;
                        break;
                }

            }

        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);

        if (currentKeyStates[SDL_SCANCODE_UP] && center.getY() - distance - currentRadius >= 0.0f) { 
            center.setY( center.getY() - distance);
            movingClosedPath = false;
        }

        if (currentKeyStates[SDL_SCANCODE_DOWN] && center.getY() + distance + currentRadius <= WINDOW_HEIGHT) {
            center.setY(center.getY() + distance);
            movingClosedPath = false;
        }

        if (currentKeyStates[SDL_SCANCODE_LEFT] && center.getX() - distance - currentRadius >= 0.0f) {
            center.setX(center.getX() - distance);
            movingClosedPath = false;
        }

        if (currentKeyStates[SDL_SCANCODE_RIGHT] && center.getX() + distance + currentRadius <= WINDOW_WIDTH) {
            center.setX(center.getX() + distance);
            movingClosedPath = false;
        }

        if (movingClosedPath) {
            switch (closedPathState) {
                case 0:
                    if (center.getX() + closedPathDistance + currentRadius < startOfClosedPath.getX() + closedPathWidth) {
                        center.setX(center.getX() + closedPathDistance);
                    } else {
                        closedPathState = 1;
                    }
                    break;
                case 1:
                    if (center.getY() + closedPathDistance + currentRadius < startOfClosedPath.getY() + closedPathHeight) {
                        center.setY(center.getY() + closedPathDistance);
                    } else {
                        closedPathState = 2;
                    }
                    break;
                case 2:
                    if (center.getX() - closedPathDistance >  startOfClosedPath.getX()) {
                        center.setX(center.getX() - closedPathDistance);
                    } else {
                        closedPathState = 3;
                    }
                    break;
                case 3:
                    if (center.getY() - closedPathDistance > startOfClosedPath.getY()) {
                        center.setY(center.getY() - closedPathDistance);   
                    } else {
                        closedPathState = 0;
                    }
                    break;
            }
        }

        if (rotate) {
            rotation += 0.01f;
        }

        if (scaleUp) {
            if (
                center.getX() + radius * (scale + scaleChangeFor) <= WINDOW_WIDTH
                && center.getX() - radius * (scale + scaleChangeFor) >= 0.0f
                && center.getY() + radius * (scale + scaleChangeFor) <= WINDOW_HEIGHT
                && center.getY() - radius * (scale + scaleChangeFor) >= 0.0f
            ) {
                scale += 0.1f;
                currentRadius = radius * scale;
            }
        }

        if (scaleDown) {
            scale = std::max(0.1f, scale - 0.1f);
            currentRadius = radius * scale;
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