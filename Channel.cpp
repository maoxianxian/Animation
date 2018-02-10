#pragma once
#include "Core.h"
#include "Channel.h"
Channel::Channel() {

}
float Channel::Evaluate(float time) {

}
bool Channel::Load(Tokenizer &scanner) {
	char buffer[64];
	scanner.GetToken(buffer);//{
	scanner.GetToken(buffer);//extrapolate
	scanner.GetToken(extrapre);
	scanner.GetToken(extraafter);
	scanner.GetToken(buffer);//keys
	numOfKeys = scanner.GetInt();
	scanner.GetToken(buffer);//{
	for(int i=0;i<numOfKeys;i++){
		char tanin[32];
		char tanout[32];
		float tim=scanner.GetFloat();
		float val = scanner.GetFloat();
		scanner.GetToken(tanin);
		scanner.GetToken(tanout);
		KeyFrame * temp = new KeyFrame(tim, val, tanin, tanout);
		frames.push_back(temp);
	}
	scanner.GetToken(buffer);//}
	scanner.GetToken(buffer);//}
}
void Channel::precompute() {
	for (int i = 0; i < frames.size(); i++)
	{
		frames[i]->precompute();
	}
}