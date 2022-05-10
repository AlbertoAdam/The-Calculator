#include "Evaluator.h"

const char* Evaluator::semne = "[]()+-*/^#";

Evaluator::Evaluator()
{
	ecuatie = new char[100];
}

Evaluator::Evaluator(const char* ec)
{
	ecuatie = new char[strlen(ec)];
	for (int i = 0; ec[i]; i++)
		ecuatie[i] = ec[i];
	ecuatie[strlen(ec)] = '\0';
}

char* Evaluator::getEcuatie()
{
	return ecuatie;
}

void Evaluator::setLn(ListaNumere ln)
{
	this->ln.setDim(ln.getDim());
	this->ln.setLen(ln.getLen());
	this->ln.setList(ln.getList());
}

void Evaluator::setEcuatie(const char* ec)
{
	ecuatie = new char[strlen(ec)];
	for (int i = 0; ec[i]; i++)
		ecuatie[i] = ec[i];
}

ListaNumere Evaluator::getLn()
{
	return ln;
}

void Evaluator::setLs(ListaSimbol ls)
{
	this->ls.setDim(ls.getDim());
	this->ls.setLen(ls.getLen());
	this->ls.setList(ls.getList());
}

ListaSimbol Evaluator::getLs()
{
	return ls;
}

void Evaluator::CreazaListe()
{
	int i = 0, j = 0;
	char* str = new char[strlen(ecuatie) + 1];
	

	for (i = 0; ecuatie[i]; i++)
		str[i] = ecuatie[i];
	str[i] = '\0';

	i = 0;
	while (str[i])  //scot spatii albe
	{
	    if (str[i] != ' ')
	        str[j++] = str[i];
	    i++;
	}
	str[j] = '\0';
	
	for (int i = 0; str[i]; i++)
		if (strchr(semne, str[i]) == NULL && !isdigit(str[i]) && str[i] != '.')
		{
			error = true;
			strcpy_s(err, "Caractere invalide");
			return;
		}

	int dimln = 0, dimls = 0;
	for (i = 0; str[i]; i++)
	    if (strchr(semne, str[i]) != NULL)
		{
			dimls++;
			if(str[i] != '(' && str[i] != ')' 
				&& str[i] != '[' && str[i] != ']') dimln++;
		}
	
	dimln++;
	ln.setDim(dimln + 1);
	ls.setDim(dimls + 1);

	for (i = 0; str[i]; i++)
		if (strchr(semne, str[i]) != NULL)
			ls.Insert(ls.getLen() + 1, str[i]);

	char* p, *smth;
	p = strtok_s(str, semne, &smth);
	i = 0;
	while (p != NULL)
	{
		ln = ln + atof(p);
	    p = strtok_s(NULL, semne, &smth);
	}
}

void Evaluator::addsub(int l, int r, int lsign)
{
	int nr = r - l;
	int j = l;

	for (int i = lsign; nr--; i++, j++)
	{
		char s = ls.getSimbol(i);
		if (s == '+' || s == '-')
		{
			double x = ListaNumere::calc(ln[j], s, ln[j + 1]);
			ls = ls - i;
			ln.Erase(j + 1);
			ln[j] = x;
			i--;
			j--;
		}
	}

}

void Evaluator::muldiv(int l, int r, int lsign)
{
	int find = 0;
	int nr = r - l;
	int j = l;

	for (int i = lsign; nr--; i++, j++)
	{
		char s = ls.getSimbol(i);

		if (s == '*' || s == '/')
		{
			if (ln[j + 1] == 0 && s == '/')
			{
				strcpy_s(err, "Apare impartire la 0");
				error = true;
				return;
			}

			find++;
			double x = ListaNumere::calc(ln[j], s, ln[j + 1]);
			ls = ls - i;
			ln.Erase(j + 1);
			ln[j] = x;
			i--;
			j--;
			
		}
	}

	addsub(l, r - find, lsign);
}

void Evaluator::powsqr(int l, int r, int lsign)
{
	int find = 0;
	int nr = r - l;
	int j = l;

	for (int i = lsign; nr--; i++, j++)
	{
		char s = ls.getSimbol(i);
		if (s == '#' || s == '^')
		{
			find++;
			if (ln[j + 1] == 0 && s == '#')
			{
				strcpy_s(err, "Apare radical de ordin 0");
				error = true;
				return;
			}

			double x = ListaNumere::calc(ln[j], s, ln[j + 1]);
			ls = ls - i;
			ln.Erase(j + 1);
			ln[j] = x;
			i--;
			j--;
		}
	}
	muldiv(l, r - find, lsign);
}

double Evaluator::Evalueaza()
{
	if (error) return 0.0;

	int top = 0;
	int* stiva = new int[ls.getDim()];

	for (int i = 1; i <= ls.getLen(); i++)
	{
		char x = ls.getSimbol(i);

		if (x == '(' || x == '[')stiva[++top] = i;
		else if (x == ')')
		{
			if (ls.getSimbol(stiva[top]) == '(')
			{
				powsqr(stiva[top] - top + 1, i - top, stiva[top] + 1);
				ls = ls - (stiva[top] + 1);
				ls = ls - stiva[top];
				i -= (i - stiva[top] + 1);
				top--;
			}
			else
			{
				error = true;
				strcpy_s(err, "Expresia nu este parantezata corect");
				return 0.0;
			}
		}
		else if (x == ']')
		{
			if (ls.getSimbol(stiva[top]) == '[')
			{
				powsqr(stiva[top] - top + 1, i - top, stiva[top] + 1);
				ls = ls - (stiva[top] + 1);
				ls = ls - stiva[top];
				i -= (i - stiva[top] + 1);
				top--;
			}
			else
			{
				error = true;
				strcpy_s(err, "Expresia nu este parantezata corect");
				return 0.0;
			}
		}
	}


	powsqr(1, ln.getLen(), 1);
	if (error) return 0.0;

	return ln[1];
}

bool Evaluator::operator!()
{
	return error;
}

Evaluator::operator const char* ()
{
	return err;
}

std::ostream& operator<<(std::ostream& os, Evaluator& obj)
{
	os << obj.ecuatie << "\n";
	os << obj.ln << "\n";
	os << obj.ls << "\n";

	return os;
}

std::istream& operator>>(std::istream& is, Evaluator& obj)
{
	std::string s;
	std::getline(is, s);
	obj.setEcuatie(s.c_str());
	
	return is;
}