#pragma once

#include "camera.h"
#include "shader.h"
#include "texture.h"
#include "model.h"
#include "scene.h"

class Level
{
public:
	Level(float width, float height);
	Scene* scene;
	Camera* camera;
	void run(bool is_paused);
	bool is_ended;
};

