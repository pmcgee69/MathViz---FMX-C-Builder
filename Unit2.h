//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Layers3D.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Objects3D.hpp>
#include <FMX.Types.hpp>
#include <FMX.Types3D.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Controls3D.hpp>
#include <FMX.MaterialSources.hpp>
#include <FMX.StdCtrls.hpp>
#include <System.Math.Vectors.hpp>
//---------------------------------------------------------------------------
class TForm3D2 : public TForm3D
{
__published:	// IDE-managed Components
	TCamera     * Camera1;
	TLayer3D    * Layer3D1;
	TButton     * Button1;
	TButton     * Button2;
	TButton     * Button3;
	TButton     * Button4;
	TButton     * Button5;
	TPanel      * Panel1;
	TSpeedButton* sbDn;
	TPath       * Path1;
	TSpeedButton* sbLt;
	TPath       * Path3;
	TSpeedButton* sbRt;
	TPath       * Path4;
	TSpeedButton* sbUp;
	TPath       * Path2;
	TTrackBar   * tbZoom;
	TArcDial    * ArcDial1;
	TCheckBox   * CheckBox1;
	TLayout3D   * Layout3D1;
	TGrid3D     * GridXY;
	TGrid3D     * GridXZ;
	TGrid3D     * GridYZ;
	TMesh       * Mesh1;
	TText3D     * Text3D1;
	TLight      * Light1;
	TTextureMaterialSource *TextureMaterialSource1;
	TLabel *Label1;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall CheckBox1Change(TObject *Sender);
	void __fastcall ArcDial1Change(TObject *Sender);
	void __fastcall sbDnMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  float X, float Y);
	void __fastcall sbDnMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  float X, float Y);
	void __fastcall tbZoomChange(TObject *Sender);
	void __fastcall Form3DCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm3D2(TComponent* Owner);
	void __fastcall GenerateMesh(int Func);
	void __fastcall RotateButtonTimer(TObject *Sender);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3D2 *Form3D2;
//---------------------------------------------------------------------------
#endif
