#include "SoundManager.h"

#include <algorithm>
#include <iostream>

SoundManager* SoundManager::instance = nullptr;

SoundManager::SoundManager()
{
    globalVolume = 25;
    soundVolume = 20;
    musicVolume = 50;
}

bool SoundManager::LoadSound(std::string path)
{
	sf::SoundBuffer buffer;

	if (buffer.loadFromFile(path) != true)
		return false;

	soundsBuffers.emplace(path, buffer);
	return true;
}

void SoundManager::PlaySound(std::string path)
{
	if (soundsBuffers.contains(path) == false)
		return;

	sf::Sound* sound = new sf::Sound();

	sound->setBuffer(soundsBuffers.find(path)->second);
	sound->setVolume((globalVolume * soundVolume * 0.01f));
	sound->play();

	activeSounds.push_back(sound);
}

void SoundManager::PlayMusic(std::string path, bool loop)
{
    sf::Music* music = new sf::Music;

    if (music->openFromFile(path) == false)
        return;

    music->setLoop(loop);

    music->setVolume(globalVolume * musicVolume * 0.01f);
    music->play();

    activeMusics.emplace_back( path, music );
}

void SoundManager::StopMusic(std::string path)
{
    for (std::pair<std::string, sf::Music*>& music : activeMusics)
    {
        if (music.first == path)
            music.second->stop();
    }
}

void SoundManager::StopAll()
{
    for (auto& sound : activeSounds)
        sound->stop();
    activeSounds.clear();

    for (auto& music : activeMusics)
        music.second->stop();
    activeMusics.clear();
}

void SoundManager::SetGlobalVolume(int newVolume)
{
    globalVolume = newVolume;
}

int* SoundManager::GetSoundVolume()
{
    return &soundVolume;
}

void SoundManager::SetSoundVolume(int newVolume)
{
    soundVolume = std::min(std::max(newVolume, 0), 100);
}

void SoundManager::ChangeSoundVolume(int amount)
{
    SetSoundVolume(soundVolume + amount);
}

int* SoundManager::GetMusicVolume()
{
    return &musicVolume;
}

void SoundManager::SetMusicVolume(int newVolume)
{
    musicVolume = std::min(std::max(newVolume, 0), 100);

    for (std::pair<std::string, sf::Music*> music : activeMusics)
        music.second->setVolume(musicVolume);
}

void SoundManager::ChangeMusicVolume(int amount)
{
    SetMusicVolume(musicVolume + amount);
}

void SoundManager::PauseAll()
{
    for (auto& sound : activeSounds)
        sound->pause();

    for (auto& music : activeMusics)
        music.second->pause();
}

void SoundManager::ContinueAll()
{
    for (auto& sound : activeSounds)
        sound->play();

    for (auto& music : activeMusics)
        music.second->play();
}

void SoundManager::Update()
{
    while (activeSounds.empty() != true && activeSounds.front()->getStatus() == sf::Sound::Stopped)
    {
        activeSounds.pop_front();
    }

    while (activeMusics.empty() != true && activeMusics.front().second->getStatus() == sf::Music::Stopped)
    {
        activeMusics.pop_front();
    }
}
