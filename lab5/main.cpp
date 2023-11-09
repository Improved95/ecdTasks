#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char *argv[]) {
    cv::VideoCapture capture = cv::VideoCapture(0);
    cv::Mat frame;

    if (!capture.isOpened()) { return 1; }

    while (true) {
        capture.read(frame);
        if (frame.empty()) {
            break;
        }

        cv::imshow("test", frame);

        if (cv::waitKey(30) >= 0) {
            break;
        }
    }

    capture.release();
    cv::destroyAllWindows();

    return 0;
}

