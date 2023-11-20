#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main(int argc, char *argv[]) {
    VideoCapture capture = VideoCapture(0);
    if (!capture.isOpened()) { return 1; }

    Mat frame;
    Mat grayFrame;
    double time = 0;
    size_t tickCountSave = 0;
    size_t tickCount = 0;

    while (true) {
        size_t tickCountSaveForFps = tickCountSave;
        capture.read(frame);
        putText(frame, "Time on out frame: " + to_string(time) + "s", Point(5, 50), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0), 1, LINE_AA);

        tickCount = getTickCount();
        time = (tickCount - tickCountSave) / (double)getTickFrequency();
        putText(frame, "Time on read frame: " + to_string(time) + "s", Point(5, 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0), 1, LINE_AA);
        tickCountSave = tickCount;
        if (frame.empty()) {
            break;
        }

        cvtColor(frame, frame, COLOR_BGR2GRAY);
        tickCount = getTickCount();
        time = (tickCount - tickCountSave) / (double)getTickFrequency();
        putText(frame, "Time on convert color: " + to_string(time) + "s", Point(5, 35), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0), 1, LINE_AA);
        tickCountSave = tickCount;

        size_t tickCountForFPS = getTickCount();
        time = (tickCountForFPS - tickCountSaveForFps) / (double)getTickFrequency();
        putText(frame, "FPS: " + to_string(1 / time) + "s", Point(5, 65), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0), 1, LINE_AA);

        imshow("Camera", frame);
        tickCount = getTickCount();
        time = (tickCount - tickCountSave) / (double)getTickFrequency();
        putText(frame, "Time on out frame: " + to_string(time) + "s", Point(5, 50), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0), 1, LINE_AA);
        tickCountSave = tickCount;
        if (waitKey(30) >= 0) {
            break;
        }
    }

    capture.release();
    destroyAllWindows();

    return 0;
}
