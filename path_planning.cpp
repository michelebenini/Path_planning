#include <stdio.h>
#include <stdint.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <vector>

const int mapw=20;
const int maph=15;
int goal[2]={1,6};
int start[2]={maph-2,1};
int map[maph][mapw];

int obs[500][2];
int nobs=0;

char direction[5]={'A','S','O','E','N'};
char starto='N';

void waitFor (unsigned int secs) //stop execution for seconds secs
{
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}

int sign(int x) //return the sign of x
{
	if(x>0)
		return 1;
	if(x<0)
		return -1;
	return 0;
}

int makeMap()	//create a map without obstacles  
{
	int r;
	for(int k=0;k<maph;k++)
	{
		for(int l=0;l<mapw;l++)
		{
			map[k][l]=0;
		}
	}
	for(int k=0;k<maph;k++)
	{
		map[k][0]=-1;
		map[k][mapw-1]=-1;
	}
	for(int k=0;k<mapw;k++)
	{
		map[0][k]=-1;
		map[maph-1	][k]=-1;
	}
	//controll
	if(start[0]<maph && start[1]<mapw && goal[0]<maph && goal[1]<mapw)
	{
		map[start[0]][start[1]]=4;
		map[goal[0]][goal[1]]=3;
	}
	else 
	{
		perror("Goal or Start out of Map.\n");
		return 1;
	}
	return 0;
}

int setObs(int x,int y)	//insert an obstacle in obstacle queue
{
	if(obs[nobs][0]<maph && obs[nobs][1]<mapw)
	{
		obs[nobs][0]=x;
		obs[nobs][1]=y;
		nobs++;
		return 0;
	}
	printf("Obstacle out of map.\n");
	return 1;
}

int addObs()	//insert all obstacle in map
{
	map[1][5]=-1;
	map[2][6]=-1;
	map[3][7]=-1;
	map[4][8]=-1;
	map[5][8]=-1;
	map[6][8]=-1;
	map[7][8]=-1;
	map[8][8]=-1;
	//map[9][8]=-1;
	map[10][8]=-1;
	map[11][8]=-1;
	map[12][8]=-1;
	map[13][8]=-1;
	map[4][6]=-1;
	map[3][mapw-2]=-1;
	for(int i=0;i<nobs;i++)
		map[obs[i][0]][obs[i][1]]=-1;
}

int addToMap(int x, int y, int val) //insert a value val in map with coordinate (x,y)
{
	if(x<maph && y<mapw)
	{
		if(map[x][y]!=-1)
		{
			map[x][y]=val;
			return 0;
		}
	}
	printf("Coordinate out of map.\n");
	return 1;
}

int printMap()	//print map on screen 
{
	printf("start: [%d,%d]\tgoal: [%d,%d]\n",start[0],start[1],goal[0],goal[1]);
	printf("x/y\n");
	for(int k=0; k<maph; k++)
	{
		for(int l=0; l<mapw;l++)
		{
			if(map[k][l]==-1)
				printf("<obs>\t");
			else if(map[k][l]==0)
				printf(" \t");
			else if(map[k][l]==2)
				printf("->\t");
			else if(map[k][l]==3)
				printf("END\t");
			else if(map[k][l]==4)
				printf("START\t");
			else
				printf("%d\t",map[k][l]);
		}
		printf("\n");
	}
	return 0;
}

int solveMap(int sol[500][2])	//find a path from start to goal	
{
	int cx=0;
	int cy=0;
	signed int dx=(goal[0]-start[0]);
	signed int dy=(goal[1]-start[1]);
	int absx=sign(dx);
	int absy=sign(dy);
	cx=absx;
	cy=absy;
	int pos[2]={start[0],start[1]};
	int p=0;
	
	
	printf("Distanza x: %d\tDistanza y: %d\n",dx,dy);
	while((dx!=0 || dy!=0 )&& p<500)
	{	
		if(dy!=0  && map[pos[0]][pos[1]+absy]!=-1 && map[pos[0]][pos[1]+absy]!=2 )		//se x,y+1 != -1
		{
			sol[p][0]=pos[0];
			//printf("Move x -> %d\t",sol[p][0]);
			sol[p][1]=pos[1]=pos[1]+absy;
			//printf("Move y -> %d\n",sol[p][1]);
			//dy=dy-absy;
			dy=(goal[1]-pos[1]);

			dx=(goal[0]-pos[0]);
			absx=sign(dx);
			cx=absx;
			p++;

		}
		else if(dx!=0  && map[pos[0]+absx][pos[1]]!=-1 && map[pos[0]+absx][pos[1]]!=2 )	//se x+1,y != -1
		{
			
			sol[p][0]=pos[0]=pos[0]+absx;
			//printf("Move x -> %d\t",sol[p][0]);
			sol[p][1]=pos[1];
			//printf("Move y -> %d\n",sol[p][1]);
			dy=(goal[1]-pos[1]);
			absy=sign(dy);
			cy=absy;

			//dx=dx-absx;
			dx=(goal[0]-pos[0]);
			p++;
		}
		else if(map[pos[0]][pos[1]+1]!=-1 && map[pos[0]][pos[1]+1]!=2)	//se x+1,y != -1
		{
			//printf("Cerco un altra strada meno diretta\n");
			sol[p][0]=pos[0];
			//printf("Move x -> %d\t",sol[p][0]);
			sol[p][1]=pos[1]=pos[1]+1;
			//printf("Move y -> %d\n",sol[p][1]);
			dy=(goal[1]-pos[1]);

			dx=(goal[0]-pos[0]);
			absx=sign(dx);
			cx=absx;
			
			p++;
		}	
		else if(map[pos[0]+1][pos[1]]!=-1 && map[pos[0]+1][pos[1]]!=2 )	//se x+1,y != -1
		{
			//printf("Cerco un altra strada meno diretta\n");
			sol[p][0]=pos[0]=pos[0]+1;
			//printf("Move x -> %d\t",sol[p][0]);
			sol[p][1]=pos[1];
			//printf("Move y -> %d\n",sol[p][1]);
			dx=(goal[0]-pos[0]);

			dy=(goal[1]-pos[1]);
			absy=sign(dy);
			cy=absy;
			
			p++;
		}
		else if(map[pos[0]][pos[1]-1]!=-1 && map[pos[0]][pos[1]-1]!=2)	//se x+1,y != -1
		{
			//printf("Cerco un altra strada meno diretta\n");
			sol[p][0]=pos[0];
			//printf("Move x -> %d\t",sol[p][0]);
			sol[p][1]=pos[1]=pos[1]-1;
			//printf("Move y -> %d\n",sol[p][1]);
			dy=(goal[1]-pos[1]);

			dx=(goal[0]-pos[0]);
			absx=sign(dx);
			cx=absx;
			
			p++;
		}
		else if(map[pos[0]-1][pos[1]]!=-1 && map[pos[0]-1][pos[1]]!=2 )	//se x+1,y != -1
		{
			//printf("Cerco un altra strada meno diretta\n");
			sol[p][0]=pos[0]=pos[0]-1;
			//printf("Move x -> %d\t",sol[p][0]);
			sol[p][1]=pos[1];
			//printf("Move y -> %d\n",sol[p][1]);
			dx=(goal[0]-pos[0]);

			dy=(goal[1]-pos[1]);
			absy=sign(dy);
			cy=absy;
			
			p++;
		}	
		else
		{
			map[pos[0]][pos[1]]=-1;
			p=p-1;
			//printf("BUCO, torno indietro di: x: da %d a %d y: da %d a %d \n",sol[p][0],sol[p-1][0],sol[p][1],sol[p-1][1]);
			pos[0]=sol[p-1][0];
			pos[1]=sol[p-1][1];

			//printf("Ora sono in [%d,%d]\n",pos[0],pos[1]);
			

			int y=sol[p-1][1]-sol[p][1];
			int x=sol[p-1][0]-sol[p][0];
			//printf("X-----> %d-%d=%d \tY----> %d-%d=%d\n",sol[p][0],sol[p-1][0],x,sol[p][1],sol[p-1][1],y);
			dy=dy+y;
			dy=(goal[1]-pos[1]);
			absy=sign(dy);
			cy=absy;
			
			dx=dx+x;
			dx=(goal[0]-pos[0]);
			absx=sign(dx);
			cx=absx;
			//p++;
			//printf("cx--> %d\tcy-->%d\n",cx,cy);
			
		}
		
		if(p==0)
		{
			printf("Path not found.\n");
			return 1;
		}	
		
		
		//printf("Passo [%d]\tDistanza x: %d ---abs: %d ---cx: %d\t    Distanza y: %d---abs: %d---cy: %d\n",p,dx,absx,cx,dy,absy,cy);
		//printf("Ora sono in [%d,%d]\n",pos[0],pos[1]);
		map[pos[0]][pos[1]]=2;
		//printMap();
		//waitFor(1);

	}
	return 0;
}

int reduceRoad(int sol[500][2],int aus[500][2]) //simplifies the path 
{
	int i=0;
	for(int k=0; aus[k][0]!=goal[0] || aus[k][1]!=goal[1]; k++ )
	{
		aus[k][0]=sol[i][0];
		aus[k][1]=sol[i][1];		
		//printf("k---> %d(%d,%d)\ti--->%d(%d,%d)\n",k,aus[k][0],aus[k][1],i,sol[i][0],sol[i][1]);
		//waitFor(1);
		for(int j=i;( sol[j][0]!=goal[0] || sol[j][1]!=goal[1]) && ( sol[i][0]!=goal[0] || sol[i][1]!=goal[1]);j++)
		{
			if((sol[j][0]==aus[k][0] && (sol[j][1]+1==aus[k][1] || sol[j][1]-1==aus[k][1])) || (sol[j][1]==aus[k][1] && (sol[j][0]+1==aus[k][0] || sol[j][0]-1==aus[k][0])))
			{
				i=j-1;	
				//break;
			}
		}

		if(aus[k][0]==goal[0] && aus[k][1]==goal[1])
			break;
		i++;
	}

	return 0;
}

int path(int s[500][2]) //call solveMap and reduceMap to have a path 
{
	int sol[500][2];
	int solw[500][2];
	int rsol[500][2];
	int i, stg,gts;
  	makeMap();
  	addObs();

  	//printMap();
  	if(solveMap(sol)==1)
  	{
  		printf("Percorso non trovato\n");
	  	printMap();
  		return 0;
  	}
  	//printMap();
  	//printf("PERCORSO BREVE\n");
  	reduceRoad(sol, rsol);
  	//makeMap();
  	//addObs();
  	for( i=0; rsol[i][0]!=goal[0] || rsol[i][1]!=goal[1]; i++ )
  	{
  		//printf("[%d]Robot ----> (%d,%d)\n",i,rsol[i][0],rsol[i][1]);
  		addToMap(rsol[i][0],rsol[i][1],2);
  	}
  	addToMap(rsol[i][0],rsol[i][1],2);
  	i++;
  	//printMap();
  	//waitFor(3);
  	for(int k=0; k<i;k++)
  	{
  		//printf("[%d]Robot ----> (%d,%d)\n",k,rsol[k][0],rsol[k][1]);
  		s[k][0]=rsol[k][0];
  		s[k][1]=rsol[k][1];
  	}
  	return i;
}

int bestPath(int rsol[500][2])	//find path from start to goal and goal to start and chose the best
{
	int p1[500][2],p2[500][2];
	int stg,gts,lsol;
	stg=path(p1);
	if(stg==0)
	{
		printf("Path not found.\n");
		return 1;
	}

	int aus[2]={goal[0],goal[1]};
  	goal[0]=start[0];
  	goal[1]=start[1];
  	start[0]=aus[0];
  	start[1]=aus[1];
  	gts=path(p2);
  	if(gts==0)
	{
		printf("Path not found.\n");
		return 1;
  	}
  	if(stg>=gts)
  	{
  		//printf("Ha vinto la prima\n");
  		int aus[2]={goal[0],goal[1]};
	  	goal[0]=start[0];
		goal[1]=start[1];
		start[0]=aus[0];
		start[1]=aus[1];

  		
  		for(int k=0; k<gts-1;k++)
	  	{
	  		rsol[k][0]=p2[gts-k-2][0];
	  		rsol[k][1]=p2[gts-k-2][1];
	  		//printf("[%d]Robot ----> (%d,%d)\n",k,rsol[k][0],rsol[k][1]);
	  	}
	  	lsol=gts-1;
	  	
		rsol[lsol][0]=goal[0];
	  	rsol[lsol][1]=goal[1];
	  	lsol++;
	  //	printf("[%d]Robot ----> (%d,%d)\n",lsol,rsol[lsol][0],rsol[lsol][1]);
	  	
	}
  	else
  	{
  		//printf("Ha vinto la seconda\n");
  		for(int k=0; k<stg;k++)
	  	{
	  		rsol[k][0]=p1[k][0];
	  		rsol[k][1]=p1[k][1];
	  		//printf("[%d]Robot ----> (%d,%d)\n",k,rsol[k][0],rsol[k][1]);
	  	}
	  	lsol=stg;
	  	int aus[2]={goal[0],goal[1]};
		goal[0]=start[0];
		goal[1]=start[1];
		start[0]=aus[0];
		start[1]=aus[1];

	}
	//makeMap();
  	//addObs();
  	for(int i=0; i<lsol; i++ )
  	{
  		//printf("[%d]Robot ----> (%d,%d)\n",i,rsol[i][0],rsol[i][1]);
  		addToMap(rsol[i][0],rsol[i][1],2);
  		//waitFor(1);
  	}
  	//printMap();
  	return lsol;
}

int printRoad(int s[500][2],int l) //print the path on map
{
	makeMap();
  	addObs();
  	for(int i=0; i<l; i++ )
  		addToMap(s[i][0],s[i][1],2);
  	printMap();
  	return 0;
}

int getRoad(char dir[500],int pas[500], int s[500][2],int l) //create two array that the first contains a direction and the second how many step must to do in the corrispondence direction
{
	int flag=0;			
	int lv=0;
	dir[0]=starto;
	pas[0]=0;

	if(dir[0]==direction[1])
		flag=1;
	else if(dir[0]==direction[2])
		flag=2;
	else if(dir[0]==direction[3])
		flag=3;
	else if(dir[0]==direction[4])
		flag=4;


	for(int i=0;i<l-1;i++)
	{
		//printf("(%d,%d)---------->(%d,%d)\n",s[i][0],s[i][1],s[i+1][0],s[i+1][1]);
		if(s[i][0]+1==s[i+1][0] && s[i][1]==s[i+1][1])
		{	
			//printf("Vado a %c\n",direction[1]);
			if(flag==1)
				pas[lv]++;
			else
			{
				lv++;
				dir[lv]=direction[1];
				pas[lv]=1;
				flag=1;
			}
		}
		if(s[i][0]==s[i+1][0] && s[i][1]==s[i+1][1]+1)
		{
			
			//printf("Vado a %c\n",direction[2]);
			if(flag==2)
				pas[lv]++;
			else
			{
				lv++;
				dir[lv]=direction[2];
				pas[lv]=1;
				flag=2;
			}
		}
		else if(s[i][0]==s[i+1][0] && s[i][1]+1==s[i+1][1])
		{
			//printf("Vado a %c\n",direction[3]);
			if(flag==3)
				pas[lv]++;
			else
			{
				lv++;
				dir[lv]=direction[3];
				pas[lv]=1;
				flag=3;
			}
		}
		else if(s[i][0]==s[i+1][0]+1 && s[i][1]==s[i+1][1])
		{
			//printf("Vado a %c\n",direction[4]);
			if(flag==4)
				pas[lv]++;
			else
			{
				lv++;
				dir[lv]=direction[4];
				pas[lv]=1;
				flag=4;
			}
		}
		if(i==0)
			pas[lv]++;
	}
	lv++;
	return lv;
}

int intArrayToVect(int l, int a[500], std::vector<int32_t> *c)
{
	//std::vector<int> v(500);
	for(int i=0;i<l;i++)
	{
		c[0].at(i)=a[i];
		//printf("%d\n",v[i]);
	}
	return 0;
}

int charArrayToVect(int l, char a[500], std::vector<uint8_t> *c)
{
	//std::vector<int> v(500);
	for(int i=0;i<l;i++)
	{
		c[0].at(i)=a[i];
		//printf("%d\n",v[i]);
	}
	return 0;
}

int moveCmd(char d[500],int p[500], int lv) //create two array, the first contains where we must turn and the second how many step we must to do in the corrispondence direction
{
	char vdir[500];
	int vpas[500];
	int k=0;
	for(int i=1; i<lv;i++)
	{
		vdir[i]=d[i];
		vpas[i]=p[i];
	}
	for(int i=0; i<lv;i++)
	{
		if((vdir[i-1]=='N' && vdir[i]=='O') || (vdir[i-1]=='S' && vdir[i]=='E') || (vdir[i-1]=='E' && vdir[i]=='N') || (vdir[i-1]=='O' && vdir[i]=='S'))
		{
			d[k]='L';
			p[k]=vpas[i];
		}
		else if((vdir[i-1]=='N' && vdir[i]=='E') || (vdir[i-1]=='S' && vdir[i]=='O') || (vdir[i-1]=='E' && vdir[i]=='S') || (vdir[i-1]=='O' && vdir[i]=='N'))
		{
			d[k]='R';
			p[k]=vpas[i];
		}
		else if((vdir[i-1]=='N' && vdir[i]=='S') || (vdir[i-1]=='S' && vdir[i]=='N') || (vdir[i-1]=='E' && vdir[i]=='O') || (vdir[i-1]=='O' && vdir[i]=='E'))
		{
			d[k]='R';
			p[k]=0;
			d[k]='R';
			p[k]=vpas[i];
		}
		else
		{
			d[k]='F';
			p[k]=vpas[i];
		}
		k++;
	}

	return k;
}

int main()
{
	int s[500][2];
	char dir[500];
	int pas[500];
	int lv=0;
	int g=0;
	std::vector<uint8_t> vdir(500);
	std::vector<int32_t> vpas(500);
	
	int l=bestPath(s);


	printRoad(s,l);
	g=getRoad(dir,pas,s,l);
	
		
	for(int i=0;i<g;i++)
		printf("%c -----> %d \n",dir[i],pas[i]);
			
	//printf("-------------------------------------\n");			
	lv=moveCmd(dir,pas,g);
	//printf("Con vector:\n");

	charArrayToVect(lv,dir,&vdir);
	intArrayToVect(lv,pas,&vpas);
	
	return 0;
}