#pragma once

#include "camera.h"
#include "shader.h"
#include "texture.h"
#include "model.h"
#include "scene.h"

class Level
{
public:
	Level(Camera* camera);
	void run(bool is_paused);
private:
	Scene* scene;
};

