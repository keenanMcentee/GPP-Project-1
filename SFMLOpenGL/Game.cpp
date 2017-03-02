#include <Game.h>
#include <Cube.h>
#include <Barrier.h>
#include <player.h>
/// @Project: Cube Game.
/// @File: Game.cpp
/// 
/// @Original file by: Philip Bourke
/// @Edits By: Keenan McEntee
/// 
/// @Description: Main Game file which handles running everything in relation to our game.
/// @Date written: 23rd/february/2017 - 24th/february/2017




int width;			// Width of texture
int height;			// Height of texture
int comp_count;		// Component of texture


unsigned char* img_data;		// image data

mat4 mvp, projection, view;			// Model View Projection
Game::Game() :
	window(VideoMode(800, 600),
		"Introduction to OpenGL Texturing")
{
}

Game::Game(sf::ContextSettings settings) :
	window(VideoMode(1376, 768),
		"Introduction to OpenGL Texturing",
		sf::Style::Default,
		settings),
	currentScreen(GameState::License)
{
}

Game::~Game() {}


void Game::run()
{

	initialize();

	Event event;

	while (window.isOpen()) {

#if (DEBUG >= 2)
		DEBUG_MSG("Game running...");
#endif

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				if (playerModel[3].x > -8.8) {
					// Set cubeModel Rotation
					playerModel = translate(playerModel, vec3(-playerSpeed, 0, 0));
					playerMoveLeft = translate(playerModel, vec3(-playerSpeed, 0, 0));
					playerMoveRight = translate(playerModel, vec3(-playerSpeed, 0, 0));
					playerNormal = translate(playerModel, vec3(-playerSpeed, 0, 0));
					playerModel = playerMoveLeft;

					viewNormal = translate(viewNormal, vec3(playerSpeed / 2, 0, 0));
					viewMoveLeft = translate(viewMoveLeft, vec3(playerSpeed / 2, 0, 0));
					viewMoveRight = translate(viewMoveRight, vec3(playerSpeed / 2, 0, 0));
					view = viewMoveLeft;
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				if (playerModel[3].x < 8.8) {
					playerModel = translate(playerModel, vec3(playerSpeed, 0, 0));
					playerMoveLeft = translate(playerModel, vec3(playerSpeed, 0, 0));
					playerMoveRight = translate(playerModel, vec3(playerSpeed, 0, 0));
					playerNormal = translate(playerModel, vec3(playerSpeed, 0, 0));
					playerModel = playerMoveRight;

					viewNormal = translate(viewNormal, vec3(-playerSpeed / 2, 0, 0));
					viewMoveLeft = translate(viewMoveLeft, vec3(-playerSpeed / 2, 0, 0));
					viewMoveRight = translate(viewMoveRight, vec3(-playerSpeed / 2, 0, 0));
					view = viewMoveRight;

				}
			}
			else
			{
				// Camera Matrix
				playerModel = playerNormal;
				view = viewNormal;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
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


	DEBUG_MSG(glGetString(GL_VENDOR));
	DEBUG_MSG(glGetString(GL_RENDERER));
	DEBUG_MSG(glGetString(GL_VERSION));

	glGenVertexArrays(1, &cubeVao); //Gen Vertex Array
	glBindVertexArray(cubeVao);

	glGenBuffers(1, &cubeVbo);		//Gen Vertex Buffer
	glBindBuffer(GL_ARRAY_BUFFER, cubeVbo);

	//Vertices (3) x,y,z , Colors (4) RGBA, UV/ST (2)
	glBufferData(GL_ARRAY_BUFFER, ((3 * VERTICES) + (4 * COLORS) + (2 * UVS)) * sizeof(GLfloat), NULL, GL_STATIC_DRAW);

	glGenBuffers(1, &cubeVib); //Gen Vertex Index Buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeVib);

	//Indices to be drawn
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * INDICES * sizeof(GLuint), indices, GL_STATIC_DRAW);

	
	createProg(cubeProgID[0], "vertexShader0.txt", "fragmentShader1.txt");
	createProg(cubeProgID[1], "vertexShader0.txt", "fragmentShader2.txt");
	createProg(cubeProgID[2], "vertexShader0.txt", "fragmentShader3.txt");


	glEnable(GL_TEXTURE_2D);
	glGenTextures(2, &to[0]);
	//loadTexture(to[0], ".//Assets//Textures//texture.tga");
	//loadTexture(to[1], ".//Assets//Textures//texture2.tga");

	loadTexture(0, ".//Assets//Textures//texture.tga");
	loadTexture(1, ".//Assets//Textures//texture2.tga");


	glGenVertexArrays(1, &barrierVao); //Gen Vertex Array
	glBindVertexArray(barrierVao);

	glGenBuffers(1, &barrierVbo);		//Gen Vertex Buffer
	glBindBuffer(GL_ARRAY_BUFFER, barrierVbo);

	//Vertices (3) x,y,z , Colors (4) RGBA, time
	glBufferData(GL_ARRAY_BUFFER, ((3 * BARRIER_VERTICES) + (4 * BARRIER_COLORS) + 1) * sizeof(GLfloat), NULL, GL_STATIC_DRAW);

	glGenBuffers(1, &barrierVib); //Gen Vertex Index Buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, barrierVib);

	//Indices to be drawn
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * BARRIER_INDICES * sizeof(GLuint), BARRIER_indices, GL_STATIC_DRAW);
	createProg(barrierProgID, "vertexShader1.txt", "fragmentShader1.txt");

	glGenVertexArrays(1, &playerVao); //Gen Vertex Array
	glBindVertexArray(playerVao);

	glGenBuffers(1, &playerVbo);		//Gen Vertex Buffer
	glBindBuffer(GL_ARRAY_BUFFER, playerVbo);

	//Vertices (3) x,y,z , Colors (4) RGBA, time
	glBufferData(GL_ARRAY_BUFFER, ((3 * player_VERTICES) + (4 * player_COLORS) + 1) * sizeof(GLfloat), NULL, GL_STATIC_DRAW);

	glGenBuffers(1, &playerVib); //Gen Vertex Index Buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, playerVib);

	//Indices to be drawn
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * player_INDICES * sizeof(GLuint), player_indices, GL_STATIC_DRAW);
	createProg(playerProgID, "vertexShader0.txt", "fragmentShader1.txt");

	// Enable Depth Test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	viewNormal = view;
	viewMoveLeft = rotate(view, 0.2f, vec3(0, 0, 1));
	viewMoveRight = rotate(view, -0.2f, vec3(0, 0, 1));
	m_ftArial.loadFromFile("./Assets/Fonts/BBrick.ttf");
	m_lblScore.intialise("Score: ", sf::Vector2f(500, 50), &m_ftArial);

	startGame();

	loseTxt.intialise("Game Over", sf::Vector2f(300, 200), &m_ftArial, sf::Color::Yellow, 0, 128);
	m_endScreenScore.intialise("Score: ", sf::Vector2f(360, 400), &m_ftArial);
	restartBtn.initialise(sf::Vector2f(600, 500), 250, 50, sf::Color::White, sf::Color::Green, sf::Color::Yellow, std::string("Press Enter"), &m_ftArial);

	/*-------------------------LICENSE ELEMENTS-----------------------*/
	if (!texture.loadFromFile("./Assets/Textures/Logo.png"))
	{
		cout << "cant load logo" << endl;
	}
	alpha = 0;
	licenseSprite.setTexture(texture);
	licenseSprite.setPosition(50, 0);
	licenseSprite.setColor(sf::Color(255, 255, 255, alpha));
	/*----------------------------------------------------------------*/
	/*-------------------------SPLASH ELEMENTS------------------------*/
	if (!splashTexture.loadFromFile("./Assets/Textures/splash.png"))
	{
		cout << "Can't load splash" << endl;
	}
	splashSprite.setTexture(splashTexture);
	splashSprite.setPosition(50, 100);
	splashSprite.setColor(sf::Color(255, 255, 255, alpha));
	m_lblSplashScreen.intialise("Press Enter to Start", sf::Vector2f(400, 500), &m_ftArial);
	/*----------------------------------------------------------------*/
	if (!m_bgMusic.openFromFile("./Assets/Audio/beat.ogg"))
	{
		std::cout << "BG MUSIC FILE NOT FOUND" << std::endl;
	}
	m_bgMusic.play();
	m_bgMusic.setLoop(true);
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
void Game::loadTexture(GLuint texture, std::string fileName)
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
	switch (currentScreen)
	{
	case GameState::License:
	{
		std::cout << m_cumlativeTime.asSeconds() << std::endl;
		licenseSprite.setColor(sf::Color(255, 255, 255, alpha));

		if (alpha < 255 && !fadingAway)
		{
			alpha++;
			if (alpha == 255)
			{
				fadingAway = true;
			}
		}

		else if (alpha > 0 && fadingAway)
		{
			alpha--;
		}

		if (fadingAway && alpha == 0)
		{
			currentScreen = GameState::Splash;
			m_cumlativeTime = m_cumlativeTime.Zero;
		}
		break;
	}
	case GameState::Splash:
	{
		
		if (alpha < 255)
		{
			alpha++;
		}
		splashSprite.setColor(sf::Color(255, 255, 255, alpha));
		if (Keyboard::isKeyPressed(Keyboard::Return) || (gamePad.m_currentState.A && !gamePad.m_previousState.A))
		{

			currentScreen = GameState::Play;
			startGame();

		}
		break;
	}
	case GameState::End:
	{
		m_endScreenScore.setText("Score: " + std::to_string((int)score));
		if (Keyboard::isKeyPressed(Keyboard::Return) || (gamePad.m_currentState.A && !gamePad.m_previousState.A))
		{

			currentScreen = GameState::Play;
			startGame();

		}
		break;
	}
	case GameState::Play:
	{
		m_lblScore.setText("Score: " + std::to_string((int)score));
		triangleRect.setPosition(playerModel[3].x, playerModel[3].z);
#if (DEBUG >= 2)
		DEBUG_MSG("Updating...");
#endif
		for (size_t i = 0; i < 6; i++)
		{
			cubeRect.setPosition(cubeModel[i][3].x, cubeModel[i][3].z);
			if (cubeRect.getGlobalBounds().intersects(triangleRect.getGlobalBounds()))
			{
				std::cout << "HIT" << std::endl;
				currentScreen = GameState::End;
			}
			else
			{
				//std::cout << ""<<std::endl;
			}
		}


		if (count > 300)
		{
			cubeSpeed += 0.05f;
			count = 0;
		}
		count++;
		moveCubes();
		break;
	}
	default:
		break;
	}
}
void Game::moveCubes()
{
	for (size_t i = 0; i < 6; i++)
	{
		cubeModel[i] = translate(cubeModel[i], vec3(0, 0, cubeSpeed));
		if (cubeModel[i][3].z > 12)
		{
			cubeModel[i] = translate(cubeModel[i], vec3(0, 0, -600));
			score += (10 + cubeSpeed);
		}
		buildingModel[i] = translate(buildingModel[i], vec3(0, 0, 0.002));
		if (buildingModel[i][3].z > 500)
		{
			buildingModel[i] = translate(buildingModel[i], vec3(0, 0, -3.0));
		}
	}
}
void Game::render()
{

#if (DEBUG >= 2)
	DEBUG_MSG("Render Loop...");
#endif
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Save current OpenGL render states
	// https://www.sfml-dev.org/documentation/2.0/classsf_1_1RenderTarget.php#a8d1998464ccc54e789aaf990242b47f7
	window.pushGLStates();

	renderSFML();

	window.popGLStates();
	

	renderOGL();
	

	window.display();


	//Disable Arrays
	glDisableVertexAttribArray(positionID);
	glDisableVertexAttribArray(colorID);
	glDisableVertexAttribArray(uvID);
	count++;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glTexEnvfv(0, 0, 0);
}
void Game::cubeRender(mat4 &model, GLuint &prog, GLuint texture)
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
	glActiveTexture(GL_TEXTURE0 +texture);
	glUniform1i(textureID, texture);

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
	glDrawElements(GL_TRIANGLES, 50, GL_UNSIGNED_INT, NULL);
}
void Game::barrierRender(mat4 &model, GLuint &prog)
{

	mvp = projection * view * (model);

	glUseProgram(prog);
	readIDs(prog);

	//VBO Data....vertices, colors and UV's appended
	glBufferSubData(GL_ARRAY_BUFFER, 0 * BARRIER_VERTICES * sizeof(GLfloat), 3 * BARRIER_VERTICES * sizeof(GLfloat), BARRIER_vertices);
	glBufferSubData(GL_ARRAY_BUFFER, 3 * BARRIER_VERTICES * sizeof(GLfloat), 4 * BARRIER_COLORS * sizeof(GLfloat), BARRIER_colors);
	// Send transformation to shader mvp uniform
	glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);

	//Set pointers for each parameter (with appropriate starting positions)
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glVertexAttribPointer.xml
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, 0, (VOID*)(3 * BARRIER_VERTICES * sizeof(GLfloat)));

	//Enable Arrays
	glEnableVertexAttribArray(positionID);
	glEnableVertexAttribArray(colorID);

	//Draw Element Arrays
	glDrawElements(GL_TRIANGLES, 50, GL_UNSIGNED_INT, NULL);
}
void Game::playerRender(mat4 &model, GLuint &prog)
{

	mvp = projection * view * (model);

	glUseProgram(prog);
	readIDs(prog);

	//VBO Data....vertices, colors and UV's appended
	glBufferSubData(GL_ARRAY_BUFFER, 0 * player_VERTICES * sizeof(GLfloat), 3 * player_VERTICES * sizeof(GLfloat), player_vertices);
	glBufferSubData(GL_ARRAY_BUFFER, 3 * player_VERTICES * sizeof(GLfloat), 4 * player_COLORS * sizeof(GLfloat), player_colors);
	// Send transformation to shader mvp uniform
	glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);
	glUniform1f(timeID, 0.05f);
	//Set pointers for each parameter (with appropriate starting positions)
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glVertexAttribPointer.xml
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, 0, (VOID*)(3 * player_VERTICES * sizeof(GLfloat)));

	//Enable Arrays
	glEnableVertexAttribArray(positionID);
	glEnableVertexAttribArray(colorID);

	//Draw Element Arrays
	glDrawElements(GL_TRIANGLES, 50, GL_UNSIGNED_INT, NULL);
}
void Game::unload()
{
#if (DEBUG >= 2)
	DEBUG_MSG("Cleaning up...");
#endif
	for (size_t i = 0; i < 3; i++)
	{
		glDeleteProgram(cubeProgID[i]);	//Delete Shader
	}
	glDeleteBuffers(1, &cubeVbo);	//Delete Vertex Buffer
	glDeleteBuffers(1, &cubeVib);	//Delete Vertex Index Buffer
	stbi_image_free(img_data);		//Free image
}
void Game::readIDs(GLuint &prog)
{
	positionID = glGetAttribLocation(prog, "sv_position");
	colorID = glGetAttribLocation(prog, "sv_color");
	uvID = glGetAttribLocation(prog, "sv_uv");
	textureID = glGetUniformLocation(prog, "f_texture");
	mvpID = glGetUniformLocation(prog, "sv_mvp");
	timeID = glGetUniformLocation(prog, "time");
}
void Game::startGame()
{// Projection Matrix 
	projection = perspective(
		45.0f,					// Field of View 45 degrees
		4.0f / 3.0f,			// Aspect ratio
		0.1f,					// Display Range Min : 0.1f unit
		400.0f					// Display Range Max : 500.0f unit
	);

	// Camera Matrix
	view = lookAt(
		vec3(0.0f, 4.0f, 10.0f),	// Camera (x,y,z), in World Space
		vec3(0.0f, 0.0f, 0.0f),		// Camera looking at origin
		vec3(0.0f, 1.0f, 0.0f)		// 0.0f, 1.0f, 0.0f Look Down and 0.0f, -1.0f, 0.0f Look Up
	);
	for (int i = 0; i < NUM_OF_CUBES; i++)
	{
		// cubeModel matrix
		cubeModel[i] = mat4(1.0f);// Identity Matrix
		buildingModel[i] = mat4(1.0f);
		buildingModel[i] = translate(buildingModel[i], vec3(0, -15, 0));
		if (i % 2 == 0)
		buildingModel[i] = translate(buildingModel[i], vec3(0, 0, -800));
		if (i < 2)
			buildingModel[i] = translate(buildingModel[i], vec3(-40, 0, 0));
		else if (i >= 4)
			buildingModel[i] = translate(buildingModel[i], vec3(40, -0, 0));
		buildingModel[i] = scale(buildingModel[i], vec3(10, 15, 600));
	}
	playerModel = mat4(1.0f);
	barrierModel[0] = mat4(1.0f);
	barrierModel[1] = mat4(1.0f);

	cubeModel[0] = translate(cubeModel[0], vec3(-2, 2, -500));
	cubeModel[1] = translate(cubeModel[1], vec3(4, 2, -400));
	cubeModel[2] = translate(cubeModel[2], vec3(-6, 2, -700));
	cubeModel[3] = translate(cubeModel[3], vec3(8, 2,-700));
	cubeModel[4] = translate(cubeModel[4], vec3(-8, 2, -500));
	cubeModel[5] = translate(cubeModel[5], vec3(0, 2, -600));

	barrierModel[0] = translate(barrierModel[0], vec3(-10, 1, 0));
	barrierModel[1] = translate(barrierModel[1], vec3(10, 1, 0));

	//playerModel = rotate(playerModel, 0.2f, vec3(1, 0, 0));
	viewNormal = view;
	viewMoveLeft = rotate(view, 0.2f, vec3(0, 0, 1));
	viewMoveRight = rotate(view, -0.2f, vec3(0, 0, 1));

	playerMoveLeft = rotate(playerModel, -0.02f, vec3(0, 0, 1));
	playerMoveRight = rotate(playerModel, 0.02f, vec3(0, 0, 1));
	playerNormal = playerModel;

	triangleRect.setSize(sf::Vector2f(1, 1));
	cubeRect.setSize(sf::Vector2f(2, 2));
	score = 0;
	cubeSpeed = 0.05;
}
void Game::gamePadControl()
{
	gamePad.update();
	float analogueDivider = 1000;
	float leftAnalogue = gamePad.m_currentState.LeftThumbStick.x;
	if (leftAnalogue < -20)
	{
		if (playerModel[3].x > -8.8) {
			// Set cubeModel Rotation
			playerModel = translate(playerModel, vec3(leftAnalogue / analogueDivider, 0, 0));
			playerMoveLeft = translate(playerModel, vec3(leftAnalogue / analogueDivider, 0, 0));
			playerMoveRight = translate(playerModel, vec3(leftAnalogue / analogueDivider, 0, 0));
			playerNormal = translate(playerModel, vec3(leftAnalogue / analogueDivider, 0, 0));
			playerModel = playerMoveLeft;

			viewNormal = translate(viewNormal, vec3(-leftAnalogue / analogueDivider / 2, 0, 0));
			viewMoveLeft = translate(viewMoveLeft, vec3(-leftAnalogue / analogueDivider / 2, 0, 0));
			viewMoveRight = translate(viewMoveRight, vec3(-leftAnalogue / analogueDivider / 2, 0, 0));
			view = viewMoveLeft;
		}
	}
	if (leftAnalogue > 20)
	{
		if (playerModel[3].x < 8.8) {
			playerModel = translate(playerModel, vec3(leftAnalogue / analogueDivider, 0, 0));
			playerMoveLeft = translate(playerModel, vec3(leftAnalogue / analogueDivider, 0, 0));
			playerMoveRight = translate(playerModel, vec3(leftAnalogue / analogueDivider, 0, 0));
			playerNormal = translate(playerModel, vec3(leftAnalogue / analogueDivider, 0, 0));
			playerModel = playerMoveRight;

			viewNormal = translate(viewNormal, vec3(-leftAnalogue / analogueDivider / 2, 0, 0));
			viewMoveLeft = translate(viewMoveLeft, vec3(-leftAnalogue / analogueDivider / 2, 0, 0));
			viewMoveRight = translate(viewMoveRight, vec3(-leftAnalogue / analogueDivider / 2, 0, 0));
			view = viewMoveRight;

		}
	}
}
void Game::renderSFML()
{
	switch (currentScreen)
	{
	case GameState::License:
	{
		window.draw(licenseSprite);
		break;
	}
	case GameState::Splash:
	{
		window.draw(splashSprite);
		m_lblSplashScreen.draw(&window);
		break;
	}
	case GameState::End:
	{
		m_endScreenScore.draw(&window);
		loseTxt.draw(&window);
		restartBtn.draw(&window);
		break;
	}
	case GameState::Play:
	{
		m_lblScore.draw(&window);
		break;
	}

	default:
		break;
	}
}
void Game::renderOGL()
{
	switch (currentScreen)
	{
	case GameState::Play:
	{
		glBindBuffer(GL_ARRAY_BUFFER, cubeVao);
		glBindBuffer(GL_ARRAY_BUFFER, cubeVbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeVib);
		for (size_t i = 0; i < 6; i++)
		{
			cubeRender(buildingModel[i], cubeProgID[2], 1);
			if (i < 3)
				cubeRender(cubeModel[i], cubeProgID[1], 0);
			else
				cubeRender(cubeModel[i], cubeProgID[1], 0);
		}

		glBindBuffer(GL_ARRAY_BUFFER, barrierVao);
		glBindBuffer(GL_ARRAY_BUFFER, barrierVbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, barrierVib);
		barrierRender(barrierModel[0], barrierProgID);
		barrierRender(barrierModel[1], barrierProgID);

		glBindBuffer(GL_ARRAY_BUFFER, playerVao);
		glBindBuffer(GL_ARRAY_BUFFER, playerVbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, playerVib);
		playerRender(playerModel, playerProgID);
		break;
	}
	default:
	{
		break;
	}
	}

}