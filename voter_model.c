/*Author: Darshan M.S. */
#include<stdio.h>
#include <stdlib.h>
#include <math.h>
int sites[40][40];

double rand_2()
{
    return (double)rand() / (double)RAND_MAX ;
}

int updateSite(x,y)
{
	int n = rand() % 4;
	if( (n ==0) && ((x-1) > 0))
		return sites[x-1][y];
	else if((n ==1) && ((x + 1) < 40))
		return sites[x+1][y];
	else if((n ==2) && ((y -1) > 0))
                return sites[x][y-1];
        else if((n == 3) && ((y + 1) < 40))
                return sites[x][y+1];
	else
		return sites[x][y];
}
int totalSum()
{
	int s = 0,i,j;
        for(i =0;i<40;i++)
		for (j=0;j<40;j++)
                        s += sites[i][j];
	return s;
}
int main(void)
{
	float probs[] = {0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9};
	float r,p;
	int ups = 0;
	int pr,x,y,s,i,j,iter;
	for (pr = 0;pr<9;pr++)
	{
		p = probs[pr];
		printf("Probability - %0.1f\n",p);
		ups = 0;
		for(iter = 0;iter<100;iter++)
		{

			for (i = 0;i<40;i++)
				for (j=0;j<40;j++)
				{
					r = rand_2();
					if(r < p)
						sites[i][j] = 1;
					else
						sites[i][j] = -1;
				}
			while(1)
			{		
				x = rand() % 40;
				y = rand() % 40;        	
				sites[x][y] = updateSite(x,y);
				s = totalSum();
				if(s == 1600)
				{
				    ups++;
				    break;		
				}
				if(s== -1600)
				{
				    break;	
				}
			}
		}
		printf("%f   %f\n",p,(ups/100.0));
	}
  return 0;
}
