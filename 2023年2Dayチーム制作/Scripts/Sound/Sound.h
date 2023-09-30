﻿#pragma once
#include <unordered_map>
#include <DxLib.h>

/// <summary>
/// サウンドクラス
/// </summary>
class Sound
{
public:
	enum Type
	{
		// 音
	};
	static void Load(int kind, const char* str)
	{
		sounds.insert(std::make_pair(kind, LoadSoundMem(str)));
	}

	static void Play(int kind)
	{
		auto itr = sounds.find(kind);
		PlaySoundMem(itr->second, DX_PLAYTYPE_BACK);
	}

	// 音全解放
	static void InitSound()
	{
		InitSoundMem();
		sounds.clear();
	}

private:
	static std::unordered_multimap<int,int> sounds;
};