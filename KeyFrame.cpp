#pragma once
#include "KeyFrame.h"
KeyFrame::KeyFrame(float Time, float val, char* Rulein, char* Ruleout) {
	this->Time = Time;
	this->Value = val;
	this->RuleIn = Rulein;
	this->RuleOut = Ruleout;
}
void KeyFrame::precompute(KeyFrame* preframe, KeyFrame* nextframe) {
	//in tangent
	if (std::string(RuleIn) == "flat") {
		TangentIn = 0;
	}
	else if (std::string(RuleIn) == "linear") {
		linearcomputetan(preframe, nextframe, true);
	}
	else if (std::string(RuleIn) == "smooth") {
		if (preframe != NULL && nextframe != NULL) {
			TangentIn = (nextframe->Value - preframe->Value) / (nextframe->Time - preframe->Time);
		}else{
			linearcomputetan(preframe, nextframe, true);
		}
	}
	else
	{
		TangentIn = std::stof(std::string(RuleIn));
	}
	//out tangent
	if (std::string(RuleOut) == "flat") {
		TangentOut = 0;
	}
	else if (std::string(RuleOut) == "linear") {
		linearcomputetan(preframe, nextframe, false);
	}
	else if (std::string(RuleOut) == "smooth") {
		if (preframe != NULL && nextframe != NULL) {
			TangentOut = (nextframe->Value - preframe->Value) / (nextframe->Time - preframe->Time);
		}
		else {
			linearcomputetan(preframe, nextframe, false);
		}
	}
	else
	{
		TangentOut = std::stof(std::string(RuleOut));
	}
}

void KeyFrame::linearcomputetan(KeyFrame* preframe, KeyFrame* nextframe,bool in) {
	if (in) {
		if (preframe != NULL) {
			TangentIn = (preframe->Value - Value) / (preframe->Time - Time);
		}
		else {
			TangentIn = 0;
		}
	}
}
