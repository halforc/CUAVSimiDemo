// UDPSetting.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CUAVSimDemo.h"
#include "UDPSetting.h"
#include "afxdialogex.h"


// CUDPSetting �Ի���

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


// CUDPSetting ��Ϣ�������


BOOL CUDPSetting::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  �ڴ���Ӷ���ĳ�ʼ��
    SetDlgItemText(IDC_EDIT1, L"10.110.0.1");
    SetDlgItemText(IDC_EDIT5, L"5656");

    SetDlgItemText(IDC_EDIT6, L"10.110.0.2");
    SetDlgItemText(IDC_EDIT7, L"5657");

    SetDlgItemText(IDC_EDIT8, L"00");

    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣:  OCX ����ҳӦ���� FALSE
}
