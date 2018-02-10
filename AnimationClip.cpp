#include "AnimationClip.h"
AnimationClip::AnimationClip(const char* filename) {
	Load(filename);
}
void AnimationClip::Evaluate(float time) {

}
void AnimationClip::Load(const char *filename) {
	Tokenizer scanner;
	scanner.Open(filename);
	char buffer[64];
	scanner.GetToken(buffer);//animation
	scanner.GetToken(buffer);//{
	scanner.GetToken(buffer);//range
	starttime = scanner.GetFloat();
	endtime = scanner.GetFloat();
	scanner.GetToken(buffer);//numchannels
	numChannels = scanner.GetInt();

	for(int i=0;i<numChannels;i++){
		char buffer1[64];
		scanner.GetToken(buffer1);
		if(std::string(buffer1) == "channel") {
			Channel *temp = new Channel();
			temp->Load(scanner);
			channels.push_back(temp);
		}else{
			std::cout << "error reading the " + std::to_string(i) + "th channel" << std::endl;
		}
	}
	scanner.Close();
}
void AnimationClip::precompute() {
	for (int i = 0; i < channels.size(); i++)
	{
		channels[i]->precompute();
	}
}