#include "ListaSimbol.h"

ListaSimbol::ListaSimbol()
{
	dim = 100;
	len = 0;
	list = new char[dim + 1];
}

ListaSimbol::ListaSimbol(int dim, int len, char* l)
{
    this->dim = dim;
    this->len = len;
    list = new char[dim + 1];
    list = l;
}

char* ListaSimbol::getList()
{
    return list;
}

void ListaSimbol::setList(char* l)
{
    list = l;
}

int ListaSimbol::getLen()
{
    return len;
}

void ListaSimbol::setLen(int len)
{
    this->len = len;
}

int ListaSimbol::getDim()
{
    return dim;
}

void ListaSimbol::setDim(int dim)
{
    this->dim = dim;
    list = new char[dim + 1];
}

char ListaSimbol::getSimbol(int pos)
{
    return list[pos];
}

void ListaSimbol::setSimbol(int pos, char ch)
{
    list[pos] = ch;
}

void ListaSimbol::Erase(int pos)
{
    if (pos <= 0) pos = 0;
    if (pos > len) pos = len;
    for (int i = pos; i <= len; i++)
        list[i] = list[i + 1];

    len--;
}

void ListaSimbol::Insert(int pos, char el)
{
    if (len + 1 == dim)
        return;

    if (pos <= 0)
        return;

    len++;
    for (int i = len; i > pos; i--)
        list[i] = list[i - 1];
    list[pos] = el;
}

ListaSimbol& ListaSimbol::operator=(ListaSimbol obj)
{
    std::swap(dim, obj.dim);
    std::swap(len, obj.len);
    std::swap(list, obj.list);
    return *this;
}

ListaSimbol operator-(ListaSimbol l, const int pos)
{
    l.Erase(pos);
    return l;
}

std::ostream& operator<<(std::ostream& os, ListaSimbol& obj)
{
    os << obj.dim << " " << obj.len << "\n";
    for (int i = 1; i <= obj.len; i++)
        os << obj.list[i] << " ";
    os << "\n";
    return os;
}

std::istream& operator>>(std::istream& is, ListaSimbol& obj)
{
    int d, t;
    is >> d >> t;
    obj.setDim(d);
    obj.setLen(t);

    char* s = new char[d + 1];
    for (int i = 1; i <= t; i++)
    {
        char x;
        is >> x;
        s[i] = x;
    }

    obj.setList(s);
    return is;
}