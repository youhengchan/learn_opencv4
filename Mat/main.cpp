#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;
int main( int argc, char** argv )
{
    cv :: String imageName( "../media/cat.jpeg" ); // by default
    if( argc > 1)
    {
        imageName = argv[1];
    }
    else {
        cout << "Usage: " << argv[0] << " " << " pic_file_path" << endl;
        cout << "Now use default image" << endl;
    }
    Mat image = imread( imageName, IMREAD_COLOR ); // Read the file
    if( image.empty() )                      // Check for invalid input
    {
        cout <<  "Could not open or find the image" << endl ;
        return -1;
    }
    // shallow copy
    Mat A = image;
    Mat B(A);
    Mat C = A;
    Mat D(A, Rect(10, 10, 100, 100));  //  Use a rectangle to extract from the pic A
    Mat E = A(Range::all(), Range(1, 39));  // Using a row and column boundaries

    // For deep copy, use cv:::Mat::clone() & cv::Mat::copyTo()
    Mat F = A.clone();
    Mat G;
    A.copyTo(G);

    namedWindow( "A", WINDOW_NORMAL | WINDOW_FREERATIO | WINDOW_GUI_EXPANDED ); // Create a window for display.
    // Use WINDOW_AUTOSIZE for no Qt-backend situation
    imshow( "A", image );                // Show our image inside it.

    // Convert the BGR image into the gray image and storage it in ../media/Gray_fish.jpg
    Mat gray_img;
    cvtColor( image, gray_img, COLOR_BGR2GRAY);  // To use COLOR_BGR2GRAY, one has to include <opencv2/opencv.hpp>
    cv :: String new_pic_name = "../media/gra.jpeg";
    imwrite(new_pic_name, gray_img);
    // Create a new window named "Gray pics" to show the window
    namedWindow("Gray version", WINDOW_AUTOSIZE);
    imshow("Gray version", gray_img);

    // cv::Mat::Mat constructor
    Mat M(8, 8, CV_8UC3, Scalar(0, 0, 255));
    cout << "M = " << endl << " " << M << endl << endl;
    namedWindow("Manipulated pic", WINDOW_AUTOSIZE);
    imshow("Manipulated pic", M);
    imwrite("../media/manipulate_pic.jpg", M);

    int sz[3] = {2, 2, 2};
    Mat L(3, sz, CV_8UC(1), Scalar::all(0));  // One channel means there are only black and write

    // For small matrices you may use comma separated initializers or initializer lists
    // (C++11 support is required in the last case):
    C = (Mat_<double>(3,3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    cout << "C = " << endl << " " << C << endl << endl;

    C = (Mat_<double>({0, -1, 0, -1, 5, -1, 0, -1, 0})).reshape(3);
    cout << "C = " << endl << " " << C << endl << endl;
    //cout << "L : " << endl <<  L << endl << endl; // Error
    // namedWindow("yz", WINDOW_AUTOSIZE);  // opencv cannot show non-2-dimensional pic with "<<"
    // imshow("yz", yz);

//    namedWindow("B", WINDOW_AUTOSIZE);
//    imshow("B", B);

//    namedWindow("C", WINDOW_AUTOSIZE);
//    imshow("C", C);


    // Use cv:: randu() to generate a picture randomly
    Mat Random_generated_pic = Mat(1000, 1000, CV_8UC4);
    randu(Random_generated_pic, Scalar::all(0), Scalar(255));
    imwrite("../media/random.bmp", Random_generated_pic);
    namedWindow("R", WINDOW_AUTOSIZE);
    imshow("R", Random_generated_pic);

//    namedWindow("D", WINDOW_AUTOSIZE);
//    imshow("D", D);

//    namedWindow("E", WINDOW_AUTOSIZE);
//    imshow("E", E);

//    namedWindow("E", WINDOW_AUTOSIZE);
//    imshow("F", F);

//    namedWindow("E", WINDOW_AUTOSIZE);
//    imshow("G", G);

    waitKey(0); // Wait for a keystroke in the window
    return 0;
}

// Tutorial Origin:
// 1. https://docs.opencv.org/master/db/deb/tutorial_display_image.html
// 2. https://docs.opencv.org/master/db/d64/tutorial_load_save_image.html
// 3. https://docs.opencv.org/master/d6/d6d/tutorial_mat_the_basic_image_container.html
