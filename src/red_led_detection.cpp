#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // Open the default camera (usually the Raspberry Pi camera)
    cv::VideoCapture cap(0);
    
    // Check if camera opened successfully
    if(!cap.isOpened()) {
        std::cout << "Error opening camera" << std::endl;
        return -1;
    }

    cv::Mat frame;
    cv::namedWindow("Camera Feed", cv::WINDOW_AUTOSIZE);

    while(true) {
        // Capture frame-by-frame
        cap >> frame;
        
        // If the frame is empty, break immediately
        if (frame.empty()) {
            std::cout << "Error: Blank frame grabbed" << std::endl;
            break;
        }

        // Display the resulting frame
        cv::imshow("Camera Feed", frame);

        // Press 'q' to exit
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    // When everything done, release the video capture object
    cap.release();

    // Closes all the frames
    cv::destroyAllWindows();

    return 0;
}
