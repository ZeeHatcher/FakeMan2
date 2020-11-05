#include "CollidableObject.h"

CollidableObject::CollidableObject(float x, float y, int32_t width, int32_t height, color col)
	: DrawableObject(x, y, width, height, col)
{
}

// Checks collision between 2 CollidableObjects
bool CollidableObject::isCollide(CollidableObject* ent)
{
	return rectangles_intersect(bounding_, ent->bounding_);
}