#include <iostream>
#include <bits/stdc++.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <list>


using namespace cv;
using namespace std;



struct Q{
           Mat img;
           Mat vis;
	 
};

struct Element{

                    int i,j,theta;
                    float dist;
                    list <struct Element> :: iterator Parent;
              };



struct PNT{
  int i,j;
};
int Isvalid(int i, int j,Mat sample)
                      {

			if (i<0||j<0||i>=sample.rows||j>=sample.cols)
		             return 0;
	                     else return 1;
                      }

class PathPlanner
{


            private:

                      struct Element start,end;
                      Mat sample,covered,finalpath,showoff;
                      list <struct Element> open,closed;
                      vector<struct Q> cspace;

            public:

                      PathPlanner(Mat z,Mat b,struct Element a, struct Element c,vector<struct Q> &A):sample(b),start(a),end(c),showoff(z),cspace(A)
                      {Getpath(); }

                      void Getpath()
                      {

			  int p,q,r,k,m,t;
			  covered=sample.clone();
			  finalpath=sample.clone();
		          open.push_back(start);
			  while(open.empty()!=1)
			  {
                               
			      list <struct Element> :: iterator u;
			      u=findmin();
                              cspace[u->theta/30].vis.at<Vec3b>(u->i,u->j)[0]=45;cspace[u->theta/30].vis.at<Vec3b>(u->i,u->j)[1]=90;cspace[u->theta/30].vis.at<Vec3b>(u->i,u->j)[2]=200;
			      
			      
			      struct Element a=*u;
			      printf("a.theta=%d\n",a.theta);
			      // waitKey(10);
			      
			     
			    
			      
			      closed.push_back(a);
			    
			      open.erase(u);
			      for(t=a.theta-30;t<=a.theta+30;t=t+30)
			      {
				  for(k=a.i-1;k<=a.i+1;k++)
				  {

				      for(m=a.j-1;m<=a.j+1;m++)
				      {

				      
					  if(Isvalid(k,m,t)==1)
					  {
					      if(cspace[t/30].vis.at<Vec3b>(k,m)[0]*cspace[t/30].vis.at<Vec3b>(k,m)[1]*cspace[t/30].vis.at<Vec3b>(k,m)[2]==pow(125,3))
					      {
						  p=cspace[t/30].img.at<Vec3b>(k,m)[0];q=cspace[t/30].img.at<Vec3b>(k,m)[1];r=cspace[t/30].img.at<Vec3b>(k,m)[2];
						  if(p*q*r==0)
						  {
						    
						    
						      if(k==end.i&&m==end.j)
						      {
							cout<<"foundout"<<endl;
							show();
							return;
						      }   
						    
						      struct Element v;
						    
						      list <struct Element> :: iterator y;
						      y=closed.end();
						      --y;
						  
						      v.i=k;v.j=m;v.Parent=y;v.theta=t;
						      v.dist=u->dist+sqrt(pow(end.i-k,2)+pow(end.j-m,2));
						      printf("v.i=%d,v.j=%d,v.theta=%d,v.dist=%f\n",v.i,v.j,v.theta,v.dist);
						    
					 

						      if(check(v)==0)
						      {

							open.push_back(v);

						      }
					  
					  

						  }   

					      }


					  }

				      }

				  }	  
					 

			      }

			  }
		      }
                    		   
		      
                      int Isvalid(int i, int j,int t)
                      {

			if (i<0||j<0||i>=sample.rows||j>=sample.cols||t<0||t>179)
		             return 0;
	                     else return 1;
                      }
                      void show()
                      {

			   list <struct Element> :: iterator Y;
                           Y=closed.end();
                           --Y;
 
                           int i,j,p;
                           while(Y!=closed.begin())
                           {

			     Mat Time=showoff.clone();
                             Mat src2(9,19,CV_8UC3,Scalar(255));
	  
	                     double angle2 =Y->theta;

	  
			     cv::Point2f center2(src2.cols/2.0, src2.rows/2.0);
			     cv::Mat rot2 = cv::getRotationMatrix2D(center2, angle2, 1.0);
	
			     cv::Rect bbox2 = cv::RotatedRect(center2,src2.size(), angle2).boundingRect();

			     rot2.at<double>(0,2) += bbox2.width/2.0 - center2.x;
			     rot2.at<double>(1,2) += bbox2.height/2.0 - center2.y;

			     cv::Mat dst2;
			     cv::warpAffine(src2, dst2, rot2, bbox2.size());
			     Mat dst3=dst2.clone();
			     cvtColor(dst2,dst3, CV_BGR2GRAY);
	 
			     for(i=0;i<dst3.rows;++i)//Making this image a binary one
			       {
				 for(j=0;j<dst3.cols;++j)
				   {
				     if(dst3.at<uchar>(i,j)>0)
				       dst3.at<uchar>(i,j)=255;
				     else dst3.at<uchar>(i,j)=0;
				   }
			       }
			     dst2=dst3.clone();

        


			     for(j=Y->i-(int)(dst2.rows/2);j<=Y->i+(dst2.rows/2);j++)
			       {
				 
				 for(p=Y->j-(int)(dst2.cols/2);p<=Y->j+(dst2.cols/2);p++)
				   {

				     if(Isvalid(j,p,Y->theta)==1)
				       {	

					 if(dst2.at<uchar>((int)(dst2.rows/2)-Y->i+j,(int)(dst2.rows/2)-Y->j+p)==255)
					   {
					     
					     Time.at<Vec3b>(j,p)[0]=255;
					     Time.at<Vec3b>(j,p)[1]=255;
					     Time.at<Vec3b>(j,p)[2]=0;
					   }
				       }
				   }
			       }
			     imshow("Time",Time);
			     waitKey(100);
			     Y=Y->Parent;
			     
			     
			     
  

			   }

	        
	              }
                      int check(struct Element G)
                      {

			  list <struct Element> :: iterator z;
			  z=open.begin();

			  int count=open.size();
			  while(count--&&z!=open.end())
			  {

			     if(z->i==G.i&&z->j==G.j&&z->theta==G.theta)
			     {

			         if(z->dist>G.dist)
			         {
				   open.erase(z);
				   return(0);
			         }
				 else return(1);
			     }
			     ++z;

			  }
	        
			  return(0);
			 
	              }
		     
                      list<struct Element>::iterator findmin()
                      {


			  list <struct Element> :: iterator t,z=open.begin();
			  t=z;
			  int count=open.size();
			  while(count--)
			  {

			    if((z->dist)<(t->dist)){t=z;}
			    ++z;

			  }
			  return(t);
	              }
                        
    
  
			  
                      
		             
  

};

int main()
{




     int i,j,p,t;
    

    Mat a = imread("a.png", 1);//Reading the colorful image
    Mat draw=a.clone();
  
      for(i=0;i<a.rows;i++)
      {

	  for(j=0;j<a.cols;j++)
	  {


	       if(a.at<Vec3b>(i,j)[0]*a.at<Vec3b>(i,j)[1]*a.at<Vec3b>(i,j)[2]!=pow(255,3))
	       {

		 a.at<Vec3b>(i,j)[0]=0;a.at<Vec3b>(i,j)[1]=0;a.at<Vec3b>(i,j)[2]=0;
	       }
	  }
      }
        
 
    Mat gray;
  
    cvtColor(a, gray, CV_BGR2GRAY);
    Mat jack=gray.clone();
    for(i=0;i<gray.rows;++i)//Making this image a binary one
    {
      for(j=0;j<gray.cols;++j)
       {
	 if(gray.at<uchar>(i,j)>=150)
	 gray.at<uchar>(i,j)=255;
	 else gray.at<uchar>(i,j)=0;
       }
    }
    Mat dest=gray.clone();
    GaussianBlur(gray,dest,Size(3,3),1.5,1.5);
    Canny(dest,gray,25,95);
    vector<struct PNT> K;
    struct PNT temp;
    for(i=0;i<gray.rows;++i)//Making this image a binary one
    {
      for(j=0;j<gray.cols;++j)
       {
	 if(gray.at<uchar>(i,j)==255)
	 {
	   temp.i=i;
	   temp.j=j;
	   K.push_back(temp);
	 }  
       }
    }
    Mat y=a.clone();
    for(i=0;i<a.rows;i++)
    {


        for(j=0;j<a.cols;j++)
	{
	  y.at<Vec3b>(i,j)[0]=125;
	  y.at<Vec3b>(i,j)[1]=125;
	  y.at<Vec3b>(i,j)[2]=125;
	}
    }
        
    vector<struct Q> R;
    for(i=0;i<180;i=i+30)
    {
       struct Q temp;
       temp.img=a.clone();
       
       temp.vis=y.clone();
       R.push_back(temp);
    }   
       
    for(t=0;t<180;t=t+30)
    {
          Mat src(9,19,CV_8UC1,Scalar(255));
	  double angle =t;

	  
	  cv::Point2f center(src.cols/2.0, src.rows/2.0);
	  cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1.0);
	
	  cv::Rect bbox = cv::RotatedRect(center,src.size(), angle).boundingRect();

	  rot.at<double>(0,2) += bbox.width/2.0 - center.x;
	  rot.at<double>(1,2) += bbox.height/2.0 - center.y;

	  cv::Mat dst;
	  cv::warpAffine(src, dst, rot, bbox.size());
         for(i=0;i<K.size();++i)
	 {


	     for(j=K[i].i-(dst.rows/2);j<=K[i].i+(dst.rows/2);j++)
	     {

	         for(p=K[i].j-(dst.cols/2);p<=K[i].j+(dst.cols/2);p++)
		 {

		     if(dst.at<uchar>((int)(dst.rows/2)-K[i].i+j,(int)(dst.rows/2)-K[i].j+p)==255)
		     {	
		       R[t/30].img.at<Vec3b>(j,p)[0]=255;
		       R[t/30].img.at<Vec3b>(j,p)[1]=255;
		       R[t/30].img.at<Vec3b>(j,p)[2]=255;
		     }
		 }
	     }
	 }

    }
  struct Element start,end;
  start.i=385;start.j=19;start.dist=0.0;start.theta=0;
  end.i=18;end.j=369;
  
  PathPlanner b(draw,a,start,end,R);
  

  return(0);

}
