#include "/home/dmitriimrsh/Projects/Labs/CG-Labs/Lab_03/src/headers/cube.hpp"

#include <iostream>

Cube::Cube() {
    this->vertices = {
        -1.0f, -1.0f, -1.0f,  // 0
        1.0f, -1.0f, -1.0f,  // 1
        1.0f,  1.0f, -1.0f,  // 2
        -1.0f,  1.0f, -1.0f,  // 3
        -1.0f, -1.0f,  1.0f,  // 4
        1.0f, -1.0f,  1.0f,  // 5
        1.0f,  1.0f,  1.0f,  // 6
        -1.0f,  1.0f,  1.0f  // 7
    };

    this->indices = {
        0, 1, 2, 3,  // back
        4, 5, 6, 7,  // front
        0, 1, 5, 4,  // bottom
        2, 3, 7, 6,  // top
        0, 3, 7, 4,  // left
        1, 2, 6, 5   // right
    };

    center = glm::vec3(0.0f, 0.0f, 0.0f);

    angleX = 0.0f;
    angleY = 0.0f;
    angleZ = 0.0f;
}

void Cube::handleCommands(glm::vec3 targetPoint) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
        rotateAroundPoint(glm::vec3(0.0f, 1.0f, 0.0f), 1.0f, center);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
        rotateAroundPoint(glm::vec3(0.0f, 1.0f, 0.0f), -1.0f, center);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
        rotateAroundPoint(glm::vec3(1.0f, 0.0f, 0.0f), -1.0f, center);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
        rotateAroundPoint(glm::vec3(1.0f, 0.0f, 0.0f), 1.0f, center);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
        rotateAroundPoint(glm::vec3(0.0f, 0.0f, 1.0f), -1.0f, center);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
        rotateAroundPoint(glm::vec3(0.0f, 0.0f, 1.0f), 1.0f, center);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        rotateAroundPoint(glm::vec3(0.0f, 1.0f, 0.0f), 1.0f, targetPoint);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        rotateAroundPoint(glm::vec3(0.0f, 1.0f, 0.0f), -1.0f, targetPoint);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        rotateAroundPoint(glm::vec3(1.0f, 0.0f, 0.0f), -1.0f, targetPoint);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        rotateAroundPoint(glm::vec3(1.0f, 0.0f, 0.0f), 1.0f, targetPoint);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
        rotateAroundPoint(glm::vec3(0.0f, 0.0f, 1.0f), -1.0f, targetPoint);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) {
        rotateAroundPoint(glm::vec3(0.0f, 0.0f, 1.0f), 1.0f, targetPoint);
    }
}

void Cube::rotateAroundPoint(glm::vec3 axis, float angle, glm::vec3 targetPoint) {
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);

    for (int edgeNumber = 0; edgeNumber < 6; ++edgeNumber) {
        for (int pointNumber = 0; pointNumber < 4; ++pointNumber) {
            int idx = indices[edgeNumber * 4  + pointNumber];
            glm::vec3 vertex = glm::vec3(vertices[idx * 3 + 0], vertices[idx * 3 + 1], vertices[idx * 3 + 2]);

            vertex -= targetPoint;
            vertex = glm::vec3(rotationMatrix * glm::vec4(vertex, 1.0f));
            vertex += targetPoint;

            vertices[idx * 3 + 0] = vertex.x;
            vertices[idx * 3 + 1] = vertex.y;
            vertices[idx * 3 + 2] = vertex.z;
        }
    }

    glm::vec3 vertex = glm::vec3(center.x, center.y, center.z);

    vertex -= targetPoint;
    vertex = glm::vec3(rotationMatrix * glm::vec4(vertex, 1.0f));
    vertex += targetPoint;

    center.x = vertex.x;
    center.y = vertex.y;
    center.z = center.z;
}

void Cube::drawCube() {
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);

    for (int edgeNumber = 0; edgeNumber < 6; ++edgeNumber) {
        for (int pointNumber = 0; pointNumber < 4; ++pointNumber) {
            int idx = indices[edgeNumber * 4 + pointNumber];
            glVertex3f(vertices[idx * 3 + 0], vertices[idx * 3 + 1], vertices[idx * 3 + 2]);
        }
    }

    glEnd();
}

void Cube::drawEdges() {
    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_LINES);

    for (int edgeNumber = 0; edgeNumber < 6; ++edgeNumber) {
        for (int pointNumber = 0; pointNumber < 4; ++pointNumber) {
            int idx1 = indices[edgeNumber * 4 + pointNumber];
            int idx2 = indices[edgeNumber * 4 + (pointNumber + 1) % 4];

            glVertex3f(vertices[idx1 * 3 + 0], vertices[idx1 * 3 + 1], vertices[idx1 * 3 + 2]);
            glVertex3f(vertices[idx2 * 3 + 0], vertices[idx2 * 3 + 1], vertices[idx2 * 3 + 2]);
        }
    }

    glEnd();
}