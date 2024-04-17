#pragma once
#include "utils/flag.h"
#include <refl.hpp>
#include "resources/model.h"
#include "world/scene.h"
#include <type_traits>

class UNDEFINED_ENGINE Inspector
{
	STATIC_CLASS(Inspector)

public:
	static void Init();
	static void ShowWindow(Scene* scene);

private:
    static inline Renderer* mRenderer;
};