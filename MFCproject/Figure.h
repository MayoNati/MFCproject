// instead of the triple
// #ifndef ... 
// #define ...
// #endif
// use:
#pragma once   
//this file include all the shapes and here we can see the polymorfism - figure->shape->(all the sahapes )
//																			   ->line->					->pen
#include <vector>// we use vector for shape "array"
using namespace std;

class Figure : public CObject
{
	DECLARE_SERIAL(Figure)
//protected:
public:
	int x1, y1, x2, y2;
	int isThin, isFill;
	COLORREF bgColor;
	CPen border;

	Figure();
	Figure(int xx1, int yy1, int xx2, int yy2)
	{
		x1 = xx1;
		x2 = xx2;
		y1 = yy1;
		y2 = yy2;
		isFill = 0;
		bgColor = RGB(0, 0, 0);
	}
	Figure(int xx1, int yy1, int xx2, int yy2, int thin, int fill, COLORREF color)
	{
		x1 = xx1;
		x2 = xx2;
		y1 = yy1;
		y2 = yy2;
		isThin = thin;
		isFill = fill;
		bgColor = color;
		border.CreatePen(PS_SOLID, 2, color);
	}
	void SetColor(COLORREF NewColor) { bgColor = NewColor; }
	virtual void Draw(CDC* dc) {}// polimorphism
	virtual ~Figure(void);
	virtual void Build(CPoint cur) {}
	virtual CPoint lastP() { CPoint p(0, 0); return p; }
	virtual double GetArea() { return 0; }
	virtual double GetPerimeter() { return 0; }
	void Serialize(CArchive& archive);
};

class RectangleM :public Figure {
	DECLARE_SERIAL(RectangleM)
public:
	RectangleM();
	RectangleM(int xx1, int yy1, int xx2, int yy2)
		:Figure(xx1, yy1, xx2, yy2) {}
	RectangleM(int xx1, int yy1, int xx2, int yy2, int thin, int fill, COLORREF color)
		:Figure(xx1, yy1, xx2, yy2, thin, fill, color) {}
	void Draw(CDC* dc)
	{
		CBrush myBrush;
		CPen myPen(PS_SOLID, isThin ? 1 : 4, bgColor);
		dc->SelectObject(&myPen);
		if (isFill) 
		{
			myBrush.CreateSolidBrush(bgColor);
		}		
		else 
		{
			myBrush.CreateSolidBrush(RGB(255, 255, 255));
		}
		dc->SelectObject(myBrush);
		
		dc->Rectangle(x1, y1, x2, y2);
	}
	double GetArea() {
		int height = 0;
		int length = 0;
		length = x1 < x2 ? x2 - x1 : x1 - x2;
		height = y1 < y2 ? y2 - y1 : y1 - y2;
		return length*height;
	}
	double GetPerimeter() {
		int height = 0;
		int length = 0;
		length = x1 < x2 ? x2 - x1 : x1 - x2;
		height = y1 < y2 ? y2 - y1 : y1 - y2;
		return ((length *2)+(height*2));
	}
};

class EllipseM :public Figure {
	DECLARE_SERIAL(EllipseM)
public:
	EllipseM();
	EllipseM(int xx1, int yy1, int xx2, int yy2)
		:Figure(xx1, yy1, xx2, yy2) {}
	EllipseM(int xx1, int yy1, int xx2, int yy2, int thin, int fill, COLORREF color)
		:Figure(xx1, yy1, xx2, yy2, thin, fill, color) {}
	void Draw(CDC* dc)
	{
		CBrush myBrush;
		CPen myPen(PS_SOLID, isThin ? 1 : 4, bgColor);
		dc->SelectObject(&myPen);	//get the info for the shape- mean if we draw thin, fill, and color
		if (isFill)
			myBrush.CreateSolidBrush(bgColor);
		else
			myBrush.CreateSolidBrush(RGB(255, 255, 255));
		dc->SelectObject(myBrush);
		dc->Ellipse(x1, y1, x2, y2);
	}
	double GetArea() {
		double ans = 0;
		int height = 0;
		int length = 0;
		length = x1 < x2 ? x2 - x1 : x1 - x2;
		height = y1 < y2 ? y2 - y1 : y1 - y2;
		ans = 3.14 * (height*0.5) * (length*0.5);

		return ans;
	}
	double GetPerimeter() {
		double ans = 0;
		int height = 0;
		int length = 0;
		double pai = 3.14;
		length = x1 < x2 ? x2 - x1 : x1 - x2;
		height = y1 < y2 ? y2 - y1 : y1 - y2;	
		ans = sqrt(pow((height * 0.5), 2) + pow((length * 0.5), 2) / 2) * 2 * pai;
		return ans;
	}
};

class TriangleM :public Figure {
	DECLARE_SERIAL(TriangleM)
	CPoint pt[3];
public:
	TriangleM();
	TriangleM(int xx1, int yy1, int xx2, int yy2)
		:Figure(xx1, yy1, xx2, yy2) {}
	TriangleM(int xx1, int yy1, int xx2, int yy2, int thin, int fill, COLORREF color)
		:Figure(xx1, yy1, xx2, yy2, thin, fill, color) {}
	void Draw(CDC* dc)	//draw the triangle with start, end point and the middle point
	{
		
		this->pt[0].SetPoint(x1, y2);
		this->pt[1].SetPoint(x2, y2);
		this->pt[2].SetPoint((x1 + x2) / 2, y1);

		CBrush myBrush;
		CPen myPen(PS_SOLID, isThin ? 1 : 4, bgColor);
		dc->SelectObject(&myPen);
		if (isFill)
			myBrush.CreateSolidBrush(bgColor);
		else
			myBrush.CreateSolidBrush(RGB(255, 255, 255));
		dc->SelectObject(myBrush);
		dc->Polygon(this->pt, 3);
		
	}
	double GetArea() 
	{
		double ans = 0;
		int height = 0;
		int length = 0;

		this->pt[0].SetPoint(x1, y2);
		this->pt[1].SetPoint(x2, y2);
		this->pt[2].SetPoint((x1 + x2) / 2, y1);

		height=this->pt[2].y< this->pt[1].y? this->pt[1].y- this->pt[2].y: this->pt[2].y - this->pt[1].y;
		length = this->pt[0].x < this->pt[1].x ? this->pt[1].x - this->pt[0].x : this->pt[0].x - this->pt[1].x;

		ans = ((height)*(length))/2;

		return ans;
	}
	double GetPerimeter() 
	{
		double ans = 0;
		int height = 0;
		int length = 0;

		this->pt[0].SetPoint(x1, y2);
		this->pt[1].SetPoint(x2, y2);
		this->pt[2].SetPoint((x1 + x2) / 2, y1);
		double a = 0;
		double b = 0;
		double c = 0;

		a= this->pt[0].x < this->pt[1].x ? this->pt[1].x - this->pt[0].x : this->pt[0].x - this->pt[1].x;
		b = sqrt(pow((pt[0].x- pt[2].x),2)+pow((pt[0].y - pt[2].y),2));
		c = sqrt(pow((pt[1].x - pt[2].x), 2) + pow((pt[1].y - pt[2].y), 2));
		ans = a + b + c;
		return ans;
	}
};

class LineM :public Figure
{
	DECLARE_SERIAL(LineM)
public:

	LineM();
	LineM(int xx1, int yy1, int xx2, int yy2) :Figure(xx1, yy1, xx2, yy2) {}
	LineM(int xx1, int yy1, int xx2, int yy2, int thin, COLORREF color) :Figure(xx1, yy1, xx2, yy2, thin, 0, color) {}
	void Draw(CDC* dc)
	{
		CPen myPen(PS_SOLID, isThin ? 1 : 4, bgColor);
		dc->SelectObject(&myPen);
		dc->MoveTo(x1, y1);
		dc->LineTo(x2, y2);
	}
};

class Pen :public LineM {
	DECLARE_SERIAL(Pen)
public:
	Pen();
	Pen(int x1, int y1)
		:LineM(x1, y1, x1, y1)
	{
		CPoint p(x1, y1);
		pArr.push_back(p);
	}
	Pen(int x1, int y1, int thin, COLORREF color)
		:LineM(x1, y1, x1, y1, thin, color)
	{
		CPoint p(x1, y1);
		pArr.push_back(p);
	}
	CPoint lastP()
	{
		return pArr[pArr.size() - 1];
	}
	void Build(CPoint cur)
	{
		pArr.push_back(cur);
	}
	void Draw(CDC* dc)// creat the line(not direct)
	{
		CPen myPen(PS_SOLID, isThin ? 1 : 4, bgColor);
		for (int i = 1; i < pArr.size(); i++)
		{
			dc->SelectObject(myPen);
			dc->MoveTo(pArr[i-1]);
			dc->LineTo(pArr[i]);
		}
	}

protected:
	vector <CPoint> pArr;	//array with all the pixels for the line
};
