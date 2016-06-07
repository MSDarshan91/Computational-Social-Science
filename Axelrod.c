#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <map>
#include <iostream>
#include <sstream> // for ostringstream
#include <string>
using namespace std;
int F = 2;
int sites[20][20][2];
int n_sites = 20;
double rand_2()
{
    return (double)rand() / (double)RAND_MAX ;
}

void updateSite(int x,int y,int x_1,int y_1)
{
	int k,c = 0;
	float f,r;
	for(k=0;k<F;k++)
	{
		if(sites[x][y][k] == sites[x_1][y_1][k])
			c++;
	}
	f = c/(float)F;
	r = rand_2();
	//if(x==0 &&  y ==17 && x_1 ==0 && y_1 == 18)
		//printf("\n%d %f %f",c,f,r);
	if(f>0.0 && f<1.0)
		if(r<f)
		{
			//printf("Updated: %d %d %d %d ",x,y,x_1,y_1);
			if(rand()%2 == 0)
			{
				//for (k = 0;k<F;k++)
				k = rand()%F;
				sites[x][y][k] = sites[x_1][y_1][k];
			}
			else
			{
				k = rand()%F;
				for(k=0;k<F;k++)
					sites[x_1][y_1][k] = sites[x][y][k];
			}
		}
}

int allSame(int x, int y)
{
	int k;
        if(((x-1) >= 0))
	   for(k = 0;k<F;k++)
           	if(sites[x][y][k] != sites[x-1][y][k])
		{
			printf("\nS %d %d x - 1 %d %d",x,y,x-1,y);
			return 0;
		}
        if(((x + 1) < 20))
	    for(k = 0;k<F;k++)
		    if(sites[x][y][k] != sites[x+1][y][k])
		    {
        	        printf("\nS %d %d %d %d",x,y,x+1,y);
			return 0;
		    }
        if(((y -1) >= 0))
	    for(k = 0;k<F;k++)
		    if(sites[x][y][k] != sites[x][y-1][k])
		    {
                        printf("\nS %d %d %d %d",x,y,x,y-1);
                        return 0;
                    }
        if(((y + 1) < 20))
	    for(k = 0;k<F;k++)
		    if(sites[x][y][k] != sites[x][y+1][k])
		    {
                        printf("\nS %d %d %d %d",x,y,x,y+1);
                        return 0;
                    }
	return 1;
}

int allDifferent(int x, int y)
{
	int k,c = 0;
        if(((x-1) >= 0))
	{
	   c = 0;
	   for(k = 0;k<F;k++)
	   {
                if(sites[x][y][k] == sites[x-1][y][k])
                        c++;
           }
	   //printf(" c x -1 %d\n",c);
	   if(c>0 && c <F) 
		return 0;
	}
        if(((x + 1) < 20))
	{
	    c=0;
	    for(k = 0;k<F;k++)
	            if(sites[x][y][k] == sites[x+1][y][k])
        	        c++;
	    //printf(" c x+1 %d\n",c);
            if(c>0 && c <F)    
                return 0;
	}
        if(((y -1) >= 0))
	{
	    c = 0;
	    for(k = 0;k<F;k++)
	            if(sites[x][y][k] == sites[x][y-1][k])
        	        c++;
	    //printf(" c y-1 %d\n",c);
	    if(c>0 && c <F)    
                return 0;
	}
        if(((y + 1) < 20))
	{
	    c=0;
	    for(k = 0;k<F;k++)
	            if(sites[x][y][k] == sites[x][y+1][k])
	                c++;
	    //printf(" c y+1 %d\n",c);
            if(c>0 && c <F)    
                return 0;
	}
        return 1;
}


int check_status()
{
	int i,j,k,s,d;
	for(i =0;i<20;i++)
		for (j=0;j<20;j++)
		{
			if( ! allDifferent(i,j))
			{
			//	printf("%d %d\n",i,j);
				return 0;			
			}
		}	
	return 1;
}

void update(int x,int y)
{
	//printf("\n%d %d\n",x,y);
	int n = rand() % 4;
	//printf("%d\n",n);
	if( (n ==0) && ((x-1) >= 0))
		updateSite(x,y,x-1,y);
	else if((n ==1) && ((x + 1) < 20))
		updateSite(x,y,x+1,y);
	else if((n ==2) && ((y -1) >= 0))
                updateSite(x,y,x,y-1);
        else if((n == 3) && ((y + 1) < 20))
                updateSite(x,y,x,y+1);
}

int main(void)
{
	int max_q = 100,q,i,j,k,x,y;
	for(q = 2;q<max_q;q++)
	{
	    for(int iter = 0;iter <100;iter++)
	    {
		for(i=0;i<20;i++)
		{
			for(j=0;j<20;j++)
			{
				for(k=0;k<F;k++)
				{
					sites[i][j][k] = rand()%q+1;
				}
			}
		}
		//for(i = 0;i <1000000;i++)
		while(!check_status())
		{
			//printf("%d\n",i)//;
			for(i = 0;i<400;i++)
			{
				x = rand()%20;
				y = rand()%20;
				update(x,y);
			}
		}	
		std::map<string,int> stringCounts;
		//printf("Status: %d\n ",check_status());
		for (i = 0; i< 20;i++)
		{
			for(j=0;j<20;j++)
			{
				//printf("<%d%d> ",sites[i][j][0],sites[i][j][1]);
				std::ostringstream out;
				out << sites[i][j][0] << "," << sites[i][j][1];
				stringCounts[out.str()]++;
				out.flush();
			}
			//printf("\n");
		}
		std::map<string, int>::iterator it;
		int max = 0;
		for ( it = stringCounts.begin(); it != stringCounts.end(); it++ )
		{
		    //std::cout << it->first<< ':'<< it->second<< std::endl ;
		    if(it->second > max)
			max = it->second;
		}		
		//for( iter = stringCounts.begin(); iter != stringCounts.end(); iter++ ) {
   		//	 cout << "word: " << iter->first << ", count: " << iter->second << endl;
		 // }		
		std::cout<<q<<" "<<(float)max/400<<std::endl;
		}
	}
	return 0;
}


