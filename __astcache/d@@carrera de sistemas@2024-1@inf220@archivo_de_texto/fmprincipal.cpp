//---------------------------------------------------------------------------
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <vcl.h>
#pragma hdrstop
#pragma package(smart_init)
#pragma resource "*.dfm"

#include "FMPrincipal.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

using namespace std;

struct Shape {
	string type;
	vector<int> params;
};

void drawShapes(vector<Shape> shapes, TForm *form);
vector<Shape> readShapesFromFile(string filename);
vector<Shape> shapes;

//---------------------------------------------------------------------------
//No es necesario tener este procedimiento para dibujar en el windows form
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
//	 shapes = readShapesFromFile("Datos.txt");
// shapes está recibiendo un valor de tipo vector<int> que contiene las
// coordenadas de las figuras por ejemplo:  0   1   2
// circunferencia (100,100,50) ==> vector<|100|100|50 |>
}
//---------------------------------------------------------------------------
//No es necesario tener este procedimiento para dibujar en el windows form
void __fastcall TForm1::FormPaint(TObject *Sender)
{
//	drawShapes(shapes, this);
// Lo que se hace en aqui es dibujar en el formulario pero con el procedimiento
// del boton dibujar (Draw) ya no es necesario este procedimiento.
//  drawShapes(shapes, this) es un procedimiento que dibuja figuras y que
// tiene por parametro un vector (vector<|100|100|50 |>)
// y un this (que sería Form1->Canvas)
}
//---------------------------------------------------------------------------

void drawShapes(vector<Shape> shapes, TForm *form) {
	TCanvas *canvas = form->Canvas;
	for (auto shape : shapes) {
		if (shape.type == "Circunferencia") {
			if (shape.params.size() >= 3) {
				int x = shape.params[0];
				int y = shape.params[1];
				int radio = shape.params[2];
				canvas->Ellipse(x - radio, y - radio, x + radio, y + radio);
			}
		}
		if (shape.type == "Rectangulo") {
			if (shape.params.size() >= 4) {
				int x = shape.params[0];
				int y = shape.params[1];
				int base = shape.params[2];
				int altura = shape.params[3];
				canvas->Rectangle(x, y, base, altura);
			}
		}
		if (shape.type == "Linea") {
			if (shape.params.size() >= 4) {
				int x = shape.params[0];
				int y = shape.params[1];
				int p1 = shape.params[2];
				int p2 = shape.params[3];
				canvas->MoveTo(x, y);
				canvas->LineTo(p1, p2);
			}
		}
	}
}

vector<Shape> readShapesFromFile(string filename) {
	vector<Shape> shapes;
	ifstream file(filename);
    if (file.is_open()) {
        string line;
		while (getline(file, line)) {
			stringstream ss(line);
			string type;
			ss >> type;
			if (type == "Circunferencia" || type == "Rectangulo" || type == "Linea") {
				Shape shape;
				shape.type = type;
				char ch;
				int param;
				while (ss >> ch >> param) { // ch siempre tomará un caracter que puede ser '(' o ','. "(100,100,50)"
					shape.params.push_back(param); // param solamente tomará los numeros
				}
				shapes.push_back(shape); // shapes es un vector que tomará el objeto shape (vector<|100|100|50 |>)
			}
		}
		file.close();  // cerrar el archivo de texto
	}
	return shapes;
}
void __fastcall TForm1::Draw(TObject *Sender)
{
	shapes = readShapesFromFile("Datos.txt");
	drawShapes(shapes, this);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DeleteDraw(TObject *Sender)
{
	Form1->Invalidate(); // borra todos los dibujos del formulario
}
//---------------------------------------------------------------------------

