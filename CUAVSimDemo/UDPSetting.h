#pragma once


// CUDPSetting �Ի���

class CUDPSetting : public CDialog
{
	DECLARE_DYNAMIC(CUDPSetting)

public:
	CUDPSetting(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUDPSetting();

// �Ի�������
	enum { IDD = IDD_UDPSETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
};
