#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
int main( int argc, char** argv ) {
	bool capturing = true;
	cv::VideoCapture cap(0);
	if ( !cap.isOpened() ) {
		std::cerr << "error opening frames source" << std::endl;
		return -1;
	}
	int frame_height, frame_width; //petla z resize okienka i mozliwoscia wpisania wielkosci//
	if (argc == 3)
	{
		frame_width = atoi(argv[1]);
		frame_height = atoi(argv[2]);

	}else
	{
		frame_height = 200, frame_width = 320;
	}
	
	

	cv::Mat img, img_s; // Macierz tworzy frame i screenshot(okna)// 
	cap.read(img);
	cv::GaussianBlur(img, img, cv::Size(15, 15), 0); // wybor rozmycia Gaussa//
	
	cv::resize(img, img, {frame_width, frame_height}); //resize//

	cv::namedWindow("hsv", cv::WINDOW_AUTOSIZE);
	int hl = 0, sl = 0, vl = 0, hu = 255, su = 255, vu = 255; //startowe paskow//
	cv::createTrackbar("h-lower", "hsv", &hl, 255); //paski//
	cv::createTrackbar("s-lower", "hsv", &sl, 255);
	cv::createTrackbar("v-lower", "hsv", &vl, 255);
	cv::createTrackbar("h-upper", "hsv", &hu, 255);
	cv::createTrackbar("s-upper", "hsv", &su, 255);
	cv::createTrackbar("v-upper", "hsv", &vu, 255);

	while(true){
		cv::imshow("IMG", img);

		cv::cvtColor(img, img_s, cv::COLOR_BGR2HSV);
		cv::inRange(img_s, cv::Scalar(hl, sl, vl), cv::Scalar(hu, su, vu), img_s);
		int pos = 0;
		cv::putText(img_s, "H-low: "+ std::to_string(hl), {10, pos+=30}, cv::FONT_HERSHEY_PLAIN, 1.0, {0, 255, 0, 255});
		cv::putText(img_s, "S-low: "+ std::to_string(sl), {10, pos+=30}, cv::FONT_HERSHEY_PLAIN, 1.0, {0, 255, 0, 255});
		cv::putText(img_s, "V-low: "+ std::to_string(vl), {10, pos+=30}, cv::FONT_HERSHEY_PLAIN, 1.0, {0, 255, 0, 255});
		cv::putText(img_s, "H-high: "+ std::to_string(hu), {10, pos+=30}, cv::FONT_HERSHEY_PLAIN, 1.0, {0, 255, 0, 255});
		cv::putText(img_s, "S-high: "+ std::to_string(su), {10, pos+=30}, cv::FONT_HERSHEY_PLAIN, 1.0, {0, 255, 0, 255});
		cv::putText(img_s, "V-high: "+ std::to_string(vu), {10, pos+=30}, cv::FONT_HERSHEY_PLAIN, 1.0, {0, 255, 0, 255});
		cv::imshow("img_s", img_s);
		char k = cv::waitKey(1);
		if(k == 27)break;
		if(k == 'x') {
			cv::Rect2d r = cv::selectROI("img_s", img_s);
			cv::imwrite("fota.jpg", cv::Mat(img_s, r));
		}
	}
	
	return 0;
}
	
	
	
	