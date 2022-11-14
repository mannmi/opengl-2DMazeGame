#define  M_PI           3.14159265358979323846f


#include "playground.h"
#include "RenderingObject.h"

// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLFW
#include <glfw3.h>

GLFWwindow *window;

// Include GLM
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

int main(void) {
    generateMazeData();
    curr_x = 0;
    curr_y = 0;
    rotation = 0;
    status = 0;
    VerticeMap.emplace_back(0.0f, 1.0f);

    //Initialize window
    bool windowInitialized = initializeWindow();
    if (!windowInitialized) return -1;

    //Initialize vertex buffer
    bool vertexbufferInitialized = newinitializeVertexbuffer();
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

void generateMazeData() {

    /*topwall
            rigth
    left
            botom*/

    map[0][0].Door[0] = true;
    map[0][0].Door[1] = true;
    map[0][0].Door[2] = true;
    map[0][0].Door[3] = false;

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



    map[1][0].Door[0] = false;
    map[1][0].Door[1] = false;
    map[1][0].Door[2] = true;
    map[1][0].Door[3] = true;

    map[1][1].Door[0] = true;
    map[1][1].Door[1] = false;
    map[1][1].Door[2] = false;
    map[1][1].Door[3] = true;

    map[1][2].Door[0] = true;
    map[1][2].Door[1] = true;
    map[1][2].Door[2] = false;
    map[1][2].Door[3] = false;

    map[1][3].Door[0] = true;
    map[1][3].Door[1] = true;
    map[1][3].Door[2] = true;
    map[1][3].Door[3] = true;

    map[2][0].Door[0] = true;
    map[2][0].Door[1] = true;
    map[2][0].Door[2] = true;
    map[2][0].Door[3] = true;

    map[2][1].Door[0] = true;
    map[2][1].Door[1] = false;
    map[2][1].Door[2] = true;
    map[2][1].Door[3] = false;

    map[2][2].Door[0] = false;
    map[2][2].Door[1] = true;
    map[2][2].Door[2] = false;
    map[2][2].Door[3] = true;

    map[2][3].Door[0] = true;
    map[2][3].Door[1] = true;
    map[2][3].Door[2] = true;
    map[2][3].Door[3] = true;

    map[3][0].Door[0] = true;
    map[3][0].Door[1] = true;
    map[3][0].Door[2] = true;
    map[3][0].Door[3] = true;

    map[3][1].Door[0] = false;
    map[3][1].Door[1] = false;
    map[3][1].Door[2] = true;
    map[3][1].Door[3] = true;

    map[3][2].Door[0] = true;
    map[3][2].Door[1] = false;
    map[3][2].Door[2] = false;
    map[3][2].Door[3] = true;

    map[3][3].Door[0] = true;
    map[3][3].Door[1] = true;
    map[3][3].Door[2] = false;
    map[3][3].Door[3] = true;
}


/**added to test draw*/
void updateAnimationLoop() {


    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use our shader
    glUseProgram(programID);


    initVectorChar();
    ground.DrawObject();
    //ground.DrawObject();
    bunny.SetVertices(playerVerticies);
    bunny.DrawObject();

    glfwSwapBuffers(window);
    glfwPollEvents();
}

static glm::mat2 myR = glm::mat2(cos(0.00f) - 0.99f, -sin(0.00f),
                                 sin(0.00f), cos(0.00f) - 0.99f);

static glm::mat2 myRLine;

static bool rotationChange = true;
static int rotationStatus = true;

static glm::vec2 myT = glm::vec2(0.0f, 0.0f);
static glm::vec2 myTLine = glm::vec2(0.0f, 0.0f);


void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
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
    window = glfwCreateWindow(1024, 768, "Maze Runner", NULL, NULL);
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

bool newinitializeVertexbuffer() {
    ground = RenderingObject();
    ground.InitializeVAO();

    //create vertex data
    initVectormap();
    ground.SetVertices(mapVericies);

    //create normal data
    std::vector<glm::vec3> normals = std::vector<glm::vec3>();
    normals.emplace_back(1.0f);
    normals.emplace_back(0.5f);
    normals.emplace_back(0.9f);
    ground.computeVertexNormalsOfTriangles(mapVericies, normals);
    //ground.SetNormals(normals);
    //glBufferSubData();


    //create texture data
    /*ground.textureSamplerID = glGetUniformLocation(programID, "myTextureSampler");
    float scaling = 5.0f;
    std::vector<glm::vec2> uvbufferdata;
    uvbufferdata.push_back({0.0f, 0.0f});
    uvbufferdata.push_back({0.0f, scaling});
    uvbufferdata.push_back({scaling, scaling});
    uvbufferdata.push_back({0.0f, 0.0f});
    uvbufferdata.push_back({scaling, scaling});
    uvbufferdata.push_back({scaling, 0.0f});
    */
    //####################### SECOND OBJECT: BUNNY ###################
    bunny = RenderingObject();
    bunny.InitializeVAO();
    /*initVectorChar();*/
    bunny.SetVertices(playerVerticies);
    /*bunny.DrawObject();*/

    return true;
}

bool initVectormap() {

    static bool inital = true;
    float localRotation = 0.0f;


    if (inital) {
        /*
         * variable decleration
         */

        int sizeOfArr = sizeof(map) / sizeof(map[0]);
        int sizeOfArrY = sizeOfArr = sizeof(map[0]) / sizeof(map[0]->Door);;

        float x_offsetVal = (2.0f / (float) sizeOfArr);
        float y_offsetVal = (2.0f / (float) sizeOfArrY);
        float point1_x = -1;
        float point1_y = 1;
        float pointtemp_x = 0.0f;
        float pointtemp_y = 0.0f;
        float x_tempOffsetVal = 0.0f;
        float y_tempOffsetVal = 0.0f;

        inital = false;
        static int rotationLevel = 0;
        const glm::vec2 triangleVerticeLine1 = glm::vec2(-0.25f, -0.01f);
        const glm::vec2 triangleVerticeLine2 = glm::vec2(x_offsetVal - 0.25f, -0.01f);
        //const glm::vec2 triangleVerticeLine2 = glm::vec2(0.25f, -0.01f);
        const glm::vec2 triangleVerticeLine3 = glm::vec2(-0.25f, 0.01f);

        glm::vec2 localtriangleVerticeLine1 = triangleVerticeLine1;
        glm::vec2 localtriangleVerticeLine2 = triangleVerticeLine2;
        glm::vec2 localtriangleVerticeLine3 = triangleVerticeLine3;

        glm::vec2 changeVecLine = glm::vec2(point1_x, point1_y);

        std::cout << "sizeOfArr  " << sizeOfArrY << std::endl;
        for (int i = 0; i < sizeOfArr; i++) {
            for (int j = 0; j < sizeOfArrY; j++) {
                for (int dor = 0; dor < 4; dor++) {
                    bool state=false;

                    pointtemp_x = 0.0f;
                    pointtemp_y = 0.0f;
                    x_tempOffsetVal = 0.0f;
                    y_tempOffsetVal = 0.0f;

                    localtriangleVerticeLine1 = triangleVerticeLine1;
                    localtriangleVerticeLine2 = triangleVerticeLine2;
                    localtriangleVerticeLine3 = triangleVerticeLine3;
                    //topwall
                    if (dor == 0 && map[i][j].Door[0]) {
                        localRotation = fmod(0, 360);
                        x_tempOffsetVal = 0.0f + (x_offsetVal / 2);
                        y_tempOffsetVal = 0.0f;
                        state=true;
                    }
                    //right
                    if (dor == 1 && map[i][j].Door[1]) {
                        localRotation = fmod(90, 360);
                        //localRotation = fmod(0, 360);
                        x_tempOffsetVal = 0.0f + x_offsetVal;
                        y_tempOffsetVal = 0.0f - (y_offsetVal / 2);
                        //y_tempOffsetVal=0.0f;
                        state=true;
                    }
                    //left
                    if (dor == 2 && map[i][j].Door[2]) {
                        localRotation = fmod(270, 360);
                        //localRotation = fmod(360, 360);
                        x_tempOffsetVal = 0.0f;
                        y_tempOffsetVal = 0.0f - (y_offsetVal / 2);
                        //y_tempOffsetVal=0.0f;
                        state=true;
                    }
                    //bottomwall
                    if (dor == 3 && map[i][j].Door[3]) {
                        localRotation = fmod(180, 360);
                        x_tempOffsetVal = 0.0f + (x_offsetVal / 2);
                        y_tempOffsetVal = 0.0f - y_offsetVal;
                        state=true;
                    }

                    if(state) {
                        pointtemp_x = point1_x + x_tempOffsetVal;
                        //pointtemp_x= point1_x+x_offsetVal;
                        pointtemp_y = point1_y + y_tempOffsetVal;
                        //pointtemp_y = point1_y+y_offsetVal;

                        changeVecLine = glm::vec2(pointtemp_x, pointtemp_y);

                        std::cout << "localRotation " << localRotation;
                        std::cout << "changeVecLine " << changeVecLine[0];
                        std::cout << " " << changeVecLine[1] << std::endl;


                        float loc_myRLine = localRotation / 180.0f * M_PI;

                        /*1st triangl*/
                        myRLine = glm::mat2(cos(loc_myRLine), -sin(loc_myRLine),
                                            sin(loc_myRLine), cos(loc_myRLine));

                        currLine_x = (myRLine * changeVecLine)[0];
                        currLine_y = (myRLine * changeVecLine)[1];

                        //changeVecLine = glm::vec2(pointtemp_x, pointtemp_y);
                        myTLine = glm::vec2(pointtemp_x, pointtemp_y);

                        localtriangleVerticeLine1 = myRLine * localtriangleVerticeLine1 + myTLine;
                        localtriangleVerticeLine2 = myRLine * localtriangleVerticeLine2 + myTLine;
                        localtriangleVerticeLine3 = myRLine * localtriangleVerticeLine3 + myTLine;


                        mapVericies.emplace_back(localtriangleVerticeLine1[0], localtriangleVerticeLine1[1], 0.0f);
                        mapVericies.emplace_back(localtriangleVerticeLine2[0], localtriangleVerticeLine2[1], 0.0f);
                        mapVericies.emplace_back(localtriangleVerticeLine3[0], localtriangleVerticeLine3[1], 0.0f);


                        /*2nd triangl*/

                        loc_myRLine = loc_myRLine + (180 / 180.0f * M_PI);


                        myRLine = glm::mat2(cos(loc_myRLine), -sin(loc_myRLine),
                                            sin(loc_myRLine), cos(loc_myRLine));

                        currLine_x = (myRLine * changeVecLine)[0];
                        currLine_y = (myRLine * changeVecLine)[1];

                        myTLine = glm::vec2(currLine_x, currLine_y);

                        localtriangleVerticeLine1 = myRLine * localtriangleVerticeLine1 + myTLine;
                        localtriangleVerticeLine2 = myRLine * localtriangleVerticeLine2 + myTLine;
                        localtriangleVerticeLine3 = myRLine * localtriangleVerticeLine3 + myTLine;

                        mapVericies.emplace_back(localtriangleVerticeLine1[0], localtriangleVerticeLine1[1], 0.0f);
                        mapVericies.emplace_back(localtriangleVerticeLine2[0], localtriangleVerticeLine2[1], 0.0f);
                        mapVericies.emplace_back(localtriangleVerticeLine3[0], localtriangleVerticeLine3[1], 0.0f);
                        state=false;
                    }
                }
                point1_x += x_offsetVal;
            }

            point1_y -= y_offsetVal;
            point1_x = -1;

        }
    }
}

bool initVectorChar() {

    static bool inital = true;

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


        //glDrawArrays(GL_TRIANGLES, 0, 6 * (1 - 1));

        myT = glm::vec2(curr_x, curr_y);

        std::cout << "change " << changeVec[0] << " change2 " << changeVec[1] << std::endl;
        triangleVertice1 = myR * triangleVertice1 + myT;
        triangleVertice2 = myR * triangleVertice2 + myT;
        triangleVertice3 = myR * triangleVertice3 + myT;

        triangleVertice1 = triangleVertice1 * 0.25f;
        triangleVertice2 = triangleVertice2 * 0.25f;
        triangleVertice3 = triangleVertice3 * 0.25f;


        myR = glm::mat2(1, 0,
                        0, 1);

        if (inital) {
            playerVerticies.emplace_back(triangleVertice1[0], triangleVertice1[1], 0.0f);
            playerVerticies.emplace_back(triangleVertice2[0], triangleVertice2[1], 0.0f);
            playerVerticies.emplace_back(triangleVertice3[0], triangleVertice3[1], 0.0f);
            inital = false;
        } else {
            playerVerticies[0] = (glm::vec3(triangleVertice1[0], triangleVertice1[1], 0.0f));
            playerVerticies[1] = (glm::vec3(triangleVertice2[0], triangleVertice2[1], 0.0f));
            playerVerticies[2] = (glm::vec3(triangleVertice3[0], triangleVertice3[1], 0.0f));
            std::cout << "test playerVerticies";

        }
        changeVec[0] = 0;
        changeVec[1] = 0;

    }
    return true;
}
