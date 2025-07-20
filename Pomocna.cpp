#include "Pomocna.h"
#include <algorithm>
#include <set>
#include <cmath>
#include <iterator>
using namespace std;


double currX = 0;

void Tacka::Crtaj(TImage* Slika, TColor boja) const {
	int vel = 4;
	Slika->Canvas->Brush->Color = boja;
	Slika->Canvas->Ellipse(x - vel, y - vel, x + vel, y + vel);
	Slika->Canvas->Brush->Color = clWhite;
}

bool operator<(const Tacka& A, const Tacka& B) {
	if (A.x != B.x) return A.x < B.x;
	return A.y < B.y;
}

bool operator==(const Tacka& A, const Tacka& B) {
	return A.x == B.x && A.y == B.y;
}

void Kruznica::Crtaj(TImage* Slika) const {
	Slika->Canvas->Pen->Color = clBlue;
	Slika->Canvas->Brush->Style = bsClear;
	Slika->Canvas->Ellipse(centar.x - r, centar.y - r, centar.x + r, centar.y + r);
}

double Ygornja(const Kruznica& k, double x) {
	double dx = x - k.centar.x;
	return k.centar.y - sqrt(k.r * k.r - dx * dx);
}

double Ydonja(const Kruznica& k, double x) {
	double dx = x - k.centar.x;
	return k.centar.y + sqrt(k.r * k.r - dx * dx);
}

bool SeSijeku(const Kruznica& a, const Kruznica& b) {
	double dx = a.centar.x - b.centar.x;
	double dy = a.centar.y - b.centar.y;
	double d = sqrt(dx * dx + dy * dy);
	if (d > a.r + b.r) return false;
	if (d < fabs(a.r - b.r)) return false;
	return true;
}

vector<Tacka> IzracunajPresjek(const Kruznica& A, const Kruznica& B) {
	vector<Tacka> tacke;
	double dx = B.centar.x - A.centar.x;
	double dy = B.centar.y - A.centar.y;
	double d = sqrt(dx * dx + dy * dy);

	if (d > A.r + B.r + 1e-9 || d < fabs(A.r - B.r) - 1e-9) return tacke;

	double a = (A.r * A.r - B.r * B.r + d * d) / (2 * d);
	double h = sqrt(A.r * A.r - a * a);

	double xm = A.centar.x + a * dx / d;
	double ym = A.centar.y + a * dy / d;

	double xs1 = xm + h * dy / d;
	double ys1 = ym - h * dx / d;

	double xs2 = xm - h * dy / d;
	double ys2 = ym + h * dx / d;

	tacke.emplace_back((int)(xs1 + 0.5), (int)(ys1 + 0.5));
	if (fabs(xs1 - xs2) > 1e-9 || fabs(ys1 - ys2) > 1e-9)
		tacke.emplace_back((int)(xs2 + 0.5), (int)(ys2 + 0.5));

	return tacke;
}

vector<pair<int, int>> SweepLineAlgoritam(const vector<Kruznica>& kruznice) {
	vector<Event> events;
	int n = kruznice.size();

	for (int i = 0; i < n; ++i) {
		events.emplace_back(kruznice[i].centar.x - kruznice[i].r, i, true);
		events.emplace_back(kruznice[i].centar.x + kruznice[i].r, i, false);
	}

	sort(events.begin(), events.end());

	set<int, AktivniUporedi> aktivni(AktivniUporedi(events[0].x, &kruznice));
	vector<pair<int,int>> presjeci;

	for (size_t i = 0; i < events.size(); ++i) {
		double currX = events[i].x;

		int id = events[i].kruznicaId;

		if (events[i].isLeft) {
			auto it = aktivni.insert(id).first;

			auto it_prev = (it == aktivni.begin()) ? aktivni.end() : prev(it);
			auto it_next = next(it);

			if (it_prev != aktivni.end() && SeSijeku(kruznice[*it_prev], kruznice[id]))
				presjeci.emplace_back(min(*it_prev, id), max(*it_prev, id));

			if (it_next != aktivni.end() && SeSijeku(kruznice[*it_next], kruznice[id]))
				presjeci.emplace_back(min(*it_next, id), max(*it_next, id));


		} else {
			auto it = aktivni.find(id);
			if (it == aktivni.end()) continue;

			auto it_prev = (it == aktivni.begin()) ? aktivni.end() : prev(it);
			auto it_next = next(it);

			if (it_prev != aktivni.end() && it_next != aktivni.end() &&
				SeSijeku(kruznice[*it_prev], kruznice[*it_next]))
					presjeci.emplace_back(min(*it_prev, *it_next), max(*it_prev, *it_next));


			aktivni.erase(it);
		}
	}
	sort(presjeci.begin(), presjeci.end());
	presjeci.erase(unique(presjeci.begin(), presjeci.end()), presjeci.end());

	return presjeci;
}

void CrtajPresjeke(TImage* slika, const vector<Kruznica>& kruznice) {
	auto parovi = SweepLineAlgoritam(kruznice);

	for (auto& p : parovi) {
		auto tacke = IzracunajPresjek(kruznice[p.first], kruznice[p.second]);
		for (auto& t : tacke) {
			t.Crtaj(slika, clRed);
		}
	}
}

