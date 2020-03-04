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
int cmmmc(int x, int y)
{
    return x * y / cmmdc(x, y);
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

int m, i;
fractie x, y, f[6];

int main()
{
    citire(6, f);

    f[0].setare_numarator(f[0].furnizare_numarator() * f[3].furnizare_numitor());
    f[0].setare_numitor(f[0].furnizare_numitor() * f[3].furnizare_numitor());

    f[3].setare_numarator(f[3].furnizare_numarator() * f[0].furnizare_numitor());
    f[3].setare_numitor(f[3].furnizare_numitor() * f[0].furnizare_numitor());
    ///coeficientii lui x din cele 2 ecuatii au acelasi numitor

    m = cmmmc(f[0].furnizare_numarator(), f[3].furnizare_numarator());
    ///multiplul comun al numaratorilor de la coeficientii lui x

    for(i = 2; i >= 0; i--)
        f[i] = operator *(f[i], m / f[0].furnizare_numarator());
    for(i = 5; i >= 3; i--)
        f[i] = operator *(f[i], -m / f[3].furnizare_numarator());
    ///parcurgem in sens invers pentru ca altfel s-ar modifica numaratorul de la f[0], respectiv f[3] prea devreme
    ///coeficientii lui x din cele 2 ecuatii au suma 0, deci putem afla y

    y = operator /(operator +(f[2], f[5]), operator +(f[1], f[4]));
    x = operator /(operator -(f[2], operator *(f[1], y)), f[0]);
    ///aflam x si y

    x.afisare();
    y.afisare();

    return 0;
}
