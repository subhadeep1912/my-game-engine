#include "Graphics.hpp"
#include "Shaders.h"
#include "Window.h"
#include <cmath>
#include "glm/vec2.hpp"
#include "MainGUI.h"
#include "Camera.h"
#include "PerlinNoise.h"

//glm::vec3(4.83672, 2.35652, -12.0177)
Camera* c = new Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -80.0f, -10.0f);

const char* vertexShaderSource = "src/Graphics/shaders/temp_1.glsl";
const char* fragShaderSource = "src/Graphics/shaders/temp_1_frag.glsl";
const char* fragShaderSource1 = "src/Graphics/shaders/temp_2.glsl";
const char* fragShaderSource2 = "src/Graphics/shaders/try_1.glsl";

// const float brh = 5.0f;

float vertices1[] = {
    -0.5f, 0.0f, 0.0f,  //0
    -0.5f, 0.0f, 1.0f, //1
    0.5f, 0.0f, 0.0f, //2
     //3
};

// int indices[] = {
//     0, 1, 2,
// };

float* vertices;



bool firstMouse = true;
double lastX = 400, lastY = 300;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
  
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;
    c->ProcessMouseMovement(xoffset, yoffset);
}

void framebuff_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0 ,width, height);
}

void processInputs(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
    std::vector<float> vertices;

    PerlinNoise pn(237);
    int var = 100;
    for(float i=0.0f;i<var;i += 1.0f)
    {
        for(float j=0.0f;j<var;j+=1.0f)
        {   
            float n = pn.noise(j, i, 0.8);
            vertices.push_back(j);
            vertices.push_back(fabs(sin(j)));
            // std::cout<<fabs(sin(i+j))<<"\n";
            vertices.push_back(i);
            
        }
     
    }
    std::vector<float> br;
    for(int i =0;i<var;i++)
    {
        float lon = i*M_PI*2/var;
        for(int j=0;j<var;j++)
        {
            float lat = j*M_PI/var;
            float x = sin(lon)*cos(lat);
            float y = sin(lon)*sin(lat);
            float z =  cos(lon);
            br.push_back(x);
            br.push_back(y);
            br.push_back(z);
            std::cout<<x<<" "<<y<<" "<<z<<"\n";
        }
    }
    float* br1 = &br1[0];
    
    std::vector<int> indices;

    
    for(int j=0;j<var;j++)
    {
        for(int i=0;i<var;i++)
        {   
            if(i==var-1 || j==var-1)
                break;
            indices.push_back(var*j+i);
            indices.push_back(var*(j+1)+i);
            indices.push_back(var*(j+1)+i+1);

            indices.push_back(var*j+i);
            indices.push_back(var*(j+1)+i+1);
            indices.push_back(var*j+i+1);
        }
    }
    int* indices1 = &indices[0];


    float* vertices2 = &vertices[0];


    Window* winObj = new Window();
    GLFWwindow* window = winObj->GiveWindow();

    

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr<<"Glad Didnt load"<<std::endl;
        return -2;
    }

    glViewport(0, 0 ,WIDTH, HEIGHT);
    
     
    glfwSetFramebufferSizeCallback(window, framebuff_size_callback);
     
    Shader *s2 = new Shader(vertexShaderSource, fragShaderSource1);
    unsigned int shaderPro2 = s2->MakeProgram();

    Shader *lightShader = new Shader(vertexShaderSource, fragShaderSource);
    unsigned int lightShade = lightShader->MakeProgram();

    GLuint VAO2;

    glGenVertexArrays(1, &VAO2);
    glBindVertexArray(VAO2);

    Buffers b1(br1, 3, sizeof(float), (var-1)*(var-1)*6, 0, sizeof(int), indices.size(), indices1);

    glBindVertexArray(0);

    GLuint lineVao;

    glGenBuffers(1, &lineVao);
    glBindVertexArray(lineVao);
    Buffers b2();
      
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    
    glm::vec3 direction;


    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    // Setup Platform/Renderer bindings

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    bool called = false;
    
    glEnable(GL_PROGRAM_POINT_SIZE);
    glPointSize(100.0f);
    while(!glfwWindowShouldClose(window))
    {
        // io.AddMouseButtonEvent(0, true);
        // io.AddMousePosEvent(lastX, lastY);
        // std::cout<<io.WantCaptureMouse<<"\n";
        // if(!io.WantCaptureMouse){
            if(glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS){
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                glfwSetCursorPosCallback(window, mouse_callback);
                // std::cout<<"alt pressed"<<"\n"; 
                called = false;
            }
            if(glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_RELEASE){
                glfwGetCursorPos(window, &lastX, &lastY);
                
                if(glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_RELEASE && !called){
                    // std::cout<<"alt released"<<"\n";
                    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                    glfwSetCursorPosCallback(window, 0); 
                    called=true;
                }
            }
        // }

        // glfwSetCursorPosCallback(window, 0);

        processInputs(window);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        

        
        // The Plane starts here
        glUseProgram(shaderPro2);
        glm::mat4 view;
        view = c->GetViewMatrix();


        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        s2->ModUniform4fv(shaderPro2, "view", view);
        s2->ModUniform4fv(shaderPro2, "projection", projection);
        glm::vec3 lightCol(1.0f, 1.0f, 0.0f);
        glm::vec3 toyColor(1.0f, 0.5f, 0.31f);
        glm::vec3 result = lightCol * toyColor;

        s2->ModUniform4f(shaderPro2, "ourColor", result.x, result.y, result.z, 1.0);
        glBindVertexArray(VAO2);
        // const float divinv = 1/brh;

        glm::mat4 model = glm::mat4(1.0f);
        s2->ModUniform4fv(shaderPro2, "model", model);

        glDrawElements(GL_TRIANGLES,(var-1)*(var-1)*6, GL_UNSIGNED_INT, 0);

        
        // Imgui camera coordinates showing
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Camera Coords");
        // ImGui::SetWindowPos(ImVec2(5,5));
        ImGui::SetWindowSize(ImVec2(0,0));
        ImGui::Text("Position: (%f, %f, %f)", c->Position.x, c->Position.y, c->Position.z);
        ImGui::Text("Right: (%f, %f, %f)", c->Right.x, c->Right.y, c->Right.z);
        ImGui::Text("Up: (%f, %f, %f)", c->Up.x, c->Up.y, c->Up.z);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        // Inputs start from here
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame; 


        if (glfwGetKey(window, GLFW_KEY_W))
            c->ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S))
            c->ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A))
            c->ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D))
            c->ProcessKeyboard(RIGHT, deltaTime);
        if ( glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        // if(glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE)   
        //     glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            

        glfwPollEvents();
        glfwSwapBuffers(window);

    }
    
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    
    delete s2;
    glfwTerminate();
    return 0;
}