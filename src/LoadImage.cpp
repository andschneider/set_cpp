#include <string>
#include <stdio.h>
#include <opencv2/opencv.hpp>

cv::Mat loadImg(std::string, bool);

// Simple image loader from disk.
cv::Mat loadImg(std::string filePath, bool hsv=true)
{
    cv::Mat image = cv::imread( filePath, 1 );

    if ( !image.data ) {
        printf("No image data \n");
    }

    if (hsv) {
      cv::cvtColor(image, image, cv::COLOR_BGR2HSV);
    }
    return image;
    
}
