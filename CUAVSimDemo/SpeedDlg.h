#pragma once


// CSpeedDlg �Ի���

class CSpeedDlg : public CDialog
{
	DECLARE_DYNAMIC(CSpeedDlg)

public:
	CSpeedDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSpeedDlg();

// �Ի�������
	enum { IDD = IDD_SPEEDDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
