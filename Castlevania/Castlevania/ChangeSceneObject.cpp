#include "ChangeSceneObject.h"
#include "Define.h"

void ChangeSceneObject::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = l + CHANGE_SCENE_BBOX_WIDTH;
	b = t + CHANGE_SCENE_BBOX_HEIGHT;
}

