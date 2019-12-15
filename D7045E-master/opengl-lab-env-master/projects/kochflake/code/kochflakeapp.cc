//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2017 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "kochflakeapp.h"
#include <cstring>
#include <glm.hpp>
#include <vec3.hpp> // glm::vec3
#include <vec4.hpp> // glm::vec4
#include <mat4x4.hpp> // glm::mat4
#include <gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <vector>
#include <iostream>

const GLchar* vs =
"#version 310 es\n"
"precision mediump float;\n"
"layout(location=0) in vec3 pos;\n"
"layout(location=1) in vec4 color;\n"
"layout(location=0) out vec4 Color;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(pos, 1);\n"
"	Color = color;\n"
"}\n";

const GLchar* ps =
"#version 310 es\n"
"precision mediump float;\n"
//"layout(location=0) in vec4 color;\n"
"out vec4 Color;\n"
"void main()\n"
"{\n"
"	Color = vec4(1,0,0,1);\n"
"}\n";

using namespace Display;
namespace Kochflake
{

//------------------------------------------------------------------------------
/**
*/
KochflakeApp::KochflakeApp()
{
	// empty
}

//------------------------------------------------------------------------------
/**
*/
KochflakeApp::~KochflakeApp()
{
	// empty
}

//------------------------------------------------------------------------------
/**
*/


void KochflakeApp::kochCalc(GLint itteration, glm::vec2 a, glm::vec2 b, glm::vec2 base){
	// ax and bx are the x coordinates of a and b respectively, the same is true for ay and by in regard to the y coordinate
	GLfloat ax = a[0];
	GLfloat ay = a[1];

	GLfloat bx = b[0];
	GLfloat by = b[1];

	GLfloat basex = base[0];
	GLfloat basey = base[1];
	
	if (itteration > 0) {
		// calculate the nodes
		// the x and y coordinates are deliminated in the same manner here as for a and b, look there for details.
		// c is a point that exists one third of the way from a to b
		GLfloat cx = (ax*(2.0f/3.0f) + bx*(1.0f/3.0f));
		GLfloat cy = (ay*(2.0f/3.0f) + by*(1.0f/3.0f));

		// e is a point that exists two thirds of the way between a and b
		GLfloat ex = (ax*(1.0f/3.0f) + bx*(2.0f/3.0f));
		GLfloat ey = (ay*(1.0f/3.0f) + by*(2.0f/3.0f));

		glm::vec2 m = glm::vec2((ax + bx)/2.0f, (ay + by)/2.0f);
		// GLfloat md_size = sqrtf( powf((cx - ex), 2.0f) + powf((cy - ey), 2.0f));
		GLfloat ecSize = sqrtf(powf((bx - ex), 2.0f) + powf((by - ey), 2.0f));
		GLfloat mdSize = sqrtf(powf((ecSize), 2.0f) - powf((ecSize/2.0f), 2.0f) );

		GLfloat mx = m[0];
		GLfloat my = m[1];

		glm::vec2 d_direction = m - base;
		d_direction = glm::normalize(d_direction) * mdSize;
		glm::vec2 d = d_direction + m;

		// glm::vec2 d =(glm::normalize(m - a)*(float)(m_to_d)) + m;


		glm::vec2 c = glm::vec2(cx, cy);
		glm::vec2 e = glm::vec2(ex, ey);

		GLfloat newBasex = (ax * 2.0f/3.0f) + (basex * 1.0f/3.0f);
		GLfloat newBasey = (ay * 2.0f/3.0f) + (basey * 1.0f/3.0f);

		glm::vec2 newBase = glm::vec2(newBasex, newBasey);

		kochCalc(itteration-1, a, c, newBase);
		kochCalc(itteration-1, c, d, e);
		kochCalc(itteration-1, d, e, c);

		newBasex = (bx * 2.0f/3.0f) + (basex * 1.0f/3.0f);
		newBasey = (by * 2.0f/3.0f) + (basey * 1.0f/3.0f);
		newBase = glm::vec2(newBasex, newBasey);
		
		KochflakeApp::kochCalc(itteration-1, e, b, newBase);

	}
	else if(itteration == 0) {
		// nothing will be added to data until the final itteration is reached. Then all vertices push back their starting coordinates.
		// As a result the resulting output data will contain all coordinates in order.
		
		// GLfloat z = -1.0f;
		data.push_back(a);

		/*data.push_back(1.0f);
		data.push_back(0.0f);
		data.push_back(0.0f);
		data.push_back(1.0f);
		GLfloat COLOR[] = {1.0f, 0.0f, 0.0f, 1.0f};
		*/
	}
	/*else {
		data.push_back(ax);
		data.push_back(ay);

		return data;
	}*/
}

bool
KochflakeApp::Open() {
	App::Open();
	this->window = new Display::Window;
	this->window->SetSize(800, 800);
	window->SetKeyPressFunction([this](int32, int32, int32, int32){
		this->window->Close();
	});

	// glm::vec3 position0 = glm::vec3(-0.5f, -0.5f, -1);

	// iteration is the number of iterations of the koch-snowflake that will be implemented, the base case, 0, is a triangle
	GLint itteration = 5;

	// assign the buf arrays size to hold the vertices and their color, the number of vertices are (iterations - 1) * 4 and 6 elements are 
	// required to hold information of a vertice and its color. 
	//int verticeCount = 3*pow(4, itteration);
	//int verticeDataSize = verticeCount * 6;


	// the COLOR vector is used to assign the fractals color
	// it uses input (R, G, B, gamma) so 1, 0, 0, 1 is red
	//GLfloat COLOR[] = {1.0f, 0.0f, 0.0f, 1.0f};
	// glm::vec4 COLOR = glm::vec4(1, 0, 0, 1);

	// a, b, and c are the starting edge node coordinates
	// this is the base case for the fractal
	glm::vec2 A = glm::vec2(0.0f/1.5f, 1.0f/1.5f);		
	glm::vec2 B = glm::vec2(-0.866f/1.5f, -0.5f/1.5f);  
	glm::vec2 C = glm::vec2(0.866f/1.5f, -0.5f/1.5f);
	// std::vector<glm::vec2> data;

	data.clear();

	kochCalc(itteration, A, B, C);
	
	kochCalc(itteration, B, C, A);
	
	kochCalc(itteration, C, A, B);
	
/*
	float32 Ax = A[0];
	float32 Ay = A[1];

	data.push_back(Ax);
	data.push_back(Ay);
*/

/*	for (int i = 0; i < 9; i++){
		// data is unloaded from the data vector into buf
		buf[i] = data[i];
		buf[i+1] = data[i];

		buf[i+2] = COLOR [0];
		buf[i+3] = COLOR [1];
		buf[i+4] = COLOR [2];
		buf[i+5] = COLOR [3];
		};
	GLfloat buf[data.size()];
	std::copy(data.begin(), data.end(), buf);
*/	


	if (this->window->Open()) {
		// assigns background color to pale yellow
		glClearColor(0.8f, 1.0f, 0.3f, 1.0f);

		// setup vertex shader
		this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
		GLint length = (GLint)std::strlen(vs);
		glShaderSource(this->vertexShader, 1, &vs, &length);
		glCompileShader(this->vertexShader);

		// get error log
		GLint shaderLogSize;
		glGetShaderiv(this->vertexShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
		if (shaderLogSize > 0) {
			GLchar* buf = new GLchar[shaderLogSize];
			glGetShaderInfoLog(this->vertexShader, shaderLogSize, NULL, buf);
			printf("[SHADER COMPILE ERROR]: %s", buf);
			delete[] buf;
		}

		// setup pixel shader
		this->pixelShader = glCreateShader(GL_FRAGMENT_SHADER);
		length = (GLint)std::strlen(ps);
		glShaderSource(this->pixelShader, 1, &ps, &length);
		glCompileShader(this->pixelShader);

		// get error log
		shaderLogSize;
		glGetShaderiv(this->pixelShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
		if (shaderLogSize > 0) {
			GLchar* buf = new GLchar[shaderLogSize];
			glGetShaderInfoLog(this->pixelShader, shaderLogSize, NULL, buf);
			printf("[SHADER COMPILE ERROR]: %s", buf);
			delete[] buf;
		}

		// create a program object
		this->program = glCreateProgram();
		glAttachShader(this->program, this->vertexShader);
		glAttachShader(this->program, this->pixelShader);
		glLinkProgram(this->program);
		glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &shaderLogSize);
		if (shaderLogSize > 0) {
			GLchar* buf = new GLchar[shaderLogSize];
			glGetProgramInfoLog(this->program, shaderLogSize, NULL, buf);
			printf("[PROGRAM LINK ERROR]: %s", buf);
			delete[] buf;
		}

		// setup vbo
		glGenBuffers(1, &this->triangle);
		glBindBuffer(GL_ARRAY_BUFFER, this->triangle);
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec2), &data[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		return true;
	}
	return false;
}

//------------------------------------------------------------------------------
/**
*/
void
KochflakeApp::Run() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	while (this->window->IsOpen()){
		glClear(GL_COLOR_BUFFER_BIT);

		// loads new window
		this->window->Update();


		// do stuff

		// binds the triangle object to the buffer for rendering
		glBindBuffer(GL_ARRAY_BUFFER, this->triangle);

		// seems to add color, function seems to install the specified program into the rendering stage
		glUseProgram(this->program);

		// (3*(pow(4,itteration)))+1
		
		
		glEnableVertexAttribArray(0);
		// glEnableVertexAttribArray(1);

		// first int == index of the array to be drawn i.e. vertice points
		// second int == the size of the expected input data, i.e. 3 == x, y	or 4 == R, G, B, gamma
		// GL_FLOAT == what type of input data it is
		// GL_NORMALIZED == bool to indicate if input data is normalized 
		// GL_STRIDE == indicates how large one chunks of the input data is, if it is 3 floats then it is sizeof(float32) * 2. i.e. input data off-set
		// GL_ARRAY_BUFFER (pointer) == specifies the offset from the first datatype in the datastruct to the next one
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, NULL);
		// glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float32) * 6, (GLvoid*)(sizeof(float32) * 2));
		glDrawArrays(GL_LINE_LOOP, 0, this->data.size());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		

		this->window->SwapBuffers();
	}
}

} // namespace Example