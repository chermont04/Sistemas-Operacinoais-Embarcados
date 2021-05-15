
#include <iostream>
#include <iomanip>
#include <sstream>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "face_detect.hpp"
#include "dataset.hpp"
#include "config.hpp"


std::string get_subject_name(int argc, char *argv[]) {

    std::string model_name;
    if (argc != 2) {
        std::cout << "Error: Correct usage: ./capture_positives <subject_name>" << std::endl;
        exit(1);
    } else {
        return argv[1];
    }

}


int main(int argc, char *argv[]) {

    std::string subject_name = get_subject_name(argc, argv);

    cv::VideoCapture camera = get_camera();

    // Create the positive images directory if it doesn't already exist
    create_directory(std::string(TRAINING_DIR) + "positive/", true);

    // Create a directory to hold positive images if it doesn't already exist
    if (!create_directory(std::string(TRAINING_DIR) + "positive/" + subject_name)) {
        // Failed to create directory, exit
        exit(1);
    }

    cv::Mat image;
    bool loop = true;
    int image_number = 1;

    while (loop) {
        
        flush_capture_buffer(camera);
        camera >> image;
        cv::cvtColor(image, image, cv::COLOR_RGB2GRAY);

        std::vector<cv::Rect> face_regions = detect_faces(image);

        if (face_regions.size() != 1) {

            std::cout << "Error: Detected " << face_regions.size() << " faces." << std::endl;

        } else {

            std::cout << "Successfuly found a face. Saving positive image... " << std::flush;
            image = image(face_regions[0]);

            std::stringstream ss;
            ss << std::setfill('0') << std::setw(3) << image_number;
            if(!save_pgm_image(image, std::string(TRAINING_DIR) + "positive/" + subject_name + "/" + TRAINING_FILENAME_PREFIX + ss.str() + ".pgm")) {
                exit(1);
            }

            std::cout << "[DONE]" << std::endl;
            image_number ++;

        }

        std::string input;
        std::cout << "Enter 'q' to quit, or any other key to take another picture: " << std::endl;
        std::cin >> input;
        if (input == "q" || input == "Q") {
            loop = false;
        }

    }
}