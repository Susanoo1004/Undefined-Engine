#include "world/scene_serializer.h"



SceneSerializer::SceneSerializer(Scene& scene)
	: mScene(scene)
{
}

SceneSerializer::~SceneSerializer()
{
}

void SceneSerializer::Serialize(const std::filesystem::path& path)
{


	
}

void SceneSerializer::Deserialize(const std::filesystem::path& path)
{
}

bool SceneSerializer::SerializeRuntime(const std::filesystem::path& path)
{
	return false;
}

bool SceneSerializer::DeserializeRuntime(const std::filesystem::path& path)
{
	return false;
}
