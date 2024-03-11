object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 633
  ClientWidth = 931
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  OnPaint = FormPaint
  TextHeight = 15
  object Button1: TButton
    Left = 832
    Top = 560
    Width = 75
    Height = 50
    Caption = 'Dibujar'
    TabOrder = 0
    OnClick = Draw
  end
  object Button2: TButton
    Left = 736
    Top = 560
    Width = 75
    Height = 50
    Caption = 'Borrar'
    TabOrder = 1
    OnClick = DeleteDraw
  end
end
