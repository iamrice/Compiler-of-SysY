#pragma once
#ifndef STRINGTAB_H
#define STRINGTAB_H

#include <stdlib.h>
#include <stdio.h>   
#include<cstring>
#define min(a,b) (a > b ? b : a)


template <class T>
class symbolList {

public:
	T *head;
	symbolList<T>* tail;
	symbolList(T *h, symbolList<T>* t = NULL) : head(h), tail(t) { }
	T *hd() const { return head; }
	symbolList<T>* tl() const { return tail; }
};

class Entry;
typedef Entry* Symbol;

class Entry {
public:
	char *str;     // the string
	int index;
	int  len;
	Entry(char *s, int l, int i) : str(s), len(l), index(i) {}
	int equal_string(char *s, int len) const {
		if (this->len != len)return 0;
		for (int i = 0; i < len; i++) {
			if (s[i] != str[i])
				return 0;
		}
		return 1;
	}
	bool equal_index(int ind) const { return ind == index; }

};



class IdEntry : public Entry {
public:
	IdEntry(char *s, int l, int i) : Entry(s, l, i) {}
};

class IntEntry : public Entry {
public:
	IntEntry(char *s, int l, int i) : Entry(s, l, i) {}
};

template <class Elem>
class StringTable
{
public:
	symbolList<Elem> *tbl;
	int index;

	StringTable() : tbl((symbolList<Elem> *) NULL), index(0) { }
	Elem *add_string(char *s, int maxchars = 100000) {
		int len = min((int)strlen(s), maxchars);
		for (symbolList<Elem> *l = tbl; l; l = l->tl())
			if (l->hd()->equal_string(s, len))
				return l->hd();

		Elem *e = new Elem(s, len, index++);
		tbl = new symbolList<Elem>(e, tbl);
		return e;
	}



	Elem *lookup_string(char *s) {
		int len = strlen(s);
		for (symbolList<Elem> *l = tbl; l; l = l->tl())
			if (l->hd()->equal_string(s, len))
				return l->hd();
		return NULL; // to avoid compiler warning
	}


};

class IdTable : public StringTable<IdEntry> { };

class IntTable : public StringTable<IntEntry>
{};

extern IdTable idtable;
extern IntTable inttable;


#endif // !STRINGTAB_H
