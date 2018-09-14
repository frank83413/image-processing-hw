#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <highgui.h>
#include "cv.h"
using namespace std;
using namespace cv;
void homework1(Mat SrcImg ,Mat DstImg);		//�Ĥ@�Ӱ��D
void homework2(Mat SrcImg ,Mat DstImg);		//�ĤG�Ӱ��D
void homework3(Mat SrcImg ,Mat DstImg);		//�ĤT�Ӱ��D
double power(float a, float b);				//�ΨӺ⦸��

double power(float a, float b){
	double c=1;
	for(int i=0; i<b ;i++){
		c=c*a;
	}
	return c;
}

void homework1(Mat SrcImg ,Mat DstImg){
	double r,c=255;
	cout << "enter r:";
	cin >> r;
	c=1/power(c,r-1);							//�p��c=255/(255^r)=1/255^(r-1)
	for(int i=0; i<SrcImg.rows; ++i){
		for(int j=0; j<SrcImg.cols; ++j)
		{
			DstImg.at<uchar>(i,j)=c*power(SrcImg.at<uchar>(i,j),r);	//S=c*R^r
		}
	}
}
void homework2(Mat SrcImg ,Mat DstImg){
	int bit;									//�ΨӬ����Ѧ�bit�����
	int test=0;									//�ΨӴ��լO�b0�϶��٬O1�϶�
	cout << "enter the reference bit:";			
	cin >> bit;
	bit=power(2,bit-1);							//�N�p��X�Ӫ��϶��j�p�s�^bit��
	for(int i=0; i<SrcImg.rows; ++i)
		for(int j=0; j<SrcImg.cols; ++j){
		{
			test=SrcImg.at<uchar>(i,j)/bit;		//test=pixel��/bit�᪺��
			if(test%2==0)DstImg.at<uchar>(i,j)=0;//test�������ݩ�0�϶� �_���ݩ�1�϶�
			else DstImg.at<uchar>(i,j)=255;
		}
	}
}

void homework3(Mat SrcImg ,Mat DstImg){
	float pixelnumber[256]={0};				//�����C�ӭȦ��h�֭�pixel
	float n=SrcImg.rows*SrcImg.cols;		//n=����pixel�ƶq
	for(int i=0; i<SrcImg.rows; ++i){		//�p��C�ӭȦ��h�֭�pixel
		for(int j=0; j<SrcImg.cols; ++j)
		{
			pixelnumber[SrcImg.at<uchar>(i,j)]++;
		}
	}	
	for(int i=1; i<256; ++i){
		cout <<pixelnumber[i]/n << "\n";		//��X�¾��v
		pixelnumber[i]=pixelnumber[i]+pixelnumber[i-1];	//�֥[
	}
	for(int i=0; i<256; ++i){
		pixelnumber[i]=255*pixelnumber[i]/n;			//���Hn		
	}	
	for(int i=0; i<SrcImg.rows; ++i){
		for(int j=0; j<SrcImg.cols; ++j)
		{
			DstImg.at<uchar>(i,j)=pixelnumber[SrcImg.at<uchar>(i,j)];//�s�J�s��
		}
	}
	for(int i=1; i<256; ++i){
		pixelnumber[i]=0;		
	}
	for(int i=0; i<SrcImg.rows; ++i){		//�p��C�ӭȦ��h�֭�pixel
		for(int j=0; j<SrcImg.cols; ++j)
		{
			pixelnumber[DstImg.at<uchar>(i,j)]++;
		}
	}	
	int stop;
	cout <<"���H����J�@�ӼƦr�H�~����ܷs���v";
	cin >> stop;				//��X���ª����v��A�H�K��J�@�ӼƦr�A�~���X�s�����v�A�ÿ�X�Ϥ�
	for(int i=1; i<256; ++i){
		cout<< pixelnumber[i]/n << "\n";//��X�s���v		
	}
}

int main(){
	int homework;
	// Read input images
	// Fig3.tif is in openCV\bin\Release
	cout << "enter the work number(1,2,3):";
	cin >> homework;
	Mat SrcImg;
	Mat DstImg;
	if(homework==1){
		SrcImg = imread("Fig01_Slide10.tif", CV_LOAD_IMAGE_GRAYSCALE);
		DstImg = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
		homework1(SrcImg , DstImg);
	}
	if(homework==2){
		SrcImg = imread("Fig02_Slide14.tif", CV_LOAD_IMAGE_GRAYSCALE);
		DstImg = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
		homework2(SrcImg , DstImg);
	}
	if(homework==3){
		SrcImg = imread("Fig03_Slide22.tif", CV_LOAD_IMAGE_GRAYSCALE);
		DstImg = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
		homework3(SrcImg , DstImg);
	}
	

	// Show images
	imshow("Input Image", SrcImg);
	imshow("Output Image", DstImg);

	// Write output images
	imwrite("Fig3_output.tif", DstImg);
	
	waitKey(0);
	return 0;
}