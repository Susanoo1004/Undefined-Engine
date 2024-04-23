#pragma once

#include "world/scene.h"

class SceneSerializer
{
public:
	SceneSerializer(Scene& scene);
	~SceneSerializer();

	void Serialize(const std::filesystem::path& path);
	void Deserialize(const std::filesystem::path& path);

	bool SerializeRuntime(const std::filesystem::path& path);
	bool DeserializeRuntime(const std::filesystem::path& path);

private:
	Scene& mScene;
};
