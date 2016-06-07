#include<stdio.h>
#include<stdlib.h>
int sites[30][30];
void intialize_matrix()
{
	int i,j;
	for(i = 0;i<30;i++)
		for(j=0;j<30;j++)
			sites[i][j] = 0;
}

int check_happiness(x,y)
{
	int h = 0;
	if((x-1) > 0)
                h += sites[x-1][y];
        if((x + 1) < 30)
                h += sites[x+1][y];
        if((y -1) > 0)
                h += sites[x][y-1];
        if((y + 1) < 30)
                h += sites[x][y+1];
        if(((y + 1) < 30) && ((x + 1) < 30))
                h += sites[x+1][y+1];
	if(((y - 1) > 0) && ((x - 1) > 0))
                h += sites[x-1][y-1];
	if(((y - 1) > 0) && ((x + 1) < 30))
                h += sites[x+1][y-1];
	if(((y + 1) < 30) && ((x - 1) > 0))
                h += sites[x-1][y+1];
	return h;
	
}

int check_total_happiness()
{
	int i,j;
	int sum = 0;
	int h = 0;
	int c =0;
	for(i = 0;i<30;i++)
		for(j=0;j<30;j++)
		{
			if(sites[i][j] !=0 )
			{
				c++;
				h = check_happiness(i,j)*sites[i][j];
				if(h>0)
					sum ++;
			}
		}
//	printf("%d\n",sum);
	return sum;
}

void print_mat()
{
	int i,j;
	for(i = 0;i<30;i++)
	{
                for(j=0;j<30;j++)
		{
	                        printf("%d ",sites[i][j]);
		}
		printf("\n");
	}
}

float calculate_density()
{
	int i,j,x,y;
	int sum = 0;
	for (i =0;i<30;i++)
		for (j=0;j<30;j++)
		{
			x =i,y=j;
		        if((x + 1) < 30)
				if((sites[x][y]*sites[x+1][y]) < 0)
                			sum++;//printf("%d %d && %d %d\n",x,y,x+1,y);
		        if((y + 1) < 30)
				if((sites[x][y]*sites[x][y+1]) < 0)
	                		sum ++;//printf("%d %d && %d %d\n",x,y,x,y+1);
		        if(((y + 1) < 30) && ((x + 1) < 30))
				if((sites[x][y]*sites[x+1][y+1]) < 0)
	        	        		sum++;//printf("%d %d && %d %d\n",x,y,x+1,y+1);
		        if(((x + 1) < 30) && ((y - 1) > 0))
				if((sites[x][y]*sites[x+1][y-1]) < 0)
                                                sum++;//printf("%d %d && %d %d\n",x,y,x+1,y-1);
		}
	//printf("sum %d\n",sum);
	//printf("Density %f\n ",sum/(float)(1800));
	return (sum/(float)1800);
					
}

int main()
{
	float probs[] = {0.1,0.2,0.3,0.4,0.5};
	int p,no_occupied_sites,i,j,x,y,new_x,new_y,new_h,current_state,h;
	int flag = 0,tot;
	int c,k;
	for(p = 0; p<5;p++)
	{
		for(k=0;k<1;k++)
		{
			//printf("Probability %f\n",probs[p]);
			intialize_matrix();
			no_occupied_sites = (1-probs[p]) * 30 * 30;
			//printf("Sites %d\n",no_occupied_sites);
			c= 0;
			while(c<no_occupied_sites)
			{
				
				x = rand()%30;
				y = rand()%30;
				if(sites[x][y] ==0 )
				{
					if(c%2 ==0)
					{
						sites[x][y] = 1;				
						c++;
					}
					else
						sites[x][y] = -1,c++;
				}
			}
			//printf("Initial Count %d",c);
			//printf("Total %d\n",check_total_happiness());
			i = 0;
			while (i < 900)		
			{
				x = rand()%30;
				y = rand()%30;
				if(sites[x][y] != 0)
				{
					h = check_happiness(x,y)*sites[x][y];
					current_state = sites[x][y];
					if(h<=0)
					{
						//printf("Unhappy\n");
						flag = 1;
						while(flag)
						{			
							new_x = rand()%30;
							new_y = rand()%30;
							if(sites[new_x][new_y] ==0)
							{
								new_h = check_happiness(new_x,new_y)*current_state;
								if(new_h>0)
								{
									sites[new_x][new_y] = current_state;
									sites[x][y] = 0;
									i++;
									//printf("Happy Now\n");
									flag = 0;
								}	
							}
						}				
						tot = check_total_happiness();
		                                //printf("Total Happiness %d\n",tot);
        		                        if(tot == no_occupied_sites)
                		                      break;
					}
				}
		 	 }
			//printf("%d %d\n",i,check_total_happiness());
			print_mat();
			printf("%f,%f\n",probs[p],calculate_density());
	  	}
	}
}

