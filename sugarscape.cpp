#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

class Agent
{	
	public:
		int id;
		int x;
		int y;
		int max_age;
		int cur_age;
		int wealth;
		int metabolism;
		int initial_wealth;
		int vision;
		char gender;
};
ofstream myfile;
int F = 18;
int D = 45;
int global_id = 0;
int sugar_capacity_max[80][80];
int sugar_capacity_cur[80][80];
int agent_positions[80][80];
std::vector<Agent> agents;
int p_init=1000;
int time_step;
void initialize_sugarscape()
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

  int max = 0;
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
					    sugar_capacity_max[i][j] = floor(q[i][j]/temp)+floor(q[i-30][j-30]/temp);
					else
						sugar_capacity_max[i][j] = floor(q[i][j]/temp);
						sugar_capacity_max[i][j] = floor(q[i][j]/temp);
					sugar_capacity_cur[i][j] = sugar_capacity_max[i][j]; 
					agent_positions[i][j] = 0;
                }
  }
}

void initialize_agents()
{
	int x,y;
	agents.clear();
	for (int i = 0 ;i<p_init;i++)
	{
		Agent agent;
		agent.id = global_id++;
		while(true)
		{
			x = rand() %80;
			y = rand() %80;	
			if(agent_positions[x][y] == 0)
			{
				agent.x = x;
				agent.y = y;
				agent_positions[x][y] = agent.id;
				break;
			}
		}
		agent.max_age = (rand() % 40)+60;
		agent.cur_age = 0;
		agent.initial_wealth = (rand()%20) +10;
		agent.wealth = agent.initial_wealth;
		agent.metabolism = (rand() % 4)+1;
		agent.vision = (rand() % 6)+1;
		agent.gender = (agent.id%2 > 0 ? 'm':'f');
		agents.push_back(agent);
	}
}
double halfL = 40.0;
double L = 80.0;
int isInRadius(int x_1, int y_1,int x_2, int y_2)
{
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
        if(d == 1.0)
                return 1;
        return 0;
}



float getAvgVision()
{
	int len_agents =agents.size();
	int sum = 0;
	for(int i = 0;i<len_agents;i++)
        {
		sum+=agents[i].vision;
	}
	float ret = 0.0;
	if(len_agents > 0)
		ret = sum/(float) len_agents;
	return ret;
}

float getAvgMetabolism()
{
        int len_agents =agents.size();
        int sum = 0;
        for(int i = 0;i<len_agents;i++)
        {
                sum+=agents[i].metabolism;
        }
        float ret = 0.0;
	if(len_agents>0)
	        ret = sum/(float) len_agents;
        return ret;

}



void reproduce()
{
	int len_agents =agents.size();
	std::random_shuffle(std::begin(agents), std::end(agents));
	std::vector<Agent> new_agents;
	for(int i = 0;i<len_agents;i++)
	{
		for(int j = i;j<len_agents;j++)
		{
			if(!isInRadius(agents[i].x,agents[i].y,agents[j].x,agents[j].y))
				continue;
			if( (agents[i].cur_age <F) || (agents[j].cur_age <F) )
				continue;
			if( (agents[i].cur_age > D) || (agents[j].cur_age > D) )
				continue;
			if( (agents[i].wealth < agents[i].initial_wealth) || (agents[j].wealth < agents[j].initial_wealth) )
				continue;
			if (agents[i].gender == agents[j].gender)
				continue;
			int x=-1,y=-1;
			if(agents[i].x == agents[j].x)	
			{
				if(( agent_positions[agents[i].x ][(agents[i].y+ 1)%80] ==0 ))
				{
					x = agents[i].x;
					y = (agents[i].y+ 1)%80;
				}
				else if( ( agent_positions[agents[i].x ][(agents[i].y- 1 +80)%80] ==0))
				{
					x = agents[i].x;
					y = (agents[i].y- 1 +80)%80;
				}
				else if(( agent_positions[agents[j].x ][(agents[j].y+ 1)%80] ==0 ))
				{
					x = agents[j].x;
					y = (agents[j].y+ 1)%80;
				}
				else if( ( agent_positions[agents[j].x ][(agents[j].y- 1 +80)%80] ==0))
				{
					x = agents[j].x;
					y = (agents[j].y- 1 +80)%80;
				}
			}
			else
			{
				if(( agent_positions[(agents[i].x+1)%80 ][(agents[i].y)] ==0 ))
				{
					x = (agents[i].x+1)%80;
					y = (agents[i].y);
				}
				else if( ( agent_positions[(agents[i].x- 1 +80)%80 ][(agents[i].y)] ==0))
				{
					x = (agents[i].x- 1 +80)%80;
					y = (agents[i].y);
				}
				else if(( agent_positions[(agents[j].x+1)%80 ][(agents[j].y)] ==0 ))
				{
					x = (agents[j].x+1)%80;
					y = agents[j].y;
				}
				else if( ( agent_positions[(agents[j].x- 1 +80)%80][(agents[j].y)] ==0))
				{
					x = (agents[j].x- 1 +80)%80;
					y = (agents[j].y);
				}
			}
			if(x == -1 && y == -1)
				continue;
			Agent agent;
			agent.x = x;
			agent.y = y;
			//cout<<"Reproduction "<<agents[i].x<<" "<<agents[i].y<<" "<<agents[j].x<<" "<<agents[j].y;
			agent.id = global_id++;
			agent.max_age = (rand() % 40)+60;
			agent.cur_age = 0;
			agent.initial_wealth = (agents[i].initial_wealth/2) +(agents[j].initial_wealth/2);
			agent.wealth = agent.initial_wealth;
			agent.metabolism = (rand() % 2 > 0? agents[i].metabolism:agents[j].metabolism);
			agent.vision = (rand() % 2 > 0? agents[i].vision:agents[j].vision);
			agent.gender = (rand()%2 > 0 ? 'm':'f');
			agent_positions[x][y] = agent.id ;
			new_agents.push_back(agent);
		}
	}
	agents.insert(agents.end(),new_agents.begin(),new_agents.end());
}


void grow_sugar()
{
	for(int i = 0;i<80;i++)
		for(int j=0;j<80;j++)
			sugar_capacity_cur[i][j]++;
}

bool checkDead( Agent &a )
{
    return (a.wealth <=0 || a.cur_age > a.max_age);
}

void kill_agents()
{
	int n = agents.size();
	for(int i = 0;i<n;i++)
		if(agents[i].wealth <=0 || agents[i].cur_age > agents[i].max_age)
			myfile<<F << " " << D <<" "<<p_init<<" "<<agents[i].wealth<<endl;
	agents.erase( std::remove_if(agents.begin(),agents.end(),checkDead), agents.end() );
	for(int i = 0;i<80;i++)
		for(int j=0;j<80;j++)
			agent_positions[i][j] = 0;
	for(int i=0;i<n;i++)
		agent_positions[agents[i].x][agents[i].y] = agents[i].id;
}

void update_positions()
{
	int len_agents =agents.size();
	std::random_shuffle(std::begin(agents), std::end(agents));
	for(int i = 0;i<len_agents;i++)
	{
		int ag = i;
		int max = 0;
		int x = agents[ag].x,y = agents[ag].y;
		agents[ag].cur_age++;
		for(int j = 0;j<agents[ag].vision;j++)
		{
			if( (sugar_capacity_cur[(agents[ag].x+j)%80][agents[ag].y] > max) && ( agent_positions[(agents[ag].x+j)%80][agents[ag].y] ==0 ) )
			{
				x = (agents[ag].x+j)%80;
				y = agents[ag].y;
				max = sugar_capacity_cur[(agents[ag].x+j)%80][agents[ag].y];
			}
			else if((sugar_capacity_cur[(agents[ag].x - j +80)%80][agents[ag].y] > max) && (agent_positions[(agents[ag].x - j +80)%80][agents[ag].y] ==0))
			{
				x = (agents[ag].x - j +80)%80;
				y = agents[ag].y;
				max = sugar_capacity_cur[(agents[ag].x - j +80)%80][agents[ag].y];
			}
			else if((sugar_capacity_cur[agents[ag].x ][(agents[ag].y+ j)%80] > max) && ( agent_positions[agents[ag].x ][(agents[ag].y+ j)%80] ==0 ))
			{
				x = agents[ag].x;
				y = (agents[ag].y+ j)%80;
				max = sugar_capacity_cur[agents[ag].x ][(agents[ag].y+ j)%80];
			}
			else if((sugar_capacity_cur[agents[ag].x ][(agents[ag].y- j +80)%80] > max ) && ( agent_positions[agents[ag].x ][(agents[ag].y- j +80)%80] ==0))
			{
				x = agents[ag].x;
				y = (agents[ag].y- j +80)%80;
				max = sugar_capacity_cur[agents[ag].x ][(agents[ag].y- j+80)%80];
			}
		}
		agents[ag].x = x;
		agents[ag].y = y;
		sugar_capacity_cur[x][y] =  sugar_capacity_cur[x][y] - agents[ag].metabolism;
		if (sugar_capacity_cur[x][y] < 0)
			sugar_capacity_cur[x][y] = 0;
		agents[ag].wealth = agents[ag].wealth - agents[ag].metabolism;
		agents[ag].wealth =  agents[ag].wealth + sugar_capacity_cur[x][y];
		sugar_capacity_cur[x][y] = 0;
	}
}
int main()
{
	myfile.open("death_distribution.txt");
	for(p_init = 500; p_init < 3100;p_init +=500)
		for( F = 15,D = 60; F<36;F+=5,D-=5)
		{
			global_id = 0;
			initialize_sugarscape();
			initialize_agents();
			for(time_step=0;time_step<4000;time_step++)
			{
				reproduce();
				update_positions();
				kill_agents();
				grow_sugar();
				std::cout<<time_step<<" "<<agents.size()<<" "<<getAvgVision()<<" "<<getAvgMetabolism()<<" "<<F << " " << D <<" "<<p_init<<endl;
			}
		}
	return 0;
}
