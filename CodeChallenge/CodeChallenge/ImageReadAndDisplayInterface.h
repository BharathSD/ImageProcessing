#pragma once
#include <string>

enum returnCodes
{
	success,
	failure
};
class ImageReadAndDisplayInterface
{
public:
	virtual returnCodes performIntialization(std::string fileName) = 0;

	virtual void performOperation() = 0;

	virtual void displayCanvas() = 0;

	static ImageReadAndDisplayInterface* getInstance();
};
