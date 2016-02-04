#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Opencv version: "<< CV_VERSION<<std::endl;
    
    //string filename = "/users/aminnaar/desktop/table_example2.png";
    string filename = "/users/aminnaar/desktop/table_example6.png";

    
    
    
    
    //string filename = "/users/aminnaar/desktop/table_example.png";

    
    Mat src=imread(filename);
    
    if(!src.data)
        cerr<<"problem loading image"<<endl;
    
    Mat rsz;
    
    Size size(800,900);
    
    resize(src, rsz, size);
    
    namedWindow("rsz");
    
    imshow("rsz", rsz);
    
    waitKey();
    
    //waitKey(0);
    
    Mat gray;
    
    if(rsz.channels()==3){
        cvtColor(rsz,gray,CV_BGR2GRAY);
    }else{
        gray=rsz;
    }
    
    
    Mat bw;
    adaptiveThreshold(~gray, bw, 255,CV_ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15,-2);
    
    imshow("binary", bw);
    
    waitKey();
    
    Mat horizontal = bw.clone();
    Mat vertical =bw.clone();
    
    int scale = 15;
    
    int horizontalsize = horizontal.cols/scale;
    
    Mat horizontalStructure = getStructuringElement(MORPH_RECT, Size(horizontalsize,1));
    
    erode(horizontal, horizontal, horizontalStructure, Point(-1, -1));
    dilate(horizontal, horizontal, horizontalStructure, Point(-1, -1));
    
    imshow("horizontal", horizontal);
    
    waitKey();
    
    int verticalsize = vertical.rows / scale;
    Mat verticalStructure = getStructuringElement(MORPH_RECT, Size( 1,verticalsize));
    
    erode(vertical, vertical, verticalStructure, Point(-1, -1));
    dilate(vertical, vertical, verticalStructure, Point(-1, -1));
    
    imshow("vertical", vertical);
    
    waitKey();
    
    Mat mask = horizontal + vertical;
    
    imshow("mask", mask);
    
    waitKey();
    
    Mat joints;
    bitwise_and(horizontal, vertical, joints);
    imshow("joints", joints);
    
    waitKey();
    
    // Find external contours from the mask, which most probably will belong to tables or to images
    vector<Vec4i> hierarchy;
    std::vector<std::vector<cv::Point> > contours;
    cv::findContours(mask, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
    
    vector<vector<Point> > contours_poly( contours.size() );
    vector<Rect> boundRect( contours.size() );
    vector<Mat> rois;
    
    
    for (size_t i = 0; i < contours.size(); i++)
    {
        // find the area of each contour
        double area = contourArea(contours[i]);
        
        //        // filter individual lines of blobs that might exist and they do not represent a table
        if(area < 100) // value is randomly chosen, you will need to find that by yourself with trial and error procedure
            continue;
        
        approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
        boundRect[i] = boundingRect( Mat(contours_poly[i]) );
        
        // find the number of joints that each table has
        Mat roi = joints(boundRect[i]);
        
        vector<vector<Point> > joints_contours;
        findContours(roi, joints_contours, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
        
        
        
        cout<<"Number of contours: "<<joints_contours.size() <<endl;
        
        //imshow("roi", roi);
        //waitKey();
        
        // if the number is not more than 5 then most likely it not a table
        if(joints_contours.size() <= 5)
          continue;
        
        
        
        rois.push_back(rsz(boundRect[i]).clone());
        
        //        drawContours( rsz, contours, i, Scalar(0, 0, 255), CV_FILLED, 8, vector<Vec4i>(), 0, Point() );
        rectangle( rsz, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 1, 8, 0 );
    }
    
    for(size_t i = 0; i < rois.size(); ++i)
    {
 
        imshow("roi", rois[i]);
        waitKey();
    }
    
    imshow("contours", rsz);
    
    imwrite("/Users/alexminnaar/Desktop/image_detect.jpg", rsz);
    
    waitKey();
    
    return 0;
}
*/