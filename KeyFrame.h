#pragma once
#include "Core.h"
class KeyFrame {
public:
	float Time;
	float Value;
	float TangentIn, TangentOut;
	char * RuleIn, *RuleOut;

	float A, B, C, D;
	KeyFrame(float Time, float val, char *Rulein, char* Ruleout);
	void precompute(KeyFrame* preframe,KeyFrame* nextframe);
	void linearcomputetan(KeyFrame* preframe, KeyFrame* nextframe,bool in);
};

