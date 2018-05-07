// PathSimiDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CUAVSimDemo.h"
#include "PathSimiDlg.h"
#include "afxdialogex.h"
#include <atlimage.h>
#include "resource.h"
// CPathSimiDlg 对话框

IMPLEMENT_DYNAMIC(CPathSimiDlg, CDialog)

CPathSimiDlg::CPathSimiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPathSimiDlg::IDD, pParent)
{

}

CPathSimiDlg::~CPathSimiDlg()
{
}

void CPathSimiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_STATIC_PATH, m_imageStatic);
}


BEGIN_MESSAGE_MAP(CPathSimiDlg, CDialog)
    ON_WM_SIZE()
    ON_WM_PAINT()
END_MESSAGE_MAP()


// CPathSimiDlg 消息处理程序


void CPathSimiDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);

    if(nType != SIZE_MINIMIZED)  //判断窗口是不是最小化了，因为窗口最小化之后 ，窗口的长和宽会变成0，当前一次变化的时就会出现除以0的错误操作
    {
        ReSize();
    }
    // TODO:  在此处添加消息处理程序代码
}


BOOL CPathSimiDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  在此添加额外的初始化
    //此处代码  
   

    CRect rect;
    GetClientRect(&rect);     //取客户区大小    
    old.x = rect.right - rect.left;
    old.y = rect.bottom - rect.top;
    int cx = GetSystemMetrics(SM_CXFULLSCREEN);
    int cy = GetSystemMetrics(SM_CYFULLSCREEN);
    CRect rt;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &rt, 0);
    cy = rt.bottom;
    MoveWindow(0, 0, cx, cy);

    m_imageStatic.SetImage(L"./res/path.PNG");
    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}

void CPathSimiDlg::ReSize(void)
{
    float fsp[2];
    POINT Newp; //获取现在对话框的大小  
    CRect recta;
    GetClientRect(&recta);     //取客户区大小    
    Newp.x = recta.right - recta.left;
    Newp.y = recta.bottom - recta.top;
    fsp[0] = (float)Newp.x / old.x;
    fsp[1] = (float)Newp.y / old.y;
    CRect Rect;
    int woc;
    CPoint OldTLPoint, TLPoint; //左上角  
    CPoint OldBRPoint, BRPoint; //右下角  
    HWND  hwndChild = ::GetWindow(m_hWnd, GW_CHILD);  //列出所有控件    
    while(hwndChild) {
        woc = ::GetDlgCtrlID(hwndChild);//取得ID  
        GetDlgItem(woc)->GetWindowRect(Rect);
        ScreenToClient(Rect);
        OldTLPoint = Rect.TopLeft();
        TLPoint.x = long(OldTLPoint.x*fsp[0]);
        TLPoint.y = long(OldTLPoint.y*fsp[1]);
        OldBRPoint = Rect.BottomRight();
        BRPoint.x = long(OldBRPoint.x *fsp[0]);
        BRPoint.y = long(OldBRPoint.y *fsp[1]);
        Rect.SetRect(TLPoint, BRPoint);
        GetDlgItem(woc)->MoveWindow(Rect, TRUE);
        hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
    }
    old = Newp;
}

void CPathSimiDlg::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO:  在此处添加消息处理程序代码
    // 不为绘图消息调用 CDialog::OnPaint()
}
