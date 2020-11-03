#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>


using namespace std;
using namespace cv;

class MyObject
{
public:
	int maxC;
	vector<Point> pos;
	Point getP()
	{
		Point sump = std::accumulate(pos.begin(), pos.end(), Point(0, 0));
		sump.x /= pos.size();
		sump.y /= pos.size();
		return sump;
	}
	void addP(Point p)
	{
		pos.push_back(p);
		if (pos.size() > maxC)
		{
			pos = vector<Point>(pos.begin() + 1, pos.end());
		}
	}
	void addEmpty()
	{
		if (pos.size() > 0)
		{
			pos = vector<Point>(pos.begin() + 1, pos.end());
		}
	}
};

int main()
{
	int loRange[3] = {0, 167, 84};
	int hiRange[3] = {255, 255, 255};

	namedWindow("kolor", cv::WINDOW_AUTOSIZE);
	createTrackbar("loRange0", "kolor", &(loRange[0]), 255);
	createTrackbar("loRange1", "kolor", &(loRange[1]), 255);
	createTrackbar("loRange2", "kolor", &(loRange[2]), 255);
	createTrackbar("hiRange0", "kolor", &(hiRange[0]), 255);
	createTrackbar("hiRange1", "kolor", &(hiRange[1]), 255);
	createTrackbar("hiRange2", "kolor", &(hiRange[2]), 255);
	VideoCapture camera(0);
	Mat background = imread("plaza.jpg", IMREAD_COLOR);

	MyObject myobj;
	myobj.maxC = 10;
	while (waitKey(1) != 27)
	{
		int dilation_size = 5;
		auto structElem = getStructuringElement(MORPH_ELLIPSE,
												Size(2 * dilation_size + 1, 2 * dilation_size + 1),
												Point(dilation_size, dilation_size));
		Mat frame;
		Mat backgroundScaled;
		Mat frameMask, frameNegMask;
		Mat frameWithMask, backgroundScaledWithMask;
		Mat meinniceplace;

		camera >> frame;
		flip(frame, frame, 1);
		resize(background, backgroundScaled, {frame.cols, frame.rows});

		cvtColor(frame, frameMask, COLOR_BGR2HSV);
		inRange(frameMask, Scalar(loRange[0], loRange[1], loRange[2]),
				Scalar(hiRange[0], hiRange[1], hiRange[2]), frameNegMask);
		morphologyEx(frameNegMask, frameNegMask, MORPH_CLOSE, structElem);
		morphologyEx(frameNegMask, frameNegMask, MORPH_OPEN, structElem);
		imshow("dilate", frameNegMask);

		vector<vector<Point>> contours;
		findContours(frameNegMask, contours, RETR_LIST, CHAIN_APPROX_TC89_KCOS);
		sort(contours.begin(), contours.end(),
			 [](auto &a, auto &b) {
				 return contourArea(a, false) > contourArea(b, false);
			 });

		if(contours.size() > 1){
           Rect table[2] = {Rect(), Rect()};

           for(auto c:contours){
               Rect r = boundingRect(c);
               int area = r.area();
               if(area > table[0].area()){
                   table[0] = r;
               }else if (area > table[1].area()){
                   table[1] = r;
               }
           } 
        for(int i = 0; i < 2; i++){
            rectangle(frame, table[i], {0, 0, 255}, 2);
        }
        if(!(table[0].y > table[1].y + 90 || table[1].y > table[0].y + 90)){
        arrowedLine(frame,
        {table[0].x + table ->width /2, table[0].y + table->height/ 2},
        {table[1].x + table ->width /2, table[1].y + table->height/ 2},
        {0, 255, 0}, 3);
        }
        }
        imshow("contours", frame);
	}
	return 0;
}