#pragma once
#ifndef TREE_H
#define TREE_H
#include <stdio.h>   
#include <stdlib.h>

class Node {
};

template <class Elem> class List :public Node {
public:
	virtual Elem nth_length(int n, int &len) = 0;
	virtual int len() = 0;

};

template <class Elem> class nil_node : public List<Elem> {
public:
	int len() {
		return 0;
	}
	Elem nth_length(int n, int &len) {
		len = 0;
		return NULL;
	}
};

template <class Elem> class single_node : public List<Elem> {
	
public:
	Elem elem;
	single_node(Elem t) {
		elem = t;
	}
	int len() {
		return 1;
	}
	Elem nth_length(int n, int &len) {
		len = 1;
		if (n)
			return NULL;
		else
			return elem;
	}
};

template <class Elem> class append_node : public List<Elem> {

public:
	List<Elem> *some, *rest;
	append_node(List<Elem> *l1, List<Elem> *l2) {
		some = l1;
		rest = l2;
	}
	int len() {
		return some->len() + rest->len();
	}
	Elem nth_length(int n, int &len) {
		int rlen;
		Elem tmp = some->nth_length(n, len);
		if (!tmp) {
			tmp = rest->nth_length(n - len, rlen);
			len += rlen;
		}
		return tmp;
	}
};

#endif
