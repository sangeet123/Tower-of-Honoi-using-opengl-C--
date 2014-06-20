#include "vlegs.h"
#include "plates.h"
#include "stack.h"

#define TX 50 
#define TY 150
#define TW 140
#define TH 100
#define GAP 50


#ifndef TABLE
#define TABLE

	class table{
		private:
			int id;//Each table has unique id
			vlegs l1;//The first visible leg
			vlegs l2;//The second visible leg
			stack<plates,100> s;//Each table has stack of plates

		public:
			static int ntables;
			table():l1(TX+(TW+GAP)*ntables,TY,TH),
				     l2(TX+TW+ntables*(TW+GAP),TY,TH){
						id=ntables;//Table id is given unique number 0, 1, or 2
						ntables++;//After construction of each table ntables is incremented
					}
			const vlegs& getfirstleg() const{return l1;}//returns reference to first leg
			const vlegs& getsecondleg() const{return l2;}//return reference to second leg
			stack<plates,100>* getstack(){return &s;}//return reference to stack
			int getid() const{return id;}
			~table(){}
	};
#endif

		
