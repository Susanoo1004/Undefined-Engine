#pragma once

#include "world/components/component.h"

class Model;

class ModelRenderer : public Component
{
public:
	void Draw() override;

	std::shared_ptr<Model> ModelObject;
};