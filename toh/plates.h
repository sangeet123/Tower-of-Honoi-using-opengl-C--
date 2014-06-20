/*
  Plates class
*/

#ifndef PLATES
#define PLATES

	class plates{
		private:
			float l;
			float h;
			float cx;
			float cy;
		public:
			plates(){}
			plates operator =(plates &q)
			{
				l=q.l;
				h=q.h;
				cx=q.cx;
				cy=q.cy;
				return *this;
			}
			plates(float x, float y,float ccx, float ccy):l(x),h(y),cx(ccx),cy(ccy){}
			plates(const plates &p1):l(p1.l),h(p1.h),cx(p1.cx),cy(p1.cy){}
			void setlength(float x){l=x;}//set length of plate
			void setheight(float y){h=y;}//set height of plate
			void setcenterx(float ccx){cx=ccx;}//set x-coord center of plate 
			void setcentery(float ccy){cy=ccy;}//set y-coord center of plate
			float getlength() const{return l;}//returns length of plate
			float getheight() const{return h;}//returns height of plate
			float getcenterx()const{return cx;}//returns x-coord center of plate
			float getcentery()const{return cy;}//returns y-coord center of plate
			/* For debugging purpose only */
			friend std::ostream& operator << (std::ostream& out, plates &p){
				out<<"cx="<<p.cx<<"cy="<<p.cy<<"l="<<p.l<<"h="<<p.h<<std::endl;
				return out;
			}
			~plates(){}
	};
#endif

		
