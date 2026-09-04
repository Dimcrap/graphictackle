#include "include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>
#include <cmath>
#include "shaders.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);  
void processInput(GLFWwindow * window);
void configureglfw();



constexpr float vertices[] = {
    // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
};

constexpr unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
};


unsigned int VBO{0},VAO{0},EBO{0};
int width{},height{},nrChannels;


unsigned int texture;




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


    Shader ourshader("../vertx.rt","../fregment.fs");

    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,
        8*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,
        8*sizeof(float),(void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
            
    glVertexAttribPointer(2,2,GL_FLOAT, GL_FALSE,
         8*sizeof(float),(void*)(6 *sizeof(float)));
    glEnableVertexAttribArray(2);



    unsigned int texture,texture2;
    
    glGenTextures(1,&texture);
    //glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    stbi_set_flip_vertically_on_load(true);
    unsigned char *data= stbi_load("../container.jpg", &width, &height , 
        &nrChannels, 0);
    if(data){
        glTexImage2D(GL_TEXTURE_2D, 0 , GL_RGB , width , height
             , 0 ,GL_RGB, GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else
    {
        std::cout<<"failed to load image\n";
    }
    stbi_image_free(data);
    

    glGenTextures(1,&texture2);
    //glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    data= stbi_load("../awesomeface.png", &width, &height , 
        &nrChannels, 0);
    if(data){
        //GLenum format{(nrChannels==1)?GL_RED:(nrChannels==3)?};
        glTexImage2D(GL_TEXTURE_2D, 0 , GL_RGB , width , height
             , 0 ,GL_RGBA, GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else
    {
        std::cout<<"failed to load image\n";
    }
    
    stbi_image_free(data);


    glm::vec4 vec(1.0f,0.0f,0.0f,1.0f);
    glm::mat4 trans=glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(0.5f,-0.5f,0.0f));
    trans = glm::rotate(trans, (float)glfwGetTime(),
    glm::vec3(0.0f,0.0f,1.0f));

    /*trans = glm::rotate(trans, glm::radians(90.0f),
    glm::vec3(0.0,0.0,1.0));
    trans=glm::scale(trans, glm::vec3(0.5,0.5,0.5));
    std::cout<<vec.x<<vec.y<<vec.z<<std::endl;*/
    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    ourshader.use();
    glUniform1i(glGetUniformLocation(ourshader.ID,"ourTexture"),0);
    ourshader.setInt("ourTexture2", 1);
    unsigned int transformLoc = glGetUniformLocation(ourshader.ID, "transfom");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE,
        glm::value_ptr(trans));

    float visvalue{0.0f};


    while(!glfwWindowShouldClose(window)){

        processInput(window);
        
        glClearColor(0.2f,0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D , texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D , texture2);

        ourshader.use();
        trans = glm::rotate(trans, (float)glfwGetTime(),
    glm::vec3(0.0f,0.0f,1.0f));

        glUniformMatrix4fv(transformLoc, 1, GL_FALSE,
        glm::value_ptr(trans));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES,6 , GL_UNSIGNED_INT  , 0 );
                
         if(glfwGetKey(window, GLFW_KEY_UP)){
            ourshader.setFloat("visibility",  visvalue+=0.08);
            std::cout<<"up key pressed\n";
        }else if(glfwGetKey(window, GLFW_KEY_DOWN)){
            ourshader.setFloat("visibility",   visvalue-=0.08);
            std::cout<<"down key pressed\n";
        }
        //glDrawElements(GL_TRIANGLES, 6 ,GL_UNSIGNED_INT,0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
    

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
