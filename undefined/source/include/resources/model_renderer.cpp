#include "model_renderer.h"

#include "resources/model.h"

void ModelRenderer::Draw()
{
	ModelObject->Draw(GameTransform->LocalToWorldMatrix());
}
