
// MFCprojectDlg.h : header file
//

#if !defined(AFX_DLGDLG_H__D02F91E6_1066_4AA4_AE0B_1D16C986AE2C__INCLUDED_)
#define AFX_DLGDLG_H__D02F91E6_1066_4AA4_AE0B_1D16C986AE2C__INCLUDED_

#if _MSC_VER > 1000

#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <stack>
#include "Figure.h"
#include "afxwin.h"

using namespace std;

// CMFCprojectDlg dialog
class CMFCprojectDlg : public CDialogEx
{
// Construction
public:
	CMFCprojectDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCPROJECT_DIALOG };
#endif
	enum FIGURES {RECTANGLE, LINE, ELLIPSE, TRIANGLE, PEN };
	FIGURES futureFigKIND;
	CPoint start, end;
	bool isPressed=false;
	CMFCColorButton m_ColorBorder;
	CMFCColorButton m_Backcolor;
	CTypedPtrArray< CObArray, Figure*> myShapes,tempFigs;
	COLORREF curColor;
	COLORREF bkColor;
	CPoint startP;
	CPoint endP;
	LONG width_GroupBox=0;
	int x_curLocation;
	int y_curLocation;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	BOOL isThin;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnStatic();
	BOOL isFill;

	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnEnChangeEditRecarea();
	afx_msg void OnEnChangeEditRecperimeter();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnBnClickedButtonUndo();
	afx_msg void OnBnClickedButtonRedo();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedMfccolorbutton1();
//	afx_msg void OnBnClickedMfccolorbutton2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnEnChangeEdit7();
	int radioButtonGroup;
	CButton radio1;
	double editTestArea;
};
#endif // !defined(AFX_DLGDLG_H__D02F91E6_1066_4AA4_AE0B_1D16C986AE2C__INCLUDED_)