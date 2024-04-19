#pragma once

#include <refl.hpp>
#include <type_traits>

#include "utils/flag.h"
#include "resources/model.h"
#include "world/scene_manager/scene.h"
#include <type_traits>

class UNDEFINED_ENGINE Inspector
{
	STATIC_CLASS(Inspector)

public:
	static void Init();
	static void ShowWindow();

private:
    static inline Renderer* mRenderer;
};