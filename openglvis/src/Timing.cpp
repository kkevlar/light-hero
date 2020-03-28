
#include "Timing.h"

TimingReader::TimingReader()
{
	int i;
	
	for (i = 0; i < KEY_COUNT; i++)
	{
		inputkeys[i] = false;
	}
}

void SimpleTimingReader::handleKeyCallback(long millis, int key, int action)
{
	//pass
}


bool SimpleTimingReader::getInput(long millis, int num)
{
	//todonext
}

#include <glad/glad.h>
#include "GLSL.h"
#include "WindowManager.h"

TimingWritingReader::TimingWritingReader() : TimingReader::TimingReader()
{
	outfile = fopen("timing.csv", "w");
}

void TimingWritingReader::handleKeyCallback(long millis, int key, int action)
{
	int i;
	for (i = 0; i < KEY_COUNT; i++)
	{
		if (key == (GLFW_KEY_1 + i) && action == GLFW_PRESS)
		{
			inputkeys[i] = true;
			fprintf(outfile, "%ld, %d, %c\n", millis, i, 'p');
		}
		else if (key == (GLFW_KEY_1 + i) && action == GLFW_RELEASE)
		{
			inputkeys[i] = false;
			releases--;
			fprintf(outfile, "%ld, %d, %c\n",millis, i, 'r');
		}
	}
}

bool TimingWritingReader::getInput(long millis, int num)
{
	return inputkeys[num];
}
