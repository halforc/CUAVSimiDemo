// UDPSetting.cpp : 实现文件
//

#include "stdafx.h"
#include "CUAVSimDemo.h"
#include "UDPSetting.h"
#include "afxdialogex.h"


// CUDPSetting 对话框

IMPLEMENT_DYNAMIC(CUDPSetting, CDialog)

CUDPSetting::CUDPSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CUDPSetting::IDD, pParent)
{

}

CUDPSetting::~CUDPSetting()
{
}

void CUDPSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUDPSetting, CDialog)
END_MESSAGE_MAP()


// CUDPSetting 消息处理程序


BOOL CUDPSetting::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  在此添加额外的初始化
    SetDlgItemText(IDC_EDIT1, L"10.110.0.1");
    SetDlgItemText(IDC_EDIT5, L"5656");

    SetDlgItemText(IDC_EDIT6, L"10.110.0.2");
    SetDlgItemText(IDC_EDIT7, L"5657");

    SetDlgItemText(IDC_EDIT8, L"00");

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}
