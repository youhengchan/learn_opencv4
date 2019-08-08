#include <iostream>
#include <cstdlib>
#include <sstream>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

uchar lookup_table[256];

void init_lookup_table(char* divide_factor) {
    for (int i = 0 ; i < 256 ; ++i) {
        lookup_table[i] = i;
    }
    stringstream ss;
    int compression_rate = 10;

    if (divide_factor != NULL) {
        ss << divide_factor;
        ss >> compression_rate;
    }

    if (!compression_rate) {
        cerr << "Error: No compreesion rate given" << endl;
        exit(1);
    }
    for (int i = 0 ; i < 256 ; ++i) {
        lookup_table[i] = (uchar)((compression_rate) * (lookup_table[i] / compression_rate));
    }
}

int main(int argc, char ** argv) {
    // Default
    String img_name = "../media/cat.jpeg";
    char* p_com = NULL;

    // Arguments detection
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " pic_path compression_rate [G]" << endl;
        cerr << "Hint : [] means optional" << endl;
        cerr << "Now use default img at '../media/cat.jpeg' " << endl;
        cerr << "Now use default compressing rate = 10" << endl;
        // exit(1);
    }
    else {
        img_name = argv[1];
        p_com = argv[2];
    }
    init_lookup_table(p_com);

    // Read the img
    Mat source_img = imread(img_name, IMREAD_COLOR);
    namedWindow("Original", WINDOW_AUTOSIZE);
    imshow("Original", source_img);
    Mat des_img = source_img.clone();

    // Create standard LUT for function cv :: lut()
    // Here, created a one channel lut
    Mat table(1, 256, CV_8U);
    // Created 1 * 256 matrix, with CV_8U
    // It also decide the output format as CV_8U
    uchar* p = table.data;
    // Can also be written as
    // uchar * p_start = table.ptr();  // for the defalt parameter is ptr(int row = 0);

    for (int i = 0 ; i < 256 ; ++i) {
        p[i] = lookup_table[i];
    }

    // Call function cv :: LUT([], [], [])
    LUT(source_img, table, des_img);
    namedWindow("Transformed", WINDOW_AUTOSIZE);
    imshow("Transformed", des_img);
    waitKey();
    return 0;
}
