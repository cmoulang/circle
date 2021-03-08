///*
// * Cyclic.h
// *
// *  Created on: Apr 26, 2020
// *      Author: chris
// */

#ifndef CYCLIC_H_
#define CYCLIC_H_

#include <circle/types.h>

template<typename T, int size>
class CCyclic {

public:
	CCyclic();
	~CCyclic();
	void Enqueue(T);
	T Dequeue(int&);
	boolean IsEmpty(int);
private:
	int IncIndex(int);
	volatile int nextin { 0 };
	T buff[size];
};

template<typename T, int size>
CCyclic<T, size>::CCyclic() {
}

template<typename T, int size>
CCyclic<T, size>::~CCyclic() {

}

template<typename T, int size>
int CCyclic<T, size>::IncIndex(int index) {
	return (index+1 == size) ? 0 : index+1;
}

template<typename T, int size>
void CCyclic<T, size>::Enqueue(T data) {
	buff[nextin] = data;
	nextin = IncIndex(nextin);
}

template<typename T, int size>
boolean CCyclic<T, size>::IsEmpty(int nextout) {
	return nextin == nextout;
}

template<typename T, int size>
T CCyclic<T, size>::Dequeue(int &nextout) {
	while (nextin == nextout) {
		// Spin waiting for nextin to be updated by another
		// thread or interrupt handler.
	}
	T retval = buff[nextout];
	nextout = IncIndex(nextout);
	return retval;
}

#endif /* CYCLIC_H_ */
