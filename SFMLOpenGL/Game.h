#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <GL/glew.h>
#include <GL/wglew.h>


#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include <Debug.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <sstream>
#include <fstream>

using namespace std;
using namespace sf;
using namespace glm;

class Game
{
public:
	Game();
	Game(sf::ContextSettings settings);
	~Game();
	void run();
private:
	Window window;
	bool isRunning = false;
	void initialize();
	void update();
	void render();
	void unload();
	void createProg(GLuint &prog, std::string vertexShaderPath, std::string fragmentShaderPath);
	void readIDs(GLuint &prog);
	void loadTexture(GLuint &texture, std::string fileName);
	void cubeRender(mat4 &model, GLuint &prog, GLuint &texture);
};

#endif