#include <iostream>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <vector>
#include <string>

using namespace std;


void writeToFile(std::vector<glm::vec2> dataPoints, string fileName, int dataSize){
    ofstream file;
    file.open(fileName, ios::trunc);
    for (int i = 0; i < dataSize; i++){
        if(i==0){
            cout << dataSize << endl;
        } else{
            file << dataPoints[i].x << ' ';
            file << dataPoints[i].y << endl;
        }
    }
    file.close();
    
}

std::vector<glm::vec2> readFrom(string fileName){
    ifstream dataFile;
    string fileLine;
    float Ax;
    float Ay;
    std::vector<glm::vec2> pointData;
    dataFile.open("/home/anders/Documents/D7045E/opengl-lab-env-master/projects/triangulation/data/" + fileName);
    if(!dataFile){
        cerr << "File could not be opened.";
        exit(1);
    }
    while (std::getline(dataFile, fileLine)) {
        std::string::size_type sz;
        Ax = std::stof(fileLine, &sz);
        Ay = std::stof(fileLine.substr(sz));
        glm::vec2 newPoint(Ax, Ay);
        pointData.push_back(newPoint);
    }

    return pointData;    
}

float randomFloatBetween(float low, float high){
    float random = ( (float) rand() ) / ( (float) RAND_MAX);
    float span = high - low;
    float adjustedRNG = (random * span) + low;
    return adjustedRNG;
}

// function to generate a random set of points
std::vector<glm::vec2> randomPointGenerator(int numberOfPoints){
    std::vector<glm::vec2> pointData;
    float32 generatedX, generatedY;
    for (int i = 0; i < numberOfPoints; i++){
        generatedX = randomFloatBetween(-1.0f,1.0f);
        generatedY = randomFloatBetween(-1.0f,1.0f);
        glm::vec2 newPoint = glm::vec2(generatedX, generatedY);
        pointData.push_back(newPoint);
    }
    return pointData;    
}

std::vector<glm::vec2> generator(string fileName, int generatorSize){
    std::vector<glm::vec2> dataPoints;

    dataPoints = randomPointGenerator(generatorSize);
    writeToFile(dataPoints, fileName, generatorSize);
    return dataPoints;
}
