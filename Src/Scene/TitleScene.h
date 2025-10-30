#pragma once
#include "SceneBase.h"
#include "../Application.h"

class TitleScene : public SceneBase
{

public:

	// コンストラクタ
	TitleScene(void);

	// デストラクタ
	~TitleScene(void) override;

	// 初期化
	void Init(void) override;

	// 更新
	void Update(void) override;

	// 描画
	void Draw(void) override;

	// 解放
	void Release(void) override;

private:

	static constexpr int IMG_TITLE_X = (Application::SCREEN_HALF_X - 250);
	static constexpr int IMG_TITLE_Y = 85;

	static constexpr int IMG_PUSH_X = (Application::SCREEN_HALF_X - 250);
	static constexpr int IMG_PUSH_Y = (Application::SCREEN_HALF_Y + 125);

	int imgTitle_;
	int imgPushSpace_;
};
