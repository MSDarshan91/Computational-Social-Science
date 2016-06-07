#include <iostream>
#include <random>
#include<stdlib.h>
#include<math.h>
int main()
{
  const int nrolls=10000;  // number of experiments
  const int nstars=1000;    // maximum number of stars to distribute

  std::default_random_engine generator;
  std::normal_distribution<double> distribution(25.0,13.0);
  int l = 50;
  int p[50]={};
  int q[80][80] = {{}}; 
  for (int i=0; i<nrolls; ++i) {
    double number = distribution(generator);
    if ((number>=0.0)&&(number<50.0)) ++p[int(number)];
  }

 // std::cout << "normal_distribution (5.0,2.0):" << std::endl;
  int max = 0.0;
  for (int i =0;i<l;i++)
     for(int j=0;j<l;j++)
	{
	q[i][j] = (p[i]*nstars/nrolls) * (p[j]*nstars/nrolls);
	if(q[i][j] >max)
	   max = q[i][j];
	}
  int temp = floor(max/4.2);
  for (int i=0; i<80; ++i) 
  {
	for (int j=0;j<80;j++)
		{
		if(i>35 && j>35)
			 std::cout<<floor(q[i][j]/temp)+floor(q[i-30][j-30]/temp)<<" ";
		else std::cout<<floor(q[i][j]/temp)<<" ";
		}
	std::cout<<"\n";
  }		
  return 0;
}

