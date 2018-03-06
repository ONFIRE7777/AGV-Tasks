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
			     Mat showoff1=showoff.clone();
			      for(j=z->i-4;j<=z->i+4;j++)
                              {

				  for(p=z->j-9;p<=z->j+9;p++)
	                          {

	                              
	                            if(Isvalid(j,p)==1){  	
				    showoff1.at<Vec3b>(j,p)[0]=255;
				    showoff1.at<Vec3b>(j,p)[1]=255;
				    showoff1.at<Vec3b>(j,p)[2]=0;}
				       
				  }

			       }
			       //temp.at<Vec3b>(z->i,z->j)[0]=165;temp.at<Vec3b>(z->i,z->j)[1]=98;temp.at<Vec3b>(z->i,z->j)[2]=202;
			      z=z->Parent;
			      imshow("Traversal",showoff1);
			      waitKey(100);
			     
			   }
			   ;
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
  Mat a=imread("a.png",1);


  Mat Image=imread("Configured.png",1);
  struct Element start,end;
  start.i=385;start.j=19;start.dist=0.0;
  end.i=18;end.j=369;
  
  PathPlanner b(a,Image,start,end);
  

  return(0);

}
