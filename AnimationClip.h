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
	AnimationClip(const char * filename);
	void Evaluate(float time);
	void Load(const char *filename);
	void precompute();
};

