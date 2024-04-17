#pragma once
#include "utils/flag.h"

class Object;

class SceneGraph
{
	STATIC_CLASS(SceneGraph)

public:
	static void DisplayWindow();

private:
	static void DisplayActualScene();
	static void DisplayObject(Object* object);

	static void ClickSelectObject(Object* object);

	static inline Object* mSelectedObject;
};