#include "ColliderModel.h"
#include <string>
#include <vector>
#include "./ColliderBase.h"
#include "../Common/Transform.h"


ColliderModel::ColliderModel(TAG tag, const Transform* follow)
	:
	ColliderBase(SHAPE::MODEL, tag, follow)
{
}

void ColliderModel::AddExcludeFrameIds(const std::string& name)
{
	// フレーム数を取得
	int num = MV1GetFrameNum(follow_->modelId);
	for (int i = 0; i < num; i++)
	{
		// フレーム名称を取得
		std::string frameName = MV1GetFrameName(follow_->modelId, i);

		if (frameName.find(name) != std::string::npos)
		{
			// 除外フレームに追加(ホワイトリスト)
			excludeFrameIds_.emplace_back(i);
		}
	}
}

void ColliderModel::ClearExcludeFrame(void)
{
	excludeFrameIds_.clear();
}

bool ColliderModel::IsExcludeFrame(int frameIdx) const
{
	// 除外判定
	if (std::find(excludeFrameIds_.begin(),
				  excludeFrameIds_.end(),frameIdx) != excludeFrameIds_.end())
	{
		// 除外に該当する
		return true;
	}
	return false;
}

void ColliderModel::AddTargetFrameIds(const std::string& _name)
{
	// フレーム数を取得
	int num = MV1GetFrameNum(follow_->modelId);
	for (int i = 1; i < num; i++)
	{
		// フレーム名称を除外
		std::string frameName = MV1GetFrameName(follow_->modelId, i);
		if (frameName.find(_name) != std::string::npos)
		{
			continue;
		}
		// 対象フレームに追加(ブラックリスト)
		targetFrameIds_.emplace_back(i);
	}
}

void ColliderModel::ClearTargetFrame(void)
{
	targetFrameIds_.clear();
}

bool ColliderModel::IsTargetFrame(int _frameIdx) const
{
	// 割り当て判定
	if (std::find(targetFrameIds_.begin(),
				  targetFrameIds_.end(), _frameIdx) == targetFrameIds_.end())
	{
		// 対象に該当する
		return true;
	}
	return false;
}