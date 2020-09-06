#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>

using namespace cv;


void colortransfer(Mat *mask,Mat image){ //蓝背景转白背景，有边缘残留
    double Cb;
    int num_row = image.rows,num_col = image.cols;
    for (int r = 0; r < num_row; r++){
        cv::Vec3b *data = image.ptr<cv::Vec3b>(r);
        for (int c = 0; c < num_col; c++){
            Cb = -0.169*data[c][2]  - 0.331*data[c][1] + 0.5*data[c][0]; //蓝色检测
            //printf("%f ",Cb);
            if (Cb > 5){//蓝色分量比GR分量的平均值高60且蓝色分量大于150
                data[c][0] = 255;   //blue
                data[c][1] = 255;   //green
                data[c][2] = 255;   //red
            }
        }
        //printf("\n");··
    }
}


int main(int argc, const char * argv[]) {
    Mat image,mask;
    image=imread("/Users/bytedance/Desktop/demo/opencv1.jpg",1);
    mask = Mat::zeros(image.size(),CV_8UC1);
    colortransfer(&mask,image);
    namedWindow("Display Image",WINDOW_AUTOSIZE);
    imshow("Display Image", image);
    waitKey(0);
    return 0;
}
