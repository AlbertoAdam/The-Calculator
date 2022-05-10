#pragma once
#include <iostream>

class ListaSimbol
{

private:
	int dim, len;
	char* list;

public:
	ListaSimbol();
	ListaSimbol(int dim, int len, char* l);
	char* getList();
	void setList(char* l);
	int getLen();
	void setLen(int len);
	int getDim();
	void setDim(int dim);
	char getSimbol(int pos);
	void setSimbol(int pos, char ch);

	void Erase(int pos);
	void Insert(int pos, char el);

	friend ListaSimbol operator-(ListaSimbol l, const int pos);
	ListaSimbol& operator=(ListaSimbol obj);

	friend std::ostream& operator<<(std::ostream& os, ListaSimbol& obj);
	friend std::istream& operator>>(std::istream& is, ListaSimbol& obj);

};

