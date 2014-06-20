#include<iostream>
#include<cstring>
#include<GL/glut.h>
#include<GL/freeglut.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include"my_setup_3D.h"
#include"table.h"
#include"vlegs.h"
#include"plates.h"
#include"graphics.h"


#define canvas_Width 600
#define canvas_Height 600
#define canvas_Name "Tower of Honoi"
#define BITMAP GLUT_BITMAP_9_BY_15

using namespace std;

int table::ntables=0;
table t[3];

	int main(int argc, char** argv){
		extern sem_t an_mutex; /* semaphore define in display_func.cpp file */
		pthread_t thread_toh; /*Thread that calls helper_toh for animating tower of hanoi*/
		int n = total_no_of_plates(argc,argv);/* Total number of plates */
		if(n==-1 || n>10){
			cout<<"Invalid number of plates"<<endl;
			cout<<"Support only upto 10 plates"<<endl;
			exit(0);
		}
		glutInit(&argc,argv);
		my_setup(canvas_Width,canvas_Height,canvas_Name);
		sem_init(&an_mutex,0,0);/* Initializing semaphore */
		initialize_table(t[0],n);/* Initialize first table to have n number of plates */
		glutDisplayFunc(display_func);/* Registering display event handler */
		//glutTimerFunc(15,timing,4);/* Registering timer event handler */
		glutMouseFunc(mouse_click);/* Registering mouse click event handler */
		int r = pthread_create(&thread_toh,NULL,helper_toh,NULL); /* creating helper thread for animation toh */

		if (r){
		         cout<<"ERROR; return code from pthread_create() is "<<r;
	         	 exit(0);
	         }
		
		glutMainLoop();/* Main event loop handler by main thread */
		pthread_join(thread_toh,NULL);
		return 0;
	}

	/* Function returns total number of plates */
	int total_no_of_plates(int argc, char **argv){
		for(int i=0;i<argc;i++){			
			if(!strcmp(argv[i],"-nplates"))
				return atoi(argv[i+1]);
		}

		return -1;
	}

	/* Helper function that calls recursive implementation of the famous puzzle The Tower of Hanoi */
	void* helper_toh(void *){
		extern bool stop;
		extern bool start;
		animate_toh(t[0], t[1], t[2], t[0].getstack()->get_no_of_items());
		stop=true;
		glutPostRedisplay();
		return NULL;
	}
