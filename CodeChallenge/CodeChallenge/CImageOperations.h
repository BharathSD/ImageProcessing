#pragma once
#include <iostream>
#include <cmath>
class CImageOperations
{
public:
	CImageOperations();
	~CImageOperations();

	void convertToGrayScale(unsigned char*pInputImage, int nInputRows, int nInputCols, int nInputChannels, unsigned char*pOutputImage);

	void performThresholding(unsigned char*pInputImage, int nInputRows, int nInputCols, int nInputChannels, unsigned char*pOutputImage, int thresholdValue);

	void performHorizontalFlip(unsigned char*pInputImage, int nInputRows, int nInputCols, int nInputChannels, unsigned char*pOutputImage);
	
	void performVerticalFlip(unsigned char*pInputImage, int nInputRows, int nInputCols, int nInputChannels, unsigned char*pOutputImage);
	
	void computeEdgeImage(unsigned char*pInputImage, int nInputRows, int nInputCols, int nInputChannels, unsigned char*pOutputImage);
};

