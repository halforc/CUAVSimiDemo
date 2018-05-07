// SpeedDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CUAVSimDemo.h"
#include "SpeedDlg.h"
#include "afxdialogex.h"


// CSpeedDlg 对话框

IMPLEMENT_DYNAMIC(CSpeedDlg, CDialog)

CSpeedDlg::CSpeedDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSpeedDlg::IDD, pParent)
{

}

CSpeedDlg::~CSpeedDlg()
{
}

void CSpeedDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSpeedDlg, CDialog)
END_MESSAGE_MAP()


// CSpeedDlg 消息处理程序
