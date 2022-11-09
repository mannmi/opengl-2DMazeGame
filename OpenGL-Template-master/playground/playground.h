#ifndef PLAYGROUND_H
#define PLAYGROUND_H

// Include GLEW
#include <GL/glew.h>
#include <vector>
#include "glm/vec2.hpp"

//some global variables for handling the vertex buffer
GLuint vertexbuffer;
GLuint vertexbufferChar;
GLuint VertexArrayID;
GLuint VertexArrayID2;
GLuint vertexbuffer_size;
GLuint vertexbufferChar_size;

//GLfloat g_vertex_buffer_data_char;

//program ID of the shaders, required for handling the shaders with OpenGL
GLuint programID;

GLfloat *g_vertex_buffer_data;

float curr_x;
float curr_y;
float rotation;

float currLine_x;
float currLine_y;
float rotationLine;


float rotationWall;
float wallLength;
float wallwith;

std::vector<glm::vec2> VerticeMap;

glm::vec2 lineVertice1;
glm::vec2 LineVertice2;

//GLfloat * g_vertex_buffer_data;


int main(void); //<<< main function, called at startup
void updateAnimationLoop(); //<<< updates the animation loop
bool initializeWindow(); //<<< initializes the window using GLFW and GLEW
bool initializeVertexbuffer(); //<<< initializes the vertex buffer array and binds it OpenGL
//GLfloat initializeVertexbufferChar(const GLfloat); //<<< initializes the vertex buffer array and binds it OpenGL
bool cleanupVertexbuffer(); //<<< frees all recources from the vertex buffer
bool closeWindow(); //<<< Closes the OpenGL window and terminates GLFW
//bool initializeVertexbufferChar(const GLfloat g_vertex_buffer_data[]) {

//void initializeVertexbufferChar(GLfloat &g_vertex_buffer_data[]);

#endif
