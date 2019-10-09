#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <iostream>

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;

void tezheng(Mat image1, Mat image2);
void hsvreg(int, void*);	//��ɫ����
void main_logic();   //�߼� ����
void getmodelkeypoint(Mat image , Mat imageDesc);	//��ȡ����������� �Լ�������ʱ��
Mat getthiskeypoint(Mat image);
Mat getmodelkeypoint(Mat image);
void imreadAndResizeAndGetkeypoint();	//��ȡͼƬ���Ҹ��ĳߴ�
void match_picture(Mat imageDesc1, Mat imageDesc2);

char filename[200],key;

int hmin, hmax, smin, smax, vmin, vmax, hmin1, hmax1;
int x = 0, t = 1, flag_hn = 0, flag_mf = 0; //t��ʾ��ɫʶ���������xΪ������ĵ���
double  time1 = 0;
int getpicture = 0;

Mat imageget, get_roi, frame;
Mat image_sww, image_mf, image_tls, image_lh, image_ad, image_hn,image_yld,image_xh;
Mat imageDesc_sww, imageDesc_mf, imageDesc_tls, imageDesc_lh, imageDesc_ad, imageDesc_hn, imageDesc_yld,imageDesc_xh;
Mat imageDesc;


int main(int argc, char *argv[])
{
	int count = 1;
	VideoCapture  capture(0);
	if (!capture.isOpened())
	{
		cout << "failed to open camera!" << endl;
		return -1;
	}

	imreadAndResizeAndGetkeypoint(); //��ȡģ�岢�Ҹı�ߴ粢�һ�ȡ������

	//imageget = imread("E:/tupian/����/�ֳ�ͼƬ/11.jpg");
	//imageDesc = getthiskeypoint(imageget);
	//imshow("333", imageDesc);
	//imshow("444", imageDesc_ad);
	//match_picture(imageDesc, imageDesc_ad);
	//waitKey(0);

	//time1 = (double)getTickCount();
	//imageget = imread("E:/tupian/����/�ֳ�ͼƬ/11.jpg");
	//tezheng(imageget, image_ad);
	//time1 = ((double)getTickCount() - time1) / getTickFrequency();
	//cout << time1 << endl;
	//waitKey(0);

	//hmin = 30; hmax = 45;
	//smin = 43; smax = 255;
	//vmin = 46; vmax = 255;
	//imageget = imread("E:/tupian/����/�ֳ�ͼƬ/62.jpg");
	//t = 4;
	//hsvreg(0,0);
	//waitKey(0);

	while (1)
	{
		key = waitKey(50);
		capture >> frame;
		imshow("video", frame);
		if (key == 27)
			break;     //��ESC���˳�����
		if (key == 32)   //���ո����������
		{
			time1 = (double)getTickCount();
			t = 1; //��ɫ����������Ϊ1
			getpicture = 0; //��������
			count++;
			sprintf(filename, "E:/tupian/����/�ֳ�ͼƬ/%d.jpg", count);
			imwrite(filename, frame);//ͼƬ���浽������Ŀ¼��
			imshow("image", frame);
			main_logic();
		}	
	}
	return 0;

}

void main_logic() {
	imageget = imread(filename);
	//imageget = imread("E:/tupian/����/�ֳ�ͼƬ/12.jpg");


	//imshow("121", imageget);
	//resize(imageget, imageget, Size(480, 640), 0, 0, 1);
	//tz_out = imageget(Range(50, 400), Range(150, 500));
	//imwrite("E:/tupian/����/ѩ��ģ��.jpg", tz_out);

	while (t < 5)
	{
		switch (t)
		{
		case 1:		//�жϺ�ľ��
		{
			hmin = 160; hmax = 180;
			hmin1 = 0; hmax1 = 3;
			smin = 43; smax = 255;
			vmin = 0; vmax = 255;
			hsvreg(0, 0);
			t++;
		}break;
		case 2:		//�ж���ľ��
		{
			hmin = 45; hmax = 90;
			smin = 43; smax = 255;
			vmin = 0; vmax = 255;
			hsvreg(0, 0);
			t++;
		}break;
		case 3:		//�ж���ľ��
		{
			hmin = 100; hmax = 124;
			smin = 46; smax = 255;
			vmin = 0; vmax = 255;
			hsvreg(0, 0);
			t++;
		}break;
		case 4:		//�ж�����
		{
			hmin = 30; hmax = 45;
			smin = 43; smax = 255;
			vmin = 46; vmax = 255;
			hsvreg(0, 0);
			t++;
		}break;
		if (getpicture == 1)
		{
			t = 10;
			time1 = ((double)getTickCount() - time1) / getTickFrequency();
			cout << time1 << endl;
		}
		}
	}

	if (getpicture == 0) {
		imageDesc = getthiskeypoint(imageget);
		for (int m = 1;m < 9;m++) {
			x = 0;
			if (getpicture == 1) 
			{
				time1 = ((double)getTickCount() - time1) / getTickFrequency();
				cout << time1 << endl;
				break;
			}
			if (m == 1)
			{
				match_picture(imageDesc, imageDesc_hn);
				if (x >= 3) {
					cout << "��ţ" << endl;
					getpicture = 1;
				}
			}
			if (m == 2) {
				match_picture(imageDesc, imageDesc_sww);
				if (x >=  3) {
					cout << "ˬ����" << endl;
					getpicture = 1;
					//break;
				}
			}
			if (m == 3) {
				match_picture(imageDesc, imageDesc_tls);
				if (x >= 3) {
					cout << "������" << endl;
					getpicture = 1;
					//break;
				}
			}
			if (m == 4) {
				match_picture(imageDesc, imageDesc_yld);
				if (x >=  3) {
					cout << "���ֶ�" << endl;
					getpicture = 1;
					//break;
				}
			}
			if (m == 5)
			{
				match_picture(imageDesc, imageDesc_ad);
				if (x >= 3)
				{
					cout << "ad����" << endl;
					getpicture = 1;
				}
			}
			if (m == 6) 
			{
				match_picture(imageDesc, imageDesc_xh);
				if (x >= 3)
				{
					cout << "ѩ��" << endl;
					getpicture = 1;
				}
			}
			if (m == 7)
			{
				match_picture(imageDesc, imageDesc_lh);
				if (x >= 3) {
					cout << "�ֻ�" << endl;
					getpicture = 1;
				}
			}
			if (m == 8)
			{
				match_picture(imageDesc, imageDesc_mf);
				if (x >= 3)
				{
					cout << "ħ��" << endl;
					getpicture = 1;
				}
			}

		}
		if (getpicture == 0) 
		{
			cout << "not rec" << endl;
			time1 = ((double)getTickCount() - time1) / getTickFrequency();
			cout << time1 << endl;
		}
	}

	waitKey(10);
}

void tezheng(Mat image1,Mat image2) {
	Mat tz_out;
	tz_out = image1(Range(50, 450), Range(150, 500));
	resize(tz_out, tz_out, Size(), 0.5, 0.5, 1);
	//tz_out = image1.clone();
	//imwrite("E:/tupian/����/ˬ����ģ��.jpg", tz_out);
	imshow("roi", tz_out);
	//��ȡ������
	GaussianBlur(tz_out, tz_out, Size(3, 3), 0.5);
	GaussianBlur(image2, image2, Size(3, 3), 0.5);
	Ptr<SIFT> detector = SIFT::create(80);  //�޶�����ǰ15��������
	Ptr<SIFT> detector1 = SIFT::create(80);
	vector<KeyPoint> keyPoint1, keyPoint2;
	detector->detect(tz_out, keyPoint1);
	detector1->detect(image2, keyPoint2);

	//����������
	//drawKeypoints(tz_out, keyPoint1, tz_out, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	//drawKeypoints(image2, keyPoint2, image2, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	//namedWindow("KeyPoints of image1", 0);
	//namedWindow("KeyPoints of image2", 0);

	//imshow("KeyPoints of image1", image1);
	//imshow("KeyPoints of image2", image2);

	//������������Ϊ�±ߵ�������ƥ����׼��
	SiftDescriptorExtractor siftDescriptor;
	Mat imageDesc1, imageDesc2;
	detector->compute(tz_out, keyPoint1, imageDesc1);
	detector1->compute(image2, keyPoint2, imageDesc2);

	////������ƥ�䲢��ʾƥ����
	BFMatcher matcher(NORM_L2);
	vector<DMatch> matchePoints;
	matcher.match(imageDesc1, imageDesc2, matchePoints, Mat());
	//Mat imageOutput;
	//drawMatches(tz_out, keyPoint1, image2, keyPoint2, matchePoints, imageOutput);
	//namedWindow("Mathch Points", 0);
	//imshow("Mathch Points", imageOutput);

	double minMatch = 1;
	double maxMatch = 0;
	for (int i = 0;i<matchePoints.size();i++)
	{
		//ƥ��ֵ�����Сֵ��ȡ
		minMatch = minMatch>matchePoints[i].distance ? matchePoints[i].distance : minMatch;
		maxMatch = maxMatch<matchePoints[i].distance ? matchePoints[i].distance : maxMatch;
	}
	//�����Сֵ���
	//cout << "���ƥ��ֵ�ǣ� " << minMatch << endl;
	//cout << "���ƥ��ֵ�ǣ� " << maxMatch << endl;

	//��ȡ����ǰ�ߵļ�������ƥ����
	vector<DMatch> goodMatchePoints;
	for (int i = 0;i<matchePoints.size();i++)
	{
		if (matchePoints[i].distance<minMatch + (maxMatch - minMatch) / 2.5)
		{
			x = x + 1;
			goodMatchePoints.push_back(matchePoints[i]);
		}
	}
	cout << "x= " << x << endl;
	//��������ƥ���
	Mat imageOutputgood;
	drawMatches(tz_out, keyPoint1, image2, keyPoint2, goodMatchePoints, imageOutputgood, Scalar::all(-1),
		Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	imshow("Mathch Points", imageOutputgood);
}

void hsvreg(int, void*) {
	Mat imgHSV, imageget1, mask, mask1;

	if ( t > 3 ) blur(imageget, imageget1, Size(7, 7));
	else imageget1 = imageget.clone();
	cvtColor(imageget1, imgHSV, COLOR_BGR2HSV);//תΪHSV
	inRange(imgHSV, Scalar(hmin, smin, vmin), Scalar(hmax, smax, vmax), mask);
	if (t <= 4) 
	{
		Mat element;
		if (t == 4)  element = getStructuringElement(MORPH_RECT, Size(7, 7));
		else  element = getStructuringElement(MORPH_RECT, Size(21, 21));
		//���Ͳ���
		morphologyEx(mask, mask, MORPH_OPEN, element);
	}
	if (t == 1)
	{
		inRange(imgHSV, Scalar(hmin1, smin, vmin), Scalar(hmax1, smax, vmax), mask1);
		addWeighted(mask, 1, mask1, 1, 0.0, mask);
		
	}
	imshow("imgHSV", mask);

	//Ѱ�����������
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(mask, contours, hierarchy, CV_RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	Mat imageContours = Mat::zeros(imageget.size(), CV_8UC3);    //��С��Ӿ��λ���
	float area_max = 0;
	float width = 0;
	float height = 0;
	float x = 0;
	float y = 0;
	vector<Rect> boundRect(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		boundRect[i] = boundingRect(Mat(contours[i]));
		if (boundRect[i].area()>area_max) {
			area_max = boundRect[i].area();

			width = boundRect[i].width;
			height = boundRect[i].height;
			x = boundRect[i].x;
			y = boundRect[i].y;
		}
	}
	//cout << " width=" << width << endl;
	//cout << " height=" << height << endl;
	//cout << " area=" << area_max << endl;


	if (area_max > 3000) {
		if (t == 1) {
			if (area_max > 18000 && area_max < 35000) {
				if ((width / height) > 0.85 && (width / height) < 1.15) {
					cout << "��ľ��" << endl;
					getpicture = 1;
				}
			}
			//if (area_max > 4000 && area_max < 10000) {
			//	if ((width / height) > 0.3 && (width / height) < 0.7) {
			//		cout << "AD����" << endl;
			//		getpicture = 1;
			//	}
			//}
		}
		if (t == 2) {
			if (area_max > 18000 && area_max < 35000) {
				if ((width / height) > 9 && (width / height) < 1.1) {
					cout << "��ľ��" << endl;
					getpicture = 1;
				}
			}
		}
		if (t == 3) {
			if (area_max > 18000 && area_max < 35000) {
				if ((width / height) > 0.85 && (width / height) < 1.15) {
					cout << "��ľ��" << endl;
					getpicture = 1;
				}
			}
		}
		if (t == 4) {
			if (area_max > 20000 && area_max < 80000) {
				if ((width / height) > 0.8 && (width / height) < 1.2) {
					cout << "����" << endl;
					getpicture = 1;
				}
			}
		}
	}

	if (getpicture) {
		cout << " width=" << width << endl;
		cout << " height=" << height << endl;
		cout << " area=" << area_max << endl;
		rectangle(imageContours, Rect(x, y, width, height), Scalar(0, 0, 255), 1, 8);
		imshow("��ɫʶ����", imageContours);
	}
}

//void getmodelkeypoint(Mat image, Mat imageDesc)
//{
//	Mat image_01;
//	GaussianBlur(image, image_01, Size(3, 3), 0.5);
//	Ptr<SIFT> detector = SIFT::create(80);  //�޶�����ǰ15��������
//	vector<KeyPoint> keyPoint;
//	detector->detect(image_01, keyPoint);
//	SiftDescriptorExtractor siftDescriptor;
//	detector->compute(image_01, keyPoint, imageDesc);
//	//Mat imagedraw;
//	//drawKeypoints(image_01, keyPoint, imagedraw, -1, 0);
//	//imshow("1", imagedraw);
//}

Mat getmodelkeypoint(Mat image)
{
	Mat image_01, imageDesc_back;
	GaussianBlur(image, image_01, Size(3, 3), 0.5);
	Ptr<SIFT> detector = SIFT::create(80);  //�޶�����ǰ15��������
	vector<KeyPoint> keyPoint;
	detector->detect(image_01, keyPoint);
	SiftDescriptorExtractor siftDescriptor;
	detector->compute(image_01, keyPoint, imageDesc_back);
	return imageDesc_back;
	//Mat imagedraw;
	//drawKeypoints(image_01, keyPoint, imagedraw, -1, 0);
	//imshow("1", imagedraw);
}

Mat getthiskeypoint(Mat image)
{
	Mat image_01, imageDesc_back;
	image_01 = image(Range(50, 400), Range(150, 500));
	resize(image_01, image_01, Size(), 0.5, 0.5, 1);
	imshow("roi", image_01);
	GaussianBlur(image_01, image_01, Size(3, 3), 0.5);
	Ptr<SIFT> detector = SIFT::create(80);  //�޶�����ǰ15��������
	vector<KeyPoint> keyPoint;
	detector->detect(image_01, keyPoint);
	SiftDescriptorExtractor siftDescriptor;
	//Mat imageDesc1;
	detector->compute(image_01, keyPoint, imageDesc_back);
	return imageDesc_back;
	//imshow("desc", imageDesc);
}

void match_picture(Mat imageDesc1, Mat imageDesc2)
{
	BFMatcher matcher(NORM_L2);
	vector<DMatch> matchePoints;
	matcher.match(imageDesc1, imageDesc2, matchePoints, Mat());
	//Mat imageOutput;
	//drawMatches(tz_out, keyPoint1, image2, keyPoint2, matchePoints, imageOutput);
	//namedWindow("Mathch Points", 0);
	//imshow("Mathch Points", imageOutput);

	double minMatch = 1;
	double maxMatch = 0;
	for (int i = 0;i<matchePoints.size();i++)
	{
		//ƥ��ֵ�����Сֵ��ȡ
		minMatch = minMatch>matchePoints[i].distance ? matchePoints[i].distance : minMatch;
		maxMatch = maxMatch<matchePoints[i].distance ? matchePoints[i].distance : maxMatch;
	}
	//�����Сֵ���
	//cout << "���ƥ��ֵ�ǣ� " << minMatch << endl;
	//cout << "���ƥ��ֵ�ǣ� " << maxMatch << endl;

	//��ȡ����ǰ�ߵļ�������ƥ����
	vector<DMatch> goodMatchePoints;
	for (int i = 0;i<matchePoints.size();i++)
	{
		if (matchePoints[i].distance<minMatch + (maxMatch - minMatch) / 2.5)
		{
			x = x + 1;
			goodMatchePoints.push_back(matchePoints[i]);
		}
	}
	cout << "x= " << x << endl;
	//��������ƥ���
	//Mat imageOutputgood;
	////drawMatches(tz_out, keyPoint1, image2, keyPoint2, goodMatchePoints, imageOutputgood, Scalar::all(-1),
	////	Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	//imshow("Mathch Points", imageOutputgood);
}

void imreadAndResizeAndGetkeypoint()
{
	image_sww = imread("E:/tupian/����/ˬ����.jpg");
	image_mf = imread("E:/tupian/����/ħ��.jpg");
	image_tls = imread("E:/tupian/����/������.jpg");
	image_lh = imread("E:/tupian/����/�ֻ�.jpg");
	image_ad = imread("E:/tupian/����/ad����.jpg");
	image_hn = imread("E:/tupian/����/��ţ.jpg");
	image_yld = imread("E:/tupian/����/���ֶ�.jpg");
	image_xh = imread("E:/tupian/����/ѩ��.jpg");

	resize(image_sww, image_sww, Size(), 0.5, 0.5, 1);
	resize(image_mf, image_mf, Size(), 0.5, 0.5, 1);
	resize(image_tls, image_tls, Size(), 0.5, 0.5, 1);
	resize(image_lh, image_lh, Size(), 0.5, 0.5, 1);
	resize(image_ad, image_ad, Size(), 0.5, 0.5, 1);
	resize(image_hn, image_hn, Size(), 0.5, 0.5, 1);
	resize(image_yld, image_yld, Size(), 0.5, 0.5, 1);
	resize(image_xh, image_xh, Size(), 0.5, 0.5, 1);

	imageDesc_sww = getmodelkeypoint(image_sww);
	imageDesc_mf = getmodelkeypoint(image_mf);
	imageDesc_tls = getmodelkeypoint(image_tls);
	imageDesc_lh = getmodelkeypoint(image_lh);
	imageDesc_ad = getmodelkeypoint(image_ad);
	imageDesc_hn = getmodelkeypoint(image_hn);
	imageDesc_yld = getmodelkeypoint(image_yld);
	imageDesc_xh = getmodelkeypoint(image_xh);
}