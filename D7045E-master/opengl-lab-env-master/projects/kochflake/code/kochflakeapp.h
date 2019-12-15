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
#include <glm.hpp>
#include <vec2.hpp>
#include <vec3.hpp> // glm::vec3


namespace Kochflake{
class KochflakeApp : public Core::App
{
public:
	/// constructor
	KochflakeApp();
	/// destructor
	~KochflakeApp();

	/// open app
	bool 	Open();
	/// run app
	void Run();
	
private:
	std::vector<glm::vec2> data;
	GLuint program;
	GLuint vertexShader;
	GLuint pixelShader;
	GLuint triangle;
	Display::Window* window;

	void kochCalc(GLint itteration, glm::vec2 a, glm::vec2 b, glm::vec2 base);
};
} // namespace Kochflake