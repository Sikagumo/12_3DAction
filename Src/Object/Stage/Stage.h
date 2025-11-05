#pragma once
#include "../Actor/ActorBase.h"

class Stage : public ActorBase
{
public:

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