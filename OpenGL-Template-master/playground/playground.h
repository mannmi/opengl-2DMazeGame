#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include "RenderingObject.h"
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
void generateMazeData();

void createVertext();
//void initializeVertexbufferChar(GLfloat &g_vertex_buffer_data[]);

void initializeVertexbuffer(std::vector<glm::vec3> &verticies);



void SetVertices(std::vector<glm::vec3> vertrcies);

//new Added
//added from Prof
RenderingObject ground;
RenderingObject bunny;
RenderingObject objective;

std::vector<glm::vec3> mapVericies;
std::vector<glm::vec3> playerVerticies;
std::vector<glm::vec3> boxVerticies;
glm::vec4 collor = glm::vec4(0.5, 0.0, 0.0, 1.0);


bool initVectormap();
bool initVectorChar();

bool newinitializeVertexbuffer();

bool vectorUppdate();

glm::vec3 context;
//glm::vec4 objective;

void initVectorObjective();

float pointtemp_xBox;
float pointtemp_yBox;

bool getCordinates(float x = curr_x, float y=curr_y);

int getConntext();

int curent_x_Cordinate;
int curent_y_Cordinate;
float clamp(float value, float min, float max);

glm::vec3 colisionWall;
glm::vec3 colisionWall2;
glm::vec3 colisionWall3;

float getLargest(float,float,float);
float getSmal(float,float,float);

bool collisionDetection();

int wallCount=0;

std::vector<glm::vec3> vecBack;


#endif
