/*
 * shptr.h
 *
 *  Created on: Jul 3, 2018
 *      Author: ballance
 */
#pragma once
#include <memory>

template <class T> class shptr : public std::shared_ptr<T> {
public:
	shptr(T *p) : std::shared_ptr<T>(p) { }

	T *get() const { return std::shared_ptr<T>::get(); }

};

