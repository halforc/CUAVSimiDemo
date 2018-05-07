#pragma once


// CFileDataInput 对话框

class CFileDataInput : public CDialog
{
	DECLARE_DYNAMIC(CFileDataInput)

public:
	CFileDataInput(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFileDataInput();

// 对话框数据
	enum { IDD = IDD_FILEDATAINPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
