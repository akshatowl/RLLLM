#include "Agent.h"
#include <iostream>

Agent::Agent(Map* env) 
    : environment(env), x(0), y(0), alpha(0.5), gamma(0.9), epsilon(0.5),  
      gen(rd()), randFloat(0.0, 1.0), randAction(0, 3) {
    
    if (!environment) {
        std::cerr << "ERROR: Agent initialized with NULL environment!" << std::endl;
        exit(1);
    }

    int h = env->getHeight(), w = env->getWidth();
    std::cout << "Initializing Q-table of size " << w << "x" << h << std::endl;
    Q.resize(h, std::vector<std::vector<double>>(w, std::vector<double>(4, 0.0)));

    std::cout << "Q-table initialized successfully!" << std::endl;
}


void Agent::reset() {
    x = 0;
    y = 0;
}

bool Agent::move(int dx, int dy) {
    int newX = x + dx;
    int newY = y + dy;
    if (environment->isValid(newX, newY)) {
        x = newX;
        y = newY;
        return true;
    }
    return false;
}

void Agent::train(int episodes) {
    std::cout << "Starting Q-learning training..." << std::endl;

    for (int e = 0; e < episodes; ++e) {
        std::cout << "Episode: " << e + 1 << std::endl;
        reset();
        int currX = x, currY = y;

        int steps = 0;
        while (!(currX == environment->goalX && currY == environment->goalY)) {
            if (steps++ > 500) { 
                std::cerr << "ERROR: Agent stuck at (" << currX << ", " << currY << ") after 500 steps." << std::endl;
                break;
            }

            std::cout << "Agent at: (" << currX << ", " << currY << ")" << std::endl;

            int action;
            if (randFloat(gen) < epsilon) {
                action = randAction(gen);  // Explore
                std::cout << "Exploring: Action " << action << std::endl;
            } else {
                action = std::distance(Q[currY][currX].begin(), 
                                       std::max_element(Q[currY][currX].begin(), Q[currY][currX].end())); // Exploit
                std::cout << "Exploiting: Action " << action << std::endl;
            }

            int dx = (action == 0) - (action == 1);
            int dy = (action == 2) - (action == 3);
            int newX = currX + dx, newY = currY + dy;

            if (environment->isValid(newX, newY)) {
                std::cout << "Moving to: (" << newX << ", " << newY << ")" << std::endl;

                double reward = (newX == environment->goalX && newY == environment->goalY) ? 100 : -1;
                double maxFutureQ = *std::max_element(Q[newY][newX].begin(), Q[newY][newX].end());

                std::cout << "Before Update Q[" << currY << "][" << currX << "][" << action << "] = " 
                          << Q[currY][currX][action] << std::endl;

                Q[currY][currX][action] += alpha * (reward + gamma * maxFutureQ - Q[currY][currX][action]);

                std::cout << "After Update Q[" << currY << "][" << currX << "][" << action << "] = " 
                          << Q[currY][currX][action] << std::endl;

                currX = newX;
                currY = newY;
            } else {
                std::cout << "Invalid move to (" << newX << ", " << newY << ") - Obstacle or boundary!" << std::endl;
            }
        }

        std::cout << "Episode " << e + 1 << " completed!" << std::endl;
    }

    std::cout << "Training completed!" << std::endl;
}



void Agent::step() {
    int action = std::distance(Q[y][x].begin(), std::max_element(Q[y][x].begin(), Q[y][x].end()));
    int dx = (action == 0) - (action == 1);
    int dy = (action == 2) - (action == 3);
    move(dx, dy);
}

void Agent::render() {
    std::cout << "Agent render function called!" << std::endl;
    
    if (!environment) {
        std::cerr << "ERROR: Agent's environment (Map*) is NULL!" << std::endl;
        return;
    }
    std::cout << "Environment Found!"<<std::endl;   
    float cellSize = 2.0f / environment->getWidth();
    std::cout << "Got cellsize!" << std::endl;
    float xpos = -1.0f + x * cellSize;
    float ypos = 1.0f - (y + 1) * cellSize;
    std::cout << "Got all positions!" << std::endl;
    glColor3f(0.0f, 0.0f, 1.0f); // Blue for agent
    glBegin(GL_QUADS);
    std::cout << "Drawing Agent..." << std::endl;
    glVertex2f(xpos, ypos);
    glVertex2f(xpos + cellSize, ypos);
    glVertex2f(xpos + cellSize, ypos + cellSize);
    glVertex2f(xpos, ypos + cellSize);
    glEnd();
    std::cout << "Agent drawing finished!" << std::endl;
}


