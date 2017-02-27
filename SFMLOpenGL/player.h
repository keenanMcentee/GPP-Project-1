/// @Project: Cube Game.
/// @File: player.h
/// 
/// @Author: Keenan McEntee
/// 
/// @Description: player data file.
/// @Date written: 23rd/february/2017 - 24th/february/2017

#ifndef player_H
#define player_H

#include <gl/glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
const int player_VERTICES = 9;	// Total Number of Vertices
const int player_INDICES = 3;	// Total Number of Indexes
const int player_COLORS = 9;	// Total Number of Colors

static const GLfloat player_vertices[] =
{
	//Front Right
	0.0f,0.2f,0.0f,
	0.5f,0.0f,0.5f,
	0.0f,0.0f,-1.0f,
	//Front left
	0.0f,0.2f,0.0f,
	0.0f,0.0f,-1.0f,
	-0.5f,0.0f,0.5f,
	//Back
	0.5f,0.0f,0.5f,
	0.0f,0.2f,0.0f,
	-0.5f,0.0f, 0.5f,
};

static const GLfloat player_colors[] = {
	// Left Face
	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 0.0f, 1.0f,
	// Right Face
	0.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 0.0f, 1.0f,
	//Back face
	0.0f, 0.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 0.0f, 1.0f
};
static const GLuint player_indices[] =
{
	// Front Face
	0, 1, 2,
	3, 4, 5,
	6, 7, 8
};
static GLuint playerProgID, //Shader ID.
playerVbo,	 //player Vertex Buffer.
playerVib,	 //player Vertex Index.
playerVao;
glm::mat4 playerModel;
float playerSpeed = 0.5f;
#endif
