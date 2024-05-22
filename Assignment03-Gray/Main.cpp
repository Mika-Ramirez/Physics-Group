#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "P6/MyVector.cpp"
#include "P6/P6Particle.cpp"

#include <chrono>

using namespace std::chrono_literals;
using namespace P6;

constexpr std::chrono::nanoseconds timestep(16ms);

static glm::mat4 WorldProjection;

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    using clock = std::chrono::high_resolution_clock;
    auto curr_time = clock::now();
    auto prev_time = curr_time;
    std::chrono::nanoseconds curr_ns(0);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 800, "Gracielle Ann Jacinto", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Obj */
    std::string path = "3D/sphere.obj";
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> material;
    std::string warning, error;
    tinyobj::attrib_t attributes;

    bool success = tinyobj::LoadObj(
        &attributes,
        &shapes,
        &material,
        &warning,
        &error,
        path.c_str());

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    gladLoadGL();

    /*WorldProjection = glm::ortho(
        -400.f,
        400.f,
        -400.f,
        400.f,
        -400.f,
        400.f
        );*/

    /* Obj */
    /*OpenGLShader defaultShader = OpenGLShader("Shaders/sample.frag", "Shaders/sample.vert");
    OpenGLObject sphere = OpenGLObject("3D/sphere.obj", WorldProjection);
    sphere.AssignShade(defaultShader);
    sphere.Scale = glm::vec3(100, 100, 100);*/

    /* Shaders */
    std::fstream vertSrc("Shaders/sample.vert");
    std::stringstream vertBuff;
    vertBuff << vertSrc.rdbuf();
    std::string vertS = vertBuff.str();
    const char* v = vertS.c_str();

    std::fstream fragSrc("Shaders/sample.frag");
    std::stringstream fragBuff;
    fragBuff << fragSrc.rdbuf();
    std::string fragS = fragBuff.str();
    const char* f = fragS.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &v, NULL);
    glCompileShader(vertexShader);

    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &f, NULL);
    glCompileShader(fragShader);

    GLuint shaderProg = glCreateProgram();
    glAttachShader(shaderProg, vertexShader);
    glAttachShader(shaderProg, fragShader);

    glLinkProgram(shaderProg);

    std::vector<GLuint> mesh_indices;
    for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {
        mesh_indices.push_back(shapes[0].mesh.indices[i].vertex_index);
    }

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glUseProgram(shaderProg);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
        sizeof(GL_FLOAT) * attributes.vertices.size(),
        attributes.vertices.data(),
        GL_STATIC_DRAW);

    glVertexAttribPointer(
        0,
        3, // x y z
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        sizeof(GLuint) * mesh_indices.size(),
        mesh_indices.data(),
        GL_STATIC_DRAW);

    /* Orthographic projection */
    glViewport(0,
        0,
        640,
        640);

    glm::mat4 projection = glm::ortho(-2.f, 2.f,
        -2.f, 2.f,
        -1.f, 1.f);

    /* Identity matrix */
    glm::mat4 view = glm::mat4(1.0f);

    GLint projectionLoc = glGetUniformLocation(shaderProg, "projection");
    GLint viewLoc = glGetUniformLocation(shaderProg, "view");

    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));


    P6::P6Particle particle = P6::P6Particle();
    particle.Velocity = P6::MyVector(100, 0, 0);
    particle.Acceleration = P6::MyVector(0, 10, 0);

    
    while (!glfwWindowShouldClose(window))
    {
        //Get current time
        curr_time = clock::now();
        //Check the duration in between the last iteration
        auto dur = std::chrono::duration_cast<std::chrono::nanoseconds> (curr_time - prev_time);
        //Set the prev with the current for the next iteration
        prev_time = curr_time;

        //Ass he suration since last iteration
        //to the time since our last "frame"
        curr_ns += dur;
        if (curr_ns >= timestep) {
            //Convert ns to ms
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(curr_ns);
            std::cout << "MS: " << (float)ms.count() << "\n";
            //Reset
            curr_ns -= timestep;

            //We call our updates here later
            particle.Update((float)ms.count() / 1000);
        }
        std::cout << "NormalUpdate\n";

        std::cout << "Position: (" << particle.Position.getX() << ", "
            << particle.Position.getY() << ", "
            << particle.Position.getZ() << ")\n";

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        //sphere.Color = glm::vec3(0.4f, 0, 0);
        //sphere.Position = (glm::vec3)particle.Position;
        //sphere.Draw();
        // 
        
        //glm::mat4 model = glm::mat4(1.0f); // Identity matrix
        //model = glm::translate(model, glm::vec3(particle.Position.getX(), particle.Position.getY(), particle.Position.getZ()));
        //
        //// Pass the model matrix to the shader
        //GLint modelLoc = glGetUniformLocation(shaderProg, "model");
        //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES,
            static_cast<GLsizei>(mesh_indices.size()),
            GL_UNSIGNED_INT,
            0);


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents(); //keyboard controls
    }

    /* Clean up */
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}