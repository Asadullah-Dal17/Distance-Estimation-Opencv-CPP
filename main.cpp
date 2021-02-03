#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include <cmath>

using namespace cv;
using namespace std;

float FocalLengthFinder(float Measured_Distance, float Real_Width, float Width_In_Image) {

    float Focal_length = (Measured_Distance * Width_In_Image) / Real_Width;
    return Focal_length;
}

// finding distance
float Distance_Finder(float  Real_width, float Focal_Length, float Width_in_Image) {
    float distance = (Real_width * Focal_Length) / Width_in_Image;
    return distance;
}
// variables for face rectangle 
int cord_x, cord_y, cord_w, cord_height;

int main(int, char**)

{
    //defining face detector uisng haarcasecde opencv
    //distance calculation data
    int face_width;// it will be width of 

    float focal_length;
    float orginal_distnace = 30.1;// Inches
    float Real_face_width = 14.3; //inches
    float face_width_in_image ;
    float distance;
    // int Distnace_R ;

    //===========
    //face detector object
    CascadeClassifier FaceDectector;
   // Variables 
    double scale_factor;
    int NNB;
   // Mat objects for images 
    Mat frame;
    Mat Gray;
    Mat G_Blur;

    //define the path of xml file
    string Xml_path = "C:/Users/Asadullah/Documents/Projects/CplusPlusDistanceEstimation/haarcascade_frontalface_default.xml";
    if (!FaceDectector.load(Xml_path))
    {
        cout << "erro loading file xml face detector";
        return -1;

    }
    else {
        cout << "HarrCascade xml  file is Loaded";
    }
    Mat Reference_image;
    //reading the reference image from directory
    Reference_image = imread("C:/Users/Asadullah/Documents/Projects/CplusPlusDistanceEstimation/reference_image.png", IMREAD_GRAYSCALE);
    //std::vector<Rect> faces;
    std::vector<Rect> R_face;

    FaceDectector.detectMultiScale(Reference_image, R_face, 1.3);
 
    cout << "before---------------------";
    for (size_t j = 0; j < R_face.size(); j++) {
        cout << "reading===========";
        cout << R_face[j].x;
        Rect bbox = Rect(R_face[j].x, R_face[j].y, R_face[j].width, R_face[j].height);
        rectangle(Reference_image,bbox, Scalar(0, 255, 255), 2, 8, 0);
        face_width_in_image = R_face[j].width;
        

    }
    imshow("reference", Reference_image);
 
    focal_length = FocalLengthFinder(orginal_distnace, Real_face_width, face_width_in_image);

       //--- INITIALIZE VIDEOCAPTURE
    VideoCapture cap;
    // open the default camera using default API
    // cap.open(0);
    // OR advance usage: select any API backend
    int deviceID = 2;             // 0 = open default camera
    int apiID = cv::CAP_ANY;      // 0 = autodetect default API
    // open selected camera using selected API
    cap.open(deviceID, apiID);
    // check if we succeeded
    if (!cap.isOpened()) {
        cerr << "ERROR! Unable to open camera\n";
        return -1;
    }
    //--- GRAB AND WRITE LOOP
    cout << "Start grabbing" << endl
        << "Press any key to terminate" << endl;
    for (;;)
    {
        // wait for a new frame from camera and store it into 'frame'
        cap.read(frame);
        // check if we succeeded
        if (frame.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        scale_factor = 1.3;
        NNB = 10;
        int flags = 3;
        // converting the color to gray 
        cvtColor(frame, Gray, COLOR_BGR2GRAY);
        
        // equalizeHist(Gray, Gray);
        // storing the face points in the vector
        vector<Rect> faces;
        FaceDectector.detectMultiScale(Gray, faces,scale_factor);
        for (size_t i = 0; i < faces.size(); i++) {
            //Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
            //ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 4);
          //  Mat faceReginOf_intereset = Gray(faces[i]);
            cord_x = faces[i].x; cord_y = faces[i].y; cord_w = faces[i].width; cord_height = faces[i].height;
            //cout << cord_x, cord_y, cord_w, cord_height;
            Rect rec = Rect(faces[i].x, faces[i].y, faces[i].width,faces[i].height);
		    rectangle(frame, rec, Scalar(0, 255, 255), 2, 8, 0);
            distance = Distance_Finder(Real_face_width, focal_length, cord_w);
            // cout << "  ";
            // cout << distance, "  ";
            // Distnace_R = round(distance);
            // cout<<"Distnace = ", Distnace_R<<endl; 
            string s_distance= to_string(distance);
            

            // drwaing the  text on the Screen
            cv::putText(frame, "Distance= "+s_distance+" Inches", cv::Point(50, 50), cv::FONT_HERSHEY_DUPLEX, 0.7, cv::Scalar(255, 0, 255), 2, false);
            // cout << "   ";
            //cout << focal_length;
        
        }

        //GaussianBlur(Gray, G_Blur, Size(3, 3), 0);
        // show live and wait for a key with timeout long enough to show images
        imshow("Gray", Gray);
        imshow("Live", frame);
        if (waitKey(1) >= 0)
            break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}// finding focal length,
