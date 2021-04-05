//---------------------------------------------------------------------------

#include <fmx.h>
#include <math.h>
#pragma hdrstop

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm3D2 *Form3D2;
//---------------------------------------------------------------------------
TPointF		*Down;

double			MinF = 2000;
double			MaxF = -2000;

TVector3D		CamVector;

TSpeedButton	*Btn;
TTimer			*Tmr;
int				Count;
//---------------------------------------------------------------------------
double f(int Func, double x, double z)
{
  double Result;
  double temp = x*x+z*z;
  double Pi = 3.1415926535897932384626433832795;
  double Epsilon = 1E-20;

  if (temp < Epsilon) {
	temp = Epsilon;
  }

  switch (Func) {
	case 1: Result = -2000*Sin(temp/180*Pi)/temp;
			break;
	case 2: Result = -5*Exp(Sin(x/10)-Cos(z/10));
			break;
	case 3: Result = -5*Exp(Sin(x/10)+Cos(z/10));
			break;
	case 4: Result = -5*Exp(Sin(Sqrt(fabs(x)))+Cos(Sqrt(fabs(z))));
			break;
	case 5: Result = -7*Exp(ArcTan2(x*x,z*z));
			break;
  }

  if (Result < MinF) {
	MinF = Result;
  }
  if (Result > MaxF) {
	MaxF = Result;
  }

  return Result;
}
//---------------------------------------------------------------------------
void __fastcall TForm3D2::GenerateMesh(int Func)
{
  int		MaxX = 30;
  int		MaxZ = 30;
  double 	u, v;
  TPoint3D	P0, P1, P2, P3;
  double 	d = 0.5;
  int		NP = 0;
  int		NI = 0;
  TBitmap 	*BMP;
  int		k;

  // We have to set these up front. The buffers are cleared every time Length is set.
  Mesh1->Data->VertexBuffer->Length = 2*MaxX*2*MaxZ/d/d*4;
  Mesh1->Data->IndexBuffer->Length = 2*MaxX*2*MaxZ/d/d*6;

  BMP = new TBitmap(1,360);
  for (k = 0; k < 360; k++)
	BMP->Pixels[0][k] = CorrectColor(HSLtoRGB(k/360.0,0.75,0.5));

  u = -MaxX;
  while (u < MaxX) {
	v = -MaxZ;
	while (v < MaxZ) {
	  // Set up the points in the XZ plane
	  P0.X = u;
	  P0.Z = v;
	  P1.X = u+d;
	  P1.Z = v;
	  P2.X = u+d;
	  P2.Z = v+d;
	  P3.X = u;
	  P3.Z = v+d;

	  // Calculate the corresponding function values for Y = f(X,Z)
	  P0.Y = f(Func,P0.X,P0.Z);
	  P1.Y = f(Func,P1.X,P1.Z);
	  P2.Y = f(Func,P2.X,P2.Z);
	  P3.Y = f(Func,P3.X,P3.Z);

	  // Set the points

	  Mesh1->Data->VertexBuffer->Vertices[NP+0] = P0;
	  Mesh1->Data->VertexBuffer->Vertices[NP+1] = P1;
	  Mesh1->Data->VertexBuffer->Vertices[NP+2] = P2;
	  Mesh1->Data->VertexBuffer->Vertices[NP+3] = P3;

	  // Map the colors
	  Mesh1->Data->VertexBuffer->TexCoord0[NP+0] = PointF(0,(P0.Y+35)/45);
	  Mesh1->Data->VertexBuffer->TexCoord0[NP+1] = PointF(0,(P1.Y+35)/45);
	  Mesh1->Data->VertexBuffer->TexCoord0[NP+2] = PointF(0,(P2.Y+35)/45);
	  Mesh1->Data->VertexBuffer->TexCoord0[NP+3] = PointF(0,(P3.Y+35)/45);

	  // Map the triangles
	  Mesh1->Data->IndexBuffer->Indices[NI+0] = NP+1;
	  Mesh1->Data->IndexBuffer->Indices[NI+1] = NP+2;
	  Mesh1->Data->IndexBuffer->Indices[NI+2] = NP+3;
	  Mesh1->Data->IndexBuffer->Indices[NI+3] = NP+3;
	  Mesh1->Data->IndexBuffer->Indices[NI+4] = NP+0;
	  Mesh1->Data->IndexBuffer->Indices[NI+5] = NP+1;

	  NP = NP+4;
	  NI = NI+6;

	  v = v+d;
	}
	u = u+d;
  }

  Mesh1->Data->CalcNormals();
  Mesh1->Material->Texture = BMP;
}
//---------------------------------------------------------------------------
__fastcall TForm3D2::TForm3D2(TComponent* Owner)
	: TForm3D(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm3D2::Button1Click(TObject *Sender)
{
  Text3D1->Text = Button1->Text;
  GenerateMesh(1);
}
//---------------------------------------------------------------------------
void __fastcall TForm3D2::Button2Click(TObject *Sender)
{
  Text3D1->Text = Button2->Text;
  GenerateMesh(2);
}
//---------------------------------------------------------------------------
void __fastcall TForm3D2::Button3Click(TObject *Sender)
{
  Text3D1->Text = Button3->Text;
  GenerateMesh(3);
}
//---------------------------------------------------------------------------
void __fastcall TForm3D2::Button4Click(TObject *Sender)
{
  Text3D1->Text = Button4->Text;
  GenerateMesh(4);
}
//---------------------------------------------------------------------------
void __fastcall TForm3D2::Button5Click(TObject *Sender)
{
  Text3D1->Text = Button5->Text;
  GenerateMesh(5);
}
//---------------------------------------------------------------------------
void __fastcall TForm3D2::CheckBox1Change(TObject *Sender)
{
  GridXY->Visible = CheckBox1->IsChecked;
  GridXZ->Visible = CheckBox1->IsChecked;
  GridYZ->Visible = CheckBox1->IsChecked;
}
//---------------------------------------------------------------------------
void __fastcall TForm3D2::ArcDial1Change(TObject *Sender)
{
  Layout3D1->RotationAngle->Z = ArcDial1->Value;
}
//---------------------------------------------------------------------------
void __fastcall TForm3D2::sbDnMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  float X, float Y)
{
  Count = 0;
  Btn = (TSpeedButton*) Sender;

  if (Tmr == NULL) {
	Tmr = new TTimer(this);
	Tmr->Interval = 25;
	Tmr->OnTimer = RotateButtonTimer;
  }

  Tmr->Enabled = True;
}
//---------------------------------------------------------------------------
void __fastcall TForm3D2::sbDnMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  float X, float Y)
{
  Tmr->Enabled = False;
}
//---------------------------------------------------------------------------
void __fastcall TForm3D2::tbZoomChange(TObject *Sender)
{
  Camera1->Position->Vector = Vector3DScale(CamVector,tbZoom->Value/20);
}
//---------------------------------------------------------------------------
void __fastcall TForm3D2::Form3DCreate(TObject *Sender)
{
  CamVector = Camera1->Position->Vector;
}
//---------------------------------------------------------------------------
void __fastcall TForm3D2::RotateButtonTimer(TObject *Sender)
{
  Count++;
  if (Btn == sbUp)
	Layout3D1->RotationAngle->X++;
  if (Btn == sbDn)
	Layout3D1->RotationAngle->X--;
  if (Btn == sbRt)
	Layout3D1->RotationAngle->Y++;
  if (Btn == sbLt)
	Layout3D1->RotationAngle->Y--;
}
//---------------------------------------------------------------------------

