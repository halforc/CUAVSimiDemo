#pragma once
#include "ImageStatic.h"

// CPathSimiDlg �Ի���

class CPathSimiDlg : public CDialog
{
	DECLARE_DYNAMIC(CPathSimiDlg)

public:
	CPathSimiDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPathSimiDlg();

// �Ի�������
	enum { IDD = IDD_PATHSIMIDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

    POINT old;
    CStatic m_static;
public:
    afx_msg void OnSize(UINT nType, int cx, int cy);
    virtual BOOL OnInitDialog();
    void ReSize();
    afx_msg void OnPaint();

    CImageStatic m_imageStatic;
};
