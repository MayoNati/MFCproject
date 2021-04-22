#include "stdafx.h"
#include "Figure.h"

// this file include all the defult constacturs

//Allows arrangement and access to information in runtime classes
IMPLEMENT_SERIAL(Figure, CObject, 1)
Figure::Figure(void)
{
}

Figure::~Figure(void)
{
}

IMPLEMENT_SERIAL(RectangleM, CObject, 1)
RectangleM::RectangleM() {}

IMPLEMENT_SERIAL(EllipseM, CObject, 1)
EllipseM::EllipseM() {}

IMPLEMENT_SERIAL(LineM, CObject, 1)
LineM::LineM() {}

IMPLEMENT_SERIAL(TriangleM, CObject, 1)
TriangleM::TriangleM() {}

IMPLEMENT_SERIAL(Pen, CObject, 1)
Pen::Pen() {}

void Figure::Serialize(CArchive& archive) 
{
	CObject::Serialize(archive);
	if (archive.IsStoring())
	{
		archive << isThin << isFill<<bgColor << x1 << y1 << x2 << y2;
	}
	else
	{
		int bx, by, ex, ey, thin,fill;
		COLORREF bg;
		archive >> thin >>fill>> bg >> bx >> by >> ex >> ey;
		
		this->bgColor = bg;
		this->isThin = thin;
		this->isFill = fill;
		this->x1 = bx;
		this->y1 = by;
		this->x2 = ex;
		this->y2 = ey;
		
	}
}