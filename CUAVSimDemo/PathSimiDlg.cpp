// PathSimiDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CUAVSimDemo.h"
#include "PathSimiDlg.h"
#include "afxdialogex.h"
#include <atlimage.h>
#include "resource.h"
// CPathSimiDlg �Ի���

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


// CPathSimiDlg ��Ϣ�������


void CPathSimiDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);

    if(nType != SIZE_MINIMIZED)  //�жϴ����ǲ�����С���ˣ���Ϊ������С��֮�� �����ڵĳ��Ϳ����0����ǰһ�α仯��ʱ�ͻ���ֳ���0�Ĵ������
    {
        ReSize();
    }
    // TODO:  �ڴ˴������Ϣ����������
}


BOOL CPathSimiDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  �ڴ���Ӷ���ĳ�ʼ��
    //�˴�����  
   

    CRect rect;
    GetClientRect(&rect);     //ȡ�ͻ�����С    
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
    // �쳣:  OCX ����ҳӦ���� FALSE
}

void CPathSimiDlg::ReSize(void)
{
    float fsp[2];
    POINT Newp; //��ȡ���ڶԻ���Ĵ�С  
    CRect recta;
    GetClientRect(&recta);     //ȡ�ͻ�����С    
    Newp.x = recta.right - recta.left;
    Newp.y = recta.bottom - recta.top;
    fsp[0] = (float)Newp.x / old.x;
    fsp[1] = (float)Newp.y / old.y;
    CRect Rect;
    int woc;
    CPoint OldTLPoint, TLPoint; //���Ͻ�  
    CPoint OldBRPoint, BRPoint; //���½�  
    HWND  hwndChild = ::GetWindow(m_hWnd, GW_CHILD);  //�г����пؼ�    
    while(hwndChild) {
        woc = ::GetDlgCtrlID(hwndChild);//ȡ��ID  
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
    // TODO:  �ڴ˴������Ϣ����������
    // ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
}
