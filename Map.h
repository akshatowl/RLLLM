
#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <GL/glut.h>
#include "bits/stdc++.h"
#include <vector>


class Map
{
    public:

    int width;
    int height;
    int goalX;
    int goalY;
    
    std::vector<std::vector<int>> grid;

    Map(int w, int h);

    void addObstacle(int x, int y);
    void removeObstacle(int x, int y);

    bool isValid(int x, int y);
    bool isFree(int x, int y);
    void setGoal(int x, int y);
    void display() const;
    void render(); 

    int getWidth() const
    {
        return width;
    }  
    int getHeight() const
    {
        return height;
    }
};

#endif

