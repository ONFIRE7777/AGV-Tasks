#include <iostream>
#include <bits/stdc++.h>
#include <eigen3/Eigen/Dense>
#include <vector>


using namespace std;
using namespace Eigen;
using Eigen::MatrixXd;

	  
int main()
{


    FILE *fptr;
    char filename[]="myfile1.txt";
    fptr=fopen(filename,"r");
    if(fptr==NULL)
    {
      printf("Unable to load the file\n");
    }
   
    int i;
     
    vector<float> posx;
    vector<float> posy;
    float tempx,tempy;

    while(1)
    {
        if(fscanf(fptr, "%4f", &tempx)==EOF)break;
	fscanf(fptr, "%4f", &tempy);
	posx.push_back(tempx);
	posy.push_back(tempy);
    }
    int count=posx.size();
    for (i = 0; i <count; i++)
    {
      printf("Number is: %4f %4f\n",posx[i],posy[i]);
    }
   
   
 
    
    float time;
 
    printf("Enter the time interval between the observations recorded\n");
    scanf("%f",&time);
    
    vector<float> velx;
    vector<float> vely;
    velx.push_back(posx[0]-4/time);
    vely.push_back(posy[0]/time);
  
   
    for(i=1;i<count;++i)
    {

     
       tempx=(posx[i]-posx[i-1])/time;tempy=(posy[i]-posy[i-1])/time;
       velx.push_back(tempx);
       vely.push_back(tempy);
    }
    for(i=0;i<count;i++)
    {
      printf("%f %f %f %f\n",posx[i],posy[i],velx[i],vely[i]);
    }
      
    
    printf("I have taken arbitrarily the position as (4,0) as initial position\n");
    MatrixXd A(2,2);
    A<<1,0,
       0,1;
    MatrixXd H(2,2);
    H<<1,0,0,1;
    MatrixXd X(2,1);
    X<<4,0;
    MatrixXd P(2,2);
    MatrixXd Xpredicted(2,2);
    MatrixXd Ppredicted(2,2);
    MatrixXd Xmeasured(2,1);
    MatrixXd Y(2,1);
    MatrixXd KalmanGain(2,2);
    MatrixXd Rmeaserr(2,2);
    MatrixXd U(2,1);
    MatrixXd B(2,2);
    B<<time,0,0,time;
    Rmeaserr<<.1,0,0,.1;
   
    vector<float> calculatedx;
    vector<float> calculatedy;
    P<<1000,0,0,1000;
    for(i=0;i<count;++i)
    {
       
        U<<velx[i],vely[i];
        Xpredicted=A*X+B*U;
	Ppredicted=A*P*(A.transpose());
	KalmanGain=Ppredicted*((Ppredicted+Rmeaserr).inverse());
	Y<<posx[i],posy[i];
	X=Xpredicted+KalmanGain*(Y-Xpredicted);
	float p=X(0,0);
	float q=X(1,0);
	calculatedx.push_back(p);
	calculatedy.push_back(q);
	P=(H-KalmanGain)*Ppredicted;
	cout<<"COVARIANCE MATRIX IS:"<<endl<<P<<endl;
    }
    
    cout<<"velocity in x is="<<(calculatedx[count-1]-calculatedx[count-2])/time<<endl;
    cout<<"velocity in y is="<<(calculatedy[count-1]-calculatedy[count-2])/time<<endl;
    return 0;
}
	
	 
	     
        











   
