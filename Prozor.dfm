object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 539
  ClientWidth = 767
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object Slika: TImage
    Left = 16
    Top = 24
    Width = 433
    Height = 385
    OnMouseDown = SlikaMouseDown
  end
  object LabelPoluprecnik: TLabel
    Left = 471
    Top = 164
    Width = 142
    Height = 30
    Caption = 'Unesi polupre'#269'nik kru'#382'nice'
    OnClick = LabelPoluprecnikClick
  end
  object ButtonDaLiSeKruzniceSijeku: TButton
    Left = 471
    Top = 328
    Width = 145
    Height = 25
    Caption = 'Da li se kruznice sijeku'
    TabOrder = 0
    OnClick = ButtonDaLiSeKruzniceSijekuClick
  end
  object InputRandomKruznice: TEdit
    Left = 471
    Top = 24
    Width = 145
    Height = 23
    TabOrder = 1
    Text = '10'
  end
  object ButtonGenerisiKruznice: TButton
    Left = 471
    Top = 61
    Width = 145
    Height = 25
    Caption = 'Generisi Kruznice'
    TabOrder = 2
    OnClick = ButtonGenerisiKruzniceClick
  end
  object RadioDodajKruznicu: TRadioButton
    Left = 468
    Top = 132
    Width = 145
    Height = 17
    Caption = 'Dodaj Kruznicu'
    TabOrder = 3
  end
  object ButtonOcisti: TButton
    Left = 471
    Top = 384
    Width = 145
    Height = 25
    Caption = 'Ocisti'
    TabOrder = 4
    OnClick = ButtonOcistiClick
  end
  object InputPoluprecnik: TEdit
    Left = 471
    Top = 200
    Width = 145
    Height = 31
    TabOrder = 5
  end
end
