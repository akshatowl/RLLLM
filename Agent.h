#ifndef AGENT_H
#define AGENT_H

#include "map.h"
#include "Agent.h"
#include <vector>
#include <random>

class Agent {

public:
    Map* environment;
    int x, y; 
    std::vector<std::vector<std::vector<double>>> Q; // Q-table
    double alpha, gamma, epsilon; // Learning parameters
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> randFloat;
    std::uniform_int_distribution<> randAction;


    Agent(Map* env);

    void reset(); 
    bool move(int dx, int dy);  
    void render(); 

    void train(int episodes);  // Train using Q-learning
    void step();  // Move based on learned policy
    
    int getX() { return x; }
    int getY() { return y; }
};

#endif
