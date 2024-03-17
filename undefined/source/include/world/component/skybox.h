#pragma once

#include <string>
#include <toolbox/Matrix3x3.h>
#include <toolbox/Matrix4x4.h>

#include "utils/flag.h"
#include "world/component/component.h"
#include "camera/camera.h"
#include "resources/shader.h"

class Skybox : public Component
{
public:
	UNDEFINED_ENGINE static void Setup();
	UNDEFINED_ENGINE static void Update(Camera* camera, std::shared_ptr<Shader> skyboxShader);

	static inline float skyboxVertices[24] =
	{
		//   Coordinates
		-1.0f, -1.0f,  1.0f,//        7--------6
		 1.0f, -1.0f,  1.0f,//       /|       /|
		 1.0f, -1.0f, -1.0f,//      4--------5 |
		-1.0f, -1.0f, -1.0f,//      | |      | |
		-1.0f,  1.0f,  1.0f,//      | 3------|-2
		 1.0f,  1.0f,  1.0f,//      |/       |/
		 1.0f,  1.0f, -1.0f,//      0--------1
		-1.0f,  1.0f, -1.0f
	};

	static inline unsigned int skyboxIndices[36] =
	{
		// Right
		1, 2, 6,
		6, 5, 1,
		// Left
		0, 4, 7,
		7, 3, 0,
		// Top
		4, 5, 6,
		6, 7, 4,
		// Bottom
		0, 3, 2,
		2, 1, 0,
		// Back
		0, 1, 5,
		5, 4, 0,
		// Front
		3, 7, 6,
		6, 2, 3
	};

	static inline std::string facesCubemap[6] =
	{
		"../undefined/skybox/right.jpg",
		"../undefined/skybox/left.jpg",
		"../undefined/skybox/top.jpg",
		"../undefined/skybox/bottom.jpg",
		"../undefined/skybox/front.jpg",
		"../undefined/skybox/back.jpg"
	};

	static inline unsigned int mSkyboxVAO;
	static inline unsigned int mSkyboxVBO;
	static inline unsigned int mSkyboxEBO;

	static inline unsigned int cubemapTexture;

	static inline Matrix4x4 view;
	static inline Matrix4x4 projection;
};