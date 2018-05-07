#pragma once


// CUDPSetting 对话框

class CUDPSetting : public CDialog
{
	DECLARE_DYNAMIC(CUDPSetting)

public:
	CUDPSetting(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUDPSetting();

// 对话框数据
	enum { IDD = IDD_UDPSETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
};
