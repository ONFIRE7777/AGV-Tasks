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
    

    
    printf("I have taken arbitrarily the position as (4,0) as initial position\n");
    MatrixXd A(4,4);
    A<<1,0,time,0,
       0,1,0,time,
       0,0,1,0,
       0,0,0,1;
    MatrixXd H(2,4);
    H<<1,0,0,0,
       0,1,0,0;
    MatrixXd X(4,1);
    X<<4,0,(posx[0]-4)/time,(posy[0]/time);
    MatrixXd P(4,4);
    MatrixXd Xpredicted(4,1);
    MatrixXd Ppredicted(4,4);
   
    MatrixXd Y(2,1);
    MatrixXd KalmanGain(4,2);
    MatrixXd Rmeaserr(2,2);
 
    
    Rmeaserr<<.1,0,0,.1;

    P<<1000,0,0,0,0,1000,0,0,0,0,1000,0,0,0,0,1000;
    for(i=0;i<count;++i)
    {
       
    
        Xpredicted=A*X;
	Ppredicted=A*P*(A.transpose());
	KalmanGain=(Ppredicted*H.transpose())*((H*Ppredicted*(H.transpose())+Rmeaserr).inverse());
	Y<<posx[i],posy[i];
	X=Xpredicted+KalmanGain*(Y-H*Xpredicted);

	P=Ppredicted-KalmanGain*H*Ppredicted;
	cout<<"X is ="<<X<<endl;
	cout<<"COVARIANCE MATRIX IS:"<<endl<<P<<endl;
    }
    
   
  
    return 0;
}
	
	 
	     
        











