#include "Sounds.h"

#include "SoundManager.h"

Sounds* Sounds::instance = nullptr;

Sounds::Sounds()
{
	// Chargement des sons
	{
		SoundManager* soundManager = SoundManager::GetInstance();
		soundManager->SetGlobalVolume(500);
		soundManager->SetMusicVolume(5);
		soundManager->LoadSound("../../../res/sounds/click1.wav");
		soundManager->LoadSound("../../../res/sounds/swipe1.wav");
		soundManager->LoadSound("../../../res/sounds/swipe2.wav");
	}

	soundsBuffer.emplace("click", new RandomSound{"../../../res/sounds/", 1});
	soundsBuffer.emplace("swipe", new RandomSound{"../../../res/sounds/", 1});
}

void Sounds::PlayRandomizedSound(std::string soundName)
{
	RandomSound* temp = soundsBuffer.find(soundName)->second;

	if (temp != nullptr)
	{
		int soundNumber = rand() % temp->maxAmount + 1;

		SoundManager::GetInstance()->PlaySound(temp->path + std::to_string(soundNumber) + temp->extensionType);
	}
}
