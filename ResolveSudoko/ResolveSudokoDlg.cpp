
// ResolveSudokoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ResolveSudoko.h"
#include "ResolveSudokoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


const int EDIT_WIDTH = 20;
const int EDIT_HEIGHT = 20;
const int EDIT_FontHeight = 16;
const int EDIT_FontWeightNormal = 20;
const int EDIT_FontWeightWrong = 9000;

const int PRIVATE_ID = IDC_PRIVATE_CELLS;

// const int test_sudoko [9][9] = 
// {
// 	{ 5, 3, 4, 6, 7, 8, 9, 1, 2},
// 	{ 6, 7, 2, 1, 9, 5, 3, 4, 8},
// 	{ 1, 9, 8, 3, 4, 2, 5, 6, 7},
// 	{ 8, 5, 9, 7, 6, 1, 4, 2, 3},
// 	{ 4, 2, 6, 8, 5, 3, 7, 9, 1},
// 	{ 7, 1, 3, 9, 2, 4, 8, 5, 6},
// 	{ 9, 6, 1, 5, 3, 7, 2, 8, 4},
// 	{ 2, 8, 7, 4, 1, 9, 6, 3, 5},
// 	{ 3, 4, 5, 2, 8, 6, 1, 7, 9}
// };

const int test_sudoko [9][9] = 
{
	{ 4, 0, 0,  2, 0, 0,  6, 0, 0},
	{ 6, 3, 0,  0, 0, 8,  9, 0, 0},
	{ 7, 0, 0,  0, 3, 1,  0, 0, 0},

	{ 0, 0, 4,  0, 6, 0,  0, 0, 0},
	{ 8, 0, 0,  0, 0, 2,  0, 0, 4},
	{ 0, 0, 0,  3, 5, 0,  0, 9, 0},
	
	{ 0, 9, 0,  0, 8, 0,  0, 0, 0},
	{ 5, 0, 0,  4, 0, 0,  0, 0, 7},
	{ 0, 0, 6,  0, 0, 0,  5, 0, 0}
};

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

UINT LightWrongCells( LPVOID pParam )
{
	CResolveSudokoDlg* pDlg = (CResolveSudokoDlg*)pParam;
	CFont errFont;

	if (pDlg == nullptr )
		return 1;   // if pObject is not valid

	while (1)
	{
		for ( auto index = 0; index < pDlg->m_checker.m_erros.size(); index++)
		{
			ContainerCoordinate space = pDlg->m_checker.m_erros.back();
			pDlg->m_checker.m_erros.pop_back();
			pDlg->m_pCellCtrl[space.y][space.x].SetFont(&pDlg->m_wrongFont);
		}

		Sleep(200);
	}

	return 0;   // thread completed successfully
}
CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD){}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CResolveSudokoDlg dialog



CResolveSudokoDlg::CResolveSudokoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CResolveSudokoDlg::IDD, pParent),
	m_checker(&m_data),
	m_thinker(&m_data)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pCellCtrl = new CEdit*[ROW];

	if ( m_pCellCtrl != nullptr )
	{
		for (auto i = 0; i < ROW; i++)
		{
			m_pCellCtrl[i] = new CEdit[COLUMN];
		}
	}

	AfxBeginThread(LightWrongCells, this);
}

void CResolveSudokoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

// 	for ( auto x = 0; x < ROW; x++)
// 	{
// 		for (auto y = 0; y < COLUMN; y++)
// 		{
// 			int id = PRIVATE_ID + x*ROW + y;
// 			//DDX_Text(pDX, (id), m_pCellVal[x][y]);
// 		}	
// 	}

	//DDV_MinMaxInt();
}

BEGIN_MESSAGE_MAP(CResolveSudokoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK, &CResolveSudokoDlg::OnBnClickedCheck)
	ON_BN_CLICKED(IDC_RESOLVE, &CResolveSudokoDlg::OnBnClickedResolve)
	ON_BN_CLICKED(IDC_CLEAN, &CResolveSudokoDlg::OnBnClickedClean)
END_MESSAGE_MAP()


// CResolveSudokoDlg message handlers

BOOL CResolveSudokoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	LOGFONT LogFont;
	GetFont()->GetLogFont(&LogFont);
	LogFont.lfWeight = EDIT_FontWeightNormal;
	LogFont.lfHeight = EDIT_FontHeight;
	m_normalFont.CreateFontIndirect(&LogFont);
	LogFont.lfWeight = EDIT_FontWeightWrong;
	m_wrongFont.CreateFontIndirect(&LogFont);


	int editPos_x = 25;
	int editPos_y = 30;
	double shiftFactor = 1.4;
	int cur_x = editPos_x;

	int id = PRIVATE_ID; 

	for ( auto x = 0; x < ROW; x++)
	{
		for (auto y = 0; y < COLUMN; y++)
		{
			CRect point(cur_x, editPos_y, cur_x + EDIT_WIDTH, editPos_y + EDIT_HEIGHT );
			
			m_pCellCtrl[x][y].Create ( WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_NUMBER | WS_BORDER | ES_CENTER, point, this, id++ );
			m_pCellCtrl[x][y].SetFont(&m_normalFont);
			m_pCellCtrl[x][y].SetLimitText(1);

			cur_x += (int)(shiftFactor*EDIT_WIDTH);
			if (y == 2 || y == 5) cur_x += (int)(10*shiftFactor);
		}
		editPos_y += (int)(shiftFactor*EDIT_HEIGHT);
		if ( x == 2 || x == 5 ) editPos_y += (int)(10*shiftFactor);
		
		cur_x = editPos_x;

	}

	//CopyStartingTableTest();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CResolveSudokoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
// 	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
// 	{
// 		CAboutDlg dlgAbout;
// 		dlgAbout.DoModal();
// 	}
// 	else
// 	{
 		CDialogEx::OnSysCommand(nID, lParam);
// 	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CResolveSudokoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

void CResolveSudokoDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	m_normalFont.DeleteObject();
	m_wrongFont.DeleteObject();

	if ( m_pCellCtrl != nullptr )
	{
		for (auto i = 0; i < ROW; i++)
		{
				delete[] m_pCellCtrl[i];
				m_pCellCtrl[i] = nullptr;
		}
		delete[] m_pCellCtrl;
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CResolveSudokoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool CResolveSudokoDlg::CopyStartingTableTest()
{
	for ( auto x = 0; x < ROW; x++ )
	{
		for ( auto y = 0; y < COLUMN; y++)
		{
			if ( test_sudoko[x][y] )
			{
				char number[2] = {0};
				number[0] = test_sudoko[x][y] + '0';
				m_pCellCtrl[x][y].SetWindowText(number);
			}
		}
	}

	return true;
}

bool CResolveSudokoDlg::LoadTable()
{
	for ( int x = 0; x < ROW; x++ )
	{
		for ( int y = 0; y < COLUMN; y++)
		{
			if ( m_data.Get(y, x) != 0 )
			{
				char number[2] = {0};
				number[0] = m_data.Get(y, x) + '0';
				m_pCellCtrl[x][y].SetWindowText(number);
			}
		}
	}

	return true;
}

bool CResolveSudokoDlg::SaveTable()
{
	bool retVal = true;
	for ( int x = 0; x < ROW; x++ )
	{
		for ( int y = 0; y < COLUMN; y++)
		{
			CString number;
			m_pCellCtrl[x][y].GetWindowText(number);
			m_data.Set(y, x, atoi(number));

			//if (m_data.m_pCellVal[y][x] == 0) retVal = false;
		}
	}

	return retVal;
}

bool CResolveSudokoDlg::ResetWrongCellFont()
{
	for ( int x = 0; x < ROW; x++ )
	{
		for ( int y = 0; y < COLUMN; y++)
		{
			m_pCellCtrl[x][y].SetFont(&m_normalFont);
		}
	}

	return true;
}

void CResolveSudokoDlg::OnBnClickedCheck()
{
	ResetWrongCellFont();

	if ( SaveTable() == true && m_checker.CheckTable() == true)
	{
		MessageBox("Sudoko is correct", "Sudoko resolver", MB_OK | MB_ICONINFORMATION);//
	}
	else
	{
		MessageBox("Sudoko has mistakes", "Sudoko resolver", MB_OK | MB_ICONEXCLAMATION);
	}
}

void CResolveSudokoDlg::OnBnClickedResolve()
{
	SaveTable();


	if ( m_thinker.ResolveSudoko() == false )
	{
		MessageBox("Sudoko couldn't be resolved, because not enough numbers.", "Sudoko resolver", MB_OK | MB_ICONEXCLAMATION);
	}

	LoadTable();
}

void CResolveSudokoDlg::OnBnClickedClean()
{
	for ( int x = 0; x < ROW; x++ )
	{
		for ( int y = 0; y < COLUMN; y++)
		{
			m_data.Set(y, x, 0);
			m_pCellCtrl[x][y].SetWindowText("");
		}
	}

	m_data.Clean();
	m_data.Create();
	m_thinker.Clean();
}
