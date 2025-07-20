// Pomocna.h
#ifndef POMOCNAH
#define POMOCNAH

#include <vector>
#include <Vcl.Graphics.hpp>
#include <cmath>
using namespace std;

struct Tacka {
    int x, y;
    Tacka(int x = 0, int y = 0) : x(x), y(y) {}
    void Crtaj(TImage* slika, TColor boja = clRed) const;
};

bool operator<(const Tacka& A, const Tacka& B);
bool operator==(const Tacka& A, const Tacka& B);

struct Kruznica {
    Tacka centar;
    double r;
    Kruznica(Tacka c, double r = 20) : centar(c), r(r) {}
    void Crtaj(TImage* slika) const;
};

struct Event {
	double x;
	int kruznicaId;
	bool isLeft;
	Event(double x, int id, bool left) : x(x), kruznicaId(id), isLeft(left) {}
	bool operator<(const Event& e) const {
		if (x != e.x) return x < e.x;
		return isLeft > e.isLeft;
	}
};

double Ygornja(const Kruznica& k, double x);
double Ydonja(const Kruznica& k, double x);

struct AktivniUporedi {
	double x;
	const vector<Kruznica>* kruznice;

	AktivniUporedi(double _x, const vector<Kruznica>* k) : x(_x), kruznice(k) {}

	bool operator()(int id1, int id2) const {
		double y1 = Ygornja((*kruznice)[id1], x);
		double y2 = Ygornja((*kruznice)[id2], x);
		if (fabs(y1 - y2) > 1e-9)
			return y1 < y2;
		return id1 < id2;
	}
};

std::vector<std::pair<int, int>> SweepLineAlgoritam(const std::vector<Kruznica>& kruznice);
std::vector<Tacka> IzracunajPresjek(const Kruznica& k1, const Kruznica& k2);

void CrtajPresjeke(TImage* slika, const std::vector<Kruznica>& kruznice);

#endif // POMOCNAH

