# define  M_PI           3.14159265358979323846f


#include "playground.h"

// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLFW
#include <glfw3.h>

GLFWwindow *window;

// Include GLM
void contiuneAnimatio(GLuint id);

//void initializeVertexbufferChar(const GLfloat g_vertex_buffer_data);

#include <glm/glm.hpp>

using namespace glm;

#include <common/shader.hpp>
#include <bitset>
#include <iostream>

//todo update move bug add latter when fixed
/**struct statusPos {
    //std::bitset<4> status;  // note the std - it's in that namespace
};*/

//statusPos pos;
uint8_t status;
//change vector
glm::vec2 changeVec = glm::vec2(0.0f, 0.0f);
float myRotated = 0;
bool neg = 0;
float rotationTottel = 0.0f;

int main(void) {
    curr_x = 0;
    curr_y = 0;
    rotation = 0;
    status = 0;
    VerticeMap.emplace_back(0.0f, 1.0f);

    //Initialize window
    bool windowInitialized = initializeWindow();
    if (!windowInitialized) return -1;

    //Initialize vertex buffer
    bool vertexbufferInitialized = initializeVertexbuffer();
    if (!vertexbufferInitialized) return -1;

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

    //start animation loop until escape key is pressed
    do {

        updateAnimationLoop();


    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);


    //Cleanup and close window
    cleanupVertexbuffer();
    glDeleteProgram(programID);
    closeWindow();

    return 0;
}


typedef struct Cell {
    //bool is_open;	// may be needed to generate it latter
    bool Door[4]{};   // Contains if there is a Door or not

    Cell() {
        //    is_open = false;
        //North
        Door[0] = false;
        //EAST
        Door[1] = false;
        //SOUTH
        Door[2] = false;
        //WEST
        Door[3] = false;
    }
} Cell;

Cell map[4][4];
static Cell *cell;


void generateMazeData() {

    map[0][1].Door[0] = true;
    map[0][1].Door[1] = true;
    map[0][1].Door[2] = true;
    map[0][1].Door[3] = true;

    map[0][2].Door[0] = true;
    map[0][2].Door[1] = true;
    map[0][2].Door[2] = true;
    map[0][2].Door[3] = true;

    map[0][3].Door[0] = true;
    map[0][3].Door[1] = true;
    map[0][3].Door[2] = true;
    map[0][3].Door[3] = true;

    map[0][0].Door[0] = true;
    map[0][0].Door[1] = true;
    map[0][0].Door[2] = true;
    map[0][0].Door[3] = true;

    map[1][0].Door[0] = true;
    map[1][0].Door[1] = true;
    map[1][0].Door[2] = true;
    map[1][0].Door[3] = true;

    map[1][1].Door[0] = true;
    map[1][1].Door[1] = true;
    map[1][1].Door[2] = true;
    map[1][1].Door[3] = true;

    map[1][2].Door[0] = true;
    map[1][2].Door[1] = true;
    map[1][2].Door[2] = true;
    map[1][2].Door[3] = true;

    map[1][3].Door[0] = true;
    map[1][3].Door[1] = true;
    map[1][3].Door[2] = true;
    map[1][3].Door[3] = true;

    map[2][0].Door[0] = true;
    map[2][0].Door[1] = true;
    map[2][0].Door[2] = true;
    map[2][0].Door[3] = true;

    map[2][1].Door[0] = true;
    map[2][1].Door[1] = true;
    map[2][1].Door[2] = true;
    map[2][1].Door[3] = true;

    map[2][2].Door[0] = true;
    map[2][2].Door[1] = true;
    map[2][2].Door[2] = true;
    map[2][2].Door[3] = true;

    map[2][3].Door[0] = true;
    map[2][3].Door[1] = true;
    map[2][3].Door[2] = true;
    map[2][3].Door[3] = true;

    map[3][0].Door[0] = true;
    map[3][0].Door[1] = true;
    map[3][0].Door[2] = true;
    map[3][0].Door[3] = true;

    map[3][1].Door[0] = true;
    map[3][1].Door[1] = true;
    map[3][1].Door[2] = true;
    map[3][1].Door[3] = true;

    map[3][2].Door[0] = true;
    map[3][2].Door[1] = true;
    map[3][2].Door[2] = true;
    map[3][2].Door[3] = true;

    map[3][3].Door[0] = true;
    map[3][3].Door[1] = true;
    map[3][3].Door[2] = true;
    map[3][3].Door[3] = true;

}


/**added to test draw*/
void updateAnimationLoop() {
    vertexbufferChar_size = 0;
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Use our shader
    glUseProgram(programID);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindVertexArray(vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    //glBindBuffer(GL_ARRAY_BUFFER, vertexbufferChar);



    /*glGenBuffers(1, &vertexbufferTest[2]);
    glGenBuffers(1, &vertexbufferTest[2]);*/
    glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void *) 0            // array buffer offset
    );


    /*Draw the triangle !*/
    glDrawArrays(GL_TRIANGLES, 0, vertexbuffer_size); // 3 indices starting at 0 -> 1 triangle
    //2nd attribute buffer : vertices*/
    //glDrawArrays(GL_LINE, 0, vertexbufferChar_size); // 3 indices starting at 0 -> 1 triangle





    //glDisableVertexAttribArray(0);
    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
    initializeVertexbuffer();


}

static glm::mat2 myR = glm::mat2(cos(0.00f) - 0.9f, -sin(0.00f),
                                 sin(0.00f), cos(0.00f) - 0.9f);

static glm::mat2 myRLine;

static bool rotationChange = true;
static int rotationStatus = true;

static glm::vec2 myT = glm::vec2(0.0f, 0.0f);


void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        neg = false;
        rotation = fmod(rotation + 45, 360);
        rotationChange = true;
        if (status == 6) {
            status = -1;
        } else {
            status++;
        }
        printf("%s%d%s", "Status ", status, "  \n");
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {

        rotation = fmod(rotation - 45, 360);
        neg = false;
        rotationChange = true;
        if (status == 0)
            status = 7;
        else {
            status--;
        }
        printf("%s%d%s", "Status ", status, "  \n");
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        /**what is the current rotation state**/
        if (status % 2 == 0) {
            switch (status) {
                case 0:
                    changeVec[1] += 0.1f;
                    //changeVec = glm::vec2(0.1f, 0.0f);
                    std::cout << "up" << std::endl;
                    break;
                case 2:
                    //changeVec[0] += 0.1f;
                    changeVec[1] += 0.1f;
                    //                  changeVec = glm::vec2(0.0f, 0.1f);
                    std::cout << "right" << std::endl;

                    break;
                case 4:
                    changeVec[1] += 0.1f;
                    //changeVec[0] += 0.1f;
                    //                changeVec = glm::vec2(-0.1f, 0.0f);
                    std::cout << "botom" << std::endl;

                    break;
                case 6:
                    //changeVec[0] += -0.1f;
                    changeVec[1] += 0.1f;
                    //               changeVec = glm::vec2(0.0f, 0.1f);
                    std::cout << "left" << std::endl;

                    break;
                    //changeVec[0] += -0.1f;

                default:
                    exit(123);
                    break;

            }
            rotationChange = true;

        } else
            exit(12);

    }
    //std::cout << "status " << status << std::endl;
}

bool initializeWindow() {
    // Initialise GLFW
    //static GLfloat g_vertex_buffer_data_char[sizeof map * 2 * 4];
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
        return false;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(1024, 768, "Tutorial 02 - Red triangle", NULL, NULL);
    glfwSetKeyCallback(window, key_callback);

    if (window == NULL) {
        fprintf(stderr,
                "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
        getchar();
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return false;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    return true;
}


bool initializeVertexbuffer() {
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    if (rotationChange) {
        rotationChange = false;

        static int rotationLevel = 0;

        glm::vec2 triangleVertice1 = glm::vec2(-0.25f, -0.25f);
        glm::vec2 triangleVertice2 = glm::vec2(0.25f, -0.25f);
        glm::vec2 triangleVertice3 = glm::vec2(0.0f, 0.25f);

        float loc_myR = rotation / 180.0f * M_PI;
        myR = glm::mat2(cos(loc_myR), -sin(loc_myR),
                        sin(loc_myR), cos(loc_myR));

        curr_x += (myR * changeVec)[0];
        curr_y += (myR * changeVec)[1];


        glDrawArrays(GL_TRIANGLES, 0, 6 * (1 - 1));

        myT = glm::vec2(curr_x, curr_y);

        std::cout << "change " << changeVec[0] << " change2 " << changeVec[1] << std::endl;

        triangleVertice1 = myR * triangleVertice1 + myT;
        triangleVertice2 = myR * triangleVertice2 + myT;
        triangleVertice3 = myR * triangleVertice3 + myT;


        myR = glm::mat2(1, 0,
                        0, 1);

        // amoung of wall * ammoung of walls * vetricies needed per block
        int size = 3 + (sizeof map * 4 * (9 * 2));
        vertexbuffer_size = 3 + (sizeof map * 3 * 4);
        GLfloat g_vertex_buffer_data[size];

        /*triangleVertice1[0], triangleVertice1[1], 0.0f,
        triangleVertice2[0], triangleVertice2[1], 0.0f,
        triangleVertice3[0], triangleVertice3[1], 0.0f,*/

        g_vertex_buffer_data[0] = triangleVertice1[0];
        g_vertex_buffer_data[1] = triangleVertice1[1];
        g_vertex_buffer_data[2] = 0.0f;
        g_vertex_buffer_data[3] = triangleVertice2[0];
        g_vertex_buffer_data[4] = triangleVertice2[1];
        g_vertex_buffer_data[5] = 0.0f;
        g_vertex_buffer_data[6] = triangleVertice3[0];
        g_vertex_buffer_data[7] = triangleVertice3[1];
        g_vertex_buffer_data[8] = 0.0f;

        //second triangle
        g_vertex_buffer_data[9] = -0.5f;
        g_vertex_buffer_data[10] = 0.5f;
        g_vertex_buffer_data[11] = 0.0f;
        g_vertex_buffer_data[12] = 0.5f;
        g_vertex_buffer_data[13] = 0.5f;
        g_vertex_buffer_data[14] = 0.0f;
        g_vertex_buffer_data[15] = 0.5f;
        g_vertex_buffer_data[16] = -0.5f;
        g_vertex_buffer_data[17] = 0.0f;

        //initializeVertexbufferChar(g_vertex_buffer_data);

        /*todo move out*/

        /*for (int i = 0; i < sizeof map; i++) {
            for (int j = 0; j < sizeof map[i]; j++) {
                if (map[i][j].Door[0]) {
                    rotationWall = 0;
                }
                if (map[i][j].Door[1]) {
                    rotationWall = 1;
                }
                if (map[i][j].Door[2]) {
                    rotationWall = 0.45;
                }
                if (map[i][j].Door[3]) {
                    rotationWall = 0.45;
                }
                curr_y = (wallLength * (float) i);
                curr_x = (wallLength * (float) j);

                myT = glm::vec2(curr_x, curr_y);

                vertexbufferChar_size = +2;
                lineVertice1 = VerticeMap[0];


                float loc_myRLine = rotationWall / 180.0f * M_PI;

                myRLine = glm::mat2(cos(loc_myRLine), -sin(loc_myRLine),
                                    sin(loc_myRLine), cos(loc_myRLine));
                lineVertice1 = myRLine * lineVertice1 + myT;


                g_vertex_buffer_data[(i * 2) + j] = lineVertice1[0];
                g_vertex_buffer_data[(i * 2) + j + 1] = lineVertice1[1];
            }
        }*/


        glGenBuffers(1, &vertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

        changeVec[0] = 0;
        changeVec[1] = 0;

        return true;
    }


    return true;

}

/*void initializeVertexbufferChar(GLfloat &g_vertex_buffer_data[]) {

}*/

/*GLfloat initializeVertexbufferChar(GLfloat g_vertex_buffer_data[]) {
    for (int i = 0; i < sizeof map; i++) {
        for (int j = 0; j < sizeof map[i]; j++) {
            if (map[i][j].Door[0]) {
                rotationWall = 0;
            }
            if (map[i][j].Door[1]) {
                rotationWall = 1;
            }
            if (map[i][j].Door[2]) {
                rotationWall = 0.45;
            }
            if (map[i][j].Door[3]) {
                rotationWall = 0.45;
            }
            curr_y = (wallLength * (float) i);
            curr_x = (wallLength * (float) j);

            myT = glm::vec2(curr_x, curr_y);

            vertexbufferChar_size = +2;
            lineVertice1 = VerticeMap[0];


            float loc_myRLine = rotationWall / 180.0f * M_PI;

            myRLine = glm::mat2(cos(loc_myRLine), -sin(loc_myRLine),
                                sin(loc_myRLine), cos(loc_myRLine));
            lineVertice1 = myRLine * lineVertice1 + myT;


            g_vertex_buffer_data[(i * 2) + j] = lineVertice1[0];
            g_vertex_buffer_data[(i * 2) + j + 1] = lineVertice1[1];
        }
    }

    return true;

}*/


void contiuneAnimatio(GLuint id) {
    glm::mat2 model_matrix(2.0f);
    glBindVertexArray(id);

}

bool cleanupVertexbuffer() {
    // Cleanup VBO
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteVertexArrays(1, &VertexArrayID);
    return true;
}

bool closeWindow() {
    glfwTerminate();
    return true;
}