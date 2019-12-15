//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2017 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "triangulationapp.h"
#include <cstring>
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <algorithm>

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
"	Color = vec4(0.4f,0.4f,0.4f,1);\n"
"}\n";

using namespace Display;
namespace Triangulation
{

//------------------------------------------------------------------------------
/**
*/
TriangulationApp::TriangulationApp()
{
	// empty
}

//------------------------------------------------------------------------------
/**
*/
TriangulationApp::~TriangulationApp()
{
	// empty
}

//------------------------------------------------------------------------------
/**
*/


// This function takes 3 points as input data, a, b, and c.
// It then checks if the point c is to the left side of a line
// from a to b, and if so it returns true.
bool TriangulationApp::checkDirectionLeft(glm::vec2 a, glm::vec2 b, glm::vec2 c){
	if( (b.x-a.x)*(c.y-a.y) > (b.y-a.y)*(c.x-a.x) ){
		return true;
	} else{
		return false;
	}
}

void TriangulationApp::hullCalc(){
	hull.clear();
	int i = 0;

	// this loop goes from the lowest x value to the highest, adding points to the convex hull
	while (i < data.size()){
		// if the current hull has less than 2 points in it we add the next point regardless of any checks
		// this is because this implementation of andrew's algorithm requires two points already in the hull to determine
		// if the next point should be inserted.
		if(hull.size() < 1){
			hull.push_back(data[i]);
		} else {
			// if the hull has more than two elments in it and the next element would require a left turn 
			// the last element is removed from the hull vector as it can not be part of the convex hull.
			// this is repeated until a right turn or a line is found, when it is that point will be inserted
			// into the hull vector and we move on to the next element in the inputPoints vector.
			while(checkDirectionLeft(hull[hull.size()-2], hull[hull.size()-1], data[i]) && hull.size() > 2){
				hull.pop_back();
			}
			hull.push_back(data[i]);
		}
		i++;
	}
	i--;
	// when the entire list has been inserted into the upper hull we itterate through the list again but backwards.
	// the result of this is that the hull from the previous loop (which only covered the top of the input points)
	// will be extended to cover the bottom part as well. this can be done because the function used to check a points position
	// relative to the hull is relative to the last two points in the hull and not relative to origo.
	while (i >= 0){
		if(hull.size() < 1){
			hull.push_back(data[i]);
		} else{
			while(checkDirectionLeft(hull[hull.size()-2], hull[hull.size()-1], data[i]) && hull.size() > 2){
				hull.pop_back();
			}
			hull.push_back(data[i]);
		}
		i--;
	}
}

//bubbel sort
void TriangulationApp::pointSortByX(){
	int check = 1;
	glm::vec2 temp;

	std::sort(data.begin(), data.end(), [](glm::vec2 a, glm::vec2 b){
		return (a.x < b.x);
	});

	//while (check < data.size()-1){
	//	// check is used to check if the inputPoints are sorted, if they are the check will be equal to the inputPoints size.
	//	check = 1;
	//	// setting up a for-loop to go through all the point vectors and switch them if the rightmost has a lower x-value than the left one.
	//	for (int i = 1; i < data.size(); i++){
	//		if((data[i]).x < data[i-1].x){
	//			temp = data[i-1];
	//			data[i-1] = data[i];
	//			data[i] = temp;
	//			// adding a check for the edge case when both x-values are equal, when it is the algoithm will put the input vector 
	//			// with the higher Y-value in the left most spot. This will ensure that a special edge case does not occur on either the 
	//			// hullCalc from left to right or from right to left.
	//			/*if(data[i].x == data[i-1].x && data[i].y > data[i-1].y){
	//				temp = data[i-1];
	//				data[i-1] = data[i];
	//				data[i] = temp;
	//			}*/
	//		}
	//		// if the value currently being checked is sorted relative to each other, increment the check variable by one 
	//		// check will be reset after each run through and when the check reaches the inputPoints size the loop will break and be sorted.
	//		else {
	//			check++;
	//		}
	//	}
	//}
}

void TriangulationApp::readFrom(std::string fileName){
	std::ifstream file(fileName);
	data.clear();
	if(file.is_open()){
		GLfloat xVal, yVal;

		while(file >> xVal >> yVal){
			glm::vec2 point(xVal, yVal);
			data.push_back(point);
		}
	}
	else {
		printf("No such file");
		exit(1);
	}
	file.close();
}
float TriangulationApp::randomFloatBetween(float low, float high){
    float random = ( (float) rand() ) / ( (float) RAND_MAX);
    float span = high - low;
    float adjustedRNG = (random * span) + low;
    return adjustedRNG;
}

void TriangulationApp::randomPointGenerator(int numberOfPoints){
	if(numberOfPoints > 3){
		data.clear();
		GLfloat xVal, yVal;
		for (int i = 0; i < numberOfPoints; i++){
			xVal = randomFloatBetween(-1.0f, 1.0f);
			yVal = randomFloatBetween(-1.0f, 1.0f);
			glm::vec2 point = glm::vec2(xVal, yVal);
			data.push_back(point);
		}
	}
}

void TriangulationApp::printData(){
	for (int j = 0; j < data.size(); j++){
		GLfloat xVal, yVal;
		xVal = data[j].x;
		yVal = data[j].y;
		std::cout << xVal << " " << yVal << "\n";
	}
	std::cout << "\n";
}

void TriangulationApp::printHull(){
	for (int j = 0; j < hull.size(); j++){
		GLfloat xVal, yVal;
		xVal = hull[j].x;
		yVal = hull[j].y;
		std::cout << xVal << " " << yVal << "\n";
	}
	std::cout << "\n";
}

/*
void TriangulationApp::triangulate(){
	
}
*/


bool
TriangulationApp::Open() {
	App::Open();
	this->window = new Display::Window;
	this->window->SetSize(800, 800);
	data.clear();
	hull.clear();

	window->SetKeyPressFunction([this](int32 key, int32 scancode, int32 action, int32 mods)
		{
			if (key == 256 && action == GLFW_PRESS) {
				this->window->Close();
			}
			else if (key == 51 && action == GLFW_PRESS) {
				// terminal input
			}
			else if (key == 50 && action == GLFW_PRESS) {
				this->readFrom("test.txt");
				// read from file
			}
			else if (key == 49 && action == GLFW_PRESS) {
				// generate random points
				randomPointGenerator(6);
				pointSortByX();
				printData();
				hullCalc();
				printHull();
			}
		});
	


	if (this->window->Open()) {
		// assigns background color to pale yellow
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

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
		//glBufferData(GL_ARRAY_BUFFER, hull.size() * sizeof(glm::vec2), &data[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		return true;
	}
	return false;
}

//------------------------------------------------------------------------------
/**
*/
void
TriangulationApp::Run() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPointSize(4);

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
		//glEnableVertexAttribArray(1);
	
		// first int == index of the array to be drawn i.e. vertice points
		// second int == the size of the expected input data, i.e. 3 == x, y	or 4 == R, G, B, gamma
		// GL_FLOAT == what type of input data it is
		// GL_NORMALIZED == bool to indicate if input data is normalized 
		// GL_STRIDE == indicates how large one chunks of the input data is, if it is 3 floats then it is sizeof(float32) * 2. i.e. input data off-set
		// GL_ARRAY_BUFFER (pointer) == specifies the offset from the first datatype in the datastruct to the next one
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, NULL);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (GLvoid*)(sizeof(float) * 2));
		// glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float32) * 2, (GLvoid*)(sizeof(float32) * 2));
		
		
		glBufferData(GL_ARRAY_BUFFER, hull.size()*sizeof(glm::vec2), hull.data(), GL_STATIC_DRAW);
		glDrawArrays(GL_LINE_LOOP, 0, this->hull.size());
		
		
		glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(glm::vec2), data.data(), GL_STATIC_DRAW);
		glDrawArrays(GL_POINTS, 0, this->data.size());
		

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		

		this->window->SwapBuffers();
	}
}

} // namespace Example