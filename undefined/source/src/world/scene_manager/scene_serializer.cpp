#include "world/scene_manager/scene_serializer.h"

//#include <rfl.hpp>
//#include <rfl/json.hpp>


SceneSerializer::SceneSerializer(Scene& scene)
	: mScene(scene)
{
}

SceneSerializer::~SceneSerializer()
{
}

void SceneSerializer::Serialize(const std::filesystem::path& path)
{
	//const std::string json_string = rfl::json::write(mScene);
	//rfl::json::save("/assets/scenes/" + mScene.Name + std::string(".json"), json_string);

	
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
