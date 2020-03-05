#include <iostream>
#include <cmath>

using namespace std;

class fractie
{
private:
    int numarator, numitor;

public:
    fractie(int N = 0, int n = 0);      ///constructor de initializare
    fractie(const fractie &f);          ///constructor de copiere
    ~fractie();                         ///destructor

    void setare_numarator(int n);
    int furnizare_numarator();

    void setare_numitor(int n);
    int furnizare_numitor();

    void simplificare();

    void afisare();

    friend fractie operator +(fractie p, fractie q);
    friend fractie operator -(fractie p, fractie q);
    friend fractie operator *(fractie p, fractie q);
    friend fractie operator /(fractie p, fractie q);

    friend fractie operator *(fractie p, int q);

    friend istream &operator >>(istream &read, fractie &f);
    friend ostream &operator <<(ostream &write, fractie f);

    void citire(int n, fractie f[1000]);
    void afisare(int n, fractie f[1000]);
};

fractie::fractie(int N, int n)          ///initializare
{
    this->setare_numarator(N);
    this->setare_numitor(n);
}
fractie::fractie(const fractie &f)      ///copiere
{
    numarator = f.numarator;
    numitor = f.numitor;
}
fractie::~fractie()                     ///distrugere
{
    cout << "distrugere obiect ";
    afisare();
}

void fractie::setare_numarator(int n)
{
    numarator = n;
}
int fractie::furnizare_numarator()
{
    return numarator;
}

void fractie::setare_numitor(int n)
{
    numitor = n;
}
int fractie::furnizare_numitor()
{
    return numitor;
}

int cmmdc(int x, int y)
{
    while(x * y != 0)
        if(x > y)
            x %= y;
        else
            y %= x;
    return x + y;
}

void fractie::simplificare()
{
    int n, m, d;
    n = abs(numarator);
    m = abs(numitor);
    d = cmmdc(n, m);
    numarator /= d;
    numitor /= d;
}

void fractie::afisare()
{
    if(numitor < 0)
    {
        numarator = -numarator;
        numitor = -numitor;
    }
    if(numitor == 1)
        cout << numarator << "\n";
    else
        cout << numarator << "/" << numitor << "\n";
}

fractie operator +(fractie p, fractie q)
{
    fractie f(p.numarator * q.numitor + q.numarator * p.numitor, p.numitor * q.numitor);
    f.simplificare();
    return f;
}
fractie operator -(fractie p, fractie q)
{
    fractie f(p.numarator * q.numitor - q.numarator * p.numitor, p.numitor * q.numitor);
    f.simplificare();
    return f;
}
fractie operator *(fractie p, fractie q)
{
    fractie f(p.numarator * q.numarator, p.numitor * q.numitor);
    f.simplificare();
    return f;
}
fractie operator /(fractie p, fractie q)
{
    fractie f(p.numarator * q.numitor, p.numitor * q.numarator);
    f.simplificare();
    return f;
}

fractie operator *(fractie p, int q)
{
    fractie f(p.numarator * q, p.numitor);
    f.simplificare();
    return f;
}

istream &operator >>(istream &read, fractie &f)
{
    read >> f.numarator >> f.numitor;
    return read;
}
ostream &operator <<(ostream &write, fractie f)
{
    write << f.numarator << "/" << f.numitor;
    return write;
}

void citire(int n, fractie f[1000])
{
    int i;
    for(i = 0; i < n; i++)
    {
        if(i % 3 != 2)
            cout << "Dati coeficientul ecuatiei sub forma 'numarator numitor', cu numitorul diferit de 0: ";
        else
            cout << "Dati rezultatul ecuatiei sub forma 'numarator numitor', cu numitorul diferit de 0: ";
        operator>>(cin, f[i]);
        f[i].simplificare();
    }
}
void afisare(int n, fractie f[1000])
{
    int i;
    cout << n << "\n";
    for(i = 0; i < n; i++)
        f[i].afisare();
}

fractie det, dx, dy, x, y, f[6];

int main()
{
    citire(6, f);

    det = operator -(operator *(f[0], f[4]), operator *(f[1], f[3]));
    dx = operator -(operator *(f[2], f[4]), operator *(f[1], f[5]));
    dy = operator -(operator *(f[0], f[5]), operator *(f[2], f[1]));

    if(det.furnizare_numarator() != 0)
    {
        x = operator /(dx, det);
        y = operator /(dy, det);

        x.afisare();
        y.afisare();
    }

    return 0;
}
