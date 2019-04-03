#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cv.h>
#include <highgui.h>
#include <boost/filesystem.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;




int main(int argc, char** argv)
{
	int frameRate = 20;
	string outputVideoName="output_v.avi";
	Size frameSize(752,480);
	std::string path = "/home/zn/V1_01_easy/mav0";
	std::vector<std::string> image_names;
	std::string folder(path + "/cam0/data"  );
	for (auto it = boost::filesystem::directory_iterator(folder); it != boost::filesystem::directory_iterator(); it++)
	{
		//if( !boost::filesystem::directory_iterator(it->path()))
		//{
			image_names.push_back(it->path().filename().string());
		//}
		//else {
		//	continue;
		//}
	}
	std::sort(image_names.begin(), image_names.end());

	cv::VideoWriter writer;
	writer.open(outputVideoName, CV_FOURCC('M','J','P','G'), frameRate, frameSize, true);
	cout<< image_names[1000]<<endl;
	for(int i = 1000; i < 1100; i++)
	{
		cv::Mat frame = cv::imread(path + "/cam0/data/" + image_names[i]);
		writer.write(frame);
		imshow("video", frame);
		waitKey(frameRate);
	}
	return 0;
}