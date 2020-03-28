#pragma once
#include <vector>
#define KEY_COUNT 4

class TimingReader
{

protected:
	bool inputkeys[KEY_COUNT] = { false };
	int releases = 20;
public:
	TimingReader();
	virtual bool getInput(long millis, int num) = 0;
	virtual void handleKeyCallback(long millis, int key, int action) = 0;
};

class SimpleTimingReader : public TimingReader
{
public:
	void handleKeyCallback(long millis, int key, int action);
	bool getInput(long millis, int num);
};

class TimingWritingReader : public TimingReader
{
private:
	FILE* outfile;
public:
	TimingWritingReader();
	void handleKeyCallback(long millis, int key, int action);
	bool getInput(long millis, int num);
};
