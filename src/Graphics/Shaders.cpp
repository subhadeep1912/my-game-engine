#include "Shaders.h"

std::string readFile(const char *filePath) {
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    if(!fileStream.is_open()) {
        std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while(!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

Shader::Shader(const char* vertShadeSrc, const char* fragShadeSrc)
{
    std::string vertTemp = readFile(vertShadeSrc);
    std::string fragTemp = readFile(fragShadeSrc);
    const char* vertShadSrc = vertTemp.c_str();
    const char* fragShadSrc = fragTemp.c_str();

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, (const GLchar**)&vertShadSrc, NULL);
    glCompileShader(vertexShader);
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, (const GLchar**)&fragShadSrc, NULL);
    glCompileShader(fragShader);
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    
    if(!success)
    {
        glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }    

}

unsigned int Shader::MakeProgram()
{
    shaderPro = glCreateProgram();
    glAttachShader(shaderPro, vertexShader);
    glAttachShader(shaderPro, fragShader);

    glLinkProgram(shaderPro);
    return shaderPro;
}

Shader::~Shader()
{
    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);
}


void Shader::ModUniform1f(GLuint shaderPro, const char* name, float val)
{
    int vertexColorLocation = glGetUniformLocation(shaderPro, name);

    glUniform1f(vertexColorLocation, val);

}

void Shader::ModUniform4f(GLuint shaderPro, const char* name, float valx, float valy, float valz, float vala)
{
    int vertexColorLocation = glGetUniformLocation(shaderPro, name);

    glUniform4f(vertexColorLocation, valx, valy, valz, vala);

}

void Shader::ModUniform4fv(GLuint shaderPro, const char* name, glm::mat4 trans)
{
    int vertexColorLocation = glGetUniformLocation(shaderPro, name);

    glUniformMatrix4fv(vertexColorLocation, 1, GL_FALSE, glm::value_ptr(trans));

}

