// Player.cpp
#include "Player.h"
#include <glad/glad.h>

// Vertex data for a rectangle (will be updated each frame)
float vertices[12]; // 2 triangles, 6 vertices, x/y only

Player::Player(float px, float py, float w, float h, float s)
    : x(px), y(py), width(w), height(h), speed(s)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void Player::move(float dx, float dy) {
    x += dx;
    y += dy;
}

void Player::draw() {
    // Update vertices based on current position
    float verts[] = {
        x, y,
        x + width, y,
        x + width, y + height,
        x, y,
        x + width, y + height,
        x, y + height
    };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
