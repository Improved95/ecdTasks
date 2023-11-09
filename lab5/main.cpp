#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

/*int main(int argc, char *argv[]) {
    VideoCapture capture = VideoCapture(0);
    if (!capture.isOpened()) { return 1; }

    Mat frame;
    double tick = 0;
    size_t tickCountSave = 0;

    while (true) {
        capture.read(frame);
        if (frame.empty()) {
            break;
        }

        size_t tickCount = getTickCount();
        tick = (tickCount - tickCountSave) / (double)getTickFrequency();
        putText(frame, "FPS: " + to_string(1 / tick), Point(5, 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0), 1, LINE_AA);
        tickCountSave = tickCount;

        imshow("Camera", frame);
        if (waitKey(30) >= 0) {
            break;
        }
    }

    capture.release();
    destroyAllWindows();

    return 0;
}*/

int main(int argc, char** argv) {
    VideoCapture cap("/Users/improvedmac/Documents/RecordScreen/test.mp4");
    if (!cap.isOpened()) {
        cerr << "Error: could not open video file" << endl;
        return -1;
    }

    namedWindow("Video", WINDOW_NORMAL);

    Mat frame;
    double tick = 0;
    size_t tickCountSave = 0;

    while (true) {
        cap.read(frame);
        if (frame.empty()) {
            break;
        }

        size_t tickCount = getTickCount();
        tick = (tickCount - tickCountSave) / (double)getTickFrequency();
        putText(frame, "FPS: " + to_string((int)(1 / tick)), Point(10, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2, LINE_AA);
        tickCountSave = tickCount;

        imshow("Video", frame);
        if (waitKey(30) >= 0) {
            break;
        }
    }

    cap.release();
    destroyAllWindows();

    return 0;
}
