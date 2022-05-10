#pragma once

#include <iostream>
#include <string>

class ListaNumere
{

private:
	int dim, len;
	double* list;

public:
	ListaNumere();
	ListaNumere(int dim, int len, double* l);
	double* getList();
	void setList(double* list);
	int getDim();
	void setDim(int dim);
	int getLen();
	void setLen(int len);

	void Erase(int pos);
	void Insert(int pos, double el);
	static double calc(double x, char op, double y);

	double& operator[](int index);
	friend ListaNumere operator+(ListaNumere l, const double val);

	friend std::ostream& operator<<(std::ostream& os, ListaNumere& obj);
	friend std::istream& operator>>(std::istream& is, ListaNumere& obj);
};

