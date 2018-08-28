#include "opencv\cv.h"
#include "opencv\highgui.h"
#include "direct.h"
#include "fstream"
 #include <iostream>
#include <iomanip>
using namespace cv;
using namespace std;
int test8(int argc, char *argv[])
{

	/*string inputPos=argv[1];
	string outputRatio=argv[2];
	string outputDraw=argv[3];*/

	//  txt里面一行是图片和坐标
	   string inputPos="G:/F/MTCNN/mtcnn-master2/服务器-车辆样板本/all-tiao-pos.txt";
	string outputRatio="G:/F/MTCNN/mtcnn-master2/服务器-车辆样板本/all-tiao-ratio.txt";
	 string outputDraw="G:/F/MTCNN/mtcnn-master2/服务器-车辆样板本/白天-挑选-draw";
	
	

	mkdir(outputDraw.c_str());

	fstream f_inPos;
	f_inPos.open(inputPos,ios::in);
	if(!f_inPos.is_open())
	{
		cout << "f_inPos文件数据打开错误！"<< endl;
		system("pause");
		return false;
	}
	fstream f_outRatio;
	f_outRatio.open(outputRatio,ios::out);
	if(!f_outRatio.is_open())
	{
		cout << "f_outRatio文件数据打开错误！"<< endl;
		system("pause");
		return false;
	}

	char line[1024];
	
	while(f_inPos.getline(line,sizeof(line)))
	{
		string imgName;
		int x1,x2,y1,y2;
		stringstream str_s(line);
		str_s>>imgName>>x1>>y1>>x2>>y2;
		IplImage* img=cvLoadImage(imgName.c_str());
		if(img==NULL)
		{
           printf("图片不存在!\n");
		   system("pause");
		   continue;
		}
		int pos=imgName.find_last_of('\\');
		int pos2=imgName.find_first_of('.');
		string name1=imgName.substr(pos+1,pos2-pos-1);
		CvPoint pt1,pt2;
		pt1.x=x1;pt1.y=y1;
		pt2.x=x2;pt2.y=y2;
		int width=x2-x1+1;
		int height=y2-y1+1;
		float ratio=width*1.0/height;
		cout<<name1.c_str()<<","<<ratio<<endl;
		f_outRatio<<setprecision(2)<<ratio<<endl;
		
		cvRectangle(img,pt1,pt2,cvScalar(0,0,255),2);
		char file[128];
		sprintf(file,"%s/%s.jpg",outputDraw.c_str(),name1.c_str());
		cout<<"11111"<<endl;
		cout<<file<<endl;
		cvSaveImage(file,img);
		cout<<"2222"<<endl;
		cvReleaseImage(&img);

		/*string imgName;
		int x1,x2,y1,y2;
		stringstream str_s(line);
		str_s>>imgName>>x1>>y1>>x2>>y2;
		Mat img=imread(imgName.c_str());
		if(img.data==NULL)
		{
           printf("图片不存在!\n");
		   system("pause");
		   continue;
		}
		int pos=imgName.find_last_of('\\');
		int pos2=imgName.find_first_of('.');
		string name1=imgName.substr(pos+1,pos2-pos-1);
		CvPoint pt1,pt2;
		pt1.x=x1;pt1.y=y1;
		pt2.x=x2;pt2.y=y2;
		int width=x2-x1+1;
		int height=y2-y1+1;
		float ratio=width*1.0/height;
		cout<<name1.c_str()<<","<<ratio<<endl;
		f_outRatio<<setprecision(2)<<ratio<<endl;
		Rect rt;rt.x=x1;rt.y=y1;rt.width =width;rt.height =height;
		rectangle(img,rt,cvScalar(0,0,255),2);
		char file[128];
		sprintf(file,"%s/%s.jpg",outputDraw.c_str(),name1.c_str());
		imwrite(file,img);*/
	

	}

	f_inPos.close();
	f_outRatio.close();
	return 0;
}