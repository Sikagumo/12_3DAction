#pragma once
#include "./ColliderBase.h"
#include <vector>
#include <string>

class ColliderModel : public ColliderBase
{
public:

	// コンストラクタ
	ColliderModel(TAG _tag, const Transform * _follow);

	// デストラクタ
	~ColliderModel(void) override = default;


	// 指定された文字を含むフレームを衝突判定から除外
	void AddExcludeFrameIds(const std::string& _name);

	// 衝突判定から除外するフレームをクリアする
	void ClearExcludeFrame(void);

	// 除外フレーム判定
	bool IsExcludeFrame(int _frameIdx) const;

	// 指定された文字を含むフレームを衝突判定対象とする
	void AddTargetFrameIds(const std::string& _name);

	// 衝突判定の対象するフレームをクリアする
	void ClearTargetFrame(void);

	// 対象フレーム判定
	bool IsTargetFrame(int _frameIdx) const;


protected:

	// 衝突判定から除外するフレーム番号
	std::vector<int> excludeFrameIds_;

	// 衝突判定の対象とするフレーム番号
	std::vector<int> targetFrameIds_;


	// デバッグ用描画
	void DrawDebug(int color) override {}


};