#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include "piece.h"
#include "gamestate.h"
#include "renderstate.h"
#include <iostream>
using namespace std;

extern renderstate_t g_rstate;
extern gamestate_t g_gstate;
int count=19,r,score[3],i,z;
bool  a=1, b, c, collide,out[19];

gamestate_t::gamestate_t() 
{
	srand (time(NULL));
	double delta = rand()/(double)RAND_MAX;
	double force = (rand() % 25)+30;
	striker.pos.x = -0.65 + delta;
	striker.pos.y = -0.8;
	striker.type = STRIKER;
	striker.is_visible = true;

	for(int i=0;i<6;i++)
	{
		float theta= 2*M_PI*i/6;
		coin[i].pos.x = 0.1 * cos(theta);
		coin[i].pos.y = -0.42267+ 0.1 * sin(theta);
		coin[i].vel.dx = 0.0;
		coin[i].vel.dy = 0.0;
		if(i%2==0)
			coin[i].type = WHITE;
		else
			coin[i].type = BLACK;
		coin[i].is_visible = true;
	}
	for(int i=6;i<18;i++)
	{
		float theta= 2*M_PI*(i-6)/12;
		coin[i].pos.x = 0.2 * cos(theta);
		coin[i].pos.y = -0.42267+ 0.2 * sin(theta);
		coin[i].vel.dx = 0.0;
		coin[i].vel.dy = 0.0;
		if(i%2==0)
			coin[i].type = WHITE;
		else
			coin[i].type = BLACK;
		coin[i].is_visible = true;
	}
		coin[18].pos.x = 0.0;
		coin[18].pos.y = -0.42267;
		coin[18].vel.dx = 0.0;
		coin[18].vel.dy = 0.0;
		coin[18].type = RED;
		coin[18].is_visible = true;
	striker.vel.dx = (coin[r].pos.x - striker.pos.x)/force;
	striker.vel.dy = (coin[r].pos.y - striker.pos.y)/force;
}
//Function to continue with the next/same player
void gamestate_t::conti()
{
	srand (time(NULL));
	double delta = rand()/(double)RAND_MAX;
	double force = (rand() % 25)+30;
	striker.is_visible=true;
	cout<<"After "<<z+1<<"th strike\t";
	cout<<"Score of 'a'="<<score[0]<<"\t";             // score after each strike
	cout<<"Score of 'b'="<<score[1]<<"\t";
	cout<<"Score of 'c'="<<score[2]<<"\n";
	z++;
	if(a==1)
	{
		striker.pos.x = -0.605 + delta*cos(M_PI/3);
		striker.pos.y = -0.633 + delta*sin(M_PI/3);
		a=0;
		b=1;
	}
	else if(b==1)
	{
		striker.pos.x = 0.605 - delta*cos(M_PI/3);
		striker.pos.y = -0.633 + delta*sin(M_PI/3);
		b=0;
		c=1;
	}
	else if(c==1)
	{
		striker.pos.x = -0.65 + delta;
		striker.pos.y = -0.8;
		c=0;
		a=1;
	}
	
	while(out[r]==1)
		r++;

	striker.vel.dx = (coin[r].pos.x - striker.pos.x)/force;
	striker.vel.dy = (coin[r].pos.y - striker.pos.y)/force;
}
//function to execute coin-coin collision(coefficient of restitution=0.8)
void gamestate_t::coin_coin_collision(carrompiece_t &coin1, carrompiece_t &coin2)
{
	double nx,ny,tx,ty,k,l,m,n,d;
	d=sqrt(pow((coin2.pos.x-coin1.pos.x),2)+pow((coin2.pos.y-coin1.pos.y),2));
	if(d<=0.06)
	{
		nx=(coin1.pos.x-coin2.pos.x)/d;
		ny=(coin1.pos.y-coin2.pos.y)/d;
		tx=(coin1.pos.y-coin2.pos.y)/d;
		ty=-(coin1.pos.x-coin2.pos.x)/d;
		k=coin2.vel.dx*nx+coin1.vel.dx*nx+coin2.vel.dy*ny+coin1.vel.dy*ny;
		l=-0.8*((coin2.vel.dx*nx+coin2.vel.dy*ny)-(coin1.vel.dx*nx+coin1.vel.dy*ny));
		m=coin2.vel.dx*tx+coin2.vel.dy*ty;
		n=coin1.vel.dx*tx+coin1.vel.dy*ty;
		coin2.vel.dx=(ty*((k+l)/2)-ny*m)/(nx*ty-tx*ny);
		coin2.vel.dy=((nx*m)-tx*((k+l)/2))/(nx*ty-tx*ny);
		coin1.vel.dx=(ty*((k-l)/2)-ny*n)/(nx*ty-tx*ny);
		coin1.vel.dy=((nx*n)-tx*((k-l)/2))/(nx*ty-tx*ny);
		while(d<=0.06)
		{
			coin2.pos.x+=coin2.vel.dx;
			coin2.pos.y+=coin2.vel.dy;
			coin1.pos.x+=coin1.vel.dx;
			coin1.pos.y+=coin1.vel.dy;
			d=sqrt(pow((coin2.pos.x-coin1.pos.x),2)+pow((coin2.pos.y-coin1.pos.y),2));
		}
	}
}
//function to execute striker coin collision(coefficient of restitution=0.7)
void gamestate_t::striker_coin_collision(carrompiece_t &striker, carrompiece_t &coin)
{
	double nx,ny,tx,ty,k,l,m,n,d;
	d=sqrt(pow((striker.pos.x-coin.pos.x),2)+pow((striker.pos.y-coin.pos.y),2));
	if(d<=0.068)
	{
		nx=(coin.pos.x-striker.pos.x)/d;
		ny=(coin.pos.y-striker.pos.y)/d;
		tx=(coin.pos.y-striker.pos.y)/d;
		ty=-(coin.pos.x-striker.pos.x)/d;
		k=striker.vel.dx*nx+0.492*coin.vel.dx*nx+striker.vel.dy*ny+0.492*coin.vel.dy*ny;
		l=-0.7*((striker.vel.dx*nx+striker.vel.dy*ny)-(coin.vel.dx*nx+coin.vel.dy*ny));
		m=striker.vel.dx*tx+striker.vel.dy*ty;
		n=coin.vel.dx*tx+coin.vel.dy*ty;
		striker.vel.dx=(ty*((k+l)/2)-ny*m)/(nx*ty-tx*ny);
		striker.vel.dy=((nx*m)-tx*((k+l)/2))/(nx*ty-tx*ny);
		coin.vel.dx=(ty*((k-l)/2)-ny*n)/(nx*ty-tx*ny);
		coin.vel.dy=((nx*n)-tx*((k-l)/2))/(nx*ty-tx*ny);
		collide=1;		
		while(d<=0.068)
		{
			coin.pos.x+=coin.vel.dx;
			coin.pos.y+=coin.vel.dy;
			striker.pos.x+=striker.vel.dx;
			striker.pos.y+=striker.vel.dy;
			d=sqrt(pow((striker.pos.x-coin.pos.x),2)+pow((striker.pos.y-coin.pos.y),2));
		}
	}
}
//function to execute striker-wall collision
void gamestate_t::striker_wall_collision(carrompiece_t &striker)
{
	double t1,t2;
	if(striker.pos.y<=-0.912)
	{
		striker.vel.dy=-0.9*striker.vel.dy;
		while(striker.pos.y<=-0.912)
		{
			striker.pos.x+=striker.vel.dx;
			striker.pos.y+=striker.vel.dy;
		}
	}
	if(tan(M_PI/3)*striker.pos.x-striker.pos.y+tan(M_PI/3)-1.126<=0)
	{
		t1=cos(M_PI/3)*striker.vel.dx+sin(M_PI/3)*striker.vel.dy;
		t2=-cos(M_PI/6)*striker.vel.dx+sin(M_PI/6)*striker.vel.dy;
		t2*=0.9;
		striker.vel.dx=cos(M_PI/3)*t1+sin(M_PI/3)*t2;
		striker.vel.dy=+cos(M_PI/6)*t1-sin(M_PI/6)*t2;
		while(tan(M_PI/3)*striker.pos.x-striker.pos.y+tan(M_PI/3)-1.126<=0)
		{
			striker.pos.x+=striker.vel.dx;
			striker.pos.y+=striker.vel.dy;
		}
	}
	if(tan(M_PI/3)*striker.pos.x+striker.pos.y-tan(M_PI/3)+1.126>=0)
	{
		t1=-cos(M_PI/3)*striker.vel.dx+sin(M_PI/3)*striker.vel.dy;
		t2=cos(M_PI/6)*striker.vel.dx+sin(M_PI/6)*striker.vel.dy;
		t2*=0.9;
		striker.vel.dx=-cos(M_PI/3)*t1-sin(M_PI/3)*t2;
		striker.vel.dy=+cos(M_PI/6)*t1-sin(M_PI/6)*t2;
		while(tan(M_PI/3)*striker.pos.x+striker.pos.y-tan(M_PI/3)+1.126>=0)
		{
			striker.pos.x+=striker.vel.dx;
			striker.pos.y+=striker.vel.dy;
		}
	}
}
//function to execute coin-wall collision
void gamestate_t::coin_wall_collision(carrompiece_t &coin)
{
	double t1,t2;
	if(coin.pos.y<=-0.92)
	{
		coin.vel.dy=-coin.vel.dy*0.9;
		while(striker.pos.y<=-0.92)
		{
			coin.pos.x+=coin.vel.dx;
			coin.pos.y+=coin.vel.dy;
			cout<<coin.vel.dx<<"\t"<<coin.vel.dy<<endl;
		}
	}
	if(tan(M_PI/3)*coin.pos.x-coin.pos.y+tan(M_PI/3)-1.11<=0)
	{
		t1=cos(M_PI/3)*coin.vel.dx+sin(M_PI/3)*coin.vel.dy;
		t2=-cos(M_PI/6)*coin.vel.dx+sin(M_PI/6)*coin.vel.dy;
		t2*=0.9;
		coin.vel.dx=cos(M_PI/3)*t1+sin(M_PI/3)*t2;
		coin.vel.dy=+cos(M_PI/6)*t1-sin(M_PI/6)*t2;
		while(tan(M_PI/3)*coin.pos.x-coin.pos.y+tan(M_PI/3)-1.11<=0)
		{
			coin.pos.x+=coin.vel.dx;
			coin.pos.y+=coin.vel.dy;
		}
	}
	if(tan(M_PI/3)*coin.pos.x+coin.pos.y-tan(M_PI/3)+1.11>=0)
	{
		t1=-cos(M_PI/3)*coin.vel.dx+sin(M_PI/3)*coin.vel.dy;
		t2=cos(M_PI/6)*coin.vel.dx+sin(M_PI/6)*coin.vel.dy;
		t2*=0.9;
		coin.vel.dx=-cos(M_PI/3)*t1-sin(M_PI/3)*t2;
		coin.vel.dy=+cos(M_PI/6)*t1-sin(M_PI/6)*t2;
		while(tan(M_PI/3)*coin.pos.x+coin.pos.y-tan(M_PI/3)+1.11>=0)
		{
			coin.pos.x+=coin.vel.dx;
			coin.pos.y+=coin.vel.dy;
		}
	}
}
//function to check pocketing of coins and striker
void gamestate_t::pocketing_striker_or_coin(carrompiece_t &piece, int i)
{
	double vel1,d1,d2,d3;
	int j=0;
	vel1=sqrt(pow(piece.vel.dx,2)+pow(piece.vel.dy,2));
	d1=sqrt(pow((0.607-piece.pos.y),2)+pow(piece.pos.x,2));
	d2=sqrt(pow((-0.905-piece.pos.y),2)+pow(piece.pos.x-0.875,2));
	d3=sqrt(pow((-0.905-piece.pos.y),2)+pow(piece.pos.x+0.875,2));
	if((d1<0.045 && vel1<0.01)||(d2<0.045 && vel1<0.01)||(d3<0.045 && vel1<0.01))
	{
		piece.vel.dx=piece.vel.dy=0;
		if(piece.type==STRIKER)                    //if striker is pocketed
		{
			piece.pos.x=piece.pos.y=1;
			piece.is_visible=false;
			if(a==1)
			{
				score[0]--;
				for(;j<19;j++)
				{
					if(out[j]==1)
					{
						if(piece.pos.x==-0.9+0.08*j && piece.pos.y==-0.975)
						{
							piece.pos.x=0;
							piece.pos.y=-0.42267;
							out[j]=0;
						}
					}
				}
				if(j==19)
					cout<<"Player 'a' is out";
			}
			if(b==1)
			{
				score[1]--;
				for(;j<19;j++)
				{
					if(out[j]==1)
					{
						if(piece.pos.x==-1+0.025/sqrt(3)+0.08*j*cos(M_PI/3) && piece.pos.y==-1+0.025+0.08*j*sin(M_PI/3))
						{
							piece.pos.x=0;
							piece.pos.y=-0.42267;
							out[j]=0;
						}
					}
				}
				if(j==19)
					cout<<"Player 'b' is out";
			}
			if(c==1)
			{
				score[2]--;
				for(;j<19;j++)
				{
					if(out[j]==1)
					{
						if(piece.pos.x==1-0.025/sqrt(3)-0.08*j*cos(M_PI/3) && piece.pos.y==-1+0.025+0.08*j*sin(M_PI/3))
						{
							piece.pos.x=0;
							piece.pos.y=-0.42267;
							out[j]=0;
						}
					}
				}
				if(j==19)
					cout<<"Player 'c' is out";
			}
		}
		else                                       //if coin is pocketed
		{
			if(a==1)
			{
				piece.pos.x=-0.9+0.08*i;
				piece.pos.y=-0.975;
				out[i]=1;
				if(piece.type==WHITE)
					score[0]+=2;
				else if(piece.type==BLACK)
					score[0]++;
				else if(piece.type==RED)
					score[0]+=5;
			}
			else if(b==1)
			{
				piece.pos.x=-1+0.025/sqrt(3)+0.05+0.08*i*cos(M_PI/3);
				piece.pos.y=-1+0.025+0.0866+0.08*i*sin(M_PI/3);
				out[i]=1;
				if(piece.type==WHITE)
					score[1]+=2;
				else if(piece.type==BLACK)
					score[1]++;
				else if(piece.type==RED)
					score[1]+=5;
			}
			else if(c==1)
			{
				piece.pos.x=1-0.025/sqrt(3)-0.05-0.08*i*cos(M_PI/3);
				piece.pos.y=-1+0.025+0.0866+0.08*i*sin(M_PI/3);
				out[i]=1;
				if(piece.type==WHITE)
					score[2]+=2;
				else if(piece.type==BLACK)
					score[2]++;
				else if(piece.type==RED)
					score[2]+=5;
				score[2]++;
			}
			count--;
		}
	}
}
//function to update the position
void gamestate_t::update()
{
  // TODO: 
	double vel1, vel[20];
	int flag1=0;
  // find out next position (using velocity)
	striker.vel.dx*=0.995;                                     //moving striker with friction
	striker.vel.dy*=0.995;
	striker.pos.x += striker.vel.dx;
	striker.pos.y += striker.vel.dy;
	for(int i=0; i<19; i++)                                    //moving coins with friction
	{
		if(out[i]==0)
		{
			coin[i].vel.dx*=0.996;
			coin[i].vel.dy*=0.996;
			coin[i].pos.x+=coin[i].vel.dx;
			coin[i].pos.y+=coin[i].vel.dy;
		}
	}
  // detect collision of striker and coins (may assume perfect collision)

	for(int i=0; i<19; i++)
	{
		if(out[i]==0)
		{
			striker_coin_collision(striker, coin[i]);
			for(int j=i+1; j<19; j++)
			{
				if(out[j]==0)
					coin_coin_collision(coin[i],coin[j]);
			}
		}
	}

  // detect collision with the board, and make the coins and striker bounce off the board
	
	striker_wall_collision(striker);
	for(int i=0; i<19; i++)
	{
		if(out[i]==0)
			coin_wall_collision(coin[i]);
	}
	
  // pocketing striker and coins
	pocketing_striker_or_coin(striker,-1);
	for(int i=0; i<19; i++)
	{
		if(out[i]==0)
			pocketing_striker_or_coin(coin[i],i);
	}
  //next turn
	vel1=sqrt(pow(striker.vel.dx,2)+pow(striker.vel.dy,2));
	if(vel1<0.0005)
		striker.vel.dx=striker.vel.dy=0;
	for(int i=0; i<19; i++)
	{
		if(out[i]==0)
		{
			vel[i]=sqrt(pow(coin[i].vel.dx,2)+pow(coin[i].vel.dy,2));
			if(vel[i]<0.0005)
				coin[i].vel.dx=coin[i].vel.dy=0;
		}
	}
	for(int i=0; i<19; i++)
	{
		if(out[i]==0)
		{
			if(vel[i]==0)
				flag1++;
		}
	}
	if(vel1==0)
		flag1++;
	if(collide==1 && flag1==count+1)
	{
		conti();
		collide=0;
	}
}

void gamestate_t::render_game() 
{
  // copy gamestate to renderstate for rendering
  g_rstate.copy_state();
  g_rstate.render();  
}

void gamestate_t::loopstep() 
{
  update();
  render_game();
}


void gamestate_t::c_loopstep() {
    g_gstate.loopstep();
}


