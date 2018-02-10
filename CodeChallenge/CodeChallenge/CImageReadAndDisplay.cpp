#include "CImageReadAndDisplay.h"



CImageReadAndDisplay::CImageReadAndDisplay()
{
}


CImageReadAndDisplay::~CImageReadAndDisplay()
{
}

ImageReadAndDisplayInterface * CImageReadAndDisplay::instanceBuilder()
{
	static CImageReadAndDisplay Instance;

	return &Instance;
}

returnCodes CImageReadAndDisplay::performIntialization(std::string fileName)
{
	readImage(fileName);
	performDataInitializations();
	return m_ret;
}

void CImageReadAndDisplay::performOperation()
{
	std::shared_ptr<CImageOperations> smartInstance = make_shared<CImageOperations>();

	smartInstance->convertToGrayScale(m_v_ImageData[0].data, m_v_ImageData[0].rows, m_v_ImageData[0].cols,
											m_v_ImageData[0].channels(), m_v_ImageData[1].data);

	smartInstance->performThresholding(m_v_ImageData[1].data, m_v_ImageData[1].rows, m_v_ImageData[1].cols,
		m_v_ImageData[1].channels(), m_v_ImageData[2].data, 50);

	smartInstance->performHorizontalFlip(m_v_ImageData[1].data, m_v_ImageData[1].rows, m_v_ImageData[1].cols,
		m_v_ImageData[1].channels(), m_v_ImageData[3].data);

	smartInstance->performVerticalFlip(m_v_ImageData[1].data, m_v_ImageData[1].rows, m_v_ImageData[1].cols,
		m_v_ImageData[1].channels(), m_v_ImageData[4].data);

	smartInstance->computeEdgeImage(m_v_ImageData[1].data, m_v_ImageData[1].rows, m_v_ImageData[1].cols,
		m_v_ImageData[1].channels(), m_v_ImageData[5].data);

}

void CImageReadAndDisplay::displayCanvas()
{
	if (m_ret == success)
	{
		imshow("Image Canvas", makeCanvas(m_v_ImageData, m_v_ImageData[0].rows, 2));
		cv::waitKey(0);
	}
}

cv::Mat CImageReadAndDisplay::makeCanvas(std::vector<cv::Mat>& vecMat, int windowHeight, int nRows)
{
	int N = vecMat.size();
	nRows = nRows > N ? N : nRows;
	int edgeThickness = 10;
	int imagesPerRow = ceil(double(N) / nRows);
	int resizeHeight = floor(2.0 * ((floor(double(windowHeight - edgeThickness) / nRows)) / 2.0)) - edgeThickness;
	int maxRowLength = 0;

	std::vector<int> resizeWidth;
	for (int i = 0; i < N;) {
		int thisRowLen = 0;
		for (int k = 0; k < imagesPerRow; k++) {
			double aspectRatio = double(vecMat[i].cols) / vecMat[i].rows;
			int temp = int(ceil(resizeHeight * aspectRatio));
			resizeWidth.push_back(temp);
			thisRowLen += temp;
			if (++i == N) break;
		}
		if ((thisRowLen + edgeThickness * (imagesPerRow + 1)) > maxRowLength) {
			maxRowLength = thisRowLen + edgeThickness * (imagesPerRow + 1);
		}
	}
	int windowWidth = maxRowLength;
	cv::Mat canvasImage(windowHeight, windowWidth, CV_8UC3, Scalar(0, 0, 0));

	for (int k = 0, i = 0; i < nRows; i++) 
	{
		int y = i * resizeHeight + (i + 1) * edgeThickness;
		int x_end = edgeThickness;
		for (int j = 0; j < imagesPerRow && k < N; k++, j++) 
		{
			int x = x_end;
			cv::Rect roi(x, y, resizeWidth[k], resizeHeight);
			cv::Size s = canvasImage(roi).size();
			// change the number of channels to three
			cv::Mat target_ROI(s, CV_8UC3);
			if (vecMat[k].channels() != canvasImage.channels()) 
			{
				if (vecMat[k].channels() == 1) 
				{
					cv::cvtColor(vecMat[k], target_ROI, CV_GRAY2BGR);
				}
			}
			else 
			{
				vecMat[k].copyTo(target_ROI);
			}
			cv::resize(target_ROI, target_ROI, s);
			if (target_ROI.type() != canvasImage.type()) 
			{
				target_ROI.convertTo(target_ROI, canvasImage.type());
			}
			target_ROI.copyTo(canvasImage(roi));
			x_end += resizeWidth[k] + edgeThickness;
		}
	}
	return canvasImage;
}

void CImageReadAndDisplay::readImage(string FileName)
{
	Mat InputImage = imread(FileName);
	if (InputImage.empty())
	{
		m_ret = failure;
	}
	else
	{
		m_ret = success;
		m_v_ImageData.push_back(InputImage);
	}
}

void CImageReadAndDisplay::performDataInitializations()
{
	if (m_ret == success)
	{
		Mat grayImage(m_v_ImageData[0].size(), CV_8UC1);
		Mat thresholdImage(m_v_ImageData[0].size(), CV_8UC1);
		Mat horizontalFlipImage(m_v_ImageData[0].size(), CV_8UC1);
		Mat verticalFlipImage(m_v_ImageData[0].size(), CV_8UC1);
		Mat edgeImage(m_v_ImageData[0].size(), CV_8UC1);

		m_v_ImageData.push_back(grayImage);
		m_v_ImageData.push_back(thresholdImage);
		m_v_ImageData.push_back(horizontalFlipImage);
		m_v_ImageData.push_back(verticalFlipImage);
		m_v_ImageData.push_back(edgeImage);

	}
}
