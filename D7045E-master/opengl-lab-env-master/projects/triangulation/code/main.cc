//------------------------------------------------------------------------------
// main.cc
// (C) 2015-2017 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "triangulationapp.h"
#include "./datageneration/generator.h"

int main(int argc, const char** argv){
	Triangulation::TriangulationApp app;
	if (app.Open())	{
		app.Run();
		app.Close();
	}
	app.Exit();
	
}