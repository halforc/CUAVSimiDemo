// FileDataInput.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CUAVSimDemo.h"
#include "FileDataInput.h"
#include "afxdialogex.h"


// CFileDataInput �Ի���

IMPLEMENT_DYNAMIC(CFileDataInput, CDialog)

CFileDataInput::CFileDataInput(CWnd* pParent /*=NULL*/)
	: CDialog(CFileDataInput::IDD, pParent)
{

}

CFileDataInput::~CFileDataInput()
{
}

void CFileDataInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFileDataInput, CDialog)
END_MESSAGE_MAP()


// CFileDataInput ��Ϣ�������
