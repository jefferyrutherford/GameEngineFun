#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Player.h"

// Window dimensions
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Input processing
void processInput(GLFWwindow* window, Player& player) {
    float moveAmount = player.speed * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        player.move(0.0f, moveAmount);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        player.move(0.0f, -moveAmount);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        player.move(-moveAmount, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        player.move(moveAmount, 0.0f);
}

// Shader compilation helpers
unsigned int compileShader(unsigned int type, const char* source) {
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);

    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(id, 512, nullptr, infoLog);
        std::cerr << "Shader compilation error: " << infoLog << "\n";
    }
    return id;
}

unsigned int createShaderProgram(const char* vertexSrc, const char* fragmentSrc) {
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexSrc);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentSrc);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "Shader linking error: " << infoLog << "\n";
    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

bool checkCollistion(Player& a, Player& b) {
    return(
        a.x < b.x + b.width &&
        a.y < b.y + b.height &&
        a.x + a.width > b.x &&
        a.y + a.height > b.y
    );
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // OpenGL version & profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create window
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Game Engine", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Load OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    // Set viewport
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    // Create Player object
    Player player(50.0f, 50.0f, 50.0f, 50.0f, 200.0f); // x, y, width, height, speed
    Player npc(200.0f, 150.0f, 20.0f, 20.0f, 0.0f);
    // Shader sources
    const char* vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec2 aPos;
        void main() {
            float normX = (aPos.x / 400.0) - 1.0;
            float normY = (aPos.y / 300.0) - 1.0;
            gl_Position = vec4(normX, normY, 0.0, 1.0);
        }
    )";

    const char* fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;
        void main() {
            FragColor = vec4(1.0, 0.0, 0.0, 1.0); // red
        }
    )";

    unsigned int shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);
    glUseProgram(shaderProgram);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Timing
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Input
        processInput(window, player);
        
        //ToDo: Handle Collition Check
        if (checkCollistion(player, npc)) {
            std::cout << "Collision!" << std::endl;
            glfwSetWindowShouldClose(window, true);

        }

        // Render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        player.draw();
        npc.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glfwTerminate();
    return 0;
}

