#include <iostream>
#include <cstdlib>
#include <sstream>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

unsigned char lookup_table[256];

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
        lookup_table[i] = (unsigned char)((compression_rate) * (lookup_table[i] / compression_rate));
    }
}

Mat& iterator_compress(Mat& I, const uchar* const table) {
    cout << endl << "********Use Iterator Scanner***********" << endl;
    CV_Assert(I.depth() == CV_8U);
    const int channels = I.channels();
    switch (channels) {
        case 1: {
            MatIterator_<uchar> it, end;
            for (it = I.begin<uchar>(), end = I.end<uchar>() ; it != end ; ++it) {
                *it = table[*it];
            }
            break;
        }
        case 3 :  {
            MatIterator_<Vec3b> it, end;
            for (it = I.begin<Vec3b>(), end = I.end<Vec3b>() ; it != end ; ++it) {
                (*it)[0] = table[(*it)[0]];
                (*it)[1] = table[(*it)[1]];
                (*it)[2] = table[(*it)[2]];
            }
            break;
        }
    }
    return I;
}

Mat& color_compress(Mat& I, const uchar* const table) {
    cout << endl << "********Use Pointer Scanner***********" << endl;
    CV_Assert(I.depth() == CV_8U);
    uchar *p_row = NULL;  //  Start position of the row
    int nRow = I.rows;
    int nCol = I.cols * I.channels();
    if (I.isContinuous()) {
        nCol *= nRow;
        nRow = 1;
    }
    for (int i = 0 ; i < nRow ; ++i) {
        p_row = I.ptr<uchar>(i);
        for (int j = 0 ; j < nCol ; ++j) {
            p_row[j] = table[p_row[j]];
        }
    }
    return I;
}

Mat& random_access_compress(Mat& I, uchar* const table) {
    cout << endl << "**********Use random access***********" << endl;
    CV_Assert(I.depth() == CV_8U);

    const int channels = I.channels();
    switch (channels) {
        case 1 : {
            for (int i = 0 ; i < I.rows ; ++i) {
                for (int j = 0 ; j < I.cols ; ++j) {
                    I.at<uchar>(i, j) = table[I.at<uchar>(i, j)];
                }
            }
            break;
    }
        case 3 : {
            Mat_<Vec3b> _I = I;
            for (int i = 0 ; i < I.rows ; ++i) {
                for (int j = 0 ; j < I.cols ; ++j) {
                    _I(i, j)[0] = table[_I(i, j)[0]];
                    _I(i, j)[1] = table[_I(i, j)[1]];
                    _I(i, j)[2] = table[_I(i, j)[2]];
                }
            }
            I = _I;
            break;
        }
    }
    return I;
}

int main(int argc, char** argv) {
    // Default:
    String img_name = "../media/cat.jpeg";
    char* p_com = NULL;
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
    double time_start = (double)getTickCount();

    Mat source_img = imread(img_name, IMREAD_COLOR);
    namedWindow("Original", WINDOW_AUTOSIZE);
    imshow("Original", source_img);
    random_access_compress(source_img, lookup_table);
//    color_compress(source_img, lookup_table);
//    iterator_compress(source_img, lookup_table);
    namedWindow("Reduced", WINDOW_AUTOSIZE);
    imshow("Reduced", source_img);
    imwrite("../media/reduced.jpeg", source_img);
    double time_end = (double)getTickCount();
    cout << "Time consumption : " << (time_end - time_start) / getTickFrequency() << endl;
    waitKey();
    return 0;
}
