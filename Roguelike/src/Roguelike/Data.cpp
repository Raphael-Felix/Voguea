#include "Data.h"
#include "Run.h"

Data* Data::instance = nullptr;

Data::Data()
{
	currentRun = nullptr;
}

void Data::StartNewRun()
{
	if (currentRun != nullptr)
		delete currentRun;

	currentRun = new Run();
}
