#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include "stdafx.h"
#include<opencv2/opencv.hpp>
#include<opencv/cv.h>
#include<opencv/highgui.h>
#include<opencv2\imgproc\imgproc.hpp>
#include<math.h>
using namespace cv;


int main(int, char**)
{
	/****************** Variables, videofeed setup ***********************/

	float hue_avg1,sat_avg1,int_avg1,hue_var1,sat_var1,int_var1,hue_avg2,sat_avg2,int_avg2,hue_var2,sat_var2,int_var2,hue_avg3,sat_avg3,int_avg3,hue_var3,sat_var3,int_var3;
	Mat frame,hsv,thresh1,medfilt1,thresh2,medfilt2,thresh3,medfilt3;
	Mat boundingBox;
	Mat temp;
	IplImage* centroids = NULL;
	IplImage* sfx = NULL;


	VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;






	

	/************************  Calibration  *******************************/
	while(1)
	{
		
		/*Variables for obtaining H,S and I histograms*/
		int hbins = 180, sbins = 256,ibins = 256;
		int histSize[] = {hbins, sbins};
		int histSize_i[] = {ibins};
		float hranges[] = { 0, 180 };
		float sranges[] = { 0, 256 };
		float iranges[] = { 0, 256 };
		const float* ranges[] = { hranges, sranges };
		const float* ranges_i[] = {iranges};
		MatND hist;
		MatND hist_i;
		int channels[] = {0, 1};
		int channels_i[] = {2};

		
		cap >> frame; // get a new frame from camera 





		temp = frame.colRange(250,290);
		boundingBox = temp.rowRange(200,240);
		cvtColor(boundingBox, hsv, CV_RGB2HSV);
		calcHist( &hsv, 1, channels, Mat(), // do not use mask
				 hist, 2, histSize, ranges,
				 true, // the histogram is uniform
				 false );
		calcHist( &hsv, 1, channels_i, Mat(), // do not use mask
				 hist_i, 1, histSize_i, ranges_i,
				 true, // the histogram is uniform
				 false );
		hue_avg1 = 0;
		sat_avg1 = 0;
		for( int h = 0; h < hbins; h++ ){
			for( int s = 0; s < sbins; s++ )
			{
				float binVal = hist.at<float>(h, s);
				hue_avg1 = hue_avg1 + binVal*h;
				sat_avg1 = sat_avg1 + binVal*s;
			}
		}
		hue_avg1 = hue_avg1/1600;
		sat_avg1 = sat_avg1/1600;		
		hue_var1 = 0;
		sat_var1 = 0;
		for( int h = 0; h < hbins; h++ ){
			for( int s = 0; s < sbins; s++ )
			{
				float binVal = hist.at<float>(h, s);
				hue_var1 = hue_var1 + binVal*(h-hue_avg1)*(h-hue_avg1);
				sat_var1 = sat_var1 + binVal*(s-sat_avg1)*(s-sat_avg1);
			}
		}
		hue_var1 = sqrt(hue_var1/1600);
		sat_var1 = sqrt(sat_var1/1600);
		int_avg1 = 0;
		for( int j = 0; j < ibins; j++ )
		{
			float binVal = hist_i.at<float>(j);
			int_avg1 = int_avg1 + binVal*j;
		}
		int_avg1 = int_avg1/1600;
		
		int_var1 = 0;
		for( int j = 0; j < ibins; j++ )
		{
			float binVal = hist_i.at<float>(j);
			int_var1 = int_var1 + binVal*(j-int_avg1)*(j-int_avg1);
		}
		int_var1 = sqrt(int_var1/1600);





		temp = frame.colRange(300,340);
		boundingBox = temp.rowRange(300,340);
		cvtColor(boundingBox, hsv, CV_RGB2HSV);
		calcHist( &hsv, 1, channels, Mat(), // do not use mask
				 hist, 2, histSize, ranges,
				 true, // the histogram is uniform
				 false );
		calcHist( &hsv, 1, channels_i, Mat(), // do not use mask
				 hist_i, 1, histSize_i, ranges_i,
				 true, // the histogram is uniform
				 false );
		hue_avg2 = 0;
		sat_avg2 = 0;
		for( int h = 0; h < hbins; h++ ){
			for( int s = 0; s < sbins; s++ )
			{
				float binVal = hist.at<float>(h, s);
				hue_avg2 = hue_avg2 + binVal*h;
				sat_avg2 = sat_avg2 + binVal*s;
			}
		}
		hue_avg2 = hue_avg2/1600;
		sat_avg2 = sat_avg2/1600;		
		hue_var2 = 0;
		sat_var2 = 0;
		for( int h = 0; h < hbins; h++ ){
			for( int s = 0; s < sbins; s++ )
			{
				float binVal = hist.at<float>(h, s);
				hue_var2 = hue_var2 + binVal*(h-hue_avg2)*(h-hue_avg2);
				sat_var2 = sat_var2 + binVal*(s-sat_avg2)*(s-sat_avg2);
			}
		}
		hue_var2 = sqrt(hue_var2/1600);
		sat_var2 = sqrt(sat_var2/1600);
		int_avg2 = 0;
		for( int j = 0; j < ibins; j++ )
		{
			float binVal = hist_i.at<float>(j);
			int_avg2 = int_avg2 + binVal*j;
		}
		int_avg2 = int_avg2/1600;
		
		int_var2 = 0;
		for( int j = 0; j < ibins; j++ )
		{
			float binVal = hist_i.at<float>(j);
			int_var2 = int_var2 + binVal*(j-int_avg2)*(j-int_avg2);
		}
		int_var2 = sqrt(int_var2/1600);




		

		temp = frame.colRange(350,390);
		boundingBox = temp.rowRange(200,240);
		cvtColor(boundingBox, hsv, CV_RGB2HSV);
		calcHist( &hsv, 1, channels, Mat(), // do not use mask
				 hist, 2, histSize, ranges,
				 true, // the histogram is uniform
				 false );
		calcHist( &hsv, 1, channels_i, Mat(), // do not use mask
				 hist_i, 1, histSize_i, ranges_i,
				 true, // the histogram is uniform
				 false );
		hue_avg3 = 0;
		sat_avg3 = 0;
		for( int h = 0; h < hbins; h++ ){
			for( int s = 0; s < sbins; s++ )
			{
				float binVal = hist.at<float>(h, s);
				hue_avg3 = hue_avg3 + binVal*h;
				sat_avg3 = sat_avg3 + binVal*s;
			}
		}
		hue_avg3 = hue_avg3/1600;
		sat_avg3 = sat_avg3/1600;		
		hue_var3 = 0;
		sat_var3 = 0;
		for( int h = 0; h < hbins; h++ ){
			for( int s = 0; s < sbins; s++ )
			{
				float binVal = hist.at<float>(h, s);
				hue_var3 = hue_var3 + binVal*(h-hue_avg3)*(h-hue_avg3);
				sat_var3 = sat_var3 + binVal*(s-sat_avg3)*(s-sat_avg3);
			}
		}
		hue_var3 = sqrt(hue_var3/1600);
		sat_var3 = sqrt(sat_var3/1600);
		int_avg3 = 0;
		for( int j = 0; j < ibins; j++ )
		{
			float binVal = hist_i.at<float>(j);
			int_avg3 = int_avg3 + binVal*j;
		}
		int_avg3 = int_avg3/1600;
		
		int_var3 = 0;
		for( int j = 0; j < ibins; j++ )
		{
			float binVal = hist_i.at<float>(j);
			int_var3 = int_var3 + binVal*(j-int_avg3)*(j-int_avg3);
		}
		int_var3 = sqrt(int_var3/1600);


		



		cvRectangle(&(IplImage)frame, cvPoint(250,200), cvPoint(290,240), cvScalar(0,0,255), 1, 8, 0 );
		cvRectangle(&(IplImage)frame, cvPoint(300,300), cvPoint(340,340), cvScalar(0,255,255), 1, 8, 0 );
		cvRectangle(&(IplImage)frame, cvPoint(350,200), cvPoint(390,240), cvScalar(0,255,0), 1, 8, 0 );
		cvShowImage("Calibrate",&(IplImage)frame);

		if(waitKey(20) >= 0) break;

	}












	/*Tracking and gesture recognition*/
	while(1)
	{
		
		int mean_h1 = cvRound(hue_avg1);
		int mean_s1 = cvRound(sat_avg1);
		int mean_i1 = cvRound(int_avg1);
		int mean_h2 = cvRound(hue_avg2);
		int mean_s2 = cvRound(sat_avg2);
		int mean_i2 = cvRound(int_avg2);
		int mean_h3 = cvRound(hue_avg3);
		int mean_s3 = cvRound(sat_avg3);
		int mean_i3 = cvRound(int_avg3);
		
		
		
		cap >> frame; // get a new frame from camera
		cvtColor(frame, hsv, CV_RGB2HSV);
		
		inRange(hsv, Scalar(mean_h1-2*hue_var1,mean_s1-2*sat_var1,mean_i1-3*int_var1), Scalar(mean_h1+2*hue_var1,mean_s1+2*sat_var1, mean_i1 + 3*int_var1),thresh1);		
		medianBlur( thresh1, medfilt1, 21 );
	
		inRange(hsv, Scalar(mean_h2-2*hue_var2,mean_s2-2*sat_var2,mean_i2-3*int_var2), Scalar(mean_h2+2*hue_var2,mean_s2+2*sat_var2, mean_i2 + 3*int_var2),thresh2);		
		medianBlur( thresh2, medfilt2, 21 );

		inRange(hsv, Scalar(mean_h3-2*hue_var3,mean_s3-2*sat_var3,mean_i3-3*int_var3), Scalar(mean_h3+2*hue_var3,mean_s3+2*sat_var3, mean_i3 + 3*int_var3),thresh3);		
		medianBlur( thresh3, medfilt3, 21 );


		CvMoments *moments = (CvMoments*)malloc(sizeof(CvMoments));
		cvMoments(&(IplImage)medfilt1, moments, 1);
        double moment10 = cvGetSpatialMoment(moments, 1, 0);
        double moment01 = cvGetSpatialMoment(moments, 0, 1);
        double area = cvGetCentralMoment(moments, 0, 0);
		static int x1 = 0;
		static int y1 = 0;
		int prev_x1 = x1;
		int prev_y1 = y1;
		x1 = moment10/area;
		y1 = moment01/area;

		cvMoments(&(IplImage)medfilt2, moments, 1);
        moment10 = cvGetSpatialMoment(moments, 1, 0);
        moment01 = cvGetSpatialMoment(moments, 0, 1);
        area = cvGetCentralMoment(moments, 0, 0);
		static int x2 = 0;
		static int y2 = 0;
		int prev_x2 = x2;
		int prev_y2 = y2;
		x2 = moment10/area;
		y2 = moment01/area;

		cvMoments(&(IplImage)medfilt3, moments, 1);
        moment10 = cvGetSpatialMoment(moments, 1, 0);
        moment01 = cvGetSpatialMoment(moments, 0, 1);
        area = cvGetCentralMoment(moments, 0, 0);
		static int x3 = 0;
		static int y3 = 0;
		int prev_x3 = x3;
		int prev_y3 = y3;
		x3 = moment10/area;
		y3 = moment01/area;


		
		centroids = &(IplImage)frame;
		if(prev_x1>0 && prev_y1>0 && x1>0 && y1>0 )
        {            
			cvLine(centroids, cvPoint(x1, y1), cvPoint(x1, y1), cvScalar(0,0,255), 7);
        }
		if(prev_x2>0 && prev_y2>0 && x2>0 && y2>0 )
        {
            cvLine(centroids, cvPoint(x2, y2), cvPoint(x2, y2), cvScalar(0,255,255), 7);
        }
		if(prev_x3>0 && prev_y3>0 && x3>0 && y3>0 )
        {
            cvLine(centroids, cvPoint(x3, y3), cvPoint(x3, y3), cvScalar(0,255,0), 7);
        }





		static int gesture = 0;
		
		static float prev_slope = 0;
		static float prev_mag = 0;
		float mag;
		float slope;
		double delta_theta;
		int rotate_flag=0;
		static double theta = 0;
		static double ampl = 1;
		double delta_ampl;

		static int prev_posx = 0;
		static int prev_posy = 0;
		int posx;
		int posy;
		int translate_flag = 0;
		int delta_x;
		int delta_y;
		static int cX = 300;
		static int cY = 300;

		int prev_gesture = gesture;
		
		float bg = (x1-x3)*(x1-x3) + (y1-y3)*(y1-y3);
		float rg = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
		


		if (bg < 5000 && x1>0 && x3>0 && y1>0 && y3>0  ){
			//printf("rotate gesture \n");
			gesture = 1;	
		}
		else if (rg < 5000 && x1>0 && x2>0 && y1>0 && y2>0  ){
			//printf("move gesture \n");
			gesture = 2;
		}
		else
		{
			//printf("no gesture \n");
			gesture = 0;
		}


		if (gesture == 1)
		{
			float t1 = (y2-(y1+y3)/2);
			float t2 = (x2-(x1+x3)/2);
			slope = -(t1/t2);
			mag = sqrt(t1*t1 + t2*t2);
			if (prev_gesture == 1)
			{
				delta_theta = (atan(slope) - atan(prev_slope))*180/3.1415;
				printf("Delta theta: %f \n",delta_theta);
				rotate_flag = 1;
				theta = theta - 2*delta_theta;
				delta_ampl = (mag - prev_mag)/100;
				ampl = ampl+delta_ampl;
			}
			else
			{
				rotate_flag = 0;	
			}
			prev_slope = slope;
			prev_mag = mag;
			
		}

		
		if (gesture == 2)
		{
			posx = (x1+x2)/2;
			posy = (y1+y2)/2;
			if (prev_gesture ==2)
			{
				delta_x = posx-prev_posx;
				delta_y = posy-prev_posy;
				translate_flag = 1;
				cX = cX + delta_x;
				cY = cY + delta_y;
			}
			else
			{
				translate_flag = 0;	
			}
			prev_posx = posx;
			prev_posy = posy;
		}

		if(sfx == NULL)
        {
            sfx = cvCreateImage(cvGetSize(&(IplImage)frame), 8, 3);
        }

		if(rotate_flag ==1)
		{
			cvEllipse(sfx,cvPoint(cX,cY),cvSize(100*(ampl-delta_ampl),50*(ampl-delta_ampl)),theta+2*delta_theta,0,360,cvScalar(0,0,0),1,8,0);
			cvEllipse(sfx,cvPoint(cX,cY),cvSize(100*ampl,50*ampl),theta,0,360,cvScalar(0,255,255),1,8,0);
		}

		if(translate_flag ==1)
		{
			cvEllipse(sfx,cvPoint(cX-delta_x,cY-delta_y),cvSize(100*ampl,50*ampl),theta,0,360,cvScalar(0,0,0),1,8,0);
			cvEllipse(sfx,cvPoint(cX,cY),cvSize(100*ampl,50*ampl),theta,0,360,cvScalar(0,255,255),1,8,0);
		}






















		cvShowImage("red",&(IplImage)medfilt1);
		cvShowImage("yellow",&(IplImage)medfilt2);
		cvShowImage("green",&(IplImage)medfilt3);
		cvShowImage("centroid",centroids);
		cvShowImage("SFX",sfx);
		if(waitKey(20) >= 0) break;



	}		







}