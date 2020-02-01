#include "sound.h"

Sound::Sound() {}

Sound::Sound(LPCWSTR _soundName) {
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
		IID_IGraphBuilder, (void**)&pGraph);
	pGraph->QueryInterface(IID_IMediaControl, (void**)&pCtrl);
	pGraph->QueryInterface(IID_IMediaPosition, (void**)&pPos);
	pGraph->RenderFile(_soundName, NULL);
}

void Sound::Play() {
	pPos->put_CurrentPosition(0);
	pCtrl->Run();
}

void Sound::Stop() {
	pCtrl->Stop();
}
