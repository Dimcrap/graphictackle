#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>





class Shader
{

    void  checkCompileErrors(unsigned int shader,std::string type);
public:
    unsigned int ID;

    Shader(const char * vertexPath, const char * fregPath);

    void use();

    void setBool(const std::string &name, bool value)const;
    void setInt(const std::string &name,int value)const;
    void setFloat(const std::string &name,float value)const;
    void setMat2(const std::string &name,const glm::mat2 &mat)const;
    void setMat3(const std::string & name, const glm::mat3 &mat)const;
    void setMat4(const std::string & name, const glm::mat4 &mat)const;

};



#endif