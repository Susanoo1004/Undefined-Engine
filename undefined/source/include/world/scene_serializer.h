#pragma once

#include "world/scene.h"

class SceneSerializer
{
public:
	SceneSerializer(Scene& scene);
	~SceneSerializer();

	void Serialize();
	void Deserialize();

	bool SerializeRuntime();
	bool DeserializeRuntime();

private:
	Scene& mScene;
};
