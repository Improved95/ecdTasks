#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main(int argc, char *argv[]) {
    VideoCapture capture = VideoCapture(0);
    if (!capture.isOpened()) { return 1; }

    Mat frame;
    Mat grayFrame;
    double tick = 0;
    size_t tickCountSave = 0;

    while (true) {
        capture.read(frame);
        if (frame.empty()) {
            break;
        }

        size_t tickCount = getTickCount();
        tick = (tickCount - tickCountSave) / (double)getTickFrequency();
        putText(frame, "FPS: " + to_string((int)(1 / tick)), Point(5, 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0), 1, LINE_AA);
        putText(frame, "Time on frame: " + to_string(tick) + "s", Point(5, 35), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0), 1, LINE_AA);
        tickCountSave = tickCount;

        // Применяем черно-белый эффект
        Mat grayFrame;
        cvtColor(frame, grayFrame, COLOR_BGR2GRAY);

        // Преобразуем в цветовое пространство HSV
        // Mat hsvFrame;
        // cvtColor(frame, hsvFrame, COLOR_BGR2HSV);

        // Применяем Gaussian blur
        // Mat blurredFrame;
        // GaussianBlur(frame, blurredFrame, Size(0, 0), 3);

        // resize(hsvFrame, hsvFrame, grayFrame.size());
        // resize(hsvFrame, hsvFrame, grayFrame.size());
        // resize(blurredFrame, blurredFrame, grayFrame.size());
        
        // addWeighted(grayFrame, 0.5, hsvFrame, 0.5, 1, hsvFrame);
        // resize(finalFrame, finalFrame, grayFrame.size());
        // addWeighted(finalFrame, 0.7, blurredFrame, 0.3, 0, finalFrame);

        imshow("Camera", grayFrame);
        // imshow("Camera", hsvFrame);
        if (waitKey(30) >= 0) {
            break;
        }
    }

    capture.release();
    destroyAllWindows();

    return 0;
}
