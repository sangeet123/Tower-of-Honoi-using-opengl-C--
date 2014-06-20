/*
 Legs class
*/

#ifndef VLEGS
#define VLEGS

	class vlegs{
		private:
			float ox;
			float oy;
			float h;
		public:
			vlegs(float x, float y, float hh):ox(x),oy(y),h(hh){}
			float getxcoord() const{return ox;}//returns leg x-coordinate
			float getycoord() const{return oy;}//return leg y-coordinate 
			float getheight() const{return h;}//return height of leg
			~vlegs(){}
	};
#endif

	
		

