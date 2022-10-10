#include <cv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "caliberate.h"
#include <iostream>

using namespace std;
using namespace cv;

Mat avgImage; //Road Image
float table[WIDTH_SMALL][HEIGHT_SMALL][NCHANNELS];
bool isFixed[WIDTH_SMALL][HEIGHT_SMALL];
Mat polygonImg;

Point pts[4];
int counter=0 ;
double polyArea = 0;
bool firstTime = true;
void my_mouse_callback(int event, int x, int y, int flags, void* param )
{
	if(counter==4)	counter=0;
	switch( event ) 
	{
		case CV_EVENT_LBUTTONDOWN: 
		{
			pts[counter].x = x; 
			pts[counter].y = y;
			
			cout<<pts[counter].x<<" "<<pts[counter].y<<endl;
			if(!firstTime)
			{
				int prevCounter = (counter==0?3:counter-1);
				line(avgImage, pts[prevCounter], pts[counter], CV_RGB(255,0,0), 1, CV_AA);
				imshow("draw polygon", avgImage);
			}
			firstTime = false;
		}
		break;
		case CV_EVENT_LBUTTONUP: 
		{
			++counter;
		}
		break; 
	}
}

void calibPolygon(void)
{
	//while caliberating polygon, click on four points to draw polygon.
	//If any pixel is chosen wrong keep clicking circularly clockwise to update polygon points. Finally press any key to continue.
	polygonImg = Mat(SMALL_SIZE, CV_8UC1);	
	polygonImg.setTo(0);
	imshow("draw polygon", avgImage);
	setMouseCallback("draw polygon",my_mouse_callback,(void*) 0);
	waitKey(0);

	fillConvexPoly( polygonImg, pts, 4, Scalar( 255, 255, 255 ), 4);
	double s,a,b,c,d,e;	// calculating area of quad
	a = sqrt( pow( (pts[0].x-pts[1].x), 2) + pow( (pts[0].y-pts[1].y), 2) );
	b = sqrt( pow( (pts[1].x-pts[2].x), 2) + pow( (pts[1].y-pts[2].y), 2) );
	c = sqrt( pow( (pts[0].x-pts[2].x), 2) + pow( (pts[0].y-pts[2].y), 2) );
	d = sqrt( pow( (pts[2].x-pts[3].x), 2) + pow( (pts[2].y-pts[3].y), 2) );
	e = sqrt( pow( (pts[3].x-pts[0].x), 2) + pow( (pts[3].y-pts[0].y), 2) );
	s = (a+b+c)/2;
	polyArea+= fabs(sqrt(s*(s-a)*(s-b)*(s-c)));
	s = (c+d+e)/2;
	polyArea+= fabs(sqrt( s*(s-c)*(s-d)*(s-e) ));
	destroyWindow("draw polygon");
	return ;
}

Mat findRoadImage(void)
{	
	avgImage = Mat(SMALL_SIZE, CV_8UC3);
	
	Mat img1_origSize, img1, img2, img3, img4;
	for(int i=0; i<HEIGHT_SMALL; ++i)
	{
		for(int j=0; j<WIDTH_SMALL; ++j)
		{
			isFixed[j][i] = false;
		}
	}
	capture>>img1_origSize;	
	resize(img1_origSize, img1, SMALL_SIZE, 0.0, 0.0, CV_INTER_AREA);	img1.copyTo(img4);

	capture>>img1_origSize;	
	resize(img1_origSize, img1, SMALL_SIZE, 0, 0, CV_INTER_AREA);	img1.copyTo(img3);

	capture>>img1_origSize;	
	resize(img1_origSize, img1, SMALL_SIZE, 0, 0, CV_INTER_AREA);	img1.copyTo(img2);

	int xSamples = 100;
	int thresh = 3;

	createTrackbar("road_thresh", "trackbar", &thresh, 50, 0);
	createTrackbar("road_xSamples", "trackbar", &xSamples, 200, 0);
	for(int i=0; i<xSamples; ++i)
	{
		capture>>img1_origSize;
		resize(img1_origSize, img1, img1.size(), 0, 0, INTER_LINEAR);

		int index;
		for(int h=0; h<HEIGHT_SMALL; ++h)
		{
			for(int w=0; w<WIDTH_SMALL; ++w)
			{
				index = h*WIDTH_STEP_SMALL + w*NCHANNELS;

				if( isFixed[w][h] == false &&
					abs(img1.data[index+0]-img2.data[index+0])  < thresh &&
					abs(img1.data[index+1]-img2.data[index+1])  < thresh &&
					abs(img1.data[index+2]-img2.data[index+2])  < thresh &&
					abs(img2.data[index+0]-img3.data[index+0])  < thresh &&
					abs(img2.data[index+1]-img3.data[index+1])  < thresh &&
					abs(img2.data[index+2]-img3.data[index+2])  < thresh &&
					abs(img3.data[index+0]-img4.data[index+0])  < thresh &&
					abs(img3.data[index+1]-img4.data[index+1])  < thresh &&
					abs(img3.data[index+2]-img4.data[index+2])  < thresh )
				{
					isFixed[w][h] = true;
					avgImage.data[index] = img1.data[index];
					avgImage.data[index+1] = img1.data[index+1];
					avgImage.data[index+2] = img1.data[index+2];
				}
			}
		}
		img3.copyTo(img4);
		img2.copyTo(img3);
		img1.copyTo(img2);
		imshow("road_image_formation", avgImage);
		cvWaitKey(33);
	}
	destroyWindow("road_image_formation");
	return avgImage;
}
