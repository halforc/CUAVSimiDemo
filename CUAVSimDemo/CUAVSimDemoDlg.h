
// CUAVSimDemoDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "PathSimiDlg.h"
#include "SpeedDlg.h"
#include "DataList.h"
#include "ImageStatic.h"
// CCUAVSimDemoDlg �Ի���
class CCUAVSimDemoDlg : public CDialogEx
{
// ����
public:
	CCUAVSimDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CUAVSIMDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
    CMenu m_menu;

    int m_curIndex;
    CPathSimiDlg m_pathDlg;
    CSpeedDlg m_speedDlg;
    CDialog* m_pDlg[2];

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    CTabCtrl m_tab1;
    afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnOpenFromFile();
    afx_msg void OnOpenFromUDP();
    CTabCtrl m_tab2;
    CDataList m_listCtrl;
    CTreeCtrl m_treeCtrl;
    CImageList m_imageList;
    CImageList m_ImageList;

    CToolBar m_toolbar;

    CImageStatic m_ImagStatic1;
    CImageStatic m_ImagStatic2;
};
