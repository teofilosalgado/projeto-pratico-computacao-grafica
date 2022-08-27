#pragma once
#include <string>
#include "texture.h"
#include "model.h"
class Object
{
public:
	Object(Model* model, Texture* texture);
private:
	Model* model;
	Texture* texture;
};

