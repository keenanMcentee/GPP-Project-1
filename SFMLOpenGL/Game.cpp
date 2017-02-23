#include <Game.h>
#include <Cube.h>

GLuint	vsid,		// Vertex Shader ID
		fsid,		// Fragment Shader ID
		progID, progID2,progID3,		// Program ID
		vao = 0,	// Vertex Array ID
		vbo,		// Vertex Buffer ID
		vib,		// Vertex Index Buffer
		to,to2,to3,			// Texture ID 1 to 32
		positionID,	// Position ID
		colorID,	// Color ID
		textureID,	// Texture ID
		uvID,		// UV ID
		mvpID;		// Model View Projection ID

//const string filename = ".//Assets//Textures//coordinates.tga";
//const string filename = ".//Assets//Textures//cube.tga";
//const string filename = ".//Assets//Textures//grid.tga";
const string filename = ".//Assets//Textures//grid_wip.tga";
//const string filename = ".//Assets//Textures//minecraft.tga";
//const string filename = ".//Assets//Textures//texture.tga";
//const string filename = ".//Assets//Textures//texture_2.tga";
//const string filename = ".//Assets//Textures//uvtemplate.tga";


int width;			// Width of texture
int height;			// Height of texture
int comp_count;		// Component of texture

unsigned char* img_data;		// image data

mat4 mvp, projection, view, model1, model2, model3, model4, model5;			// Model View Projection

Game::Game() : 
	window(VideoMode(800, 600), 
	"Introduction to OpenGL Texturing")
{
}

Game::Game(sf::ContextSettings settings) : 
	window(VideoMode(800, 600), 
	"Introduction to OpenGL Texturing", 
	sf::Style::Default, 
	settings)
{
}

Game::~Game(){}


void Game::run()
{

	initialize();

	Event event;

	while (isRunning){

#if (DEBUG >= 2)
		DEBUG_MSG("Game running...");
#endif

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				// Set Model Rotation
				model1 = rotate(model1, 0.05f, glm::vec3(0, 1, 0)); // Rotate
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				// Set Model Rotation
				model1 = rotate(model1, -0.05f, glm::vec3(0, 1, 0)); // Rotate
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				// Set Model Rotation
				model1 = rotate(model1, -0.05f, glm::vec3(1, 0, 0)); // Rotate
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				// Set Model Rotation
				model1 = rotate(model1, 0.05f, glm::vec3(1, 0, 0)); // Rotate
			}
		}
		update();
		render();
	}

#if (DEBUG >= 2)
	DEBUG_MSG("Calling Cleanup...");
#endif
	unload();

}

void Game::initialize()
{
	isRunning = true;

	glewInit();

	//Copy UV's to all faces
	for (int i = 1; i < 6; i++)
		memcpy(&uvs[i * 4 * 2], &uvs[0], 2 * 4 * sizeof(GLfloat));


	glm::vec2 translations[100];
	int index = 0;
	GLfloat offset = 0.1f;
	for (GLint y = -10; y < 10; y += 2)
	{
		for (GLint x = -10; x < 10; x += 2)
		{
			glm::vec2 translation;
			translation.x = (GLfloat)x / 10.0f + offset;
			translation.y = (GLfloat)y / 10.0f + offset;
			translations[index++] = translation;
		}
	}
	

	DEBUG_MSG(glGetString(GL_VENDOR));
	DEBUG_MSG(glGetString(GL_RENDERER));
	DEBUG_MSG(glGetString(GL_VERSION));

	glGenVertexArrays(1, &vao); //Gen Vertex Array
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);		//Gen Vertex Buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//Vertices (3) x,y,z , Colors (4) RGBA, UV/ST (2)
	glBufferData(GL_ARRAY_BUFFER, ((3 * VERTICES) + (4 * COLORS) + (2 * UVS)) * sizeof(GLfloat), NULL, GL_STATIC_DRAW);

	glGenBuffers(1, &vib); //Gen Vertex Index Buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vib);

	//Indices to be drawn
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * INDICES * sizeof(GLuint), indices, GL_STATIC_DRAW);

	
	createProg(progID, "vertexShader0.txt", "fragmentShader1.txt");

	
	createProg(progID2, "vertexShader0.txt", "fragmentShader2.txt");

	
	createProg(progID3, "vertexShader0.txt", "fragmentShader3.txt");
	
	

	glEnable(GL_TEXTURE_2D);
	glGenTextures(3, &to);
	loadTexture(to, ".//Assets//Textures//grid_wip.tga");
	loadTexture(to, ".//Assets//Textures//texture.tga");
	loadTexture(to, ".//Assets//Textures//texture_2.tga");

	// Projection Matrix 
	projection = perspective(
		45.0f,					// Field of View 45 degrees
		4.0f / 3.0f,			// Aspect ratio
		5.0f,					// Display Range Min : 0.1f unit
		100.0f					// Display Range Max : 100.0f unit
		);

	// Camera Matrix
	view = lookAt(
		vec3(0.0f, 4.0f, 10.0f),	// Camera (x,y,z), in World Space
		vec3(0.0f, 0.0f, 0.0f),		// Camera looking at origin
		vec3(0.0f, 1.0f, 0.0f)		// 0.0f, 1.0f, 0.0f Look Down and 0.0f, -1.0f, 0.0f Look Up
		);

	// Model matrix
	model1 = mat4(
		1.0f					// Identity Matrix
		);

	// Model matrix
	model2 = mat4(
		1.0f					// Identity Matrix
	);

	// Model matrix
	model3 = mat4(
		1.0f					// Identity Matrix
	);

	// Model matrix
	model4 = mat4(
		1.0f					// Identity Matrix
	);

	// Model matrix
	model5 = mat4(
		1.0f					// Identity Matrix
	);

	model2 = translate(model2, vec3(5, 0, 0));
	model3 = translate(model3, vec3(-5, 0, 0));
	// Enable Depth Test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
}
void Game::createProg(GLuint &prog, std::string vertexShaderPath, std::string fragmentShaderPath)
{
	GLint isCompiled = 0;
	GLint isLinked = 0;


	
	ifstream vertexFile;
	std::string vString;
	std::stringstream vContent;
	vertexFile.open(vertexShaderPath);
	vContent << vertexFile.rdbuf();
	vertexFile.close();
	vString = vContent.str();
	const char* vs_src = vString.c_str();
		

	DEBUG_MSG("Setting Up Vertex Shader");

	vsid = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vsid, 1, (const GLchar**)&vs_src, NULL);
	glCompileShader(vsid);

	//Check is Shader Compiled
	glGetShaderiv(vsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Vertex Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Vertex Shader Compilation Error");
	}

	ifstream fragFile;
	std::string fString;
	std::stringstream fContent;
	fragFile.open(fragmentShaderPath);
	fContent << fragFile.rdbuf();
	fragFile.close();
	fString = fContent.str();
	const char* fs_src = fString.c_str();
		

	DEBUG_MSG("Setting Up Fragment Shader");

	fsid = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fsid, 1, (const GLchar**)&fs_src, NULL);
	glCompileShader(fsid);

	//Check is Shader Compiled
	glGetShaderiv(fsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Fragment Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Fragment Shader Compilation Error");
	}

	DEBUG_MSG("Setting Up and Linking Shader");
	prog = glCreateProgram();
	glAttachShader(prog, vsid);
	glAttachShader(prog, fsid);
	glLinkProgram(prog);

	//Check is Shader Linked
	glGetProgramiv(prog, GL_LINK_STATUS, &isLinked);

	if (isLinked == 1) {
		DEBUG_MSG("Shader Linked");
	}
	else
	{
		DEBUG_MSG("ERROR: Shader Link Error");
	}

	//Use Progam on GPU
	glUseProgram(prog);

}
void Game::loadTexture(GLuint &texture , std::string fileName)
{
	img_data = stbi_load(fileName.c_str(), &width, &height, &comp_count, 4);

	if (img_data == NULL)
	{
		DEBUG_MSG("ERROR: Texture not loaded");
	}

	glBindTexture(GL_TEXTURE_2D, texture);

	//Wrap around
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	//Filtering
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Bind to OpenGL
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexImage2D.xml
	glTexImage2D(
		GL_TEXTURE_2D,			//2D Texture Image
		0,						//Mipmapping Level 
		GL_RGBA,				//GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_BGR, GL_RGBA 
		width,					//Width
		height,					//Height
		0,						//Border
		GL_RGBA,				//Bitmap
		GL_UNSIGNED_BYTE,		//Specifies Data type of image data
		img_data				//Image Data
	);
}
void Game::update()
{
#if (DEBUG >= 2)
	DEBUG_MSG("Updating...");
#endif
	// Update Model View Projection
	//mvp = projection * view * model1;
}

void Game::render()
{

#if (DEBUG >= 2)
	DEBUG_MSG("Render Loop...");
#endif

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cubeRender(model1, progID, to);
	cubeRender(model2, progID2, to2);
	cubeRender(model3, progID3, to3);

	window.display();

	//Disable Arrays
	glDisableVertexAttribArray(positionID);
	glDisableVertexAttribArray(colorID);
	glDisableVertexAttribArray(uvID);
	
}
void Game::cubeRender(mat4 &model, GLuint &prog, GLuint &texture)
{
	
	mvp = projection * view * (model);

	glUseProgram(prog);
	readIDs(prog);

	//VBO Data....vertices, colors and UV's appended
	glBufferSubData(GL_ARRAY_BUFFER, 0 * VERTICES * sizeof(GLfloat), 3 * VERTICES * sizeof(GLfloat), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, 3 * VERTICES * sizeof(GLfloat), 4 * COLORS * sizeof(GLfloat), colors);
	glBufferSubData(GL_ARRAY_BUFFER, ((3 * VERTICES) + (4 * COLORS)) * sizeof(GLfloat), 2 * UVS * sizeof(GLfloat), uvs);

	// Send transformation to shader mvp uniform
	glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);

	//Set Active Texture .... 32
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(1, 0);

	//Set pointers for each parameter (with appropriate starting positions)
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glVertexAttribPointer.xml
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, 0, (VOID*)(3 * VERTICES * sizeof(GLfloat)));
	glVertexAttribPointer(uvID, 2, GL_FLOAT, GL_FALSE, 0, (VOID*)(((3 * VERTICES) + (4 * COLORS)) * sizeof(GLfloat)));

	//Enable Arrays
	glEnableVertexAttribArray(positionID);
	glEnableVertexAttribArray(colorID);
	glEnableVertexAttribArray(uvID);

	//Draw Element Arrays
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);
}
void Game::unload()
{
#if (DEBUG >= 2)
	DEBUG_MSG("Cleaning up...");
#endif
	glDeleteProgram(progID);	//Delete Shader
	glDeleteBuffers(1, &vbo);	//Delete Vertex Buffer
	glDeleteBuffers(1, &vib);	//Delete Vertex Index Buffer
	stbi_image_free(img_data);		//Free image
}
void Game::readIDs(GLuint &prog)
{
	positionID = glGetAttribLocation(prog, "sv_position");
	colorID = glGetAttribLocation(prog, "sv_color");
	uvID = glGetAttribLocation(prog, "sv_uv");
	textureID = glGetUniformLocation(prog, "f_texture");
	mvpID = glGetUniformLocation(prog, "sv_mvp");
}