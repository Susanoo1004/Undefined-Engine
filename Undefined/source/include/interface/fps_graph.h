#pragma once 

#include <vector>

#include "utils/flag.h"

class FPSGraph
{
	STATIC_CLASS(FPSGraph)

public:
	UNDEFINED_ENGINE static void Init();

	//Update for the FPS Graph
	UNDEFINED_ENGINE static void ShowWindow();

	UNDEFINED_ENGINE static void Delete();

private:
	UNDEFINED_ENGINE static inline float mUpdateTime;
	UNDEFINED_ENGINE static inline size_t mArrayIndex;
	UNDEFINED_ENGINE static inline float mLastTotalTime;
	UNDEFINED_ENGINE static inline float mMaxFPS;
	UNDEFINED_ENGINE static inline int mArraySize;
	UNDEFINED_ENGINE static inline int mMinFpsOffset;
	UNDEFINED_ENGINE static inline size_t mArraySizeOffset;
	static inline std::vector<float> mFrameRateArray;

};