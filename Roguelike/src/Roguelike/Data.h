#pragma once

class Run;

class Data
{
private:
    static Data* instance;
	Data();

public:
	Run* currentRun;

    static Data* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new Data();
		}
		
		return instance;
	}

	void StartNewRun();
};
