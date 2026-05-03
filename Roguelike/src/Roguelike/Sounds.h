#pragma once

#include <map>
#include <string>

struct RandomSound
{
	std::string path;

	int maxAmount;

	std::string extensionType = ".wav";
};

class Sounds
{
private:
    static Sounds* instance;
	Sounds();

	std::map<std::string, RandomSound*> soundsBuffer;

public:
	static Sounds* GetInstance()
	{
		if (instance == nullptr)
			instance = new Sounds();
		return instance;
	}

	void PlayRandomizedSound(std::string soundName);
};
