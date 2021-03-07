#include "Tema2.h"
#include <iostream>
#include <Core/Engine.h>

Tema2::Tema2()
{
	camera = new Cam::Camera();

	projectionMatrix = glm::mat4(1);

	player = new Player(ORIGIN, PLAYER_SIZE);

	start_platform = new Platform(ORIGIN, PLATFORM_SIZE);

	generator = new Generator();

	camera_mode = false;
}

Tema2::~Tema2()
{
}

void Tema2::Init()
{
	{
		Mesh* sphere = new Mesh("player");
		sphere->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[sphere->GetMeshID()] = sphere;
	}

	{
		Mesh* start_platform_mesh = Object3D::CreateCube("start_platform", start_platform->getCenter(), start_platform->getLength(), GRAY, true);
		AddMeshToList(start_platform_mesh);

		start_platform->scale(START_PLATFORM_SIZE, PLATFORM_SCALE_Y, START_PLATFORM_SIZE);
		start_platform->translate(0, 0, -start_platform->getLength() / 2);
	}

	{
		Mesh* platform_mesh = Object3D::CreateCube("platform", ORIGIN, PLATFORM_SIZE, GREEN, true);
		AddMeshToList(platform_mesh);
	}

	{
		Mesh* obstacle_mesh = Object3D::CreateCube("obstacle", ORIGIN, OBSTACLE_SIZE, WHITE, true);
		AddMeshToList(obstacle_mesh);
	}

	{
		glm::ivec2 resolution = window->GetResolution();

		Mesh* fuel_mesh = Object3D::CreateSquare("fuel", ORIGIN, FUEL_SIZE, GREEN);
		AddMeshToList(fuel_mesh);
	}

	player->translate(0, start_platform->getHeight() / 2 + player->getDiameter() / 2, 0);

	Pattern** patterns = generator->getPatterns();
	for (int i = 0; i < PATTERN_COUNT; i++) {
		generator->generate(patterns[i]);
	}

	{
		Shader* shader = new Shader("Shader");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	start_platform->setColor(GRAY);
}

void Tema2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

	Platform::willLand = false;

	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(0.85f, 0.5f, 0);
	modelMatrix *= Transform3D::Scale(1, player->getFuel() / 500, 1);
	RenderSimpleMesh(meshes["fuel"], shaders["Shader"], modelMatrix, BROWN, 3);

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(0.85f, 0.5f, 0);
	RenderSimpleMesh(meshes["fuel"], shaders["Shader"], modelMatrix, WHITE, 3);
}

void Tema2::Update(float deltaTimeSeconds)
{
	player->setDifficultyTime(player->getDifficultyTime() + deltaTimeSeconds);

	if (player->getDifficultyTime() > GAME_DIFF_TIME) {
		player->setMinAccel(player->getMinAccel() + GAME_DIFF_INC);
		player->setDifficultyTime(0);
	}

	if (player->isInvincible()) {
		player->setInvincibilityTime(player->getInvincibilityTime() + deltaTimeSeconds);
	}

	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

	if (camera_mode) {
		camera->Set(player->getPosition() - glm::vec3(0, 0, player->getDiameter() / 2),
			player->getPosition() - glm::vec3(0, 0, player->getDiameter() / 2 + 1),
			glm::vec3(0, 1, 0));
	}
	else {
		camera->Set(player->getPosition() + glm::vec3(0, 3.5f * player->getDiameter() / 2, 3.5f * player->getDiameter()),
			player->getPosition(),
			glm::vec3(0, 1, 0));
	}

	if (!player->isDead()) {
		generator->translate(0, 0, (GAME_SPEED + player->getAcceleration()) * deltaTimeSeconds);
		start_platform->translate(0, 0, (GAME_SPEED + player->getAcceleration()) * deltaTimeSeconds);
	}

	Pattern** patterns = generator->getPatterns();
	for (int i = 0; i < PATTERN_COUNT; i++) {
		if (patterns[i]->getUp() > PLATFORM_DEATH) {
			generator->setGone(i);
		}

		if (generator->isGone(i)) {
			patterns[i]->resetPlatforms();
			generator->generate(patterns[i]);
		}

		int count = patterns[i]->getCount();

		Platform** platforms = patterns[i]->getPlatforms();
		Obstacle** obstacles = patterns[i]->getObstacles();

		for (int j = 0; j < count; j++) {
			RenderSimpleMesh(meshes["platform"], shaders["Shader"], platforms[j]->getMatrix(), platforms[j]->getColor(), 0);
		}

		for (int j = 0; j < count / 3; j++) {
			if (obstacles[j]->isRendered()) {
				RenderSimpleMesh(meshes["obstacle"], shaders["Shader"], obstacles[j]->getMatrix(), obstacles[j]->getColor(), 0);
			}
		}
	}

	generator->checkLanding(player);
	generator->checkIfLanded(player);

	RenderSimpleMesh(meshes["start_platform"], shaders["Shader"], start_platform->getMatrix(), start_platform->getColor(), 0);
	start_platform->checkLanding(player);

	if (player->getPowerUp()) {
		if (!camera_mode) {
			RenderSimpleMesh(meshes["player"], shaders["Shader"], player->getMatrix(), RED, 1);
		}
		player->setPowerUpTime(player->getPowerUpTime() + deltaTimeSeconds);
	}
	else if (!player->isDead() && !camera_mode) {
		if (player->isInvincible() && player->isBlocked()) {
			RenderSimpleMesh(meshes["player"], shaders["Shader"], player->getMatrix(), BOTH, 0);
		}
		else if (player->isInvincible()) {
			RenderSimpleMesh(meshes["player"], shaders["Shader"], player->getMatrix(), BLUE, 0);
		}
		else if (player->isBlocked()) {
			RenderSimpleMesh(meshes["player"], shaders["Shader"], player->getMatrix(), ORANGE, 0);
		}
		else {
			RenderSimpleMesh(meshes["player"], shaders["Shader"], player->getMatrix(), RED, 0);
		}
	}

	if (player->isDead()) {
		camera_mode = false;

		RenderSimpleMesh(meshes["player"], shaders["Shader"], player->getMatrix(), RED, player->getDeathType());

		player->setDeathTime(player->getDeathTime() + deltaTimeSeconds);

		if (player->getDeathTime() >= DEATH_TIME) {
			printf("GAME OVER\n");
			exit(1);
		}
	}

	if (!Platform::willLand) {
		player->setGround(PLAYER_DEATH);
		if (!player->isJumping()) {
			player->setFall(true);
		}
		else {
			player->setFall(false);
		}
	}

	if (!player->isDead()) {
		if (player->isJumping() && !player->isFalling()) {
			player->doJump(deltaTimeSeconds, PLAYER_JUMP_HEIGHT);
		}

		if (player->isFalling()) {
			player->doFall(deltaTimeSeconds);
		}
	}

	if (player->isBlocked()) {
		player->setBlockedTime(player->getBlockedTime() + deltaTimeSeconds);
		player->setAcceleration(MAX_ACCEL);
	}

	if (!player->isDead()) {
		player->useFuel(deltaTimeSeconds);
	}

	if (player->getFuel() == 0) {
		player->setDeath(true);
	}
}

void Tema2::FrameEnd()
{
}

void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color, const int type)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	float timeLoc = glGetUniformLocation(shader->program, "time");
	glUniform1f(timeLoc, player->getDeathTime());

	int location = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	location = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));

	location = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	location = glGetUniformLocation(shader->program, "type");
	glUniform1i(location, type);

	location = glGetUniformLocation(shader->program, "v_color");
	glUniform3fv(location, 1, glm::value_ptr(color));


	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	float playerSpeed = PLAYER_LATERAL_SPEED * deltaTime;

	if (!player->isBlocked()) {
		if (window->KeyHold(GLFW_KEY_W)) {
			player->setAcceleration(player->getAcceleration() + deltaTime * ACCEL_FACTOR);
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			player->setAcceleration(player->getAcceleration() - deltaTime * ACCEL_FACTOR);
		}
	}

	if (!player->isDead()) {
		if (window->KeyHold(GLFW_KEY_A)) {
			player->translate(-playerSpeed, 0, 0);
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			player->translate(playerSpeed, 0, 0);
		}
	}
}

void Tema2::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_SPACE && !player->isJumping() && !player->isFalling()) {
		player->setJump(true);
	}

	if (key == GLFW_KEY_C) {
		camera_mode = !camera_mode;
	}
}

void Tema2::OnKeyRelease(int key, int mods)
{
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}
