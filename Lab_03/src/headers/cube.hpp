#pragma once

#include <SFML/Window.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <vector>

class Cube {

    private:
        std::vector<GLfloat> vertices;
        std::vector<GLuint> indices;
        glm::vec3 center;
        GLfloat angleX;
        GLfloat angleY;
        GLfloat angleZ;

        void rotateAroundPoint(glm::vec3 axis, float angle, glm::vec3 targetPoint);

    public:
        Cube();

        void handleCommands(glm::vec3 targetPoint);

        void drawCube();
        void drawEdges();

        ~Cube() = default;
};