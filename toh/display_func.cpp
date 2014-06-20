/*
  This file contains all the essential functions needed
  to animate the tower of honai puzzle problem. All the
  needed global flags and variable with its description
  is provided in the place where these flags are declared.
*/


#include<iostream>
#include<GL/glut.h>
#include <GL/freeglut.h>
#include <semaphore.h>
#include "vlegs.h"
#include "plates.h"
#include "table.h"
#define BITMAP GLUT_BITMAP_9_BY_15

const float PH=10; //Height of all plates
const float PL=100;
int vheight=0;//to keep track of initial lift of plates from its source table. Each moving plate it lifted by 100 units up first.
bool pmove=false;//is set to true when ever place_plate function is called for animation purpose
bool key = false;//key pressed is set to true when user presses start button
bool start = false;//start flag is set when user presses start button to start animation
bool stop = false;//stop flag is set when animation ends
plates flying;//plate which is currently moving
float dcx;//destination x-center of moving plate
float dcy;//destination y-center of moving plate
int t1;//t1 is -1 if plate has to move towards left else it is +1
sem_t an_mutex;//for holding the place_plate function until flying plate moves its destination position

	/* Timer event handler */
	void timing(int x){
			float tempx=flying.getcenterx();
			float tempy=flying.getcentery();
			
			if(vheight!=100){	/* Moving plates vertically up first */
				vheight+=5;
				flying.setcentery(5+tempy);
				glutTimerFunc(2,timing,0);
				glutPostRedisplay();
			}else if(tempx!=dcx){	/* Moving plates to the center of the destination table */
				flying.setcenterx(tempx+t1*5);
				glutTimerFunc(2,timing,0);
				glutPostRedisplay();
			}else if(tempy!=dcy){	/* Finally Aligning the plates to the center of the destination table */
				flying.setcentery(tempy-5);
				glutTimerFunc(2,timing,0);
				glutPostRedisplay();
			}else{
				pmove=false;
				sem_post(&an_mutex);
			}
	}


	/*Function used for placing plates form table to table*/
	void place_plate(plates &pl, table &ta, table &tb){
		float x1=tb.getfirstleg().getxcoord();
		float x2=tb.getsecondleg().getxcoord();
		float yc=tb.getfirstleg().getycoord()+tb.getfirstleg().getheight()+(PH/2);
		stack<plates,100> *p =tb.getstack();
		int nitems = p->get_no_of_items();
		yc+=nitems*PH;
		float xc=(x1+x2)/2;
		pmove=true;
		flying = pl;
		dcx=xc;
		dcy=yc;
		vheight=0;
		if(flying.getcenterx()>xc)t1=-1;
		else t1=1;
		glutTimerFunc(2,timing,0);
		sem_wait(&an_mutex);
		p->push(plates(pl.getlength(),pl.getheight(),xc,yc));
		glutPostRedisplay();
	}

	/* Function used for animating */
	void animate_toh(table& t1, table& t2, table& t3, int n){
		while(!start);
		if(n==0)return;
	try{
		if(n==1){
			stack<plates,100> *p =t1.getstack();
			plates pl = p->pop();
			place_plate(pl,t1,t3);
		}else{
			animate_toh(t1, t3, t2, n-1);
			stack<plates,100> *p =t1.getstack();
			plates pl = p->pop();
			place_plate(pl,t1,t3);
			animate_toh(t2,t1,t3,n-1);
		}
	}catch(char const *s){
		std::cout<<s<<std::endl;
	}

	}


	/* Initialize the initial state of table 1*/
	void initialize_table(table &t, int n){
		float x1=t.getfirstleg().getxcoord();
		float x2=t.getsecondleg().getxcoord();
		float yc=t.getfirstleg().getycoord()+t.getfirstleg().getheight()+(PH/2);
		
		
		float xc=(x1+x2)/2;

		try{
			stack<plates,100> *p =t.getstack();
			for(int i=0;i<n;i++){
				p->push(plates(PL-i*10,PH,xc,yc+i*PH));
			}				

		}catch(char const *s){
			std::cout<<s<<std::endl;
		}
	}

	/* This function draws plates */
	void draw_plates(plates &p){
		float cx=p.getcenterx();
		float cy=p.getcentery();
		float l=p.getlength();
		float h=p.getheight();
		glBegin(GL_QUADS);
		glColor3f(0,1,0);
		glVertex3f(cx-l/2,cy-h/2,0);
		glColor3f(0,1,1);
		glVertex3f(cx+l/2,cy-h/2,0);
		glColor3f(1,1,0);
		glVertex3f(cx+l/2,cy+h/2,0);
		glColor3f(0,0,1);
		glVertex3f(cx-l/2,cy+h/2,0);
		glEnd();

	}
	
	/*This function draws plates on the table */
	void draw_plates_on_table(table &t){
		
		try{
			stack<plates,100> *s =t.getstack();
			stack<plates,100> temp;

			while(!s->IsEmpty()){
				temp.push(s->pop());
			}

			while(!temp.IsEmpty()){
				plates p = temp.pop();
				draw_plates(p);
				s->push(p);
			}
		}catch(char const *str){
			std::cout<<str<<std::endl;
		}


	}

	/* Function to draw legs of table */
	void draw_legs(const vlegs &l){
		float x=l.getxcoord();
		float y=l.getycoord();
		float h=l.getheight();
		glColor3f(1,0,0);
		glLineWidth(3);
		glBegin(GL_LINES);
		glVertex3f(x,y,0);
		glVertex3f(x,y+h,0);
		glEnd();
		glLineWidth(1);
	}

	/* Function to draw upper surface of table */
	void draw_surface(float x, float y){
		glColor3f(1,0,0);
		glLineWidth(3);
		glBegin(GL_LINES);
		glVertex3f(x-2,y,0);
		glVertex3f(x+TW+1,y,0);
		glEnd();
		glLineWidth(1);
	}

	/* Function that draws table */
	void draw_table(table &t){
		draw_legs(t.getfirstleg());
		draw_legs(t.getsecondleg());
		float x=t.getfirstleg().getxcoord();
		float y=t.getfirstleg().getycoord()+t.getfirstleg().getheight();
		draw_surface(x,y);

	}

	/* Draw the start button on screen */
	void draw_start_button(){
		const unsigned char p[] = "START";
		glColor3f(1.0,1.0,0.0);
		glRasterPos3d(540,580,0);
		glutBitmapString(BITMAP,p);
		glBegin(GL_LINE_LOOP);
		glVertex3f(535,575,0);
		glVertex3f(588,575,0);
		glVertex3f(588,595,0);
		glVertex3f(535,595,0);
		glEnd();
	}

	/* This function prints the exit mesg */
	void print_exit_mesg(){
		const unsigned char p[] = "Thank You For Your Patience";
		glColor3f(1.0,1.0,0.0);
		glRasterPos3d(200,500,0);
		glutBitmapString(BITMAP,p);
		const unsigned char q[]="Did You See how Visualization Can Make Things Simpler?????";
		glRasterPos3d(70,485,0);
		glutBitmapString(BITMAP,q);
	}

	/* Mouse Click Event Handler */
	void mouse_click(int button,int state,int x,int y) {

		if(!start){
  			if(state!=GLUT_DOWN && button==GLUT_LEFT_BUTTON){
				if(x>=535 && x<=588 && y>=5 && y<=25){				
					key=true;
					start=true;
					glutPostRedisplay();
				}
			}
		}	
	}

	/* This is the main display function which is called when program starts */
	void display_func(){
		extern table t[3];
		glClear(GL_COLOR_BUFFER_BIT);
		draw_start_button();

			for(int i=0;i<3;i++){
				draw_table(t[i]);
				draw_plates_on_table(t[i]);
				if(pmove)
					draw_plates(flying);
				if(stop)
					print_exit_mesg();
			}
					
		glutSwapBuffers();
	}

