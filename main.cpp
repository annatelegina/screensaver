//internal includes
#include "common.h"
#include "ShaderProgram.h"

//External dependencies
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <random>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


static const GLsizei WIDTH = 640, HEIGHT = 480; //размеры окна
const float SPEED = 80.0f;

glm::mat4 transform;
glm::vec3 trPos = glm::vec3(0.0f, 0.0f, 0.0f);

float cam_rot = 0.0f;

float deltaTime = 0.0f;	
float lastFrame = 0.0f;
float velocity;
int figure;

int first = 0;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    velocity = SPEED * deltaTime;
    if (key == GLFW_KEY_ESCAPE)
        glfwSetWindowShouldClose(window, GL_TRUE);
    else if ((key == GLFW_KEY_LEFT_SHIFT || key == GLFW_KEY_RIGHT_SHIFT) && action == GLFW_PRESS)
    {
        velocity *= 10.0;
    }
    else if ((key == GLFW_KEY_LEFT_SHIFT || key == GLFW_KEY_RIGHT_SHIFT) && action == GLFW_RELEASE)
    {
        velocity /= 10.0;
    }
    else if (key == GLFW_KEY_W)
    {
	    trPos -= velocity * glm::vec3(0.0,0.0,0.1);
    }
    else if (key == GLFW_KEY_S)
    {
	    trPos += velocity * glm::vec3(0.0,0.0,0.1);
    }
    else if (key == GLFW_KEY_D)
    {
	    trPos += velocity * glm::vec3(0.1,0.0,0.0);
    }
    else if (key == GLFW_KEY_A)
    {
	    trPos -= velocity * glm::vec3(0.1,0.0,0.0);
    }
    else if (key == GLFW_KEY_R)
    {
	    trPos += velocity * glm::vec3(0.0,0.1,0.0);
    }
    else if (key == GLFW_KEY_F)
    {
	    trPos -= velocity * glm::vec3(0.0,0.1,0.0);
    }
    else if (key == GLFW_KEY_Q)
    {
        cam_rot += 1.0 * velocity;
    }
    else if (key == GLFW_KEY_E)
    {
        cam_rot -= 1.0 * velocity;
    }
}

int initGL()
{
	int res = 0;
	//грузим функции opengl через glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		return -1;
	}

	std::cout << "Vendor: "   << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Version: "  << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL: "     << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	return 0;
}

int main(int argc, char** argv)
{
	if(!glfwInit())
    return -1;

	//запрашиваем контекст opengl версии 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); 

  GLFWwindow*  window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL basic sample", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window); 
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	if(initGL() != 0) 
		return -1;
	
  //Reset any OpenGL errors which could be present for some reason
	GLenum gl_error = glGetError();
	while (gl_error != GL_NO_ERROR)
		gl_error = glGetError();


   // glEnable(GL_DEPTH_TEST);
	//создание шейдерной программы из двух файлов с исходниками шейдеров
	//используется класс-обертка ShaderProgram
	std::unordered_map<GLenum, std::string> shaders;
	shaders[GL_VERTEX_SHADER]   = "vertex.glsl";
	shaders[GL_FRAGMENT_SHADER] = "fragment.glsl";
	ShaderProgram program(shaders); GL_CHECK_ERRORS;
	
    std::unordered_map<GLenum, std::string> shaders_2;
	shaders_2[GL_VERTEX_SHADER]   = "vertex_2.glsl";
	shaders_2[GL_FRAGMENT_SHADER] = "fragment_2.glsl";
	ShaderProgram program_2(shaders_2); GL_CHECK_ERRORS;


  glfwSwapInterval(1); 
  
  GLuint g_vertexBufferObject;
  GLuint g_vertexArrayObject;
  
  GLuint g_vertexBufferCube;
  GLuint g_vertexArrayCube; 
  
  GLuint g_vertexBufferQ;
  GLuint g_vertexArrayQ; 
  
  GLuint g_vertexBuffer6;
  GLuint g_vertexArray6; 
    float triangles[] =
    {
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
      0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
      0.0f, +0.5f, 0.0f, 0.5f, 1.0f
    };

    float ver4[] = 
    {
     0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
    
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, 0.0f ,0.0f, 1.0f  
    };
    float ver6[] = { 
        0.0f, 0.0f, 0.0f,
        -0.4f, 0.4f, 0.0f,
        0.4f, 0.4f, 0.0f,
        0.8f, 0.0f, 0.0f,
        0.4f, -0.4f, 0.0f,
        -0.4f, -0.4f, 0.0f,
        -0.8f, 0.0f, 0.0f,
        -0.4f, 0.4f, 0.0f
    };
    float cubeVers[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f, 
    };
    
    glm::vec3 cubePosition[] = {
        glm::vec3( 0.0f,  0.0f,  -0.1f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -1.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( -1.5f,  0.2f, -4.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f),
        glm::vec3(2.3f,  2.0f, -8.5f)
    };
    
    glm::vec3 colours[] = {
        glm::vec3( 0.0f,  0.0f,  1.0f),
        glm::vec3(0.33f, 0.42f, 0.18f),
        glm::vec3(0.6f, 0.1f, 0.5f),
        glm::vec3(0.0f, 1.0f, 0.1f),
        glm::vec3( 0.7f, 0.7f, 0.0f),
        glm::vec3(1.0f,  0.0f, 0.0f),
        glm::vec3( 0.3f, 0.3f, 0.3f),
        glm::vec3( 0.1f,  0.6f, 0.1f),
        glm::vec3( 0.5f,  0.2f, 0.0f),
        glm::vec3(0.3f,  0.6f, 0.5f),
        glm::vec3(0.8f,  0.5f, 0.1f)
    };



    g_vertexBufferObject = 0;
    GLuint vertexLocation = 0; // simple layout, assume have only positions at location = 0

    glGenBuffers(1, &g_vertexBufferObject);                                                        GL_CHECK_ERRORS;
    glBindBuffer(GL_ARRAY_BUFFER, g_vertexBufferObject);                                           GL_CHECK_ERRORS;
    glBufferData(GL_ARRAY_BUFFER, 5*3* sizeof(GLfloat), (GLfloat*)triangles, GL_STATIC_DRAW);     GL_CHECK_ERRORS;
    glGenVertexArrays(1, &g_vertexArrayObject);                                                    GL_CHECK_ERRORS;
    glBindVertexArray(g_vertexArrayObject);                                                        GL_CHECK_ERRORS;
    glBindBuffer(GL_ARRAY_BUFFER, g_vertexBufferObject);                                           GL_CHECK_ERRORS;
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
    
    
    g_vertexBuffer6 = 0;
    glGenBuffers(1, &g_vertexBuffer6);                                                        GL_CHECK_ERRORS;
    glBindBuffer(GL_ARRAY_BUFFER, g_vertexBuffer6);                                           GL_CHECK_ERRORS;
    glBufferData(GL_ARRAY_BUFFER, 3*8* sizeof(GLfloat), (GLfloat*)ver6, GL_STATIC_DRAW);     GL_CHECK_ERRORS;
    glGenVertexArrays(1, &g_vertexArray6);                                                    GL_CHECK_ERRORS;
    glBindVertexArray(g_vertexArray6);                                                        GL_CHECK_ERRORS;
    glBindBuffer(GL_ARRAY_BUFFER, g_vertexBuffer6);                                           GL_CHECK_ERRORS;
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    
    g_vertexBufferQ = 0;
    glGenBuffers(1, &g_vertexBufferQ);                                                        GL_CHECK_ERRORS;
    glBindBuffer(GL_ARRAY_BUFFER, g_vertexBufferQ);                                           GL_CHECK_ERRORS;
    glBufferData(GL_ARRAY_BUFFER, 5*6* sizeof(GLfloat), (GLfloat*)ver4, GL_STATIC_DRAW);     GL_CHECK_ERRORS;
    glGenVertexArrays(1, &g_vertexArrayQ);                                                    GL_CHECK_ERRORS;
    glBindVertexArray(g_vertexArrayQ);                                                        GL_CHECK_ERRORS;
    glBindBuffer(GL_ARRAY_BUFFER, g_vertexBufferQ);                                           GL_CHECK_ERRORS;
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);


    g_vertexBufferCube = 0;
    glGenBuffers(1, &g_vertexBufferCube);  GL_CHECK_ERRORS;
    glBindBuffer(GL_ARRAY_BUFFER, g_vertexBufferCube);                                           GL_CHECK_ERRORS;
    glBufferData(GL_ARRAY_BUFFER, 36*3* sizeof(GLfloat), (GLfloat*)cubeVers, GL_STATIC_DRAW);    GL_CHECK_ERRORS;
    glGenVertexArrays(1, &g_vertexArrayCube);                                                    GL_CHECK_ERRORS;
    glBindVertexArray(g_vertexArrayCube);
    glBindBuffer(GL_ARRAY_BUFFER, g_vertexBufferCube); 
    glEnableVertexAttribArray(vertexLocation);                                                  GL_CHECK_ERRORS;
    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindVertexArray(0);
    
    unsigned int texture1, texture2;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    unsigned char *data = stbi_load("./../space.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width1, height1, nrChannels1;
    data = stbi_load("./../texture.jpg", &width1, &height1, &nrChannels1, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);


	while (!glfwWindowShouldClose(window))
	{
        if (first == 0)
        {
	        float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
            first = 1;
        }
        else if (first == 1)
        {
            deltaTime = (float)glfwGetTime() - lastFrame;
            first = 2;
        }
        
		glfwPollEvents();
		//очищаем экран каждый кадр
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);               GL_CHECK_ERRORS;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); GL_CHECK_ERRORS;

        glViewport  (0, 0, WIDTH, HEIGHT);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (unsigned int i = 0; i < 12; i++)
        {
            glBindTexture(GL_TEXTURE_2D, 0);
            if (i == 0 || i == 1) {
                program.StartUseShader(); GL_CHECK_ERRORS;
             }
            else {
                program_2.StartUseShader(); GL_CHECK_ERRORS;
            }
    
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
       if (i != 0 )
       {
            projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
            view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        }
        if (i == 0 || i == 1) 
        {
            program.SetUniform("projection",projection);
            program.SetUniform("view", view);
        }
        else 
        {
            program_2.SetUniform("projection",projection);
            program_2.SetUniform("view", view);
        }

        if (i == 5 || i == 9) 
            glBindVertexArray(g_vertexArrayCube);
        else if (i == 0 || i == 3 )
            glBindVertexArray(g_vertexArrayQ); 
        else if (i == 10 || i == 11)
            glBindVertexArray(g_vertexArray6); 
        else
            glBindVertexArray(g_vertexArrayObject); 
       
       GL_CHECK_ERRORS;
    
    
            // calculate the model matrix for each object and pass it to shader before drawing
        velocity = SPEED * deltaTime;
        glm::mat4 model = glm::mat4(1.0f);
        if ( i != 0 )
        {
            int k = i % 2;
            glm::vec3 tmp = cubePosition[i-1] - glm::vec3(0.0f, 0.0f, 0.5f);
           if (i != 1)
            {
               if (k == 0)
                {
                    float help = sin((float)glfwGetTime())*2.0f;
                    tmp = tmp - velocity * help * cubePosition[i-1];
                }
                else
                {
                    float help = sin((float)glfwGetTime())*2.0f;
                    tmp = tmp + velocity * help * cubePosition[i-1];
                 }
            }
            else
                tmp = tmp + trPos;
            model = glm::translate(model, tmp);
            float angle;
            if (i != 1)
            {
                angle = 20.0 * 5 * (float) glfwGetTime();
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.5f));
            }
            else
            {
                angle = cam_rot;
                model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 2.0f, 0.0f));
            }
        }
        else {
            glm::vec3 st = glm::vec3(0.0f, 0.0f, 0.0f);
            model = glm::translate(model, st);
            model = glm::scale(model, glm::vec3(2.0, 2.0, 1.0)); 
        }
        if (i ==0 || i == 1)
            program.SetUniform("model", model);
        else
        {
            program_2.SetUniform("model", model);
            //settings of colours for ogjects
            program_2.SetUniform("c", colours[i-1]);
        }
        
        
       if (i == 0) 
       {
            program.SetUniform("t", 1);
            glBindTexture(GL_TEXTURE_2D, texture1);
        }
        else if (i == 1) 
        {
            program.SetUniform("t", 2);
            glBindTexture(GL_TEXTURE_2D, texture2);
        }
        
        if (i == 5 || i == 9)
            glEnable(GL_DEPTH_TEST);
        if (i == 6 || i == 10) {
           glEnable(GL_BLEND);
           glBlendFunc(GL_ONE, GL_ONE);
        }
        if (i == 5 || i == 9) 
           glDrawArrays(GL_TRIANGLES, 0, 36);
        else if (i == 0 || i == 3) 
            glDrawArrays(GL_TRIANGLES, 0, 6);
        else if (i == 10 || i == 11) 
            glDrawArrays(GL_TRIANGLE_FAN, 0, 8);
        else 
            glDrawArrays(GL_TRIANGLES, 0, 3);
            
            
        if (i == 6 || i == 10)
            glDisable(GL_BLEND);
        if (i == 5 || i == 9)
            glDisable(GL_DEPTH_TEST);
    }
        glBindVertexArray(0);
		glfwSwapBuffers(window); 
    }


	glDeleteVertexArrays(1, &g_vertexArrayObject);
  glDeleteBuffers(1,      &g_vertexBufferObject);
  
  glDeleteVertexArrays(1, &g_vertexArray6);
  glDeleteBuffers(1,      &g_vertexBuffer6);
 
  glDeleteVertexArrays(1, &g_vertexArrayQ);
  glDeleteBuffers(1,      &g_vertexBufferQ);
  
  glDeleteVertexArrays(1, &g_vertexArrayCube);
  glDeleteBuffers(1,      &g_vertexBufferCube);
  
	glfwTerminate();
	return 0;
}
