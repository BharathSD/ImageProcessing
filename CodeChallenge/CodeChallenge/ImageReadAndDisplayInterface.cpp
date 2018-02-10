#include "ImageReadAndDisplayInterface.h"
#include "CImageReadAndDisplay.h"
ImageReadAndDisplayInterface * ImageReadAndDisplayInterface::getInstance()
{
	return CImageReadAndDisplay::instanceBuilder();
}
