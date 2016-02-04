//
//  main.cpp
//  opencv-table-detection
//
//  Created by Alex Minnaar on 11/4/15.
//  Copyright (c) 2015 Alex Minnaar. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;



using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Opencv version: "<< CV_VERSION<<std::endl;
    
    //string filename = "/users/aminnaar/downloads/nys100/file-page1.jpg";
    
    //string filename = "/Users/aminnaar/Downloads/IA900/file-page2.jpg";
    
    //string filename = "/Users/aminnaar/Downloads/file-page1 2.jpg";
    
    //string filename = "/Users/aminnaar/Downloads/f433aoi-page-008.jpg";

    //string filename="/users/aminnaar/Downloads/f712/file-page1.jpg";
    //string filename="/users/aminnaar/Downloads/f907-page-001.jpg";
    
    //string filename="/users/aminnaar/Downloads/f211a-page-002.jpg";
    //string filename="/users/aminnaar/Downloads/f56f-page-002.jpg";
    
    //string filename="/users/aminnaar/Downloads/f673-page-002.jpg";
    //string filename="/users/aminnaar/Downloads/f706gsd1-page-003.jpg";
    
    //string filename="/users/aminnaar/Downloads/f712-page-003.jpg";
    
    //string filename="/users/aminnaar/Downloads/f720to-page-003.jpg";
    
   // string filename="/users/aminnaar/Downloads/f921-page-002.jpg";
    
    //string filename="/users/aminnaar/Downloads/f921a-page-001.jpg";
    
    //string filename="/users/aminnaar/Downloads/f921p-page-002.jpg";
    
    string filename="/users/aminnaar/Downloads/f952-page-001.jpg";






    
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
    
    imshow("gray", gray);
    
    waitKey();
    
    Mat bw;
    adaptiveThreshold(~gray, bw, 255,CV_ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15,-2);
    
    imshow("binary", bw);
    
    waitKey();
    
    Mat horizontal = bw.clone();
    Mat vertical =bw.clone();
    
    int scale = 85;
    
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
    
    
    /*
    Mat joints;
    bitwise_and(horizontal, vertical, joints);
    imshow("joints", joints);
    
    waitKey();
    
    // Find external contours from the mask, which most probably will belong to tables or to images
    vector<Vec4i> hierarchy;
    std::vector<std::vector<cv::Point> > contours;
    cv::findContours(mask, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
    
    vector<vector<Point> > contours_poly( contours.size() );
    vector<Rect> boundRect( contours.size() );
    vector<Mat> rois;
    
    for (size_t i = 0; i < contours.size(); i++)
    {
        // find the area of each contour
        //double area = contourArea(contours[i]);
        
        //        // filter individual lines of blobs that might exist and they do not represent a table
        //if(area < 100) // value is randomly chosen, you will need to find that by yourself with trial and error procedure
          //  continue;
        
        approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
        boundRect[i] = boundingRect( Mat(contours_poly[i]) );
        
        
        cout<<hierarchy[i]<<endl;
        
        // find the number of joints that each table has
       // Mat roi = joints(boundRect[i]);
        
        //vector<vector<Point> > joints_contours;
        //findContours(roi, joints_contours, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
        
        // if the number is not more than 5 then most likely it not a table
        //if(joints_contours.size() <= 4)
        //  continue;
        
        rois.push_back(rsz(boundRect[i]).clone());
        
        //        drawContours( rsz, contours, i, Scalar(0, 0, 255), CV_FILLED, 8, vector<Vec4i>(), 0, Point() );
        rectangle( rsz, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 1, 8, 0 );
    }
    
    
    */
    
    
    
    
    
    
    

    
    
    
    vector<Vec4i> hierarchy;
    vector<vector<Point> > contours;

     //findContours(horizontal, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
    findContours(mask, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
    
    vector<vector<Point> > contours_poly( contours.size() );
    vector<Rect> boundRect( contours.size() );
    vector<Mat> rois;

    cout<<contours.size()<<endl;
    
    for (size_t i = 0; i < contours.size(); i++)
    {
        
        approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
        
        Rect r = boundingRect( Mat(contours_poly[i]) );
        boundRect[i] =r;
        
        
        int numBlack=countNonZero(bw(r));
       
        Rect upperRect = boundRect[i];
        upperRect.y -= 2;  // you can change this value if needed on other images
        int nonzeropixels = countNonZero( bw( upperRect ) );
        double blackPct =numBlack*1.0/r.area();
        int hasChild = hierarchy[i][3];
        
        
        //cout<<"Non-zero pixels above line: "<<nonzeropixels<<endl;
        
        //if( nonzeropixels < 10) // // you can change this value if needed on other images
        if(r.height < 4 && r.width>20 && r.width<650 && nonzeropixels < 10){
            cout<<"NEW LINE FF"<<endl;
            cout<< "width: "<<r.width<<endl;
            cout<< "height: "<<r.height<<endl;
            cout<<"black pct: "<<nonzeropixels<<endl;
            rectangle( rsz, boundRect[i].tl(), boundRect[i].br(),Scalar(0, 255, 0), 1, 8, 0 );
        }
        else if (abs(r.width - r.height) < 5 && r.width <30 && blackPct < 0.32){
            cout<<"NEW CHECKBOX"<<endl;
            cout<< "width: "<<r.width<<endl;
            cout<< "height: "<<r.height<<endl;
            cout<<"nonzero pixels in box: "<< nonzeropixels<<endl;
            cout<<"box area: "<<r.area()<<endl;
            cout<<"black pct: "<<nonzeropixels*1.0/r.area()<<endl;
            cout<<"nonzero pct: "<<numBlack*1.0/r.area()<<endl;
            rectangle( rsz, boundRect[i].tl(), boundRect[i].br(),Scalar(0, 0, 255), 1, 8, 0 );

        }
        
        else if(r.height>10 && r.width>50 && hasChild!= -1 && blackPct< 0.3){
            cout<<"NEW GENERAL BOX"<<endl;
            cout<<"hierarchy: "<<hierarchy[i]<<endl;
            cout<< "width: "<<r.width<<endl;
            cout<< "height: "<<r.height<<endl;
            cout<<"black pct: "<<blackPct<<endl;
            cout<<"haschild: "<<hasChild<<endl;
            rectangle( rsz, boundRect[i].tl(), boundRect[i].br(),Scalar(255, 0, 0), 1, 8, 0 );

            
        }
     
        
        rois.push_back(rsz(upperRect).clone());
        
        
    }
    
    
    
   // for(size_t i = 0; i < rois.size(); ++i)
    //{
        /* Now you can do whatever post process you want
         * with the data within the rectangles/tables. */
      //  imshow("roi", rois[i]);
       // waitKey();
    //}
    
   // imshow("horizontalOnOriginal", horizontalOnOriginal);
    
   // waitKey();
    imshow("contours", rsz);

 waitKey();
    
    imwrite("/Users/aminnaar/Desktop/file-page3.jpg", rsz);

    
    return 0;
}
