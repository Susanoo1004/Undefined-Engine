#include "interface\FPSgraph.h"

#include <glfw/glfw3.h>
#include <imgui/imgui.h>
#include <string>

#include "utils/utils.h"

void FPSGraph::Init()
{
    mUpdateTime = 0.1f;
    mLastTotalTime = glfwGetTime();
    mMaxFPS = 200.0f;
    mArraySize = 50;
}

void FPSGraph::ShowWindow()
{
    ImGui::Begin("FPS Graph");
 
    // Every ImGUI slider 
    ImGui::SliderFloat("Time between updates", &mUpdateTime, 0.0f, 1.0f, "%.2f");
    ImGui::SliderFloat("Max FPS", &mMaxFPS, 0.0f, 300, "%.2f");
    if (ImGui::SliderInt("Array Size", &mArraySize, 2, 100))
    {
        mFrameRateArray.resize(mArraySize);
    }

    if (Utils::OnInterval(glfwGetTime(), mLastTotalTime, mUpdateTime))
    {
        float lastFPS = 1.0f / ImGui::GetIO().DeltaTime;

        if (mFrameRateArray.size() < mArraySize)
            mFrameRateArray.push_back(lastFPS);
        
        // We check if the ArrayIndex is in the FrameRateArray size so there is no vector out of range because of call stack when we change ArraySize
        if(mArrayIndex <= mFrameRateArray.size())
            mFrameRateArray[mArrayIndex] = lastFPS;

        mArrayIndex = (mArrayIndex + 1) % mFrameRateArray.size();
        mLastTotalTime = glfwGetTime();
    }

    std::string string = "average : " + std::to_string((int)Utils::Average(mFrameRateArray));

    if (mMaxFPS < Utils::Average(mFrameRateArray))
    {
        mMaxFPS = Utils::Average(mFrameRateArray) + 5;
    }

    // Draw FPS Graph
    ImGui::PlotLines("", mFrameRateArray.data(), (int)mFrameRateArray.size(), 0, string.c_str(), 0, mMaxFPS, ImGui::GetContentRegionAvail());

    ImGui::End();
}

void FPSGraph::Delete()
{
    mFrameRateArray.resize(0);
    mFrameRateArray.shrink_to_fit();
}
