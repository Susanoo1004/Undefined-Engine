#include "model_renderer.h"

#include "resources/model.h"

#include "imgui/imgui.h"

void ModelRenderer::Draw()
{
	ModelObject->Draw(GameTransform->LocalToWorldMatrix());
}
