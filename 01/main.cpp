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
    String imageName( "fish.jpeg" ); // by default
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
    namedWindow( "Colorful pics", WINDOW_NORMAL | WINDOW_FREERATIO | WINDOW_GUI_EXPANDED ); // Create a window for display.
    // Use WINDOW_AUTOSIZE for no Qt-backend situation
    imshow( "Colorful pics", image );                // Show our image inside it.

    // Convert the BGR image into the gray image and storage it in ../media/Gray_fish.jpg
    Mat gray_img;
    cvtColor( image, gray_img, COLOR_BGR2GRAY);  // To use COLOR_BGR2GRAY, one has to include <opencv2/opencv.hpp>
    imwrite("../media/Gray_fish.jpg", gray_img);
    // Create a new window named "Gray pics" to show the window
    namedWindow("Gray pics", WINDOW_AUTOSIZE);
    imshow("Gray pics", gray_img);

    waitKey(0); // Wait for a keystroke in the window
    return 0;
}

// Tutorial Origin:
// 1. https://docs.opencv.org/master/db/deb/tutorial_display_image.html
// 2. https://docs.opencv.org/master/db/d64/tutorial_load_save_image.html
