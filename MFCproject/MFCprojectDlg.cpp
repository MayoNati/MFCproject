
// MFCprojectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCproject.h"
#include "MFCprojectDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CMFCprojectDlg dialog


CMFCprojectDlg::CMFCprojectDlg(CWnd* pParent /*=nullptr*/):CDialogEx(IDD_MFCPROJECT_DIALOG, pParent), isThin(FALSE),isFill(FALSE)
, radioButtonGroup(0)
{
	futureFigKIND=RECTANGLE;

	curColor = RGB(0, 0, 0);
	
	isPressed = false;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCprojectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, m_ColorBorder);

	//DDX_Radio(pDX, IDC_RADIO1, radioButtonGroup);
	//DDX_Control(pDX, IDC_RADIO1, radio1);
	//DDX_Text(pDX, IDC_EDIT3, editTestArea);
}

BEGIN_MESSAGE_MAP(CMFCprojectDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_RADIO1, &CMFCprojectDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CMFCprojectDlg::OnBnClickedRadio2)


	ON_BN_CLICKED(IDC_BUTTON1, &CMFCprojectDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCprojectDlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCprojectDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CMFCprojectDlg::OnEnChangeEdit2)
	ON_COMMAND(IDC_STATIC, &CMFCprojectDlg::OnStatic)

	ON_BN_CLICKED(IDC_CHECK1, &CMFCprojectDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CMFCprojectDlg::OnBnClickedCheck2)
	

	ON_EN_CHANGE(IDC_EDIT4, &CMFCprojectDlg::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, &CMFCprojectDlg::OnEnChangeEdit5)
	ON_BN_CLICKED(IDC_BUTTON_Undo, &CMFCprojectDlg::OnBnClickedButtonUndo)
	ON_BN_CLICKED(IDC_BUTTON_Redo, &CMFCprojectDlg::OnBnClickedButtonRedo)
	ON_BN_CLICKED(IDC_BUTTON_Clear, &CMFCprojectDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &CMFCprojectDlg::OnBnClickedMfccolorbutton1)
	ON_BN_CLICKED(IDC_RADIO3, &CMFCprojectDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CMFCprojectDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &CMFCprojectDlg::OnBnClickedRadio5)
	ON_EN_CHANGE(IDC_EDIT6, &CMFCprojectDlg::OnEnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT7, &CMFCprojectDlg::OnEnChangeEdit7)
END_MESSAGE_MAP()


// CMFCprojectDlg message handlers

BOOL CMFCprojectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	CheckRadioButton(IDC_RADIO1, IDC_RADIO5, IDC_RADIO1);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
	
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCprojectDlg::OnPaint()
{
	CWnd* hndStatic = this->GetDlgItem(IDC_STATIC); // returning the CWnd of the dialog instead of the IDC_STATIC
	CRect cltRect;
	hndStatic->GetWindowRect(&cltRect);
	width_GroupBox= cltRect.Width();

	int curIndex = myShapes.GetSize();
	CPaintDC dc(this);
	for (int i = 0; i < curIndex; i++)
		myShapes[i]->Draw(&dc);

		CRect MyRect;
		CWnd::GetWindowRect(MyRect);
		x_curLocation = MyRect.left;
		y_curLocation = MyRect.top;

	
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCprojectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCprojectDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default


	

	if (point.x >= width_GroupBox)
	{
		int index = myShapes.GetSize();
		endP = startP = point;
		isPressed = true;
		switch (futureFigKIND)
		{
		case PEN:
			myShapes.Add(new Pen(startP.x, startP.y, isThin, curColor));
			break;
		}

		CDialog::OnLButtonDown(nFlags, point);
	}

}

void CMFCprojectDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	if (point.x >= width_GroupBox)
	{
		if (isPressed)
		{
			endP = point;
			isPressed = false;
			int index = 0;


			switch (futureFigKIND)
			{
			case RECTANGLE:
				myShapes.Add(new RectangleM(startP.x, startP.y, endP.x, endP.y, isThin, isFill, curColor));

				SetDlgItemInt(IDC_EDIT3, myShapes[myShapes.GetSize() - 1]->GetArea()); //Write coordinate values
				SetDlgItemInt(IDC_EDIT_RecPerimeter, myShapes[myShapes.GetSize() - 1]->GetPerimeter()); //Write coordinate values

				break;

			case ELLIPSE:
				myShapes.Add(new EllipseM(startP.x, startP.y, endP.x, endP.y, isThin, isFill, curColor));
				SetDlgItemInt(IDC_EDIT4, myShapes[myShapes.GetSize() - 1]->GetArea()); //Write coordinate values
				SetDlgItemInt(IDC_EDIT5, myShapes[myShapes.GetSize() - 1]->GetPerimeter()); //Write coordinate values

				break;
			case LINE:
				myShapes.Add(new LineM(startP.x, startP.y, endP.x, endP.y, isThin, curColor));
				break;
			case TRIANGLE:
				myShapes.Add(new TriangleM(startP.x, startP.y, endP.x, endP.y, isThin, isFill, curColor));
				SetDlgItemInt(IDC_EDIT6, myShapes[myShapes.GetSize() - 1]->GetArea()); //Write coordinate values
				SetDlgItemInt(IDC_EDIT7, myShapes[myShapes.GetSize() - 1]->GetPerimeter()); //Write coordinate values
				break;
			case PEN:
				break;
			}
			Invalidate();
		}
		CDialogEx::OnLButtonUp(nFlags, point);
	}
	
}

void CMFCprojectDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	
	int curIndex = myShapes.GetSize();


	//IDC_STATIC
	CWnd* hndStatic = this->GetDlgItem(IDC_STATIC); // returning the CWnd of the dialog instead of the IDC_STATIC
	CRect cltRect;
	hndStatic->GetWindowRect(&cltRect);
	cltRect.bottom;
	LONG x1 = cltRect.left;
	LONG y1 = cltRect.top;
	LONG x2 = cltRect.right;
	LONG y2 = cltRect.bottom;

	if (isPressed)
	{
		if (point.x >= width_GroupBox) 
		{
			CClientDC dc(this);
			CBrush myBrush, * oldBrush;
			if (isFill)
			{
				myBrush.CreateSolidBrush(curColor);
				oldBrush = dc.SelectObject(&myBrush);
			}

			dc.SetROP2(R2_NOTXORPEN);
			CPen myPen1(PS_SOLID, isThin ? 1 : 4, curColor);
			CPen* oldPen;
			oldPen = dc.SelectObject(&myPen1);
			switch (futureFigKIND)
			{
			case RECTANGLE:
				dc.Rectangle(startP.x, startP.y, endP.x, endP.y);
				endP = point;
				dc.Rectangle(startP.x, startP.y, endP.x, endP.y);
				break;
			case ELLIPSE:
				dc.Ellipse(startP.x, startP.y, endP.x, endP.y);
				endP = point;
				dc.Ellipse(startP.x, startP.y, endP.x, endP.y);
				break;
			case LINE:
				dc.MoveTo(startP);
				dc.LineTo(endP.x, endP.y);
				endP = point;
				dc.MoveTo(startP);
				dc.LineTo(endP.x, endP.y);
				break;
			case PEN:
				myShapes[curIndex-1]->Build(point);
				dc.MoveTo(myShapes[curIndex-1]->lastP());
				dc.LineTo(endP.x, endP.y);
				endP = point;
				dc.MoveTo(myShapes[curIndex-1]->lastP());
				dc.LineTo(endP.x, endP.y);
				break;
			case TRIANGLE:
				dc.MoveTo(startP.x, endP.y);
				dc.LineTo(endP.x, endP.y);
				dc.LineTo((startP.x + endP.x) / 2, startP.y);
				dc.LineTo(startP.x, endP.y);
				endP = point;
				dc.MoveTo(startP.x, endP.y);
				dc.LineTo(endP.x, endP.y);
				dc.LineTo((startP.x + endP.x) / 2, startP.y);
				dc.LineTo(startP.x, endP.y);
				break;
			}
		}
	}

	SetDlgItemInt(IDC_EDIT1, point.x); //Write coordinate values
	SetDlgItemInt(IDC_EDIT2, point.y); //Write

}

void CMFCprojectDlg::OnBnClickedButton1()//Save
{
	// TODO: Add your control notification handler code here

	//FALSE=Save
	CFileDialog dlg(FALSE, _T(".figs"), NULL, 0, _T("Figures (*.figs)|*.figs|All Files (*.*)|*.*||"));
	CString filename;
	if (dlg.DoModal() == IDOK)
	{
		filename = dlg.GetPathName(); // return full path and filename
		CFile file(filename, CFile::modeCreate | CFile::modeWrite);
		CArchive ar(&file, CArchive::store);
		myShapes.Serialize(ar);
		ar.Close();
		file.Close();
	}
	
}

void CMFCprojectDlg::OnBnClickedButton2()//Load
{
	// TODO: Add your control notification handler code here
	//TRUE=Load
	CFileDialog dlg(TRUE, _T(".figs"), NULL, 0, _T("Figures (*.figs)|*.figs|All Files (*.*)|*.*||"));
	CString filename;
	if (dlg.DoModal() == IDOK)
	{
		filename = dlg.GetPathName(); // return full path and filename
		CFile file(filename, CFile::modeRead);
		CArchive ar(&file, CArchive::load);
		myShapes.Serialize(ar);
		ar.Close();
		file.Close();
		Invalidate();
	}
}

void CMFCprojectDlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CMFCprojectDlg::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CMFCprojectDlg::OnStatic()
{
	// TODO: Add your command handler code here
}

void CMFCprojectDlg::OnBnClickedCheck1()//Thin
{
	// TODO: Add your control notification handler code here
	CButton* m_ctlCheck = (CButton*)GetDlgItem(IDC_CHECK1);
	int ChkBox = m_ctlCheck->GetCheck();
	CString str;
	isThin = ChkBox == 1 ? true : false;
	
}

void CMFCprojectDlg::OnBnClickedCheck2()//fill
{
	CButton* m_ctlCheck = (CButton*)GetDlgItem(IDC_CHECK2);
	int ChkBox = m_ctlCheck->GetCheck();
	CString str;
	isFill = ChkBox == 1 ? true : false;	
}

void CMFCprojectDlg::OnEnChangeEditRecarea()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CMFCprojectDlg::OnEnChangeEditRecperimeter()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CMFCprojectDlg::OnEnChangeEdit4()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CMFCprojectDlg::OnEnChangeEdit5()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CMFCprojectDlg::OnBnClickedButtonUndo()
{
	// TODO: Add your control notification handler code here
	if (myShapes.IsEmpty())
		return;
	int s = myShapes.GetSize();
	tempFigs.Add(myShapes.GetAt(s-1));
	myShapes.RemoveAt(s-1);
	Invalidate();
}

void CMFCprojectDlg::OnBnClickedButtonRedo()
{
	// TODO: Add your control notification handler code here
	if (tempFigs.IsEmpty())
		return;
	int s = tempFigs.GetSize();
	myShapes.Add(tempFigs.GetAt(s-1));
	tempFigs.RemoveAt(s-1);
	Invalidate();
}

void CMFCprojectDlg::OnBnClickedButtonClear()
{
	// TODO: Add your control notification handler code here
	myShapes.RemoveAll();
	Invalidate();
}

void CMFCprojectDlg::OnBnClickedMfccolorbutton1()
{
	// TODO: Add your control notification handler code here
	curColor = m_ColorBorder.GetColor();
	Invalidate();
}

//void CMFCprojectDlg::OnBnClickedMfccolorbutton2()
//{
//	// TODO: Add your control notification handler code here
//	bkColor = m_Backcolor.GetColor();
//	Invalidate();
//}

void CMFCprojectDlg::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
	futureFigKIND = RECTANGLE;
	UpdateData(FALSE);
}

void CMFCprojectDlg::OnBnClickedRadio2()
{
	// TODO: Add your control notification handler code here
	futureFigKIND = ELLIPSE;
	UpdateData(FALSE);
}

void CMFCprojectDlg::OnBnClickedRadio3()
{
	// TODO: Add your control notification handler code here
	futureFigKIND = LINE;
	UpdateData(FALSE);
}

void CMFCprojectDlg::OnBnClickedRadio4()
{
	// TODO: Add your control notification handler code here
	futureFigKIND = TRIANGLE;
	UpdateData(FALSE);
}

void CMFCprojectDlg::OnBnClickedRadio5()
{
	futureFigKIND = PEN;
	UpdateData(FALSE);
}

void CMFCprojectDlg::OnEnChangeEdit6()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CMFCprojectDlg::OnEnChangeEdit7()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
