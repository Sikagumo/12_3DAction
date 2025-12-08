#include "ColliderSphere.h"
#include "./ColliderBase.h"

ColliderSphere::ColliderSphere(TAG tag, const Transform* follow, const VECTOR& localPos, float radius):
	ColliderBase::ColliderBase(SHAPE::SPHERE, tag, follow),
	localPos_(localPos),radius_(radius)
{

}

const VECTOR& ColliderSphere::GetLocalPos(void) const
{
	return localPos_;
}

VECTOR ColliderSphere::GetPos(void) const
{
	return GetRotPos(localPos_);
}

void ColliderSphere::DrawDebug(int color)
{
	DrawSphere3D(GetPos(), radius_, 10, color, color, true);
}
