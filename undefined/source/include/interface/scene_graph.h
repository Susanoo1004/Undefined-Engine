#pragma once

#include <toolbox/Vector3.h>
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
	static void RightClickObject(Object* object);

	static inline Object* mSelectedObject;

	static inline Vector3 mBaseCamPos = Vector3();
	static inline bool mLerpCam = false;
	static inline float mCamTravelTime = 0;
};