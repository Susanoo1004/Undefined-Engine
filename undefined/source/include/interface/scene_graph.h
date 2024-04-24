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

	static void NodeInteraction(Object* object);

	static void ClickSelectObject(Object* object);
	static void RightClickObject(Object* object);

	static void BeginDragObject(Object* object);
	static void BeginDropOnObject(Object* object, bool setBefore = false);

	static inline Object* mSelectedObject;
	
	// to del Debog
	static void Print(Object* object, const char* plus);
};