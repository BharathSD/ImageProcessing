#include "CImageOperations.h"



CImageOperations::CImageOperations()
{
}


CImageOperations::~CImageOperations()
{
}

void CImageOperations::convertToGrayScale(unsigned char * pInputImage, int nInputRows, int nInputCols, int nInputChannels, unsigned char * pOutputImage)
{
	//Write your code here
	// Note : if the no of channels is 3, its a RGB image and pixels are arranged as BGR|BGR|BGR...
	// intensity = 0.2989*red + 0.5870*green + 0.1140*blue
	if (nInputChannels == 3)
	{
		float arr_coeff[3] = { 0.1140f , 0.5870f ,0.2989f };
		int blue(0), green(1), red(2);
		int nTotalIterations(nInputRows * nInputCols);
		for (int itr(0); itr < nTotalIterations; ++itr)
		{
			*pOutputImage = (pInputImage[blue] * arr_coeff[blue])
				+ (pInputImage[green] * arr_coeff[green])
				+ (pInputImage[red] * arr_coeff[red]);

			pOutputImage++;
			pInputImage += 3;
		}
	}
}

void CImageOperations::performThresholding(unsigned char * pInputImage, int nInputRows, int nInputCols, int nInputChannels, unsigned char * pOutputImage, int thresholdValue)
{
	//Write your code here
	int nTotalIterations(nInputRows * nInputCols);
	for (int itr(0); itr < nTotalIterations; ++itr)
	{
		*pOutputImage = *pInputImage > thresholdValue ? 255 : 0;
		pOutputImage++;
		pInputImage++;
	}
}

void CImageOperations::performHorizontalFlip(unsigned char * pInputImage, int nInputRows, int nInputCols, int nInputChannels, unsigned char * pOutputImage)
{
	//Write your code here
	unsigned int left(0);
	unsigned int right(nInputCols - 1);

	for (int r(0); r < nInputRows; r++) 
	{
		while ( right > left) 
		{
			int index1(r * nInputCols + left);
			int index2(r * nInputCols + right);

			pOutputImage[index1] = pInputImage[index2];
			pOutputImage[index2] = pInputImage[index1];
			right--;
			left++;
		}

		// Reset left and right after processing a row.
		left = 0;
		right = nInputCols - 1;
	}
}

void CImageOperations::performVerticalFlip(unsigned char * pInputImage, int nInputRows, int nInputCols, int nInputChannels, unsigned char * pOutputImage)
{
	//Write your code here
	int top(0);
	int bottom((nInputRows - 1) * nInputCols);

	while (top < bottom) 
	{
		for (int c(0); c < nInputCols; ++c)
		{
			pOutputImage[top + c] = pInputImage[bottom + c];
			pOutputImage[bottom + c] = pInputImage[top + c];
		}

		top += nInputCols;
		bottom -= nInputCols;
	}
}

void CImageOperations::computeEdgeImage(unsigned char * pInputImage, int nInputRows, int nInputCols, int nInputChannels, unsigned char * pOutputImage)
{
	//Write your code here
#pragma region Memory_Allocation
	// Allocate memory for x gradients and y gradients
	int noOfPixels(nInputRows * nInputCols);
	unsigned char *pInputImageX = new unsigned char[noOfPixels];
	unsigned char *pInputImageY = new unsigned char[noOfPixels];
#pragma endregion

#pragma region Compute_X_Gradients
	unsigned char *pInputImage0 = pInputImage;
	unsigned char *pInputImage1 = pInputImage + nInputCols;
	unsigned char *pInputImage2 = pInputImage + (2 * nInputCols);

	// point to the second row, second column element
	unsigned char *px = pInputImageX + nInputCols + 1;
	// compute X gradients
	for (int rowItr(0); rowItr < (nInputRows - 2); ++rowItr)
	{
		for (int colItr(0); colItr < (nInputCols - 2); ++colItr)
		{
			*pInputImageX = (pInputImage0[2] - pInputImage0[0]) +
							((pInputImage1[2] - pInputImage1[0]) << 1) +
							(pInputImage2[2] - pInputImage2[0]);
			px++;
			pInputImage0++;
			pInputImage1++;
			pInputImage2++;
		}
		px +=2;
		pInputImage0+=2;
		pInputImage1+=2;
		pInputImage2+=2;
	}

#pragma endregion
#pragma endregion Compute_Y_Gradients
	pInputImage0 = pInputImage;
	pInputImage2 = pInputImage + (2 * nInputCols);

	// point to the second row, second column element
	px = pInputImageY + nInputCols + 1;

	// compute Y gradients
	for (int rowItr(0); rowItr < (nInputRows - 2); ++rowItr)
	{
		for (int colItr(0); colItr < (nInputCols - 2); ++colItr)
		{
			*px = (pInputImage2[0] + (pInputImage2[1] << 2) + pInputImage2[2]) -
					(pInputImage0[0] + (pInputImage0[1] << 2) + pInputImage0[2]);
			px++;
			pInputImage0++;
			pInputImage2++;
		}
		px+=2;
		pInputImage0+=2;
		pInputImage2+=2;
	}
#pragma region 

#pragma region Compute_Magnitude
	for (int itr(0); itr < noOfPixels; ++itr)
	{
		pOutputImage[itr] = std::sqrt((pInputImageX[itr] * pInputImageX[itr]) +
								(pInputImageY[itr] * pInputImageY[itr]));
	}
#pragma endregion
	delete[] pInputImageX;
	delete[] pInputImageY;
}
