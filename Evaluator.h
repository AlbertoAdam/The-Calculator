#pragma once
#include <iostream>
#include <string>
#include "ListaSimbol.h"
#include "ListaNumere.h"

class Evaluator
{

private:
	bool error = false;
	char* ecuatie, err[100];
	static const char* semne;
	ListaNumere ln;
	ListaSimbol ls;

public:
	Evaluator();
	Evaluator(const char *ec);

	void setEcuatie(const char* ec);
	char* getEcuatie();
	void setLn(ListaNumere ln);
	ListaNumere getLn();
	void setLs(ListaSimbol ls);
	ListaSimbol getLs();

	void CreazaListe();
	void addsub(int l, int r, int lsign);
	void muldiv(int l, int r, int lsign);
	void powsqr(int l, int r, int lsign);
	double Evalueaza();

	bool operator!();
	operator const char*();

	friend std::ostream& operator<<(std::ostream& os, Evaluator& obj);
	friend std::istream& operator>>(std::istream& is, Evaluator& obj);
};

