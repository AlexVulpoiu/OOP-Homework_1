#include <iostream>
#include <cmath>

using namespace std;

class fractie
{
private:
    int numarator, numitor;

public:
    explicit fractie(int N = 0, int n = 1);      ///constructor de initializare
    fractie(const fractie &f);                   ///constructor de copiere
    ~fractie();                                  ///destructor

    void setare_numarator(int n);
    int furnizare_numarator();

    void setare_numitor(int n);
    int furnizare_numitor();

    void simplificare();

    void afisare();

    friend fractie operator +(const fractie &p, const fractie &q);
    friend fractie operator -(const fractie &p, const fractie &q);
    friend fractie operator *(const fractie &p, const fractie &q);
    friend fractie operator /(const fractie &p, const fractie &q);

    friend fractie operator *(const fractie &p, int q);

    friend istream &operator >>(istream &read, fractie &f);
    friend ostream &operator <<(ostream &write, const fractie &f);
};

fractie::fractie(int N, int n): numarator{N}, numitor{n} {}       ///initializare

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

fractie operator +(const fractie &p, const fractie &q)
{
    fractie f(p.numarator * q.numitor + q.numarator * p.numitor, p.numitor * q.numitor);
    f.simplificare();
    return f;
}

fractie operator -(const fractie &p, const fractie &q)
{
    fractie f(p.numarator * q.numitor - q.numarator * p.numitor, p.numitor * q.numitor);
    f.simplificare();
    return f;
}

fractie operator *(const fractie &p, const fractie &q)
{
    fractie f(p.numarator * q.numarator, p.numitor * q.numitor);
    f.simplificare();
    return f;
}

fractie operator /(const fractie &p, const fractie &q)
{
    fractie f(p.numarator * q.numitor, p.numitor * q.numarator);
    f.simplificare();
    return f;
}

fractie operator *(const fractie &p, int q)
{
    fractie f(p.numarator * q, p.numitor);
    f.simplificare();
    return f;
}

istream &operator >>(istream &read, fractie &f)
{
    read >> f.numarator >> f.numitor;
    f.simplificare();
    return read;
}

ostream &operator <<(ostream &write, const fractie &f)
{
    if(f.numitor == 1)
        write << f.numarator << "\n";
    else
        if(f.numitor == -1)
            write << -f.numarator << "\n";
        else
            if(f.numitor < 0)
                write << -f.numarator << "/" << -f.numitor << "\n";
            else
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
        cin >> f[i];
    }
}

void afisare(int n, fractie f[1000])
{
    int i;
    cout << n << "\n";
    for(i = 0; i < n; i++)
        f[i].afisare();
}

int main()
{
    fractie det, dx, dy, f[6];

    citire(6, f);

    det = f[0] * f[4] - f[1] * f[3];
    dx = f[2] * f[4] - f[1] * f[5];
    dy = f[0] * f[5] - f[2] * f[3];

    if(det.furnizare_numarator() != 0)
    {
        cout << "x = " << dx / det << "\n";
        cout << "y = " << dy / det << "\n";
    }
    else
        if(f[0].furnizare_numarator() != 0 || f[3].furnizare_numarator() != 0)
            if(dy.furnizare_numarator() == 0)
                cout << "sistemul are o infinitate de solutii\n";
            else
                cout << "sistemul este incompatibil\n";
        else
            if(f[1].furnizare_numarator() != 0 || f[4].furnizare_numarator() != 0)
                if(dx.furnizare_numarator() == 0)
                    cout << "sistemul are o infinitate de solutii\n";
                else
                    cout << "sistemul este incompatibil\n";
            else
                cout << "sistemul este incompatibil\n";

    return 0;
}
