#include <vcl.h>
#pragma hdrstop

#include "Prozor.h"
#include "Pomocna.h"
#include <algorithm>

#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	Slika->Canvas->Brush->Color = clWhite;
	Slika->Canvas->FillRect(Rect(0, 0, Slika->Width, Slika->Height));
	Slika->Canvas->Brush->Color = clBlack;
	Slika->Canvas->FrameRect(Rect(0, 0, Slika->Width, Slika->Height));
	Slika->Canvas->Brush->Color = clWhite;
}

void __fastcall TForm1::SlikaMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
									   int X, int Y)
{
	if (RadioDodajKruznicu->Checked) {
		int r = InputPoluprecnik->Text.ToIntDef(20);

		if (X - r < 0 || X + r > Slika->Width || Y - r < 0 || Y + r > Slika->Height) {
			ShowMessage("Kružnica ne može biti iscratana jer izlazi van platna.");
			return;
		}

		Tacka t(X, Y);
		Kruznica nova(t, r);
		kruznice.push_back(nova);
		nova.Crtaj(Slika);
	}
}

void __fastcall TForm1::ButtonGenerisiKruzniceClick(TObject *Sender)
{
	int brojKruznica = InputRandomKruznice->Text.ToIntDef(5);
	int r = 20;

	for (int i = 0; i < brojKruznica; i++) {
		int x = r + rand() % (Slika->Width - 2 * r);
		int y = r + rand() % (Slika->Height - 2 * r);

		Tacka t(x, y);
		Kruznica nova(t, r);
		kruznice.push_back(nova);
		nova.Crtaj(Slika);
	}
}

void __fastcall TForm1::ButtonOcistiClick(TObject *Sender)
{
	Slika->Canvas->Brush->Color = clWhite;
	Slika->Canvas->FillRect(Rect(0, 0, Slika->Width, Slika->Height));
	Slika->Canvas->Brush->Color = clBlack;
	Slika->Canvas->FrameRect(Rect(0, 0, Slika->Width, Slika->Height));
	Slika->Canvas->Brush->Color = clWhite;

	kruznice.clear();
}

void TForm1::PronadjiPresjeke()
{
	if (kruznice.size() < 2) {
		ShowMessage("Nema dovoljno kruznica za provjeru presjeka.");
		return;
	}

	auto presjeci = SweepLineAlgoritam(kruznice);

	if (presjeci.empty()) {
		ShowMessage("Nijedne dvije kruznice se ne sijeku.");
		return;
	}

	Slika->Canvas->Brush->Color = clWhite;
	Slika->Canvas->FillRect(Rect(0, 0, Slika->Width, Slika->Height));
	Slika->Canvas->Brush->Color = clBlack;
	Slika->Canvas->FrameRect(Rect(0, 0, Slika->Width, Slika->Height));

	for (auto& k : kruznice)
		k.Crtaj(Slika);

	for (auto& p : presjeci) {
		auto tacke = IzracunajPresjek(kruznice[p.first], kruznice[p.second]);
		for (auto& t : tacke) {
			t.Crtaj(Slika, clRed);
		}
	}

	AnsiString poruke;
	for (auto& p : presjeci) {
		AnsiString tekst = "Kružnice sa centrima (" +
			IntToStr(kruznice[p.first].centar.x) + "," +
			IntToStr(kruznice[p.first].centar.y) + ") i (" +
			IntToStr(kruznice[p.second].centar.x) + "," +
			IntToStr(kruznice[p.second].centar.y) + ") se sijeku.\n";
		poruke += tekst;
	}

	ShowMessage(poruke);
}

void __fastcall TForm1::ButtonDaLiSeKruzniceSijekuClick(TObject *Sender)
{
	PronadjiPresjeke();
}


void __fastcall TForm1::LabelPoluprecnikClick(TObject *Sender)
{
	Slika->Canvas->Font->Color = clBlack;
	Slika->Canvas->Font->Size = 12;
}
//---------------------------------------------------------------------------

