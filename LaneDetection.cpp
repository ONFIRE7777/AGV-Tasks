#include <iostream>
#include <bits/stdc++.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <list>


using namespace cv;
using namespace std;

int main()
{

  Mat a=imread("kitti.png",1);
  int i,j,k,p,q,r;
  Mat b(a.rows,a.cols,CV_8UC3,Scalar(0,0,0));
  for(i=0;i<a.rows;++i)
  {
     for(j=0;j<a.cols;++j)
     {
       r=a.at<Vec3b>(i,j)[0];
       q=a.at<Vec3b>(i,j)[1];
       p=a.at<Vec3b>(i,j)[2];
       if((((p>=225)&&(p<=255))&&((q>=180)&&(q<=255))&&((r>=0)&&(r<=170)))||(((p>=100)&&(p<=255))&&((q>=100)&&(q<=255))&&((r>=200)&&(r<=255))))
       {

	      b.at<Vec3b>(i,j)[0]=r;
	      b.at<Vec3b>(i,j)[1]=q;
	      b.at<Vec3b>(i,j)[2]=p;                
       }
     }


	 
  }
  Mat dest;
  cvtColor(b,dest,CV_BGR2GRAY);
  Canny(dest,b,12,125);
  vector<Vec2f> lines;
  HoughLines(b,lines, 1, CV_PI/180, 100, 0, 0);
  Mat cdst(b.size(),CV_8UC3,Scalar(0,0,0));
  {
      for( size_t i = 0; i < lines.size(); i++ )
      {
    
         float rho = lines[i][0], theta = lines[i][1];
	 Point pt1, pt2;
	 if(abs(tan(theta))>.26794&&abs(tan(theta))<3.732)
	 {
	    double a = cos(theta), b = sin(theta);
	    double x0 = a*rho, y0 = b*rho;
	    pt1.x = cvRound(x0 + 1000*(-b));
	    pt1.y = cvRound(y0 + 1000*(a));
	    pt2.x = cvRound(x0 - 1000*(-b));
	    pt2.y = cvRound(y0 - 1000*(a));
	    line(cdst, pt1, pt2, Scalar(0,0,255), 3, CV_AA);
	 }

      }
  }
  //float A[4]={.05,.2,.3,.45};
  //vector<Mat> A;
  //vector<vector<Vec2f> > Z;
  
  //for(i=0;i<4;++i)
  //{

    // Mat temp(A[i]*b.rows,b.cols,CV_8UC1,Scalar(0));
    //for(j=0;j<b.cols;++j)
    //  {

	//    for(k=0;k<A[i]*b.rows;k++)
  //    {
	    //  temp.at<Vec3b>(j,k)[0]=b.at<Vec3b>(j,k)
	     
      
	  
  
  imshow("canny",cdst);
  waitKey(0);

  
}
  
