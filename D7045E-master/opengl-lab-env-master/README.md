# opengl-lab-env
C++11 and OpenGL based application base for developing apps.

# Requirements
1. Visual Studio 2017 or newer (Windows) or CMake 3+ (Linux).
2. Compiler with support for lambda functions (C++11), such as VS 2017.
  
# Visual Studio Users
1. Open `vstudio\lab-env.sln`
2. Work either in the example app project, or create a new project with the same settings as example app.

GLM math library is included by default in the example app project.

# Usage
The lab environment contains two classes, Window and App. Override the App class for your project to implement your own update loop. The Window class is used to open a window and connect input handlers to it. 

This is done by assigning a lambda function to a callback matching the input you require. It is possible to have more than one window open at a time, although one must select which window to render to using the function called Window::MakeCurrent prior to doing any GL calls.

## Common problems
* Q: Build log says Windows SDK version was not found
    - A: Right click the project in the solution explorer and click `Retarget projects`, then select a version.

---
---

# CMake instructions
Put your laboration in the folder titled 'projects'. It must be accompanied with its own CMakeLists.txt which is used to generate a project/solution. Then run 'cmake ..' in root/build, there should be a target in your project matching the name of your lab.
To build a specific target, run 'make <TARGET>'.
To list targets, run 'make help'.
Build binaries are placed in 'root/bin'
To execute project run './<TARGET>' in /bin.