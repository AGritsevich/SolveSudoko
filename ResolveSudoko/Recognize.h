#pragma once

#include "opencv2/opencv.hpp"
#include <api/baseapi.h>
#include <iostream>
#include <vector>

namespace test_OpenCV
{
	using namespace cv;
	using namespace std;

	class CRecognize
	{

	public:

		CRecognize(void);
		~CRecognize(void);


		int attempRecognize2();
		int attempRecognize1();
		std::vector<cv::Rect> detectLetters(cv::Mat img);
	};
}

