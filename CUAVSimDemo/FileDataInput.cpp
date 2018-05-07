// FileDataInput.cpp : 实现文件
//

#include "stdafx.h"
#include "CUAVSimDemo.h"
#include "FileDataInput.h"
#include "afxdialogex.h"


// CFileDataInput 对话框

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


// CFileDataInput 消息处理程序
