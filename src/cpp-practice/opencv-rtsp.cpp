#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
    std::string username = "", password = "";
    cout << "Enter username: ";
    std::cin >> username;

    cout << "Enter password: ";
    std::cin >> password;

    std::string url = "rtsp://" + username + ":" + password + "@192.168.1.162:554/h264Preview_01_main";

    cv::VideoCapture capture(url);

    if (!capture.isOpened()) {
        cout << "Can't open" << endl;
        return -1;
    }

    cv::namedWindow("TEST", CV_WINDOW_AUTOSIZE);

    cv::Mat frame;

    while(true) {
        if (!capture.read(frame)) {
            cout << "error reading frame" << endl;
        }
        cv::imshow("TEST", frame);
        cv::waitKey(30);
    }

    return 0;
}
