#include "Map.h"
#include <iostream>

Map* globalMap = nullptr;

Map::Map(int w, int h) : width(w), height(h), grid(h, std::vector<int>(w,0))
{
    goalX = w - 1;
    goalY = h - 1;
}

    
void Map::addObstacle(int x, int y) 
{
    if (isValid(x, y)) 
    {
        grid[y][x] = 1;
    }
}

void Map::removeObstacle(int x, int y) 
{
    if (isValid(x, y)) 
    {
        grid[y][x] = 0;
    }
}


bool Map::isValid(int x, int y)  {
    bool insideBounds = x >= 0 && x < width && y >= 0 && y < height;
    bool isObstacle = (insideBounds && grid[y][x] == 1);

    if (!insideBounds) {
        std::cerr << "Blocked: (" << x << ", " << y << ") is out of bounds!" << std::endl;
    } else if (isObstacle) {
        std::cerr << "Blocked: (" << x << ", " << y << ") is an obstacle!" << std::endl;
    } else {
        std::cout << "Valid Move: (" << x << ", " << y << ")" << std::endl;
    }

    return insideBounds && !isObstacle;
}


void Map::setGoal(int x, int y) 
{
    if (isValid(x, y)) 
    {
        goalX = x;
        goalY = y;
    }
}

bool Map::isFree(int x, int y)  
{
    return isValid(x, y) && grid[y][x] == 0;
}


void Map::display() const {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            std::cout << (grid[i][j] ? "#" : ".") << " ";
        }
        std::cout << "\n";
    }
}

void drawMap() {
    if (!globalMap) return;

    int w = globalMap->width;
    int h = globalMap->height;

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    float cellSize = 2.0f / std::max(w, h); // Scale cells for OpenGL [-1,1] space

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            float xpos = -1.0f + x * cellSize;
            float ypos = 1.0f - (y + 1) * cellSize;

            if (globalMap->grid[y][x] == 1) {
                glColor3f(1.0f, 0.0f, 0.0f); // Red for obstacles
            } else {
                glColor3f(1.0f, 1.0f, 1.0f); // White for free space
            }

            glBegin(GL_QUADS);
            glVertex2f(xpos, ypos);
            glVertex2f(xpos + cellSize, ypos);
            glVertex2f(xpos + cellSize, ypos + cellSize);
            glVertex2f(xpos, ypos + cellSize);
            glEnd();
        }
    }

    glutSwapBuffers();
}

void Map::render() {
    const float cellSize = 2.0f / width;
    glLoadIdentity();

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float xpos = -1.0f + x * cellSize;
            float ypos = 1.0f - (y + 1) * cellSize;

            if (x == goalX && y == goalY) {
                glColor3f(0.0f, 1.0f, 0.0f); // Green for goal
            } else if (grid[y][x] == 1) {
                glColor3f(1.0f, 0.0f, 0.0f); // Red for obstacles
            } else {
                glColor3f(1.0f, 1.0f, 1.0f); // White for free space
            }

            glBegin(GL_QUADS);
            glVertex2f(xpos, ypos);
            glVertex2f(xpos + cellSize, ypos);
            glVertex2f(xpos + cellSize, ypos + cellSize);
            glVertex2f(xpos, ypos + cellSize);
            glEnd();
        }
    }
}

