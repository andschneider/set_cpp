#include <string>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "load_image.cpp"

static const std::string RAW_WINDOW = "raw window";
static const std::string CONVERTED_WINDOW = "converted window";
static const std::string THRESHOLD_WINDOW = "threshold window";
static const std::string CONTOUR_WINDOW = "contour window";

const int slider_max = 255;
const int hue_max = 180;
int slider_lower_hue = 150;
int slider_upper_hue = 180;
int slider_lower_saturation = 250;
int slider_lower_value = 250;
int slider_upper_saturation = 255;
int slider_upper_value = 255;

cv::Mat cv_hsv, thresh_img;

void threshold_img(int, void*) {
  // threshold based on a given range
  cv::Scalar thresh_min =
      cv::Scalar(slider_lower_hue, slider_lower_saturation, slider_lower_value);
  cv::Scalar thresh_max =
      cv::Scalar(slider_upper_hue, slider_upper_saturation, slider_upper_value);
  inRange(cv_hsv, thresh_min, thresh_max, thresh_img);

  cv::imshow(CONVERTED_WINDOW, thresh_img);
}

int main(int argc, char** argv) {
  // Load an image
  cv_hsv = LoadImg(argv[1]);

  // Convert to hsv
  // cv::cvtColor(img, cv_hsv, cv::COLOR_BGR2HSV);

  // Create a window
  cv::namedWindow(RAW_WINDOW);

  // Create sliders for selecting HSV threshold values
  cv::createTrackbar("lower hue", RAW_WINDOW, &slider_lower_hue, hue_max,
                     threshold_img);
  cv::createTrackbar("upper hue", RAW_WINDOW, &slider_upper_hue, hue_max,
                     threshold_img);

  cv::createTrackbar("lower saturation", RAW_WINDOW, &slider_lower_saturation,
                     slider_max, threshold_img);
  cv::createTrackbar("upper saturation", RAW_WINDOW, &slider_upper_saturation,
                     slider_max, threshold_img);

  cv::createTrackbar("lower value", RAW_WINDOW, &slider_lower_value, slider_max,
                     threshold_img);
  cv::createTrackbar("upper value", RAW_WINDOW, &slider_upper_value, slider_max,
                     threshold_img);

  threshold_img(0, 0);

  cv::waitKey(0);

  return 0;
}
