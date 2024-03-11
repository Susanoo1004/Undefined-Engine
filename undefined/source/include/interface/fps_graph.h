#pragma once 

#include <vector>
#include <glfw/glfw3.h>

#include "utils/flag.h"

class FPSGraph
{
	STATIC_CLASS(FPSGraph)

public:
	//Update for the FPS Graph
	UNDEFINED_ENGINE static void ShowWindow();

	UNDEFINED_ENGINE static void Delete();

private:
	UNDEFINED_ENGINE static inline size_t mArrayIndex = 0;
	UNDEFINED_ENGINE static inline size_t mArraySizeOffset = 5;

	UNDEFINED_ENGINE static inline float mLastTotalTime = (float)glfwGetTime();
	UNDEFINED_ENGINE static inline float mUpdateTime = 0.1f;
	UNDEFINED_ENGINE static inline float mMaxFPS = 200;

	UNDEFINED_ENGINE static inline int mArraySize = 50;
	UNDEFINED_ENGINE static inline int mMinFpsOffset = 5;
	
	static inline std::vector<float> mFrameRateArray;
};