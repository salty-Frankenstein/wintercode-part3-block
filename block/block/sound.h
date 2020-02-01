/*						*\
		sound.h
	基于DirectShow
		的音频库
	2020 wintercode
	by id:191220017
\*						*/

#pragma once
#ifndef SOUND_H
#define SOUND_H
#include <dshow.h>

class Sound {
public:
	Sound();
	Sound(LPCWSTR _soundName);
	void Play();
	void Stop();

private:
	IGraphBuilder * pGraph;
	IMediaControl *pCtrl;
	IMediaPosition *pPos;
};


#endif // !SOUND_H
