/// @Project: Cube Game.
/// @File: Cube.h
/// 
/// @Author: Keenan McEntee
/// 
/// @Description: Cube data file.
/// @Date written: 23rd/february/2017 - 24th/february/2017

#ifndef CUBE_H
#define CUBE_H

#include <gl/glew.h>

//Cube Vertices
/*
(-1.0f, 1.0f, -1.0f)          (1.0f, 1.0f, -1.0f)
[7]                          [6]
#-----------------------------#
/|                            /|
/ |                           / |
(-1.0f, 1.0f, 1.0f)           (1.0f, 1.0f, 1.0f)
[3] /                         [2] /
#-----------------------------#    |
|    |                        |    |
|    |                        |    |
|   [4]                       |   [5]
(-1.0f, -1.0f, -1.0f)         (1.0f, -1.0f, -1.0f)
|    #-----------------------------#
|   /                         |   /
|  /                          |  /
| /                           | /
|/                            |/
#-----------------------------#
[0]                           [1]
(-1.0f, -1.0f, 1.0f)         (1.0f, -1.0f, 1.0f)
*/

const int VERTICES = 24;	// Total Number of Vertices
const int INDICES = 12;	// Total Number of Indexes
const int UVS = 48;	// Total Number of UVs
const int COLORS = 24;	// Total Number of Colors

						/// <summary>
						/// Vertex points of each face on our cube.
						/// </summary>
static GLfloat vertices[] =
{
	// Front Face
	-1.00f, -1.00f,  1.00f,	// [0]	// ( 0)
	1.00f, -1.00f,  1.00f,	// [1]	// ( 1)
	1.00f,  1.00f,  1.00f,	// [2]	// ( 2)
	-1.00f,  1.00f,  1.00f,	// [3]	// ( 3)

							// Top Face
							-1.00f,  1.00f,  1.00f,	// [3]	// ( 4)
							1.00f,  1.00f,  1.00f,	// [2]	// ( 5)
							1.00f,  1.00f, -1.00f,	// [6]	// ( 6)
							-1.00f,  1.00f, -1.00f,	// [7]	// ( 7)

													// Back Face
													1.00f, -1.00f, -1.00f,	// [5]	// ( 8)
													-1.00f, -1.00f, -1.00f, // [4]	// ( 9)
													-1.00f,  1.00f, -1.00f,	// [7]	// (10)
													1.00f,  1.00f, -1.00f,	// [6]	// (11)

																			// Bottom Face
																			-1.00f, -1.00f, -1.00f, // [4]	// (12)
																			1.00f, -1.00f, -1.00f, // [5]	// (13)
																			1.00f, -1.00f,  1.00f, // [1]	// (14)
																			-1.00f, -1.00f,  1.00f, // [0]	// (15)

																									// Left Face
																									-1.00f, -1.00f, -1.00f, // [4]	// (16)
																									-1.00f, -1.00f,  1.00f, // [0]	// (17)
																									-1.00f,  1.00f,  1.00f, // [3]	// (18)
																									-1.00f,  1.00f, -1.00f, // [7]	// (19)

																															// Right Face
																															1.00f, -1.00f,  1.00f, // [1]	// (20)
																															1.00f, -1.00f, -1.00f, // [5]	// (21)
																															1.00f,  1.00f, -1.00f, // [6]	// (22)
																															1.00f,  1.00f,  1.00f, // [2]	// (23)
};
/// <summary>
/// Colours associated which each vertex in corresponding order.
/// </summary>
static GLfloat colors[] = {

	// Front Face
	1.0f, 0.0f, 0.0f, 1.0f, // [0]	// ( 0)
	1.0f, 0.0f, 0.0f, 1.0f, // [1]	// ( 1)
	1.0f, 0.0f, 0.0f, 1.0f, // [2]	// ( 2)
	1.0f, 0.0f, 0.0f, 1.0f, // [3]	// ( 3)

							// Top Face
							0.0f, 1.0f, 0.0f, 1.0f, // [3]	// ( 4)
							0.0f, 1.0f, 0.0f, 1.0f, // [2]	// ( 5)
							0.0f, 1.0f, 0.0f, 1.0f, // [6]	// ( 6)
							0.0f, 1.0f, 0.0f, 1.0f, // [7]	// ( 7)

													// Back Face
													0.0f, 0.0f, 1.0f, 1.0f, // [5]	// ( 8)
													0.0f, 0.0f, 1.0f, 1.0f, // [4]	// ( 9)
													0.0f, 0.0f, 1.0f, 1.0f, // [7]	// (10)
													0.0f, 0.0f, 1.0f, 1.0f, // [6]	// (11)

																			// Bottom Face
																			0.0f, 1.0f, 1.0f, 1.0f, // [4]	// (12)
																			0.0f, 1.0f, 1.0f, 1.0f, // [5]	// (13)
																			0.0f, 1.0f, 1.0f, 1.0f, // [1]	// (14)
																			0.0f, 1.0f, 1.0f, 1.0f, // [0]	// (15)

																									// Left Face
																									1.0f, 1.0f, 0.0f, 1.0f, // [4]	// (16)
																									1.0f, 1.0f, 0.0f, 1.0f, // [0]	// (17)
																									1.0f, 1.0f, 0.0f, 1.0f, // [3]	// (18)
																									1.0f, 1.0f, 0.0f, 1.0f, // [7]	// (19)

																															// Right Face
																															1.0f, 0.0f, 1.0f, 1.0f, // [1]	// (20)
																															1.0f, 0.0f, 1.0f, 1.0f, // [5]	// (21)
																															1.0f, 0.0f, 1.0f, 1.0f, // [6]	// (22)
																															1.0f, 0.0f, 1.0f, 1.0f, // [2]	// (23)
};
/// <summary>
/// UV points for mapping a texture on to our cube.
/// </summary>
GLfloat uvs[2 * 4 * 6] = {
	// Front Face (other faces populated in initialisation)
	0.0, 0.0,
	1.0, 0.0,
	1.0, 1.0,
	0.0, 1.0
};
/// <summary>
/// Index positions for drawing our verteces.
/// </summary>
static GLuint indices[] =
{
	// Front Face
	0, 1, 2,
	2, 3, 0,

	// Top Face
	4, 5, 6,
	6, 7, 4,

	// Back Face
	8, 9, 10,
	10, 11, 8,

	// Bottom Face
	12, 13, 14,
	14, 15, 12,

	// Left Face
	16, 17, 18,
	18, 19, 16,

	// Right Face
	20, 21, 22,
	22, 23, 20
};
static GLuint cubeVbo,		// Vertex Buffer ID
cubeVib,		// Vertex Index Buffer
cubeProgID[3];		// Program ID
static float cubeSpeed = 0.02f;		//Speed at which the cubes move
#endif

