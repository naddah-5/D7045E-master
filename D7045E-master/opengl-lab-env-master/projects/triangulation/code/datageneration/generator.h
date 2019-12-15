#include "generator.cc"
#include <iostream>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <vector>

using namespace std;

std::vector<glm::vec2> generator(string fileName, int generatorSize);
std::vector<glm::vec2> retrieveFrom(string FileName);
std::vector<glm::vec2> randomPoints(int numberOfPoints);
std::vector<glm::vec2> readFrom(string fileName);