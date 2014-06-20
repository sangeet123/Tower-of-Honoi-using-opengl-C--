

/* 
   @author: Sangeet Dahal
   Signature information of all the functions
   used for graphical visualization of the
   Tower of Hanoi
*/

#ifndef GRAPHICS
#define GRAPHICS

	void display_func();
	void keyboard();
	void timing();
	void draw_table(table&);
	void draw_plates_on_table(table &);
	void draw_plates(plates&);
	void initialize_table(table&, int);
	void animate_toh(table&, table&, table&, int);
	void place_plate(plates&, table&, table&);
	void draw_start_button();
	void mouse_click(int,int,int,int);
	void timing(int);
	void* helper_toh(void *);
	int total_no_of_plates(int,char**);
	void print_exit_mesg();

#endif
