#include <string>
#include <stdio.h>
#include <opencv2/opencv.hpp>

cv::Mat loadImg(std::string);

// Simple image loader from disk.
cv::Mat loadImg(std::string filePath)
{
    cv::Mat image;
    image = cv::imread( filePath, 1 );

    if ( !image.data ) {
        printf("No image data \n");
    }
    return image;
    
}
