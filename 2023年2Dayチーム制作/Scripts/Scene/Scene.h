#pragma once

enum class TAG_SCENE
{
	TAG_TITLE,
	TAG_PLAY,
	TAG_RESULT,
	TAG_END,

	TAG_NONE
};

class Scene
{
public:
	Scene() { /*処理なし*/ }
	virtual ~Scene(){ /*処理なし*/ }

	virtual TAG_SCENE Update(float deltaTime) = 0;
	virtual void Draw() = 0;
};