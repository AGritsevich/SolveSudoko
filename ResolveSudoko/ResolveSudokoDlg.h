
// ResolveSudokoDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "Logic/Checker.h"
#include "Logic/Solver.h"


UINT LightWrongCells( LPVOID pParam );

// CResolveSudokoDlg dialog
class CResolveSudokoDlg : public CDialogEx
{
	friend UINT LightWrongCells( LPVOID pParam );
// Construction
public:
	CResolveSudokoDlg(CWnd* pParent = NULL);	// standard constructor

	HICON m_hIcon;
	enum { IDD = IDD_RESOLVESUDOKO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()

public:


private:
	CCustodian m_data;
	CChecker m_checker;
	CSolver m_thinker;
	CFont m_normalFont;
	CFont m_wrongFont;

	CEdit m_edit;
	CEdit** m_pCellCtrl;

private:
	bool CopyStartingTableTest();
	bool LoadTable();
	bool SaveTable();
	bool ResetWrongCellFont();
	
public:
	afx_msg void OnBnClickedCheck();
	afx_msg void OnBnClickedResolve();
	afx_msg void OnBnClickedClean();
};


