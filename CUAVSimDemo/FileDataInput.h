#pragma once


// CFileDataInput �Ի���

class CFileDataInput : public CDialog
{
	DECLARE_DYNAMIC(CFileDataInput)

public:
	CFileDataInput(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFileDataInput();

// �Ի�������
	enum { IDD = IDD_FILEDATAINPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
