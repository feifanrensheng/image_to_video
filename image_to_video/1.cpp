#include <iostream>
#include <string>
#include <io.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	string fileFolderPath="/home/zn/mav0/cam0/data";
	string fileExtension="png";
	string fileFolder = fileFolderPath + "//*." + fileExtension;

	string outputVideoName="output.avi";

	VideoWriter writer;

	int codec=0;
	int frameRate = 20;
	Size frameSize;

	char fileName[1000];
	struct _finddata_t fileInfo;

	long findResult = _findfirst(fileFolder.c_str(), &fileInfo);
	if (findResult == -1)
	{
		_findclose(findResult);
		return -1;
	}

	do
	{
		sprintf(fileName, "%s//%s", fileFolderPath.c_str(), fileInfo.name);
		if(fileInfo.attrib == _A_ARCH)
		{
			Mat frame;
			
			frame = imread(fileName);
			if (!writer.isOpened())
			{
				frameSize.width  = frame.cols;
				frameSize.height = frame.rows;
				if (!writer.open(outputVideoName, CV_FOURCC('D','I','V','X') , frameRate, frameSize, true))
				{
					cout << "open writer error..." << endl;
					return -1;
				}
			}

			writer.write(frame)
			imshow("video", frame);
			waitKey(frameRate);
		}
	} while (!_findnext(findResult, &fileInfo));  
	_findclose(findResult); 
	return 0;
}