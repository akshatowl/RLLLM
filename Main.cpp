#include "Map.h"
#include "Agent.h"
#include <stdio.h>
#include <GL/glut.h>

Map myMap(50, 50);
Agent agent(&myMap);

void display() 
{
    glClear(GL_COLOR_BUFFER_BIT);
    myMap.render();
    std::cout << "Map Rendered!" << std::endl;
    agent.render();
    std::cout << "Agent Rendered!" << std::endl;
    glutSwapBuffers();
    std::cout << "Swap Buffers Est!" << std::endl;

    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL ERROR: " << gluErrorString(err) << std::endl;
    }
}

void update(int value) {
    agent.step(); // Move using learned Q-values
    glutPostRedisplay(); 
    glutTimerFunc(200, update, 0); // Move every 200ms
}

void handleClose() 
{
    std::cout << "Window is closing... Cleaning up!" << std::endl;
    exit(0);  
}

int main(int argc, char** argv)
{
    
    myMap.addObstacle(3, 3);
    myMap.addObstacle(4, 4);
    myMap.setGoal(9, 9);

    std::cout << "Training agent..." << std::endl;
    agent.train(1000); 
    std::cout << "Training complete!" << std::endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Map Navigation");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 

    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);



    std::cout << "GLUT LOOP STARTS" << std::endl;
    glutMainLoop();
    
    std::cout << "GLUT LOOP EXITS";

    return 0;
}

