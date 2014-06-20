
#ifndef STACK
#define STACK

	template <class T, size_t N=50>
	class stack{
		private:
			int size;
			int top;
			T data[N];

		public:
			stack():size(N),top(-1){}
			bool IsEmpty();
			bool IsFull();
			void incrementtop(){++top;}
			void decrementtop(){--top;}
			int get_no_of_items(){return top+1;}
			T pop();
			void push(T data);
			~stack(){}
	};

	/* Checks if stack is empty*/
	template <class T, size_t N>
	bool stack<T,N>::IsEmpty(){
		return top==-1;
	}

	/* Checks if stack is full*/
	template <class T, size_t N>
	bool stack<T,N>::IsFull(){
		return top==size-1;
	}

	/* pops item from the stack*/
	template <class T, size_t N>
	T stack<T,N>::pop(){
		if(!(this->IsEmpty())){
		T temp = data[top];
		this->decrementtop();
		return temp;
		}else{
			throw "Empty Stack"; //throws string "Empty Stack" if stack if empty
		}
	}

	/* Push item into the stack */
	template<class T, size_t N>
	void stack<T,N>::push(T dat){
		if(!(this->IsFull())){
			this->incrementtop();
			data[top]=dat;
		}else{
			throw "Full Stack"; //throws string "Full Stack" if stack if full
		}
	}
#endif
