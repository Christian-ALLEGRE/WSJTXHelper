
// WSJTXHelperDlg.h : fichier d'en-t�te
//

#pragma once


// bo�te de dialogue CWSJTXHelperDlg
class CWSJTXHelperDlg : public CDialogEx
{
// Construction
public:
	CWSJTXHelperDlg(CWnd* pParent = NULL);	// constructeur standard
	void LoadComboList();
	void ManageWSJTX();
	void ManageMouse(int when);
	void EnableTX();
	void DisableTX();
	COLORREF GetColor(int when);


// Donn�es de bo�te de dialogue
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WSJTXHELPER_DIALOG };
#endif
	UINT_PTR m_nTimer;
	long m_TimerValue;
	long m_STimerValue;
	CProgressCtrl	m_Progress;
	CProgressCtrl	m_ProgressMn;
	POINT EnableTXPos;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Prise en charge de DDX/DDV


// Impl�mentation
protected:
	HICON m_hIcon;

	// Fonctions g�n�r�es de la table des messages
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonstart();
	afx_msg void OnBnClickedButtonstop();
	afx_msg void OnBnClickedButtoncalibrate();
};
