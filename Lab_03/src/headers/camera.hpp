#pragma once

#include <SFML/Window.hpp>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

class Camera {

    private:
        glm::vec3 cameraPos;
        glm::vec3 cameraFront;
        glm::vec3 cameraUp;
        GLfloat cameraSpeed;
   
    public:
        Camera();

        void handleCommands(sf::Window* window);
        void update();

        glm::vec3 getCameraPointing();

        ~Camera() = default;

};