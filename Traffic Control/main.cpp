#include <cv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "caliberate.h"	
#include <iostream>
#include <ctime>				
#include <cmath>


using namespace std;
using namespace cv;
VideoCapture capture;		//The capture class captures video either from harddisk(.avi) or from camera
Mat frameImg;				
Mat g_image;				

double dist(Point2i x1, Point2i x2)	
{	
	return sqrt( pow((x1.x-x2.x),2) + pow((x1.y-x2.y),2) ); 
}

int main() 
{
	string fileName = "traffic.avi";
	capture.open(fileName);		
	if( !capture.isOpened() )
	{	
		cerr<<"video opening error\n"; waitKey(0); system("pause");  
	}

	Mat frameImg_origSize;							//image taken from camera feed in original size
	namedWindow( "out"	  , CV_WINDOW_AUTOSIZE);	//window to show output
	namedWindow( "trackbar", CV_WINDOW_AUTOSIZE);	//Trackbars to change value of parameters
	resizeWindow( "trackbar", 300, 600);			//Resizing trackbar window for proper view of all the parameters
	
	capture>>frameImg_origSize;
	if( frameImg_origSize.empty() ) { cout<<"something wrong"; }
	
	resize(frameImg_origSize, frameImg, SMALL_SIZE, 0, 0, CV_INTER_AREA);	//Resize original frame into smaller frame for faster calculations

	g_image = Mat(SMALL_SIZE, CV_8UC1);	g_image.setTo(0);	//Gray image of frameImg
	
	Mat roadImage = Mat(SMALL_SIZE, CV_8UC3);	//Image of the road (without vehicles)
	roadImage = findRoadImage();
	
	calibPolygon();	//Polygon caliberation: Select four points of polygon (ROI) clockwise and press enter

	Mat binImage = Mat(SMALL_SIZE,CV_8UC1);	//white pixel = cars, black pixel = other than cars
	Mat finalImage = Mat(SMALL_SIZE, CV_8UC3);	//final image to show output

	time_t T = time(0);	//Current time
	float fps = 0, lastCount = 0;	//frames per second

	int thresh_r = 43, thresh_g = 43, thresh_b = 49;						//Threshold parameters for Red, Green, Blue colors
	createTrackbar( "Red Threshold", "trackbar", &thresh_r, 255, 0 );		//Threshold for Red color
	createTrackbar( "Green Threshold", "trackbar", &thresh_g, 255, 0 );		//Threshold for Green color
	createTrackbar( "Blue Threshold", "trackbar", &thresh_b, 255, 0 );		//Threshold for Blue color

	int dilate1=1, erode1=2, dilate2=5;	//Dilate and Erode parameters
	Mat imgA = Mat(SMALL_SIZE, CV_8SC3);	//Used for opticalFlow
	int win_size = 20;	//parameter for opticalFlow
	int corner_count = MAX_CORNERS;	//no of points tracked in opticalFlow
	vector<Point2i> cornersA, cornersB;

	frameImg.copyTo(imgA);

	int arrowGap = 5;	//distance between consecutive tracking points (opticalFlow)
	
	createTrackbar("dilate 1","trackbar", &dilate1, 15, 0);	
	createTrackbar("erode 1","trackbar", &erode1, 15, 0);	
	createTrackbar("dilate 2","trackbar", &dilate2, 15, 0);	
	
	//TODO make callback function for dilate and erode and update their element matrixes
	Mat dilate1_element = getStructuringElement(MORPH_ELLIPSE , Size(2 * dilate1 + 1, 2 * dilate1 + 1), Point(-1,-1) );
	Mat erode1_element = getStructuringElement(MORPH_ELLIPSE , Size(2 * erode1 + 1, 2 * erode1 + 1), Point(-1,-1) );
	Mat dilate2_element = getStructuringElement(MORPH_ELLIPSE , Size(2 * dilate2 + 1, 2 * dilate2 + 1), Point(-1,-1) );
	
	vector< Vec4i > hierarchy;
	vector< vector<Point> > contours;
	vector< uchar > vstatus; 
	vector< float >verror;

	while(true) //Loops till video buffers
	{
		++fps;	//calculation of Frames Per Second

		capture>>frameImg_origSize; //Store image in original size
		if( frameImg_origSize.empty() ) break; //if there is no frame available (end of buffer); stop.

		resize(frameImg_origSize, frameImg, frameImg.size()); //resize original image into smaller image for fast calculation
		imshow("Original Video", frameImg);
		
		for( int i=0; i<HEIGHT_SMALL; ++i) //iter through whole frame and compare it with image of road; if greater than threshold, it must be a vehicle
		{
			for(int j=0; j<WIDTH_SMALL; ++j)
			{
				if(	abs(roadImage.at<Vec3b>(i,j)[0]-frameImg.at<Vec3b>(i,j)[0])<thresh_r &&
					abs(roadImage.at<Vec3b>(i,j)[1]-frameImg.at<Vec3b>(i,j)[1])<thresh_g &&
					abs(roadImage.at<Vec3b>(i,j)[2]-frameImg.at<Vec3b>(i,j)[2])<thresh_b ) //comparing frame image against road image using threshold of Red, Green and Blue
				{	binImage.at<uchar>(i,j) = 0;
					
				}	//other than vehicle (black)
				else
				{	binImage.at<uchar>(i,j) = 255;
					
				}	//vehicle (white)
		    }
		}
		
		frameImg.copyTo(finalImage);
		
		bitwise_and(binImage, polygonImg, binImage, noArray());	//Quadrilateral Cropping

		imshow("Binary Image", binImage);	//with noise
		
		dilate(binImage, binImage, dilate1_element);
		erode(binImage, binImage, erode1_element);
		dilate(binImage, binImage, dilate2_element);
		imshow("noise removed", binImage);	//without noise

		binImage.copyTo(g_image);
		
		findContours( g_image, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
		/// finds contours. g_image = imput image (binary)

		double  percentArea = 0; // % of area occupied by vehicles from the area of polygon
		double contoursArea = 0;

		cout<<"("<<contours.size()<<") ";	// Number of vehicles.

		for(unsigned int idx=0; idx<contours.size(); idx++)
		{
			if( !contours.at(idx).empty() )	
			{
				contoursArea += contourArea( contours.at(idx) );
			}
			Scalar color( rand()&255, rand()&255, rand()&255 );
			drawContours(finalImage, contours, idx, color);
		}

		contours.clear();
		hierarchy.clear();

		percentArea = contoursArea/polyArea;
		cout<<(int)(percentArea*100)<<"% ";

		int xCorners = 0; //No of points to be tracked by opticalFlow
		for(int i=0; i<HEIGHT_SMALL; i+=arrowGap) //preparing input points to be tracked
		{
			for(int j=0; j<WIDTH_SMALL; j+=arrowGap)
			{
				if( xCorners >= MAX_CORNERS-1 ) break; //no of points must not exceed MAX_CORNERS
				if( binImage.at<uchar>(i,j) == 255 )	// white = vehicle
				{
					cornersA.push_back(Point2i(i,j));
					++xCorners;
				}
			}
		}
		cornersB.reserve(xCorners);		
		
		calcOpticalFlowPyrLK(imgA,frameImg,cornersA,cornersB,vstatus, verror, Size( win_size,win_size ),5, cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 20, .3 ),0); //calculates opticalFlow
		/// imgA = previous image; frameImg = current image; cornersA = input points; cornersB = output points
			
		double avgDist = 0; //average length of tracked lines = average movement of vehicles.
		for( int i=0; i<xCorners; i++ ) //iterate through all tracking points
		{
			avgDist += dist(cornersA[i], cornersB[i]); //add length of all lines
			line( finalImage, Point(cornersA[i].x,cornersA[i].y), Point(cornersB[i].x,cornersB[i].y) , CV_RGB(0,0,255),1 , CV_AA); //draw all tracking  lines
		}
		avgDist /= xCorners; //average length of lines
		cout<<setprecision(2)<<avgDist;
		frameImg.copyTo(imgA);

		cornersA.clear();
		cornersB.clear();
		vstatus.clear();
		verror.clear();

		line(finalImage, pts[0], pts[1], CV_RGB(0,255,0),1,CV_AA); //draw polygon in final image (Green)
		line(finalImage, pts[1], pts[2], CV_RGB(0,255,0),1,CV_AA);
		line(finalImage, pts[2], pts[3], CV_RGB(0,255,0),1,CV_AA);
		line(finalImage, pts[3], pts[0], CV_RGB(0,255,0),1,CV_AA);
		imshow( "Final Output", finalImage); 
		waitKey(33);
		if(time(0) >= T+1)
		{
			cout<<" ["<<fps<<"]";
			fps = 0;
			T = time(0);
		}
		cout<<endl;
	}
	return 0;
}
