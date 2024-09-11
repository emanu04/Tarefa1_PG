/* Hello Triangle - código adaptado de https://learnopengl.com/#!Getting-started/Hello-Triangle 
 *
 * Adaptado por Rossana Baptista Queiroz
 * para a disciplina de Processamento Gráfico - Unisinos
 * Versão inicial: 7/4/2017
 * Última atualização em 13/08/2024
 *
 */


#include <cmath>  //adicionei pra usar funções matemáticas
#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

// GLAD
#include <glad/glad.h>

// GLFW
#include <GLFW/glfw3.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int setupShader();
int setupGeometry();

const GLuint WIDTH = 800, HEIGHT = 600;

const GLchar* vertexShaderSource = "#version 400\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";

const GLchar* fragmentShaderSource = "#version 400\n"
"uniform vec4 inputColor;\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = inputColor;\n"
"}\n\0";

// Função MAIN
int main()
{
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Ola Triangulo! -- Emanu :D", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}

	const GLubyte* renderer = glGetString(GL_RENDERER); 
	const GLubyte* version = glGetString(GL_VERSION); 
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	GLuint shaderID = setupShader();

	GLuint VAO = setupGeometry();
	

	GLint colorLoc = glGetUniformLocation(shaderID, "inputColor");
	
	glUseProgram(shaderID);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //cor de fundo
		glClear(GL_COLOR_BUFFER_BIT);

		glLineWidth(10);
		glPointSize(20);

		glBindVertexArray(VAO);

		glUniform4f(colorLoc, 1.0f, 0.0f, 1.0f, 1.0f);


//CODIGO PARA IMPRIMIR A CASA DO EXERCICIO 9 ---------------------------------------------------------------------
	while (!glfwWindowShouldClose(window))
{
    glfwPollEvents();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Cor de fundo
    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(10);
    glPointSize(20);

    glBindVertexArray(VAO);

    //telhado
    glUniform4f(colorLoc, 1.0f, 0.0f, 0.0f, 1.0f); //vermelho
    glDrawArrays(GL_TRIANGLES, 0, 3);

    //quadrado
    glUniform4f(colorLoc, 0.0f, 0.0f, 1.0f, 1.0f); //azul
    glDrawArrays(GL_TRIANGLE_STRIP, 3, 4);

    //porta
    glUniform4f(colorLoc, 0.5f, 0.25f, 0.0f, 1.0f); //marrom
    glDrawArrays(GL_TRIANGLE_STRIP, 7, 4);

    //janela
    glUniform4f(colorLoc, 1.0f, 1.0f, 0.0f, 1.0f); //amarelo
    glDrawArrays(GL_TRIANGLE_STRIP, 11, 4);

    //piso
    glUniform4f(colorLoc, 0.8f, 0.5f, 0.2f, 1.0f); //laranja
    glDrawArrays(GL_LINES, 15, 2);

    glBindVertexArray(0);

    glfwSwapBuffers(window);
}
//FIM DO CODIGO DO DESNEHO DA CASA-----------------------------------------------------------------------------

	//-------------------------------------------------------------------------------------------
	//INICIO DA ATIVIDADE 1
	//const int numVertices = 6;
	//CODIGO PARA 2 TRIANGULOS INTEIROS (5)
	/*
		glDrawArrays(GL_TRIANGLES, 0, 6);
	
		//CODIGO PARA SOMENTE CONTORNO
	    glLineWidth(3.0f); //espessura do contorno
    	glUniform4f(colorLoc, 0.0f, 1.0f, 0.0f, 1.0f); // Cor do contorno (verde)
		glDrawArrays(GL_LINE_LOOP, 0, 3);	
		glDrawArrays(GL_LINE_LOOP, 3, 3);

		//CODIGO PARA DESENHO COM PONTOS
		glDrawArrays(GL_POINTS, 0, 6);
	*/

	//CODIGO PARA CIRCULO (6)
	//glDrawArrays(GL_TRIANGLE_FAN, 0, 100);  // Alterado para desenhar o círculo, 100 vértices

	//CODIGO PARA O PACMAN
	//glDrawArrays(GL_TRIANGLE_FAN, 0, numVertices); 

	//CODIGO PARA O PENTAGONO
	//glDrawArrays(GL_TRIANGLE_FAN, 0, 7);  // Desenha o pentágono completo com 7 vértices (inclui o centro e o último para fechar)

	//FATIA DE PIZZA
	//glDrawArrays(GL_TRIANGLE_FAN, 0, numVertices);	

	//ESPIRAL
	//glDrawArrays(GL_LINE_STRIP, 0, numVertices);


	//--------------------------------------------------------------------------------------------
		glBindVertexArray(0); 

		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &VAO);
	glfwTerminate();
	return 0;
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}


int setupShader()
{
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

//ATIVIDADE 1 (outra parte do código)
//--------------------------------------------------------------------------------------------------
#ifndef M_PI
#define M_PI 3.14159265358979323846 
#endif
// CIRCULO
/*
int setupGeometry()
{
    const int numVertices = 100;  
    GLfloat vertices[numVertices * 3];  //array para armazenar os vértices (x, y, z)

    float angleStep = 2.0f * M_PI / (numVertices - 2);  // tamanho que gera cada vertice
    float radius = 0.5f;  //raio

    //meio do circulo
    vertices[0] = 0.0f;
    vertices[1] = 0.0f;
    vertices[2] = 0.0f;

    //demais vertices para gerar o circulo
    for (int i = 1; i < numVertices; ++i) {
        float angle = (i - 1) * angleStep;
        vertices[i * 3] = radius * cos(angle);    // X
        vertices[i * 3 + 1] = radius * sin(angle);  // Y
        vertices[i * 3 + 2] = 0.0f;              // Z
    }
*/

//PACMAN (Esse era pra ser meu pentagono mas ele acabou parecendo um pacman então usei)
/*
int setupGeometry()
{
    const int numVertices = 6;  // 5 vértices do pentágono + 1 central

    GLfloat vertices[numVertices * 3]; 

    float angleStep = 2.0f * M_PI / 5.0f;  //angulo entre os vertices
    float radius = 0.5f;  //raio

    //meio do pacman
    vertices[0] = 0.0f;
    vertices[1] = 0.0f;
    vertices[2] = 0.0f;

    //vértices do pacman
    for (int i = 1; i < numVertices; ++i) {
        float angle = (i - 1) * angleStep;
        vertices[i * 3] = radius * cos(angle);    // X
        vertices[i * 3 + 1] = radius * sin(angle);  // Y
        vertices[i * 3 + 2] = 0.0f;              // Z
    }
}
*/

//PENTAGONO
/*
int setupGeometry()
{
    const int numVertices = 7;  

    GLfloat vertices[numVertices * 3]; 

    float angleStep = 2.0f * M_PI / 5.0f; 
    float radius = 0.5f; 

    vertices[0] = 0.0f;
    vertices[1] = 0.0f;
    vertices[2] = 0.0f;

    for (int i = 1; i <= 5; ++i) {
        float angle = (i - 1) * angleStep;
        vertices[i * 3] = radius * cos(angle);    // X
        vertices[i * 3 + 1] = radius * sin(angle);  // Y
        vertices[i * 3 + 2] = 0.0f;              // Z
    }
	vertices[18] = radius * cos(0.0f);  // X
    vertices[19] = radius * sin(0.0f);  // Y
    vertices[20] = 0.0f;  
}
*/
//FATIA DE PIZZA
/*
int setupGeometry()
{
    const int numVertices = 10;  

    GLfloat vertices[numVertices * 3];  

    float startAngle = 0.0f;  //começando no angulo 0
    float endAngle = M_PI / 2;  //angulo final da fatia
    float angleStep = (endAngle - startAngle) / (numVertices - 2); 

    float radius = 0.5f;  //raio

    vertices[0] = 0.0f;
    vertices[1] = 0.0f;
    vertices[2] = 0.0f;

    for (int i = 1; i < numVertices; ++i) {
        float angle = startAngle + (i - 1) * angleStep;
        vertices[i * 3] = radius * cos(angle);    // X
        vertices[i * 3 + 1] = radius * sin(angle);  // Y
        vertices[i * 3 + 2] = 0.0f;              // Z
    }
}
*/
//ESPIRAL (Esse tive dificuldade para fazer e acredito que não ficou do jeito que era para ficar)
/*
int setupGeometry()
{
    const int numVertices = 5000;  //tentei aumentar bastante para ficar maior a espiral mas não mudou muito

    GLfloat vertices[numVertices * 3];  

    float angleStep = 0.80f;  
    float initialRadius = 0.01f;  
    float radiusGrowth = 0.10f;  

    for (int i = 0; i < numVertices; ++i) {
        float angle = i * angleStep;  
        float radius = initialRadius + radiusGrowth * i; 
        vertices[i * 3] = radius * cos(angle);    
        vertices[i * 3 + 1] = radius * sin(angle);  
        vertices[i * 3 + 2] = 0.0f;             
}
*/

//EXERCICIO 9 - CASA
int setupGeometry()
{
    GLfloat vertices[] = {
        0.0f,  0.7f, 0.0f,  
        -0.5f, 0.2f, 0.0f,  
         0.5f, 0.2f, 0.0f,  
        
        
        -0.5f, 0.2f, 0.0f,  
         0.5f, 0.2f, 0.0f,  
        -0.5f, -0.5f, 0.0f, 
         0.5f, -0.5f, 0.0f, 

     
        -0.1f, -0.5f, 0.0f, 
         0.1f, -0.5f, 0.0f, 
        -0.1f, -0.2f, 0.0f, 
         0.1f, -0.2f, 0.0f, 
        
        
        -0.3f,  0.0f, 0.0f, 
        -0.1f,  0.0f, 0.0f, 
        -0.3f,  0.2f, 0.0f, 
        -0.1f,  0.2f, 0.0f, 

        -0.6f, -0.5f, 0.0f, 
         0.6f, -0.5f, 0.0f  
    };

	GLuint VBO, VAO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	glBindVertexArray(0); 

	return VAO;

}
