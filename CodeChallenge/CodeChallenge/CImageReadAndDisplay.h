#pragma once
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include "ImageReadAndDisplayInterface.h"
#include "CImageOperations.h"


using namespace cv;
using namespace std;

class CImageReadAndDisplay : public ImageReadAndDisplayInterface
{
public:
	static ImageReadAndDisplayInterface* instanceBuilder();

	returnCodes performIntialization(std::string fileName);

	void performOperation();

	void displayCanvas();

protected:

	CImageReadAndDisplay();
	
	~CImageReadAndDisplay();

	vector<Mat> m_v_ImageData; /*< container that holds Images to display*/
	/**
	* @brief makeCanvas Makes composite image from the given images
	* @param vecMat Vector of Images.
	* @param windowHeight The height of the new composite image to be formed.
	* @param nRows Number of rows of images. (Number of columns will be calculated
	*              depending on the value of total number of images).
	* @return new composite image.
	*/
	cv::Mat makeCanvas(std::vector<cv::Mat>& vecMat, int windowHeight, int nRows);

	/**
	* @brief function to read the Image.
	* @param FileName Image file path.
	*/
	void readImage(string FileName);

	void performDataInitializations();

	returnCodes m_ret;
};

