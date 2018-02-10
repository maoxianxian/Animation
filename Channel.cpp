#pragma once
#include "Core.h"
#include "Channel.h"
Channel::Channel() {

}
float Channel::Evaluate(float time) {

}
void Channel::Load(Tokenizer &scanner) {
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
		std::cout << tim<<" "<<val<<" "<<std::string(tanin) << " " << std::string(tanout) << std::endl;
		frames.push_back(temp);
	}
	std::cout << std::endl;
	scanner.GetToken(buffer);//}
	scanner.GetToken(buffer);//}
}
void Channel::precompute() {
	frames[0]->precompute(nullptr, frames[1]);
	for (int i = 1; i < frames.size()-1; i++)
	{
		frames[i]->precompute(frames[i-1],frames[i+1]);
	}
	frames[numOfKeys - 1]->precompute(frames[numOfKeys - 2], NULL);
}