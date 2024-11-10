#include "/home/dmitriimrsh/Projects/Labs/CG-Labs/Lab_02/src/headers/Vector3f.hpp"

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/glu.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGTH = 600;

const GLfloat vertices[] = {
    -1.0f, -1.0f, -1.0f,  // 0
     1.0f, -1.0f, -1.0f,  // 1
     1.0f,  1.0f, -1.0f,  // 2
    -1.0f,  1.0f, -1.0f,  // 3
    -1.0f, -1.0f,  1.0f,  // 4
     1.0f, -1.0f,  1.0f,  // 5
     1.0f,  1.0f,  1.0f,  // 6
    -1.0f,  1.0f,  1.0f   // 7
};

const GLuint indices[] = {
    0, 1, 2, 3,  // front
    4, 5, 6, 7,  // back
    0, 1, 5, 4,  // bottom
    2, 3, 7, 6,  // top
    0, 3, 7, 4,  // left
    1, 2, 6, 5   // right
};

const Vector3f normals[] = {
    Vector3f(0.0f, 0.0f, -1.0f), // front
    Vector3f(0.0f, 0.0f, 1.0f),  // back
    Vector3f(0.0f, -1.0f, 0.0f), // bottom
    Vector3f(0.0f, 1.0f, 0.0f),  // top
    Vector3f(-1.0f, 0.0f, 0.0f), // left
    Vector3f(1.0f, 0.0f, 0.0f)   // right
};

const Vector3f edgeCenters[] = {
    Vector3f(0.0f, 0.0f, -1.0f), // front center
    Vector3f(0.0f, 0.0f, 1.0f),  // back center
    Vector3f(0.0f, -1.0f, 0.0f), // bottom center
    Vector3f(0.0f, 1.0f, 0.0f),  // top center
    Vector3f(-1.0f, 0.0f, 0.0f), // left center
    Vector3f(1.0f, 0.0f, 0.0f)   // right center
};

void drawCube() {
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);

    for (int edgeNumber = 0; edgeNumber < 6; ++edgeNumber) {
        const Vector3f& normal = normals[edgeNumber];
        glNormal3f(normal.getX(), normal.getY(), normal.getZ());

        for (int pointNumber = 0; pointNumber < 4; ++pointNumber) {
            int idx = indices[edgeNumber * 4 + pointNumber];
            glVertex3f(vertices[idx * 3 + 0], vertices[idx * 3 + 1], vertices[idx * 3 + 2]);
        }
    }

    glEnd();
}

void drawEdges() {
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

void drawNormals() {
    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_LINES);

    for (int edgeNumber = 0; edgeNumber < 6; ++edgeNumber) {
        const Vector3f& edgeCenter = edgeCenters[edgeNumber];

        glVertex3f(edgeCenter.getX(), edgeCenter.getY(), edgeCenter.getZ());
        glVertex3f(
            edgeCenter.getX() + normals[edgeNumber].getX(),
            edgeCenter.getY() + normals[edgeNumber].getY(),
            edgeCenter.getZ() + normals[edgeNumber].getZ()
        );
    }

    glEnd();
}

void rotateCube(float angleX, float angleY) {
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);
}

int main() {
    sf::Window window(
        sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGTH),
        "Lab_02",
        sf::Style::Default,
        sf::ContextSettings(24, 8, 4)
    );

    window.setVerticalSyncEnabled(true);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 800.0 / 600.0, 1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float angleX = 0.0f, angleY = 0.0f, cubePositionZ = -5.0f;

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            angleY -= 1.0f;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            angleY += 1.0f;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            angleX -= 1.0f;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            angleX += 1.0f;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            cubePositionZ -= 0.1f;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) {
            cubePositionZ += 0.1f;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, cubePositionZ);

        rotateCube(angleX, angleY);

        drawCube();
        drawEdges();
        drawNormals();

        window.display();
    }

    return 0;
}
