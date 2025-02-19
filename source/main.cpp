#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <iostream>

#include "texture.hpp"
#include "common.hpp"
#include "control.hpp"
#include "render.hpp"

MouseData mouseData;
CameraData cameraData;
CubeTextureData cubeTextureData;

void
InitGame()
{
    // Mouse Init
    mouseData.buttonNumber = 0;
    mouseData.isPressed = false;
    mouseData.mousePos.x = 0;
    mouseData.mousePos.y = 0;

    // Camera Init
    cameraData.pos.x = 0;
    cameraData.pos.y = 0;
    cameraData.pos.z = -7;

    cameraData.rotation.x = 0;
    cameraData.rotation.y = 0;
    cameraData.rotation.z = 0;
    cameraData.angle = 0;

    // Cube Texture Load;
    cubeTextureData.face1 = LoadTexture("../Data/skate.bmp", 1024, 1024);
    cubeTextureData.face2 = LoadTexture("../Data/cat.bmp", 1024, 1024);
    cubeTextureData.face3 = LoadTexture("../Data/brick.bmp", 1024, 1024);
    cubeTextureData.face4 = LoadTexture("../Data/ceramic.bmp", 1024, 1024);
    cubeTextureData.face5 = LoadTexture("../Data/tiles.bmp", 1024, 1024);
    cubeTextureData.face6 = LoadTexture("../Data/metal.bmp", 1024, 1024);

    InitRender(&cameraData, &cubeTextureData);
    InitControl(&mouseData);
}

int
main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(2450, 100);
    glutCreateWindow("Koeboes");

    InitGame();    

    glutDisplayFunc(RenderDisplay);
    glutReshapeFunc(ReshapeDisplay);
    glutMouseFunc(MouseButtonEventHandler);
    glutMotionFunc(MouseDragEventHandler);
    glutPassiveMotionFunc(MouseMoveEventHandler);

    glutTimerFunc(16, BlitDisplay, 0);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
    glClearDepth(1.0f);

    glEnable(GL_MULTISAMPLE);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);   
    glDepthFunc(GL_LEQUAL);    
    glShadeModel(GL_SMOOTH);   
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  

    glLoadIdentity();

    glutMainLoop();

    return 0;
}