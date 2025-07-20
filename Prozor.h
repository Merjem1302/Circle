#ifndef ProzorH
#define ProzorH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <vector>
#include "Pomocna.h"

using namespace std;

class TForm1 : public TForm
{
__published:
	TImage *Slika;
	TRadioButton *RadioDodajKruznicu;
	TEdit *InputPoluprecnik;
	TButton *ButtonGenerisiKruznice;
	TEdit *InputRandomKruznice;
	TButton *ButtonOcisti;
	TButton *ButtonDaLiSeKruzniceSijeku;
	TLabel *LabelPoluprecnik;

	void __fastcall SlikaMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall ButtonGenerisiKruzniceClick(TObject *Sender);
	void __fastcall ButtonOcistiClick(TObject *Sender);
	void __fastcall ButtonDaLiSeKruzniceSijekuClick(TObject *Sender);
	void __fastcall LabelPoluprecnikClick(TObject *Sender);

private:
	vector<Kruznica> kruznice;

	void PronadjiPresjeke();
public:
	__fastcall TForm1(TComponent* Owner);
};

extern PACKAGE TForm1 *Form1;

#endif

