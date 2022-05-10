#include "ListaNumere.h"

ListaNumere::ListaNumere()
{
    dim = 100;
    len = 0;
    list = new double[100];
}

ListaNumere::ListaNumere(int dim, int len, double* l)
{
    this->dim = dim;
    this->len = len;
    list = new double[dim + 1];
    list = l;
}

double* ListaNumere::getList()
{
    return list;
}

void ListaNumere::setList(double* list)
{
    this->list = list;
}

int ListaNumere::getDim()
{
    return dim;
}

void ListaNumere::setDim(int dim)
{
    this->dim = dim;
    list = new double[this->dim + 1];
}

int ListaNumere::getLen()
{
    return len;
}

void ListaNumere::setLen(int len)
{
    this->len = len;
}

void ListaNumere::Erase(int pos)
{
    if (pos <= 0) pos = 0;
    if (pos > len) pos = len;
    for (int i = pos; i <= len; i++)
        list[i] = list[i + 1];

    len--;
}

void ListaNumere::Insert(int pos, double el)
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

double ListaNumere::calc(double x, char op, double y)
{
    switch (op)
    {
        case '+': return (x + y);
        case '-': return (x - y);
        case '*': return (x * y);
        case '/': return (y == 0 ? 0.0 : (x / y));
        case '^': return pow(x, y);
        case '#': return (y == 0 ? 0.0 : pow(x, 1.0 / y));
        default: return 0.0;
    }
}

double& ListaNumere::operator[](int index)
{
    return list[index];
}

ListaNumere operator+(ListaNumere l, const double val)
{
    l.Insert(l.len + 1, val);
    return l;
}

std::ostream& operator<<(std::ostream& os, ListaNumere& obj)
{
    os << obj.dim << " " << obj.len << "\n";
    for (int i = 1; i <= obj.len; i++)
        os << obj[i] << " ";
    os << "\n";
    return os;
}

std::istream& operator>>(std::istream& is, ListaNumere& obj)
{
    int dim, len;
    is >> dim >> len;
    double* l = new double[dim + 1];

    for (int i = 1; i <= len; i++)
    {
        double x;
        is >> x;
        l[i] = x;
    }

    obj.setDim(dim);
    obj.setLen(len);
    obj.setList(l);
    return is;
}