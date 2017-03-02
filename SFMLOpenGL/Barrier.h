/// @Project: Cube Game.
/// @File: Barrier.h
/// 
/// @Author: Keenan McEntee
/// 
/// @Description: Barrier data file.
/// @Date written: 23rd/february/2017 - 24th/february/2017

#ifndef BARRIER_H
#define BARRIER_H

#include <gl/glew.h>
#include <glm/gtc/matrix_transform.hpp>
const int BARRIER_VERTICES = 8;	// Total Number of Vertices
const int BARRIER_INDICES = 4;	// Total Number of Indexes
const int BARRIER_COLORS = 8;	// Total Number of Colors

static const GLfloat BARRIER_vertices[] =
{
	// Left Face
	0.00f, -1.00f, -500.00f, // [4]	// (16)
	0.00f, -1.00f,  15.00f, // [0]	// (17)
	0.00f,  1.00f,  15.00f, // [3]	// (18)
	0.00f,  1.00f, -500.00f, // [7]	// (19)

							 // Right Face
							 0.00f, -1.00f,  15.00f, // [1]	// (20)
							 0.00f, -1.00f, -500.00f, // [5]	// (21)
							 0.00f,  1.00f, -500.00f, // [6]	// (22)
							 0.00f,  1.00f,  15.00f, // [2]	// (23)
};

static const GLfloat BARRIER_colors[] = {
	// Left Face
	1.0f, 0.0f, 1.0f, 0.0f,
	1.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,

	// Right Face
	1.0f, 0.0f, 1.0f, 0.0f,
	1.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,
};
static const GLuint BARRIER_indices[] =
{
	// Front Face
	0, 1, 2,
	2, 3, 0,

	// Top Face
	4, 5, 6,
	6, 7, 4,
};
static GLuint barrierProgID, //Shader ID.
barrierVbo,	 //Barrier Vertex Buffer.
barrierVib,	 //Barrier Vertex Index.
barrierVao;
glm::mat4 barrierModel[2];		//Models for the barriers.
#endif
