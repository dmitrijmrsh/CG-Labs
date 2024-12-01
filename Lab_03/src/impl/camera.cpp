#include "/home/dmitriimrsh/Projects/Labs/CG-Labs/Lab_03/src/headers/camera.hpp"

#include <iostream>

Camera::Camera() {
    this->cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
    this->cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    this->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    this->cameraSpeed = 0.05f;
}

void Camera::handleCommands(sf::Window* window) {
    static bool mouseButtonPressed = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        cameraPos += cameraSpeed * cameraFront;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        cameraPos -= cameraSpeed * cameraFront;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
}

void Camera::update() {
    glm::mat4 viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    glLoadMatrixf(glm::value_ptr(viewMatrix));
}

glm::vec3 Camera::getCameraPointing() {
    return this->cameraPos + this->cameraFront;
}