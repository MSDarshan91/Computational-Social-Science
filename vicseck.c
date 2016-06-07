#include<stdio.h>
#include<math.h>	
#include<stdlib.h>
int N = 400;
double bird_x[400];
double bird_y[400];
double bird_angle[400];
int L = 5;
double r_i = 1.0;
double prev_x_avg = 0.0;
double prev_y_avg = 0.0;
double nu = 0.1;
float v = 0.03;
float halfL = 2.5;
void update_positions()
{
	int i;
	
	for(i = 0;i<400;i++) 
	{
		//if(i == 0)
			//printf("%d  %f %f %f \n",i,bird_x[i],bird_y[i],bird_angle[i]);
		bird_x[i] = bird_x[i] + (v * cos(bird_angle[i])) ;
		//if(i == 0)
			//printf("At the End %d  %f %f %f \n",i,bird_x[i],bird_y[i],v*cos(bird_angle[i]));
		if(bird_x[i] > 5.0)
			bird_x[i] = 5.0 - bird_x[i];
		if(bird_x[i] < 0.0)
			bird_x[i] = 5.0 + bird_x[i];		
		bird_y[i] = bird_y[i]  + ( v * sin(bird_angle[i])) ;
		if(bird_y[i] > 5.0 )
			bird_y[i] = 5.0 - bird_y[i];
		if(bird_y[i] < 0.0)
			bird_y[i] = 5.0 + bird_y[i];	
			
	}
}

double Randomdouble(double a, double b) 
{
    double random = ((double) rand()) / (double) RAND_MAX;
    double diff = b - a;
    double r = random * diff;
    return a + r;
}


int isInRadius(int b, int b_1)
{
	double x_1 = bird_x[b];
	double y_1 = bird_y[b];
	double x_2 = bird_x[b_1];
	double y_2 = bird_y[b_1];
	double d;
	double x = x_1 - x_2;
	double y = y_1 - y_2;
	while(x>halfL)
		x = x - L;
	while(x< -halfL)
		x = x + L;
	while(y>halfL)
		y = y - L;
	while(y< -halfL)
		y = y + L;
	d = sqrt((x*x) + (y*y));
	if(d < r_i)
		return 1;
	return 0;	
}

double getAverage(int b)
{
	double x = bird_x[b];
	double y = bird_y[b];
	int i,j;
	double sin_t = 0.0,cos_t = 0.0,tan_t;
	int n=0;
	double temp;
	double new_ang,avg_ang;
	for(i = 0;i<400;i++)
	{
		if(isInRadius(b,i))
		{
			sin_t += sin(bird_angle[i]);					
			cos_t += cos(bird_angle[i]);
			//tan_t += (sin_t/cos_t);
			n++;
		}
		
	}
	avg_ang = atan2((sin_t/(float)n), (cos_t/(float)n) );	
	//printf("AVG ANG %f",avg_ang);
	new_ang = avg_ang + Randomdouble(-nu/2 , nu/2);
	//printf("%f %f %f %d\n",bird_angle[b],avg_ang,new_ang,n);
	//printf("%f ",new_ang);
	//if(b == 0)
		//printf("%d %f %f \n",b,avg_ang,new_ang);
	return new_ang;		
}


double avgVelocity()
{
	int i;
	float temp = 0.0,x_t = 0.0,y_t = 0.0;
	for(i = 0;i<400;i++)
	{
		x_t += v*cos(bird_angle[i]);
		y_t += v*sin(bird_angle[i]);
	}
	temp = (x_t*x_t) + (y_t*y_t);
	temp = sqrt(temp);
	temp = temp/ (N*v);
	return(temp);
}

int main(void)
{
	int i,j,k,iter;
	double new_ang,new_x,new_y;
	double new_avg, prev_avg;
	while(nu < (2*3.14))
	{
		for(iter = 0;iter < 5;iter++)
		{
			for(i = 0;i<400;i++)
			{
				bird_x[i] = Randomdouble(0.0,5.0);
				bird_y[i] = Randomdouble(0.0,5.0);
				bird_angle[i] = Randomdouble(0.0,2*3.14);
				//printf("%d %f %f %f \n",i, bird_x[i] ,bird_y[i],bird_angle[i]);
		
			}
			for(j = 0;j<100;j++)
			{
				prev_avg = new_avg;
				for(i = 0;i<400;i++)
				{
					for(k=0;k<400;k++)
					{
						new_ang = getAverage(k);
						bird_angle[k] = new_ang;
						if(bird_angle[k] > 2*3.14)
							bird_angle[k] = bird_angle[k] - 2*3.14;
						if(bird_angle[k] < 0)
							bird_angle[k] = bird_angle[k] + 2*3.14;
						//printf("%d %f %f %f %f \n",k, bird_x[k] ,bird_y[k],bird_angle[k],new_ang);
					}
					update_positions();
					//printf("\n%f %f %f\n",nu, new_avg,fabs(new_avg - prev_avg));
				}
				new_avg = avgVelocity();
				//printf("\n%f %f %f\n",nu, new_avg,fabs(new_avg - prev_avg));
				if( fabs(new_avg - prev_avg) < 0.0001)
				{
					printf("%f %f\n",nu, new_avg);
					break;
				}
			}
		}
		nu= nu+0.1;
	}
	return 0;
}
