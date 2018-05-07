
// CUAVSimDemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CUAVSimDemo.h"
#include "CUAVSimDemoDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "FileDataInput.h"
#include "UDPSetting.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ID_ADDINFO   111115

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCUAVSimDemoDlg �Ի���



CCUAVSimDemoDlg::CCUAVSimDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCUAVSimDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCUAVSimDemoDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TAB1, m_tab1);
    DDX_Control(pDX, IDC_TAB2, m_tab2);
    DDX_Control(pDX, IDC_STATIC1, m_ImagStatic1);
    DDX_Control(pDX, IDC_STATIC2, m_ImagStatic2);
    DDX_Control(pDX, IDC_TREE1, m_treeCtrl);
}

BEGIN_MESSAGE_MAP(CCUAVSimDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CCUAVSimDemoDlg::OnTcnSelchangeTab1)
    ON_COMMAND(ID_32791, &CCUAVSimDemoDlg::OnOpenFromFile)
    ON_COMMAND(ID_32792, &CCUAVSimDemoDlg::OnOpenFromUDP)
END_MESSAGE_MAP()


// CCUAVSimDemoDlg ��Ϣ�������

BOOL CCUAVSimDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
    m_menu.LoadMenuW(IDR_MENU1);
    SetMenu(&m_menu);

    

    m_ImagStatic1.SetImage(L".//res//dyt.png");
    m_ImagStatic2.SetImage(L".//res//target.png");

    m_tab1.InsertItem(0, L"�켣����");
    m_tab1.InsertItem(1, L"�ٶ�");
    m_pathDlg.Create(IDD_PATHSIMIDLG,&m_tab1);
    m_speedDlg.Create(IDD_SPEEDDLG, &m_tab1);
    CRect rc;
    m_tab1.GetClientRect(&rc);
    rc.top += 20;
    rc.left += 2;
    rc.right -= 2;
    rc.bottom -= 1;
    m_pathDlg.MoveWindow(&rc);
    m_speedDlg.MoveWindow(&rc);

    m_pDlg[0] = &m_pathDlg;
    m_pDlg[1] = &m_speedDlg;

    m_speedDlg.ShowWindow(SW_HIDE);
    m_pathDlg.ShowWindow(SW_SHOW);
    m_tab1.SetCurSel(0);
    m_curIndex = 0;

    m_tab2.InsertItem(0, L"��������");

    m_tab2.GetClientRect(&rc);
    rc.top += 40;
    rc.left += 20;
    rc.right -= 20;
    rc.bottom -= 10;
    m_listCtrl.Create(LVS_REPORT | LVS_ALIGNLEFT, rc, &m_tab2, 1900);
    m_listCtrl.SetExtendedStyle(m_listCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
    // Ϊ�б���ͼ�ؼ��������   
    m_listCtrl.InsertColumn(0, _T("ʱ��"), LVCFMT_CENTER, rc.Width() / 4, 0);
    m_listCtrl.InsertColumn(1, _T("����"), LVCFMT_CENTER, rc.Width() / 4, 1);
    m_listCtrl.InsertColumn(2, _T("γ��"), LVCFMT_CENTER, rc.Width() / 4, 2);
    m_listCtrl.InsertColumn(2, _T("�߶�"), LVCFMT_CENTER, rc.Width() / 4, 3);
    // ���б���ͼ�ؼ��в����б���������б������ı�   
    m_listCtrl.InsertItem(0, _T("0"));
    m_listCtrl.SetItemText(0, 1, _T("0"));
    m_listCtrl.SetItemText(0, 2, _T("10"));
    m_listCtrl.SetItemText(0, 3, _T("10"));
    m_listCtrl.InsertItem(1, _T("1"));
    m_listCtrl.SetItemText(1, 1, _T("10"));
    m_listCtrl.SetItemText(1, 2, _T("20"));
    m_listCtrl.SetItemText(1, 3, _T("30"));
    m_listCtrl.InsertItem(2, _T("2"));
    m_listCtrl.SetItemText(2, 1, _T("30"));
    m_listCtrl.SetItemText(2, 2, _T("60"));
    m_listCtrl.SetItemText(2, 3, _T("90"));
    m_listCtrl.InsertItem(3, _T("3"));
    m_listCtrl.SetItemText(3, 1, _T("40"));
    m_listCtrl.SetItemText(3, 2, _T("80"));
    m_listCtrl.SetItemText(3, 3, _T("100"));

    HICON hIcon[3];      // ͼ��������   
    HTREEITEM hRoot;     // ���ĸ��ڵ�ľ��   
    HTREEITEM hCataItem; // �ɱ�ʾ��һ����ڵ�ľ��   
    HTREEITEM hArtItem;  // �ɱ�ʾ��һ���½ڵ�ľ��   
    m_treeCtrl.ModifyStyle(NULL, TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT);
    //// ��������ͼ�꣬�������ǵľ�����浽����   
    hIcon[0] = theApp.LoadIcon(IDI_ICON3);
    hIcon[1] = theApp.LoadIcon(IDI_ICON2);
    hIcon[2] = theApp.LoadIcon(IDI_ICON1);

    // ����ͼ������CImageList����   
    m_imageList.Create(32, 32, ILC_COLOR32, 3, 3);
    // ������ͼ����ӵ�ͼ������   
    for(int i = 0; i<3; i++) {
        m_imageList.Add(hIcon[i]);
    }
    m_toolbar.CreateEx(this);
    //m_wndToolBar.LoadToolBar(IDR_MAINFRAME_256, 0, 0, TRUE, 0, 0, IDB_BITMAP1))
    m_toolbar.LoadToolBar(IDR_TOOLBAR1);          //���ع�������Դ  
    CRect rect;
    GetClientRect(&rect);                         //����ͻ�����С  
    m_toolbar.MoveWindow(0, 0, rect.Width(), 24);   //�������ù�������ʾλ�� 

    // ������ڵ�   
    hRoot = m_treeCtrl.InsertItem(_T("ʵ��"), 0, 0);
    // �ڸ��ڵ��²����ӽڵ�   
    hCataItem = m_treeCtrl.InsertItem(_T("�ܴ�1"), 1, 1, hRoot, TVI_LAST);
    m_treeCtrl.SetItemData(hCataItem, 1);
    hArtItem = m_treeCtrl.InsertItem(_T("ʵ��1"), 2, 2, hCataItem, TVI_LAST);
    m_treeCtrl.SetItemData(hArtItem, 2);
    hArtItem = m_treeCtrl.InsertItem(_T("ʵ��2"), 2, 2, hCataItem, TVI_LAST);
    m_treeCtrl.SetItemData(hArtItem, 3);
 
    hCataItem = m_treeCtrl.InsertItem(_T("�ܴ�2"), 1, 1, hRoot, TVI_LAST);
    m_treeCtrl.SetItemData(hCataItem, 4);  
    hArtItem = m_treeCtrl.InsertItem(_T("ʵ��1"), 2, 2, hCataItem, TVI_LAST);
    m_treeCtrl.SetItemData(hArtItem, 5); 
    hArtItem = m_treeCtrl.InsertItem(_T("ʵ��2"), 2, 2, hCataItem, TVI_LAST); 
    m_treeCtrl.SetItemData(hArtItem, 6);
  
    hCataItem = m_treeCtrl.InsertItem(_T("�ܴ�3"), 1, 1, hRoot, TVI_LAST);
    m_treeCtrl.SetItemData(hCataItem, 7);
    hArtItem = m_treeCtrl.InsertItem(_T("ʵ��1"), 2, 2, hCataItem, TVI_LAST); 
    m_treeCtrl.SetItemData(hArtItem, 8); 
    hArtItem = m_treeCtrl.InsertItem(_T("ʵ��2"), 2, 2, hCataItem, TVI_LAST);
    m_treeCtrl.SetItemData(hArtItem, 9);

    m_listCtrl.ShowWindow(SW_SHOW);


    HBITMAP hBitmap;
    //����ͼƬID    
    hBitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(),
                                 MAKEINTRESOURCE(IDB_PNG1),
                                 IMAGE_BITMAP, 0, 0,
                                 LR_LOADMAP3DCOLORS);
    //���ָ��̬�ؼ���ָ��      
    CStatic *pStatic = (CStatic *)GetDlgItem(IDC_STATIC1);//�ؼ�ID       
    //���þ�̬�ؼ�����ʽ��ʹ�����ʹ��λͼ������λ����ʾʹ����      
    pStatic->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
    //���þ�̬�ؼ���ʾλͼ      
    pStatic->SetBitmap(hBitmap);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCUAVSimDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCUAVSimDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCUAVSimDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCUAVSimDemoDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������

    m_pDlg[m_curIndex]->ShowWindow(SW_HIDE);

    m_curIndex = m_tab1.GetCurSel();

    m_pDlg[m_curIndex]->ShowWindow(SW_SHOW);

    *pResult = 0;
}

void CCUAVSimDemoDlg::OnOpenFromFile()
{
    // TODO: Add your control notification handler code here   
    // ���ù�����   
    TCHAR szFilter[] = _T("�ı��ļ�(*.txt)|*.txt|�����ļ�(*.*)|*.*||");
    // ������ļ��Ի���   
    CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
    CString strFilePath;

    // ��ʾ���ļ��Ի���   
    if(IDOK == fileDlg.DoModal()) {
        // ���������ļ��Ի����ϵġ��򿪡���ť����ѡ����ļ�·����ʾ���༭����   
        strFilePath = fileDlg.GetPathName();
        //SetDlgItemText(IDC_OPEN_EDIT, strFilePath);
        CFileDataInput dlg;
        if(IDOK == dlg.DoModal()) {
            MessageBox(L"hello");
        }
    }
}

void CCUAVSimDemoDlg::OnOpenFromUDP()
{
    // TODO: Add your control notification handler code here   
    CUDPSetting dlg;
    if(IDOK == dlg.DoModal()) {
        MessageBox(L"wait data from UDP");
    }
}