#include "stdafx.h"
#include "Recognize.h"

namespace test_OpenCV
{
	CRecognize::CRecognize(void)
	{
	}


	CRecognize::~CRecognize(void)
	{
	}

	std::vector<cv::Rect> CRecognize::detectLetters(cv::Mat img)
	{
		//	namedWindow("MyWindow", WINDOW_AUTOSIZE );

		std::vector<cv::Rect> boundRect;
		cv::Mat img_gray, img_sobel, img_threshold, element;

		cvtColor(img, img_gray, CV_BGR2GRAY);

		cv::Sobel(img_gray, img_sobel, CV_8U, 1, 0, 3, 1, 0, cv::BORDER_DEFAULT);

		cv::threshold(img_sobel, img_threshold, 0, 255, CV_THRESH_OTSU + CV_THRESH_BINARY);

		element = getStructuringElement(cv::MORPH_RECT, cv::Size(70, 15) );//cv::Size(17, 3)

		cv::morphologyEx(img_threshold, img_threshold, CV_MOP_CLOSE, element); //Does the trick

		std::vector< std::vector< cv::Point> > contours;

		cv::findContours(img_threshold, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

		std::vector<std::vector<cv::Point> > contours_poly( contours.size() );

		for( UINT i = 0; i < contours.size(); i++ )
		{
			if (cv::contourArea(contours[i]) < 100)
			{ 
				cv::approxPolyDP( cv::Mat(contours[i] ), contours_poly[i], 3, true );
				cv::Rect appRect( boundingRect( cv::Mat(contours_poly[i]) ));

				if ( appRect.width > appRect.height )
				{
					boundRect.push_back(appRect);
				}

				tesseract::TessBaseAPI tess;

				tess.Init(NULL, "eng", tesseract::OEM_DEFAULT);
				//tess.SetVariable("tessedit_char_whitelist", "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ");
				//tess.SetPageSegMode(tesseract::PSM_SINGLE_LINE/*PSM_SINGLE_BLOCK*/);
				tess.SetImage((uchar*)img_threshold.data, img_threshold.cols, img_threshold.rows, 1, img_threshold.cols);

				char* out = tess.GetUTF8Text();
				std::cout << out << std::endl;
			}
			//return boundRect;
		}

		// 	imshow("MyWindow", img_threshold);
		// 	waitKey(0);
		// 
		// 	destroyWindow("MyWindow");

		return boundRect;
	}

	int CRecognize::attempRecognize1()
	{
		for ( int index = 1; index < 71; index++ )
		{
			char fileNameRead[100] = {0};
			char fileNameWrite[100] = {0};

			sprintf_s( fileNameRead, sizeof(fileNameRead), "C:\\Users\\user\\Desktop\\example\\%02d.jpg", index);

			cv::Mat img=cv::imread(fileNameRead, CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);

			if (img.empty()) //check whether the image is loaded or not
			{
				continue;
			}

			namedWindow(fileNameRead, WINDOW_AUTOSIZE ); //create a window with the name "MyWindow"

			std::vector<cv::Rect> letterBoxes = detectLetters(img);

			sprintf_s( fileNameWrite, sizeof(fileNameWrite), "C:\\Users\\user\\Desktop\\example\\~%02d.jpg", index);

			for(UINT i=1; i< letterBoxes.size(); i++)
			{
				cv::rectangle(img, letterBoxes[i], cv::Scalar(0,255,0), 3, 8, 0 );
			}

			cv::imwrite( fileNameWrite, img);

			imshow(fileNameRead, img); //display the image which is stored in the 'img' in the "MyWindow" window

			waitKey(0);

			destroyWindow(fileNameRead);
		}

		return 0;
	}

	int CRecognize::attempRecognize2()
	{
		char fileNameRead[100] = {0};
		char fileNameWrite[100] = {0};

		sprintf_s( fileNameRead, sizeof(fileNameRead), "C:\\Users\\user\\Desktop\\example\\41.jpg");

		cv::Mat img=cv::imread(fileNameRead, CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);

		if (img.empty()) //check whether the image is loaded or not
		{
			return 0;
		}

		namedWindow(fileNameRead, WINDOW_AUTOSIZE ); //create a window with the name "MyWindow"

		std::vector<cv::Rect> letterBoxes = detectLetters(img);

		sprintf_s( fileNameWrite, sizeof(fileNameWrite), "C:\\Users\\user\\Desktop\\example\\~41.jpg");

		for(UINT i=0; i< letterBoxes.size(); i++)
		{
			cv::rectangle(img, letterBoxes[i], cv::Scalar(0,255,0), 3, 8, 0 );
		}

		cv::imwrite( fileNameWrite, img);

		imshow(fileNameRead, img); //display the image which is stored in the 'img' in the "MyWindow" window

		waitKey(0);

		destroyWindow(fileNameRead);

		return 0;
	}
}
