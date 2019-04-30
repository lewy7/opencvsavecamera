#include "cv.h"
#include "highgui.h"
#include <stdio.h>
#include <ctype.h>

int main()
{
	CvCapture* capture = cvCaptureFromCAM(0);
	IplImage* frame = 0;
	CvVideoWriter* video=NULL;
	int n=0;
	if(!capture){
		printf("error open cammera\n");
		return -1;
	}
	
	frame=cvQueryFrame(capture);
	printf("size %d * %d\n",frame->width,frame->height);
	//video=cvCreateVideoWriter("aaa.avi",CV_FOURCC('x','v','i','d'),25, cvSize(frame->width,frame->height));
	//video=cvCreateVideoWriter("aaa.avi",CV_FOURCC('M','J','P','G'),25, cvSize(frame->width,frame->height));
	
	video=cvCreateVideoWriter("c:\\aaa.avi",-1,15, cvSize(frame->width,frame->height)); //为防止编码不支持，第二个参数选择对话框
	//我这里只能选 micosoft vedio 1 
 	if(!video){
 		printf("VideoWriter create error \n");
 		return -1;
 	}
	
	cvNamedWindow("Motion", 1 );
	while(1)  
	{  
		frame=cvQueryFrame(capture);
		if(!frame)
		{
			printf("get frame error\n");
			break;
		}
		n = cvWriteFrame(video,frame);
		if(n!=1){
			printf("write frame error : %d\n",n);
		}
		cvShowImage("Motion",frame);

		if(cvWaitKey(1)>0) break; //这个必须要有，否则只有灰色窗口
	}


	cvReleaseVideoWriter(&video);
	cvReleaseCapture( &capture );
    cvDestroyWindow( "Motion" );
	return 0;
}
