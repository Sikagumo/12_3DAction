#pragma once
#include "../Actor/ActorBase.h"

class Stage : public ActorBase
{
public:

	// è’ìÀîªíËéÌï 
	enum class COLLIDER_TYPE
	{
		MODEL = 0,
		MAX,
	};

	Stage(void);

	~Stage(void)override = default;

	void Update(void)override;

	void Draw(void)override;

protected:

	void InitLoad(void)override;

	void InitTransform(void)override;

	void InitCollider(void)override;

	void InitAnimation(void)override;

	void InitPost(void)override;
};