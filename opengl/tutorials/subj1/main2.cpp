
#include "include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>



void framebuffer_size_callback(GLFWwindow* window, int width, int height);  
void processInput(GLFWwindow * window);
void configureglfw();


constexpr float triangles[]{0.25f,-0.5f,0.0f,
                        0.75f,-0.5f,0.0f,
                        0.5f,0.5f,0.0f,
                        /*   second triangle|   */
                        -0.75f,-0.5f,0.0f,
                        -0.25f,-0.5f,0.0f,
                        -0.5f,0.5,0.0f};




unsigned int VBO{0},VAO{0};


const char *vertexShaderSource{"#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0"};
unsigned int vertexShader{0};

const char * fregmentShaderSource{
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0"
};
unsigned int fragmentShader;


int success{0};
char infoLog[512];

unsigned int shaderprogram{0};





int main(){

configureglfw();



GLFWwindow * window = glfwCreateWindow(800,600,"LearningOpenGL",NULL,NULL);
if( window==NULL){
    std::cout<<"failed to create glfw window"<<std::endl;
    glfwTerminate();
    return -1;
}

glfwMakeContextCurrent(window);
glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    std::cout<<"Failed to initialize  GLAD "<<std::endl;
    return -1;
}


    vertexShader =  glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader , 1, &vertexShaderSource  
        ,NULL);
    glCompileShader(vertexShader);
    
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);

    if(!success){
        glGetShaderInfoLog(vertexShader,512,NULL,
            infoLog);
        std::cout<<"ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"<<infoLog;
    }

    fragmentShader=glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,
        &fregmentShaderSource,NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);

    if(!success){
        glGetShaderInfoLog(fragmentShader,512,NULL,
            infoLog);
        std::cout<<"ERROR::SHADER::freagmentShader::COMPILATION_FAILED\n"<<infoLog<<std::endl;
    }

    shaderprogram=glCreateProgram();
    glAttachShader(shaderprogram,vertexShader);
    glAttachShader(shaderprogram,fragmentShader);
    glLinkProgram(shaderprogram);

    glGetProgramiv(shaderprogram,GL_LINK_STATUS, &success);
    
    if(!success){
        glGetProgramInfoLog(shaderprogram,512,NULL,infoLog);
                std::cout<<"ERROR::SHADER::SHADERPROGRAM::COMPILATION_FAILED\n"<<infoLog<<std::endl;
    };  
    

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    
    
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(triangles),
    triangles,GL_STATIC_DRAW);
    
    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE,
         3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);


    //glBindVertexArray(0);

    
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    while(!glfwWindowShouldClose(window)){

        processInput(window);
        
        glClearColor(0.2f,0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shaderprogram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0 ,6);
        //glDrawElements(GL_TRIANGLES, 6 ,GL_UNSIGNED_INT,0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteProgram(shaderprogram);

    glfwTerminate();
        return -1;
}




void configureglfw(){

glfwInit();
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

};


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

void processInput(GLFWwindow * window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window,true);
    }
};
