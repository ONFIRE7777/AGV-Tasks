#include <iostream>
#include <bits/stdc++.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <list>


using namespace cv;
using namespace std;

struct Element{

                    int i,j;
                    float dist;
                    list <struct Element> :: iterator Parent;
              };

class PathPlanner
{


            private:

                      struct Element start,end;
                      Mat sample,covered,finalpath,showoff;
                      list <struct Element> open,closed;

            public:

                      PathPlanner(Mat z,Mat b,struct Element a, struct Element c):sample(b),start(a),end(c),showoff(z)
                      {
			 Getpath();
		      }

                      void Getpath()
                      {

			  int p,q,r,k,m;
			  covered=sample.clone();
			  finalpath=sample.clone();
		          open.push_back(start);
			  while(open.empty()!=1)
			  {
                               
			      list <struct Element> :: iterator u;
			      u=findmin();
                              covered.at<Vec3b>(u->i,u->j)[0]=165;covered.at<Vec3b>(u->i,u->j)[1]=98;covered.at<Vec3b>(u->i,u->j)[2]=202;
			     
			      
			      struct Element a=*u;
			      
			     
			    
			      
			      closed.push_back(a);
			    
			      open.erase(u);
			      for(k=a.i-1;k<=a.i+1;k++)
			      {

				  for(m=a.j-1;m<=a.j+1;m++)
				  {

				      p=covered.at<Vec3b>(k,m)[0];q=covered.at<Vec3b>(k,m)[1];r=covered.at<Vec3b>(k,m)[2];
				      if(p*q*r!=255*255*255){
				      if(Isvalid(k,m)==1&&(p*q*r!=165*98*202))
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
					  
					  v.i=k;v.j=m;v.Parent=y;
					  v.dist=u->dist+sqrt(pow(end.i-k,2)+pow(end.j-m,2));
					 

					  if(check(v)==0)
					  {

					    open.push_back(v);

					  }
					  
					  
                                      }}

				  }

			      }	  
					 

			  }

		      }
                      void show()
                      {

			   list <struct Element> :: iterator z;
			   z=closed.end();
			   --z;
			   int j,p;
			  
			  
			   while(z!=closed.begin())
			   {
			     
			   
			            p=z->j;  
			            j=z->i;	
				    showoff.at<Vec3b>(j,p)[0]=255;
				    showoff.at<Vec3b>(j,p)[1]=255;
				    showoff.at<Vec3b>(j,p)[2]=0;
		        
			 
			      z=z->Parent;
			      imshow("Traversal",showoff);
			      waitKey(50);
			     
			   }
			   imshow("Final",showoff);
			   waitKey(0);
	              }		   
		      
                      int Isvalid(int i, int j)
                      {

			if (i<0||j<0||i>=sample.rows||j>=sample.cols)
		             return 0;
	                     else return 1;
                      }
                      int check(struct Element G)
                      {

			  list <struct Element> :: iterator z;
			  z=open.begin();

			  int count=open.size();
			  while(count--)
			  {

			     if(z->i==G.i&&z->j==G.j)
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

  int i,j;
  
  Mat a = imread("a.png", 1);//Reading the colorful image
  Mat Image=a.clone();
  
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



  struct Element start,end;
  start.i=385;start.j=19;start.dist=0.0;
  end.i=18;end.j=369;
  
  PathPlanner b(Image,a,start,end);
  

  return(0);

}
