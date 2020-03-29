#pragma once
#define KEY_COUNT 4


class TimingReader
{

protected:
	bool inputkeys[KEY_COUNT] = { false };
	int releases = 20;
public:
	TimingReader();
	virtual bool getInput(long millis_elapsed, int num) = 0;
	virtual void handleKeyCallback(long millis_elapsed, int key, int action) = 0;
	int getReleases();
	void setReleases(int r);
};

class SimpleTimingReader : public TimingReader
{
private:
	int progress_index;
public:
	SimpleTimingReader();
	void handleKeyCallback(long millis_elapsed, int key, int action);
	bool getInput(long millis_elapsed, int num);
	int getFirstEventTime();
	void resetProgress();
};

#include <iostream>

class TimingWritingReader : public TimingReader
{
private:
	FILE* outfile;
public:
	TimingWritingReader();
	void handleKeyCallback(long millis_elapsed, int key, int action);
	bool getInput(long millis_elapsed, int num);
};
