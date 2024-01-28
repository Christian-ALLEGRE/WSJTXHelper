// WSJTXHelperDlg.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "WSJTXHelper.h"
#include "WSJTXHelperDlg.h"
#include "afxdialogex.h"
#include "KeyDef.h"
#include "RegKey.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// boîte de dialogue CAboutDlg utilisée pour la boîte de dialogue 'À propos de' pour votre application

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Données de boîte de dialogue
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

// Implémentation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// boîte de dialogue CWSJTXHelperDlg



CWSJTXHelperDlg::CWSJTXHelperDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_WSJTXHELPER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWSJTXHelperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESSSEC, m_Progress);
	DDX_Control(pDX, IDC_PROGRESSMIN, m_ProgressMn);
}

BEGIN_MESSAGE_MAP(CWSJTXHelperDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTONSTART, &CWSJTXHelperDlg::OnBnClickedButtonstart)
	ON_BN_CLICKED(IDC_BUTTONSTOP, &CWSJTXHelperDlg::OnBnClickedButtonstop)
	ON_BN_CLICKED(IDC_BUTTONCALIBRATE, &CWSJTXHelperDlg::OnBnClickedButtoncalibrate)
END_MESSAGE_MAP()

CString IString(long i)
{
	char Buff[16];
	sprintf_s(Buff, "%i", i);
	return CString(Buff);
}

// gestionnaires de messages pour CWSJTXHelperDlg
#define TIMERMAX 15
CWSJTXHelperDlg* Dlg = NULL;


const COLORREF rgbRed = 0x000000FF;
const COLORREF rgbGreen = 0x0000FF00;

COLORREF CWSJTXHelperDlg::GetColor(int when)
{
	if (((when >= 0) && (when <= 14))
		||
		((when >= 30) && (when <= 44)))
		return rgbRed;
	else
		return rgbGreen;
}

void CALLBACK EXPORT TimerProc(
	HWND hWnd,			// handle of CWnd that called SetTimer
	UINT nMsg,			// WM_TIMER
	UINT_PTR nIDEvent,  // timer identification
	DWORD dwTime		// system time
)
{
	SYSTEMTIME st;
	GetSystemTime(&st);
	Dlg->m_TimerValue = st.wSecond % TIMERMAX;
	if (Dlg->m_TimerValue != Dlg->m_STimerValue)
	{
		Dlg->SetDlgItemText(IDC_MESSAGE, CString("Monitoring... (") + IString(Dlg->m_TimerValue) + "/" + IString(st.wSecond) + ")");
		Dlg->m_Progress.SetBarColor(Dlg->GetColor(st.wSecond));
		Dlg->m_Progress.SetPos(Dlg->m_TimerValue);
		Dlg->m_ProgressMn.SetPos(st.wSecond);
		Dlg->m_STimerValue = Dlg->m_TimerValue;
		Dlg->ManageMouse(st.wSecond);
	}
}

char buff[10];
char* Str2Char(CString s)
{
	for (int i = 0; i < s.GetLength(); i++)
		buff[i] = (char)s.GetBuffer(0)[i];
	buff[s.GetLength()] = '\0';
	return buff;
}

BOOL CWSJTXHelperDlg::OnInitDialog()
{
	Dlg = this;
	CDialogEx::OnInitDialog();

	// Ajouter l'élément de menu "À propos de..." au menu Système.

	// IDM_ABOUTBOX doit se trouver dans la plage des commandes système.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// Définir l'icône de cette boîte de dialogue.  L'infrastructure effectue cela automatiquement
	//  lorsque la fenêtre principale de l'application n'est pas une boîte de dialogue
	SetIcon(m_hIcon, TRUE);			// Définir une grande icône
	SetIcon(m_hIcon, FALSE);		// Définir une petite icône

	// TODO: ajoutez ici une initialisation supplémentaire
	EnableTXPos.x = 0;
	EnableTXPos.y = 0;
	// Restore window position
	WINDOWPLACEMENT wp;
	wp.length = sizeof wp;
	if (GetWindowPlacement(&wp))
	{
		int top = atoi(Str2Char(GetUserKey(CString(TOP)).GetBuffer(0)));
		int left = atoi(Str2Char(GetUserKey(CString(LEFT)).GetBuffer(0)));
		int bottom = atoi(Str2Char(GetUserKey(CString(BOTTOM)).GetBuffer(0)));
		int right = atoi(Str2Char(GetUserKey(CString(RIGHT)).GetBuffer(0)));
		if ((bottom > top) && (right > left)) // Values where stored in regitry
		{
			// Retore position and size
			wp.rcNormalPosition.top = top;
			wp.rcNormalPosition.left = left;
			wp.rcNormalPosition.bottom = bottom;
			wp.rcNormalPosition.right = right;
			SetWindowPlacement(&wp);

			// Restore CheckBoxes
			CButton* cb = (CButton*)GetDlgItem(IDC_CHECK1ST);
			cb->SetCheck(GetUserKey(CString(FIRST)) == "1" ? 1 : 0);
			cb = (CButton*)GetDlgItem(IDC_CHECKONLY1);
			cb->SetCheck(GetUserKey(CString(ONLY1)) == "1" ? 1 : 0);
			cb = (CButton*)GetDlgItem(IDC_CHECKPREVENTAUTOREPLY);
			cb->SetCheck(GetUserKey(CString(PREVENTAUTOREPLY)) == "1" ? 1 : 0);

			EnableTXPos.x = atoi(Str2Char(GetUserKey(CString(ENABLETXPOSX)).GetBuffer(0)));
			EnableTXPos.y = atoi(Str2Char(GetUserKey(CString(ENABLETXPOSY)).GetBuffer(0)));
		}
	}

	CButton* button = (CButton*)GetDlgItem(IDC_BUTTONSTART);
	button->EnableWindow(EnableTXPos.x > 0 ? true : false);
	if (EnableTXPos.x > 0)
		SetDlgItemText(IDC_MESSAGE, CString("Using last Calibration"));
	else
		SetDlgItemText(IDC_MESSAGE, CString("Please Calibrate before Start"));
	button = (CButton*)GetDlgItem(IDC_BUTTONSTOP);
	button->EnableWindow(false);

	m_Progress.SetRange(0, TIMERMAX);
	m_ProgressMn.SetRange(0, 4 * TIMERMAX);

	return TRUE;  // retourne TRUE, sauf si vous avez défini le focus sur un contrôle
}

void CWSJTXHelperDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

void CWSJTXHelperDlg::OnClose()
{
	CreateUserKey(CString("F4LAA"));
	SetUserKey(CString(FIRST), IsDlgButtonChecked(IDC_CHECK1ST) ? CString("1") : CString("0"));
	SetUserKey(CString(ONLY1), IsDlgButtonChecked(IDC_CHECKONLY1) ? CString("1") : CString("0"));
	SetUserKey(CString(PREVENTAUTOREPLY), IsDlgButtonChecked(IDC_CHECKPREVENTAUTOREPLY) ? CString("1") : CString("0"));

	WINDOWPLACEMENT wp;
	wp.length = sizeof wp;
	if (GetWindowPlacement(&wp))
	{
		SetUserKey(CString(TOP), IString(wp.rcNormalPosition.top));
		SetUserKey(CString(LEFT), IString(wp.rcNormalPosition.left));
		SetUserKey(CString(BOTTOM), IString(wp.rcNormalPosition.bottom));
		SetUserKey(CString(RIGHT), IString(wp.rcNormalPosition.right));
	}

	CDialog::OnClose();
}

// Si vous ajoutez un bouton Réduire à votre boîte de dialogue, vous devez utiliser le code ci-dessous
//  pour dessiner l'icône.  Pour les applications MFC utilisant le modèle Document/Vue,
//  cela est fait automatiquement par l'infrastructure.

void CWSJTXHelperDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // contexte de périphérique pour la peinture

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrer l'icône dans le rectangle client
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Dessiner l'icône
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Le système appelle cette fonction pour obtenir le curseur à afficher lorsque l'utilisateur fait glisser
//  la fenêtre réduite.
HCURSOR CWSJTXHelperDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CWSJTXHelperDlg::OnBnClickedButtonstart()
{
	CButton* button = (CButton*)GetDlgItem(IDC_BUTTONSTART);
	button->EnableWindow(false);
	button = (CButton*)GetDlgItem(IDC_BUTTONSTOP);
	button->EnableWindow(true);

	SYSTEMTIME st;
	GetSystemTime(&st);	
	m_TimerValue = st.wSecond % TIMERMAX;
	SetDlgItemText(IDC_MESSAGE, CString("Monitoring... (") + IString(m_TimerValue) + "/" + IString(st.wSecond) + ")");
	m_Progress.SetBarColor(GetColor(st.wSecond));
	m_Progress.SetPos(m_TimerValue);
	m_ProgressMn.SetPos(st.wSecond);
	m_STimerValue = m_TimerValue;

	// Start Timer
	UINT_PTR timerId = 0;
	m_nTimer = SetTimer(timerId, 250, TimerProc);
}

void CWSJTXHelperDlg::OnBnClickedButtonstop()
{
	// Stop Timer
	UINT_PTR timerID = 0; 
	m_nTimer = SetTimer(timerID, -1, NULL);
	m_TimerValue = 0;
	m_STimerValue = 0;
	m_Progress.SetPos(0);
	m_ProgressMn.SetPos(0);

	CButton* button = (CButton*)GetDlgItem(IDC_BUTTONSTOP);
	button->EnableWindow(false);
	button = (CButton*)GetDlgItem(IDC_BUTTONSTART);
	button->EnableWindow(true);
	SetDlgItemText(IDC_MESSAGE, CString("Stopped."));
}

void CWSJTXHelperDlg::EnableTX()
{
	// Save cursor position
	POINT curPos;
	GetCursorPos(&curPos);

	// Enable TX
	SetCursorPos(EnableTXPos.x, EnableTXPos.y);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	Sleep(100);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

	// Restore mouse position
	SetCursorPos(curPos.x, curPos.y);
}

void CWSJTXHelperDlg::DisableTX()
{
	// Save cursor position
	POINT curPos;
	GetCursorPos(&curPos);

	// Disable TX
	SetCursorPos(EnableTXPos.x, EnableTXPos.y);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	Sleep(100);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

	// Restore mouse position
	SetCursorPos(curPos.x, curPos.y);
}

void CWSJTXHelperDlg::ManageMouse(int when)
{
	if (Dlg->IsDlgButtonChecked(IDC_CHECK1ST))
	{
		// 1st checked : 0s and 30s
		if (when == 0)
			EnableTX();
		if (Dlg->IsDlgButtonChecked(IDC_CHECKPREVENTAUTOREPLY))
			if (when == 3)
				DisableTX();

		if (!Dlg->IsDlgButtonChecked(IDC_CHECKONLY1))
		{
			if (when == 30)
				EnableTX();
			if (Dlg->IsDlgButtonChecked(IDC_CHECKPREVENTAUTOREPLY))
				if (when == 33)
					DisableTX();
		}
	}
	else
	{
		// 1st not checked : 15s and 45s
		if (when == 15)
			EnableTX();
		if (Dlg->IsDlgButtonChecked(IDC_CHECKPREVENTAUTOREPLY))
			if (when == 18)
				DisableTX();

		if (!Dlg->IsDlgButtonChecked(IDC_CHECKONLY1))
		{
			if (when == 45)
				EnableTX();
			if (Dlg->IsDlgButtonChecked(IDC_CHECKPREVENTAUTOREPLY))
				if (when == 48)
					DisableTX();
		}
	}
}

void CWSJTXHelperDlg::OnBnClickedButtoncalibrate()
{
	SetDlgItemText(IDC_MESSAGE, CString("Right Click on <<EnableTX>> button in WSJT-X"));
	Sleep(1000);
	int cpt = 0;
	while ( (GetAsyncKeyState(0x02) >= 0) && (cpt < 20) )
	{
		cpt++;
		// wait
		Sleep(250);
	}
	if (cpt < 20)
	{
		// Right click pressed, now Get Mouse position
		GetCursorPos(&EnableTXPos);
		SetDlgItemText(IDC_MESSAGE, CString("OK: Calibrated. X=") + IString(EnableTXPos.x) + " Y=" + IString(EnableTXPos.y));
		CButton* bStart = (CButton*)GetDlgItem(IDC_BUTTONSTART);
		bStart->EnableWindow(true);
		SetUserKey(CString(ENABLETXPOSX), IString(EnableTXPos.x));
		SetUserKey(CString(ENABLETXPOSY), IString(EnableTXPos.y));
	}
	else
		SetDlgItemText(IDC_MESSAGE, CString("KO: Not calibrated."));
}
