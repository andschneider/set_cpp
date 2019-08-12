#ifndef IMAGE_CONTOURS
#define IMAGE_CONTOURS

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <string>

using namespace cv;
using namespace std;

void SaveContour(vector<vector<Point> >, Size);
vector<vector<Point> > LoadContour(string);

// Saves a single contour out as a white outline on a black background.
void SaveContour(string file_path, vector<vector<Point> > contours,
                 Size output_image_size) {
  Mat canvas = Mat::zeros(output_image_size, CV_8UC1);

  vector<Vec4i> hierarchy;
  drawContours(canvas, contours, 0, CV_RGB(255, 255, 255), 2, 8, hierarchy, 0);

  imwrite(file_path, canvas);

  cout << "Image successfully saved to " << file_path << endl;
}

// Loads an image that was created using the SaveContour function and finds a
// contour. This is used for contour matching to determine a card's shape.
vector<vector<Point> > LoadContour(string file_path) {
  Mat input_img = imread(file_path, 0);

  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;
  findContours(input_img, contours, hierarchy, CV_RETR_EXTERNAL,
               CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

  // cout << "Contour successfully created" << endl;
  return contours;
}

// 
Mat DrawContour(vector<vector<Point> > contours, Size output_image_size) {
  Mat canvas = Mat::zeros(output_image_size, CV_8UC1);
  vector<Vec4i> hierarchy;
  drawContours(canvas, contours, 0, CV_RGB(255, 255, 255), 2, 8, hierarchy, 0);

  return canvas;
}

#endif
