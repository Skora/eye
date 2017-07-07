#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/videoio/videoio.hpp"
#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat, Scalar)
#include "opencv2/objdetect/objdetect.hpp"
#include <string>
#include <iostream>



using namespace cv;
using namespace std;

string face_cascade_name = "cascades/haarcascade_frontalface_alt.xml";    //Nazwa kaskady którą wykorzystujemy do rozpoznania twarzy
string eyes_cascade_name = "cascades/haarcascade_eye_tree_eyeglasses.xml";    //Nazwa kaskady którą wykorzystujemy do rozpoznania oczu
string mouth_cascade_name = "cascades/haarcascade_mcs_mouth.xml";            //Nazwa kaskady wykorzystywanej przy rozpoznawaniu ust
string nose_cascade_name = "cascades/haarcascade_mcs_nose.xml";
string body_cascade_name = "cascades/haarcascade_fullbody.xml";
CascadeClassifier face_cascade;                                //Utworzenie obiektu cascady twarzy
CascadeClassifier eyes_cascade;                                //Utworzenie obiektu cascady oczu
CascadeClassifier mouth_cascade;                            //Utworzenie obiektu cascady ust
CascadeClassifier nose_cascade;                                //Utworzenie obiektu cascady nosa
CascadeClassifier body_cascade;
string window_name = "Hello Face !";

RNG rng(12345);

void detectFace( Mat img );
vector<Point> detect(Mat img, CascadeClassifier cascade);
void draw ( Mat img);

int main( int argc, char** argv )
{
    Mat img, frame;                                            //Utworzenie nowej macierzy na nasz obrazek
    VideoCapture capture = VideoCapture(0);


	if( !face_cascade.load( face_cascade_name ) )        //Ładowanie pliku ze sprawdzeniem poprawnoci
	{
		cout << "Nie znaleziono pliku " << face_cascade_name << ".";
		return -2;
	}
	if( !eyes_cascade.load(eyes_cascade_name) )        //Ładowanie pliku ze sprawdzeniem poprawnoci
	{
		cout << "Nie znaleziono pliku " << eyes_cascade_name << ".";
		return -2;
	}
	if( !mouth_cascade.load(mouth_cascade_name) )        //Ładowanie pliku ze sprawdzeniem poprawnoci
	{
		cout << "Nie znaleziono pliku " << mouth_cascade_name << ".";
		return -2;
	}
	if( !nose_cascade.load(nose_cascade_name) )        //Ładowanie pliku ze sprawdzeniem poprawnoci
	{
		cout << "Nie znaleziono pliku " << nose_cascade_name << ".";
		return -2;
	}

	namedWindow(window_name, CV_WINDOW_AUTOSIZE);    //Utworzenie okna (nazwa okna, ustalenie rozmiaru)
	vector<Point> center;
    while ( waitKey(20) != 27 )
     {
        capture >> frame;
        center = detect(frame, face_cascade);
        if ( center.size() > 0)
        {
        	cout << center  << " \n";
        }


        //Show img for debug
		for (unsigned int i = 0; i < center.size(); i++)
		{
			circle(frame, center[i], 2, Scalar( 120, 5, 86 ), 2, 2, 0 );
		}
		if (!(frame.empty()))
		{
			draw(frame);
		}


     }
    waitKey(0);                                            //Odczekanie na wcinięce klawisza z opóxnieniem 0ms
    return 0;
}

void draw ( Mat img)
{
	imshow(window_name, img);                        //Pokazanie obrazka w onkie o nazwie "Hello Face !"

}
vector<Point> detect(Mat img, CascadeClassifier cascade)
{
    vector<Rect> objects;                            //Utworzenie bufora na twarze
    Mat img_gray;                                //Utworzenie bufora na obrazek w odcieniach szarosci
    vector<Point> center;
    Point centPnt;


    cvtColor(img, img_gray,  CV_BGR2GRAY );                //Konwersja obrazu do odcieni szarosci
    //equalizeHist(img_gray, img_gray);                    //Zaaplikowanie do obrazu jego historogramu, poprawa kontrastu

    cascade.detectMultiScale(img_gray, objects, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(50, 50) );
    for( unsigned i = 0; i < objects.size(); i++ )
    {
    	centPnt.x = objects[i].x + objects[i].width/2;
    	centPnt.y = objects[i].y + objects[i].height/2;
    	center.push_back(centPnt);
    }

    return center;
}

void detectFace( Mat img )
{
    vector<Rect> faces;                            //Utworzenie bufora na twarze
    Mat img_gray;                                //Utworzenie bufora na obrazek w odcieniach szarosci
    Mat img_face;
    Mat img_bottom_face;
    int center[2];
    cvtColor(img, img_gray,  CV_BGR2GRAY );                //Konwersja obrazu do odcieni szarosci
    //equalizeHist(img_gray, img_gray);                    //Zaaplikowanie do obrazu jego historogramu, poprawa kontrastu

    face_cascade.detectMultiScale(img_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(50, 50) );
    for( unsigned i = 0; i < faces.size(); i++ )
    {
    	center[0] = faces[i].x + faces[i].width/2;
    	center[1] = faces[i].y - faces[i].height/2;
    	cout << center[0] << " " << center[1] << " \n";
        Rect rect_face( faces[i] );    //Kwadrat okreslający twarz
        //ellipse( img, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 120, 12 ), 2, 2, 0 );
        rectangle(img, rect_face, Scalar( 120, 5, 86 ), 2, 2, 0  );
        img_face = img_gray( faces[i] );
        vector<Rect> eyes;
        vector<Rect> mouth;
        vector<Rect> nose;

        eyes_cascade.detectMultiScale(img_face, eyes, 1.1, 2,  0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );

        for( unsigned j = 0; j < eyes.size(); j++ )
        {
            cv::Rect rect_eye( faces[i].x + eyes[j].x, faces[i].y + eyes[j].y,
                    eyes[j].width, eyes[j].height );
            rectangle(img, rect_eye, Scalar( 0, 120, 12 ), 2, 2, 0  );
        }
        Rect rect_bottom_face( 0, faces[i].height / 2, faces[i].width, faces[i].height/2);
        //rectangle(img_face, rect_bottom_face, Scalar( 125, 120, 12 ), 2, 2, 0);
        img_bottom_face = img_face( rect_bottom_face );
        mouth_cascade.detectMultiScale(img_bottom_face, mouth, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(40, 40));
        for( unsigned j = 0; j < mouth.size(); j++ )
        {
            Rect rect_mouth( faces[i].x + mouth[j].x, faces[i].y + faces[i].height/2 + mouth[j].y, mouth[j].width, mouth[j].height );
            rectangle(img, rect_mouth, Scalar( 56, 23, 129 ), 2, 2, 0  );
        }
        nose_cascade.detectMultiScale( img_bottom_face, nose, 1.1, 2,  0 |CV_HAAR_SCALE_IMAGE, Size(40, 40) );
        for( unsigned j = 0; j < nose.size(); j++ )
        {
            Rect rect_nose( faces[i].x + nose[j].x, faces[i].y + faces[i].height/2 + nose[j].y, nose[j].width, nose[j].height );
            rectangle(img, rect_nose, Scalar( 100, 100, 129 ), 2, 2, 0  );
        }
    }
    imshow(window_name, img);                        //Pokazanie obrazka w onkie o nazwie "Hello Face !"
}
