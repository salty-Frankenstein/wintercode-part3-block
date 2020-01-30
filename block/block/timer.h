#pragma once
#ifndef TIMER_H
#define TIMER_H

#include <windows.h>
#include <time.h>

class Timer {
public:
	void SetTime();//start timing
	void Update();
	void StopTime();//end timing
	long long GetIntervalMilli();
private:
	SYSTEMTIME startTime;
	SYSTEMTIME now;
	bool stop;
};

void Timer::SetTime() {
	GetLocalTime(&now);
	startTime = now;
	stop = false;
}

void Timer::Update() {
	if (!stop)
		GetLocalTime(&now);
}

void Timer::StopTime() {
	stop = true;
}

long long Timer::GetIntervalMilli() {
	long long st = startTime.wMilliseconds + startTime.wSecond * 1000 + startTime.wMinute * 60 * 1000
		+ startTime.wHour * 60 * 60 * 1000 + startTime.wDay * 24 * 60 * 60 * 1000;
	long long ed = now.wMilliseconds + now.wSecond * 1000 + now.wMinute * 60 * 1000
		+ now.wHour * 60 * 60 * 1000 + now.wDay * 24 * 60 * 60 * 1000;
	return ed - st;

}

//////////
#endif // !TIMER_H
