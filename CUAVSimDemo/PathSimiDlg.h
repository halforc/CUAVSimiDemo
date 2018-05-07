#pragma once
#include "ImageStatic.h"

// CPathSimiDlg 对话框

class CPathSimiDlg : public CDialog
{
	DECLARE_DYNAMIC(CPathSimiDlg)

public:
	CPathSimiDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPathSimiDlg();

// 对话框数据
	enum { IDD = IDD_PATHSIMIDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
