/// <summary>
/// INCLUDE GUARD TO AVOID HEADER HELL.
/// </summary>
#ifndef GAME_H
#define GAME_H

//All our basic includes to get the project running.
//IOSTREAM TO PRINT TO CONSOLE.
#include <iostream>
//GLEW
#include <GL/glew.h>
#include <GL/wglew.h>
//GLM
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
//SFML
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
//DEBUG HEADER TO PRINT TO CONSOLE
#include <Debug.h>
//IMAGE LOADER HEADER
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
//TEXT LOADER HEADERS
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
	int NUM_OF_CUBES = 5;
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
	void barrierRender(mat4 &model, GLuint &prog);
	void playerRender(mat4 &model, GLuint &prog);
	GLuint maxCubes = 100;
	GLuint cubeVbo;
	float count = 0;
	float pushBack = -500;
	mat4 viewMoveLeft, viewMoveRight, viewNormal;

	GLuint	vsid,		// Vertex Shader ID
			fsid,		// Fragment Shader ID
			cubeVao = 0,	// Vertex Array ID
			to, to2, to3,	// Texture ID 1 to 32
			positionID,	// Position ID
			colorID,	// Color ID
			textureID,	// Texture ID
			uvID,		// UV ID
			mvpID;		// Model View Projection ID

	mat4 cubeModel[5];
	//const string filename = ".//Assets//Textures//coordinates.tga";
	//const string filename = ".//Assets//Textures//cube.tga";
	//const string filename = ".//Assets//Textures//grid.tga";
	const string filename = ".//Assets//Textures//grid_wip.tga";
	//const string filename = ".//Assets//Textures//minecraft.tga";
	//const string filename = ".//Assets//Textures//texture.tga";
	//const string filename = ".//Assets//Textures//texture_2.tga";
	//const string filename = ".//Assets//Textures//uvtemplate.tga";
};

#endif