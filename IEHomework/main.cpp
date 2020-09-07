#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>

using namespace cv;


void getBackground(Mat image,Mat Mask){ //蓝背景转白背景，有边缘残留
    int rowLen = image.rows,colLen = image.cols;
    for (int r = 0; r < rowLen; r++){
        Vec3b *data = image.ptr<Vec3b>(r);  //Vec3b:vector<uchar, 3>
        Vec3b *mask = Mask.ptr<Vec3b>(r);
        for (int c = 0; c < colLen; c++){//YCrCb
            double Cb = -0.169*data[c][2]  - 0.331*data[c][1] + 0.5*data[c][0]; //蓝色检测
            double Y= 0.299*data[c][2] + 0.587*data[c][1] + 0.114*data[c][0];
            printf("%f ",Y);
            if (Cb > 5){
                mask[c][0] = mask[c][1] = mask[c][2] = 0;
            }
        }
        print("\n");
    }
}

int main(int argc, const char * argv[]) {
    Mat image,mask,imageAns;
    image=imread("/Users/bytedance/Desktop/IEHomework/opencv1.jpg",1);
    mask = Mat::zeros(image.size(),CV_8UC3);
    mask.setTo(255);
    getBackground(image,mask);

    namedWindow("Mask Image",WINDOW_AUTOSIZE);
    imshow("Mask Image", mask);
    
    bitwise_and(image, mask,imageAns);
    namedWindow("Display Image",WINDOW_AUTOSIZE);
    imshow("Display Image", imageAns);
    
    waitKey(0);
    return 0;
}
