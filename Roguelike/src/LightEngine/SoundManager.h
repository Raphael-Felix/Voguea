#pragma once

#include <SFML/Audio.hpp>
#include <string>
#include <map>
#include <deque>

class SoundManager
{
private:

	static SoundManager* instance;
	SoundManager();

	std::map<std::string, sf::SoundBuffer> soundsBuffers;

	std::deque<sf::Sound*> activeSounds;
	std::deque<std::pair<std::string, sf::Music*>> activeMusics;

	int globalVolume;
	int soundVolume;
	int musicVolume;

public:
	static SoundManager* GetInstance()
	{
		if (instance == nullptr)
			instance = new SoundManager();
		return instance;
	}

	bool LoadSound(std::string path);

	void PlaySound(std::string path);
	void PlayMusic(std::string path, bool loop = true);

	void StopMusic(std::string path);

	void SetGlobalVolume(int newVolume);
	int* GetSoundVolume();
	void SetSoundVolume(int newVolume);
	void ChangeSoundVolume(int amount);
	int* GetMusicVolume();
	void SetMusicVolume(int newVolume);
	void ChangeMusicVolume(int amount);

	void PauseAll();
	void ContinueAll();
	void StopAll();

	void Update();
};
