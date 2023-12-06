#include <opencv2/opencv.hpp>
#include <iostream>
#include<vector>
using namespace cv;
using namespace std;
Mat image = imread("E:\\RM\\opencv_picture\\192.jpg");
int w = image.cols, h = image.rows;

//���ͼ��
void imen(int& row,int* col, int& length)
{
    int j = row - 0.6*length;
    int i = col[0];

    for (; i < col[1]; i++)
    {
        image.at<Vec3b>(j, i)[0]=0;
        image.at<Vec3b>(j, i)[1] = 0;
        image.at<Vec3b>(j, i)[2] = 255;
    }
    for (; j < row + 1.6 * length; j++)
    {
        image.at<Vec3b>(j, i)[0] = 0;
        image.at<Vec3b>(j, i)[1] = 0;
        image.at<Vec3b>(j, i)[2] = 255;
    }
 
    for (; i >col[0]; i--)
    {
        image.at<Vec3b>(j, i)[0] = 0;
        image.at<Vec3b>(j, i)[1] = 0;
        image.at<Vec3b>(j, i)[2] = 255;
    }
    for (; j > row - 0.6 * length; j--)
    {
        image.at<Vec3b>(j, i)[0] = 0;
        image.at<Vec3b>(j, i)[1] = 0;
        image.at<Vec3b>(j, i)[2] = 255;
    }
    
}
//ͼ������ֵɸѡ
void imselect(Mat &image2 )
{
    
    int m = w / 100;
    vector<int> width(m + 1, 0);
    vector<int> row(m+1,h);
    for (int i = 0; i < w; i++)
    {   
        int j = 0;
        int pixel = image2.at<uchar>(j, i);
        while (pixel == 0&&j<h-1)
        {  
            pixel = image2.at<uchar>(++j,i);
        }
        if (j != h - 1)
        {   
            //cout << j << " " << i << endl;
            int x = i / 100;
            width[x]++;
            if (j < row[x]) row[x]=j;
        }
    }  

    //Ѱ�ҵƴ����
    int wid = 0;
    for (int i = 0; i < m; i++)
    {
        if (width[i] > wid)wid = width[i];
    }
 
    //Ѱ�ҵƴ���������
    int ro = 0;
    for (int i = 0; i <= m; i++)
    {
        if (row[i] < h)
        {
            ro = row[i]; int k = i+1;
            while (k <= m && row[k++] < h && row[k++] != ro);
            if (k <= m) 
                break;
        }
   } 
    //cout << ro << endl;
    int co[2]={0}, count = 0;
    //Ѱ����������
    for (int i = 0; i < w; i++)
    {
        int pixel = image2.at<uchar>(ro, i);
        if (pixel == 255)
        {
            co[count++] = i;
            i += wid;
        }
        if (count == 2) break;
  }
    //Ѱ�ҵƴ�����
    int len = 0;
    for (int i =co[0];i<co[0]+wid; i++)
    {   
        for (int j = ro; j < h; j++)
        {
            int pixel = image2.at<uchar>(j, i);
            if (pixel == 255 && j > len) len = j;
        }
    }
    len -= ro;
    imen(ro, co, len);
    //cout << len - ro << endl;
    //cout << co[0] << endl << co[1] << endl;
}

int main() {
   
    //cout << w<< endl << h << endl;
    //imshow("image", image);
    if (image.empty()) {
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    // ��ͼ���BGR��ɫ�ռ�ת��ΪHSV��ɫ�ռ�
    Mat hsvImage;
    cvtColor(image, hsvImage, COLOR_BGR2HSV);
   
    
    // �����ɫ��HSV��Χ
    Scalar lowerRed = Scalar(0, 43, 46);
    Scalar upperRed = Scalar(10, 255, 255);
   
    // ������ģ�Թ��˺�ɫ����
    Mat redMask;
    inRange(hsvImage, lowerRed, upperRed, redMask);
    //imshow("mask", redMask);
    imselect(redMask);
    imshow("img", image);
   waitKey(0);
   //imwrite("E:\\RM\\opencv_picture\\task4_1.jpg", image);
    return 0;
}