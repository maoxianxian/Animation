#pragma once
#include "Core.h"
#include "Tokenizer.h"
#include "Channel.h"

class AnimationClip {
public:
	float starttime;
	float endtime;
	int numChannels;
	std::vector<Channel*> channels;
	void Evaluate(float time);
	bool Load(const char *filename);
	void precompute();
};
