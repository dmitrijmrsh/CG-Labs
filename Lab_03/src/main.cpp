#include "/home/dmitriimrsh/Projects/Labs/CG-Labs/Lab_03/src/headers/camera.hpp"
#include "/home/dmitriimrsh/Projects/Labs/CG-Labs/Lab_03/src/headers/cube.hpp"

#include <iostream>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main() {
    sf::Window window(
        sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
        "Lab_03",
        sf::Style::Default,
        sf::ContextSettings(24, 8, 4)
    );
    
    window.setVerticalSyncEnabled(true);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);

    Camera camera;
    Cube cube;

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        camera.handleCommands(&window);
        cube.handleCommands(camera.getCameraPointing());

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        camera.update();

        cube.drawCube();
        cube.drawEdges();

        window.display();
    }

    return 0;
}