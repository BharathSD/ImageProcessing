#include <iostream>
#include <string>
#include "ImageReadAndDisplayInterface.h"
using namespace std;


int main(int argc, char**argv)
{
	if (argc != 2)
	{
		std::cerr << "Provide the ImagePath" << std::endl;
		system("pause");
		return EXIT_FAILURE;
	}
	string fileName(argv[1]);

	ImageReadAndDisplayInterface *pInstance = ImageReadAndDisplayInterface::getInstance();

	if (pInstance->performIntialization(fileName) == failure)
	{
		std::cerr << "Provide the proper ImagePath" << std::endl;
		system("pause");
		return EXIT_FAILURE;
	}

	pInstance->performOperation();

	pInstance->displayCanvas();
	return EXIT_SUCCESS;
}