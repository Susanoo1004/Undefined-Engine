#include "interface\fps_graph.h"

#include <glfw/glfw3.h>
#include <imgui/imgui.h>
#include <string>

#include "utils/utils.h"

void FPSGraph::Init()
{
    mUpdateTime = 0.1f;
    mLastTotalTime = (float)glfwGetTime();
    mMaxFPS = 200.0f;
    mArraySize = 50;
    mMinFpsOffset = 5;
    mArraySizeOffset = 5;
}

void FPSGraph::ShowWindow()
{
    ImGui::Begin("FPS Graph");
 
    //Every ImGUI slider 
    ImGui::SliderFloat("Time between updates", &mUpdateTime, 0.0f, 1.0f, "%.2f");
    ImGui::SliderFloat("Max FPS", &mMaxFPS, 0.0f, 300, "%.2f");
    ImGui::SliderInt("Array Size", &mArraySize, 2, 100);

    if (Utils::OnInterval((float)glfwGetTime(), mLastTotalTime, mUpdateTime))
    {
        float lastFPS = 1.0f / ImGui::GetIO().DeltaTime;

        //If the array is not full we pushback values instead of going to an index to modify the value so the array fills up and display a correct fps average and not an average with multiple zero's in the array
        if (mFrameRateArray.size() < mArraySize)
        {
            mFrameRateArray.push_back(lastFPS);
        }

        //If the array is full we resize it and move the arrayIndex to the arraySize minus an offset to avoid vector out of range fatal error
        else if (mFrameRateArray.size() > mArraySize)
        {
            mFrameRateArray.resize(mArraySize);
            mArrayIndex = mArraySize - mArraySizeOffset;
        }
        
        //We check if the ArrayIndex is in the FrameRateArray size so there is no vector out of range because of call stack when we change ArraySize
        if(mArrayIndex <= mFrameRateArray.size())
            mFrameRateArray[mArrayIndex] = lastFPS;

        mArrayIndex = (mArrayIndex + 1) % mFrameRateArray.size();
        mLastTotalTime = (float)glfwGetTime();
    }

    std::string string = "average : " + std::to_string((int)Utils::Average(mFrameRateArray));

    //Cap the min fps to : current fps + 5
    if (mMaxFPS < Utils::Average(mFrameRateArray))
    {
        mMaxFPS = Utils::Average(mFrameRateArray) + mMinFpsOffset;
    }

    //Draw FPS Graph
    ImGui::PlotLines("", mFrameRateArray.data(), (int)mFrameRateArray.size(), 0, string.c_str(), 0, mMaxFPS, ImGui::GetContentRegionAvail());

    ImGui::End();
}

void FPSGraph::Delete()
{
    mFrameRateArray.resize(0);
    mFrameRateArray.shrink_to_fit();
}
