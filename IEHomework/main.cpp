#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>

using namespace cv;


void getBackground(Mat Image,Mat Mask){
    int rowLen = Image.rows,colLen = Image.cols;
    for (int r = 0; r < rowLen; r++){
        Vec3b *data = Image.ptr<Vec3b>(r);  //Vec3b:vector<uchar, 3>
        Vec3b *mask = Mask.ptr<Vec3b>(r);
        for (int c = 0; c < colLen; c++){//YCrCb
            double Cb = -0.169*data[c][2] - 0.331*data[c][1] + 0.500*data[c][0]; //蓝色检测
            double Y  =  0.299*data[c][2] + 0.587*data[c][1] + 0.114*data[c][0]; //亮度检测
            if (Cb > 5){
                mask[c][0] = mask[c][1] = mask[c][2] = 0;
            }
        }
    }
}

void getImageAns(Mat Image,Mat Background,Mat Mask,Mat ImageAns){
    int rowLen = Image.rows,colLen = Image.cols;
    for (int r = 0; r < rowLen; r++){
        Vec3b *image = Image.ptr<Vec3b>(r);  //Vec3b:vector<uchar, 3>
        Vec3b *mask = Mask.ptr<Vec3b>(r);
        Vec3b *background = Background.ptr<Vec3b>(r);
        Vec3b *imageAns = ImageAns.ptr<Vec3b>(r);
        for (int c = 0; c < colLen; c++){//YCrCb
            for(int color = 0; color < 3; ++color){
                imageAns[c][color] = (mask[c][color] & image[c][color]) + (~mask[c][color] & background[c][color]);
            }
        }
    }
}


int main(int argc, const char * argv[]) {
    Mat image,mask,imageAns,background,backgroundChange;
    image=imread("/Users/bytedance/Desktop/IEHomework/opencv2.jpg",1);
    background=imread("/Users/bytedance/Desktop/IEHomework/background.jpg",1);
    resize(background,backgroundChange,Size(image.cols,image.rows));
    mask = Mat::zeros(image.size(),CV_8UC3);
    imageAns = Mat::zeros(image.size(),CV_8UC3);
    mask.setTo(255);
    getBackground(image,mask);
    
    getImageAns(image, backgroundChange, mask, imageAns);
    
    
    namedWindow("Mask Image",WINDOW_AUTOSIZE);
    imshow("Mask Image", mask);
    imwrite("/Users/bytedance/Desktop/IEHomework/mask.jpg",mask);
    
    namedWindow("Image",WINDOW_AUTOSIZE);
    imshow("Image", image);
    imwrite("/Users/bytedance/Desktop/IEHomework/image.jpg",image);
    
    namedWindow("Display Image",WINDOW_AUTOSIZE);
    imshow("Display Image", imageAns);
    imwrite("/Users/bytedance/Desktop/IEHomework/imageAns.jpg",imageAns);
    
    
    waitKey(0);
    return 0;
}
