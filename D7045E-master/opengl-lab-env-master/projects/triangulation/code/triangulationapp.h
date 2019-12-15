#pragma once
//------------------------------------------------------------------------------
/**
	Application class used for example application.
	
	(C) 2015-2017 Individual contributors, see AUTHORS file
*/
//------------------------------------------------------------------------------
#include "core/app.h"
#include "render/window.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp> // glm::vec3


namespace Triangulation{
class TriangulationApp : public Core::App
{
public:
	/// constructor
	TriangulationApp();
	/// destructor
	~TriangulationApp();

	/// open app
	bool 	Open();
	/// run app
	void Run();
	
private:
	std::vector<glm::vec2> data;
	std::vector<glm::vec2> hull;
	std::vector<glm::vec2> internalPoints;
	GLuint program;
	GLuint vertexShader;
	GLuint pixelShader;
	GLuint triangle;
	Display::Window* window;

	bool checkDirectionLeft(glm::vec2 a, glm::vec2 b, glm::vec2 c);
	void hullCalc();
	void pointSortByX();
	void readFrom(std::string fileName);
	float randomFloatBetween(float min, float max);
	void randomPointGenerator(int numberOfPoints);
	void printData();
	void printHull();
	void triangulate();
	bool checkPointInArea();
};
} // namespace Triangulation