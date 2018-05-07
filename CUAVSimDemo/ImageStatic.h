#pragma once
#include <atlimage.h>  
#include <afxglobals.h>  

// CImageStatic

class CImageStatic : public CStatic
{
	DECLARE_DYNAMIC(CImageStatic)

public:
	CImageStatic();
	virtual ~CImageStatic();
    BOOL SetImage(LPCTSTR szFileName);
protected:
    CImage m_Image;
	DECLARE_MESSAGE_MAP()
    virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};


