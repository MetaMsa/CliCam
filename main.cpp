#include <opencv2/opencv.hpp>
#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace cv;
using namespace std;

const string ASCII_CHARS = "@%#*+=-:. ";

void printAsciiArt(const Mat &frame)
{
    system("cls"); 

    for (int y = 0; y < frame.rows; y++)
    { 
        for (int x = 0; x < frame.cols; x++)
        {
            int pixel = frame.at<uchar>(y, x);
            char asciiChar = ASCII_CHARS[pixel * ASCII_CHARS.length() / 256];
            cout << asciiChar;
        }
        cout << endl;
    }
}

int main()
{
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    VideoCapture cap(0);

    if (!cap.isOpened())
    {
        cerr << "Kamera acilamadi!" << endl;
        getchar();
    }

    while (true)
    {
        Mat frame, gray;

        cap >> frame; 
        if (frame.empty())
            break;

        cvtColor(frame, gray, COLOR_BGR2GRAY);                
        resize(gray, gray, Size(80, 40), 0, 0, INTER_LINEAR); 

        printAsciiArt(gray);
    }

    return 0;
}