// sous mac 
// >g++ -I/u/usr/local/include/ -lglfw -lGLEW main3.cpp -framework OpenGL  -omain3 
// >./main3

// sous linux 	
// >g++ -I/usr/local/include/ -I/public/ig/glm/ -c main3.cpp  -omain3.o
// >g++ -I/usr/local main3.o -lglfw  -lGLEW  -lGL  -omain3
// >./main3

// Inclut les en-têtes standards
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#include <stdlib.h>
#include <string.h>



#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
using namespace glm;

const int N = 40;


GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open()){
		std::string Line = "";
		while(getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}else{
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::string Line = "";
		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;


	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}



	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}



	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

int main(){
	ifstream myfile;

	myfile.open("data.txt");
	int N;
	myfile >> N;
    // Initialise GLFW
	if( !glfwInit() )
	{
	    fprintf( stderr, "Failed to initialize GLFW\n" );
	    return -1;
	}
GLfloat g_vertex_buffer_data[9*N];

GLfloat g_vertex_color_data[9*N];

    //g_vertex_buffer_data = malloc(sizeof(GLfloat)*N*3);
	
	
	float angles[N];
	float sumAngle;
	for (int i = 0; i < N; i ++){.
		myfile >> angles[i];
		sumAngle += angles[i];
	}
	float angleThen = 0;
	float angleNow = 0;
    for (int i=0; i<N; i++){
       	float r = 1;
		cout<< angles[i] <<endl;
		angleNow +=  2* M_PI * angles[i]/sumAngle;
		
	    g_vertex_buffer_data[0+i*9] = 0.0;
		g_vertex_buffer_data[1+i*9] = 0.0;
		g_vertex_buffer_data[2+i*9] = 0.0;

		g_vertex_buffer_data[3+i*9] = 0.0+r*cos((angleThen));
		g_vertex_buffer_data[4+i*9] = 0.0+r*sin((angleThen));
		g_vertex_buffer_data[5+i*9] = 0.0;

		g_vertex_buffer_data[6+i*9] = 0.0+r*cos((angleNow));
		g_vertex_buffer_data[7+i*9] = 0.0+r*sin((angleNow));
		g_vertex_buffer_data[8+i*9] = 0.0;

		g_vertex_color_data[0+i*9] = 0.0;
		g_vertex_color_data[1+i*9] = 0.0;
		g_vertex_color_data[2+i*9] = 1.0;

		g_vertex_color_data[3+i*9] = 0.5;
		g_vertex_color_data[4+i*9] = 0.0;
		g_vertex_color_data[5+i*9] = 0.0;

		g_vertex_color_data[6+i*9] = 1.0;
		g_vertex_color_data[7+i*9] = 0.0;
		g_vertex_color_data[8+i*9] = 0.0;
		angleThen = angleNow;
    }


	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // On veut OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Pour rendre MacOS heureux ; ne devrait pas être nécessaire
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // On ne veut pas l'ancien OpenGL

	// Ouvre une fenêtre et crée son contexte OpenGl
	GLFWwindow* window; // (Dans le code source qui accompagne, cette variable est globale)
	window = glfwCreateWindow( 1024, 768, "Tutorial 01", NULL, NULL);
	if( window == NULL ){
	    fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
	    glfwTerminate();
	    return -1;
	}

	glfwMakeContextCurrent(window); // Initialise GLEW
	glewExperimental=true; // Nécessaire dans le profil de base
	if (glewInit() != GLEW_OK) {
	    fprintf(stderr, "Failed to initialize GLEW\n");
	    return -1;
	}

    // modern OpenGL do not have a default VAO anymore. Even if we don't want to use it
	// we have a create and bind one before playing with buffers ! 
    GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// This will identify our vertex buffer
	GLuint vertexbuffer;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);

	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	  // Only allocqte memory. Do not send yet our vertices to OpenGL.
	  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data)+sizeof(g_vertex_color_data), 0, GL_STATIC_DRAW);

      // send vertices in the first part of the buffer
	  glBufferSubData(GL_ARRAY_BUFFER, 0,                            sizeof(g_vertex_buffer_data), g_vertex_buffer_data);

	  // send vertices in the second part of the buffer
	  glBufferSubData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), sizeof(g_vertex_color_data), g_vertex_color_data);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	// Assure que l'on peut capturer la touche d'échappement enfoncée ci-dessous
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	GLuint programID = LoadShaders( "SimpleVertexShader3.vertexshader", "SimpleFragmentShader3.fragmentshader" );

	do{
		// clear before every draw 1
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use our shader
		glUseProgram(programID); 

	    // 1rst attribute buffer : vertices
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
		   0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		   3,                  // size
		   GL_FLOAT,           // type
		   GL_FALSE,           // normalized?
		   0,                  // stride
		   (void*)0            // array buffer offset
		);
		glEnableVertexAttribArray(0);

        glVertexAttribPointer( // same thing for the colors
        	1, 
        	3, 
        	GL_FLOAT, 
        	GL_FALSE, 
        	0, 
        	(void*)sizeof(g_vertex_buffer_data));
		glEnableVertexAttribArray(1);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, sizeof(g_vertex_buffer_data)/(3*sizeof(float))); // Starting from vertex 0; 3xN vertices total -> N triangles

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

	    // Swap buffers
	    glfwSwapBuffers(window);
	    glfwPollEvents();

	    // apres avoir recupere les evenements, on teste si la touche E est pressee et si c'est le cas
	    // on re-genere des donnees
	    if (glfwGetKey(window, GLFW_KEY_E ) == GLFW_PRESS){
	    	//g_vertex_buffer_data = malloc(sizeof(GLfloat)*N*3);
		    for (int i=0; i<N; i++){
		       float r = (rand()%1000)/1000.0; 

			    g_vertex_buffer_data[0+i*9] = 0.0;
				g_vertex_buffer_data[1+i*9] = 0.0;
				g_vertex_buffer_data[2+i*9] = 0.0;

				g_vertex_buffer_data[3+i*9] = 0.0+r*cos((2*i+0)*M_PI/(N));
				g_vertex_buffer_data[4+i*9] = 0.0+r*sin((2*i+0)*M_PI/(N));
				g_vertex_buffer_data[5+i*9] = 0.0;

				g_vertex_buffer_data[6+i*9] = 0.0+r*cos((2*i+2)*M_PI/(N));
				g_vertex_buffer_data[7+i*9] = 0.0+r*sin((2*i+2)*M_PI/(N));
				g_vertex_buffer_data[8+i*9] = 0.0;
		    }
		    // ici on n'envoie que les sommets car on souhaite garder les memes couleurs ... et le nombre
		    // n'a pas change !
	    	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	    	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(g_vertex_buffer_data), g_vertex_buffer_data);
	        glBindBuffer(GL_ARRAY_BUFFER, 0);
	    }
	    

	} // Vérifie si on a appuyé sur la touche échap (ESC) ou si la fenêtre a été fermée
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
	glfwWindowShouldClose(window) == 0 );
}