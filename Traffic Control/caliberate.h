#ifndef CALIBERATE_H_
#define CALIBERATE_H_

using namespace cv;
#define NCHANNELS 3
#define WIDTH_SMALL 320
#define HEIGHT_SMALL 240
#define WIDTH_STEP_SMALL WIDTH_SMALL*NCHANNELS
#define MAX_CORNERS 2500
#define RED   Scalar(0,0,255)
#define GREEN Scalar(0,255,0)
#define BLUE  Scalar(255,0,0)
#define SMALL_SIZE Size(WIDTH_SMALL, HEIGHT_SMALL)

// common variables used in both cpp files
extern VideoCapture capture;
extern Mat frameImg;
extern Mat polygonImg;
extern char* frameData;
extern Point pts[4];
extern double polyArea;
#endif

Mat findRoadImage(void);
void calibPolygon(void);
