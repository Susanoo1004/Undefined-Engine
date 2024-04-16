#pragma once

#include "world/components/component.h"
#include <refl.hpp>

class Model;

/// <summary>
/// Class for ModelRenderer that draw the model
/// </summary>
class ModelRenderer : public Component
{
public:
	/// <summary>
	/// Draw the model
	/// </summary>
	void Draw() override;

	/// <summary>
	/// Model of the Object
	/// </summary>
	std::shared_ptr<Model> ModelObject;
};

REFL_AUTO(type(ModelRenderer, bases<Component>))