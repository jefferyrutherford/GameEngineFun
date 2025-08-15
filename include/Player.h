#pragma once

class Player {
public:
    float x, y;
    unsigned int VAO, VBO;
    float width, height;
    float speed;

    Player(float startX, float startY, float width, float height, float speed);
    void draw();
    void move(float dx, float dy);
};
