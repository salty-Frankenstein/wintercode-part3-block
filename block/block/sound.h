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

protected:
	IGraphBuilder * pGraph;
	IMediaControl *pCtrl;
	IMediaPosition *pPos;
};

class Music :public Sound {
public:
	Music();
	Music(LPCWSTR _soundName, REFTIME _loopBegin = 0);
	void Pause();
	void Play();
	void Stop();
	void Loop();
	bool active;
	REFTIME loopBegin;
};

#endif // !SOUND_H
