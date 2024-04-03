#pragma once 

#include <vector>
#include <glfw/glfw3.h>

#include "utils/flag.h"

class FPSGraph
{
	STATIC_CLASS(FPSGraph)

public:
	//Update for the FPS Graph
	static void ShowWindow();
	static void Delete();

private:
	static inline size_t mArrayIndex = 0;
	static inline size_t mArraySizeOffset = 5;

	static inline float mLastTotalTime = (float)glfwGetTime();
	static inline float mUpdateTime = 0.1f;
	static inline float mMaxFPS = 200;

	static inline int mArraySize = 50;
	static inline int mMinFpsOffset = 5;
	
	static inline std::vector<float> mFrameRateArray;
};