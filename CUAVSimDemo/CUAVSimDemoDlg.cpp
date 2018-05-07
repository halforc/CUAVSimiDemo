
// CUAVSimDemoDlg.cpp : 实现文件
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

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CCUAVSimDemoDlg 对话框



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


// CCUAVSimDemoDlg 消息处理程序

BOOL CCUAVSimDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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
	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
    m_menu.LoadMenuW(IDR_MENU1);
    SetMenu(&m_menu);

    

    m_ImagStatic1.SetImage(L".//res//dyt.png");
    m_ImagStatic2.SetImage(L".//res//target.png");

    m_tab1.InsertItem(0, L"轨迹外推");
    m_tab1.InsertItem(1, L"速度");
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

    m_tab2.InsertItem(0, L"俯冲数据");

    m_tab2.GetClientRect(&rc);
    rc.top += 40;
    rc.left += 20;
    rc.right -= 20;
    rc.bottom -= 10;
    m_listCtrl.Create(LVS_REPORT | LVS_ALIGNLEFT, rc, &m_tab2, 1900);
    m_listCtrl.SetExtendedStyle(m_listCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
    // 为列表视图控件添加三列   
    m_listCtrl.InsertColumn(0, _T("时间"), LVCFMT_CENTER, rc.Width() / 4, 0);
    m_listCtrl.InsertColumn(1, _T("经度"), LVCFMT_CENTER, rc.Width() / 4, 1);
    m_listCtrl.InsertColumn(2, _T("纬度"), LVCFMT_CENTER, rc.Width() / 4, 2);
    m_listCtrl.InsertColumn(2, _T("高度"), LVCFMT_CENTER, rc.Width() / 4, 3);
    // 在列表视图控件中插入列表项，并设置列表子项文本   
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

    HICON hIcon[3];      // 图标句柄数组   
    HTREEITEM hRoot;     // 树的根节点的句柄   
    HTREEITEM hCataItem; // 可表示任一分类节点的句柄   
    HTREEITEM hArtItem;  // 可表示任一文章节点的句柄   
    m_treeCtrl.ModifyStyle(NULL, TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT);
    //// 加载三个图标，并将它们的句柄保存到数组   
    hIcon[0] = theApp.LoadIcon(IDI_ICON3);
    hIcon[1] = theApp.LoadIcon(IDI_ICON2);
    hIcon[2] = theApp.LoadIcon(IDI_ICON1);

    // 创建图像序列CImageList对象   
    m_imageList.Create(32, 32, ILC_COLOR32, 3, 3);
    // 将三个图标添加到图像序列   
    for(int i = 0; i<3; i++) {
        m_imageList.Add(hIcon[i]);
    }
    m_toolbar.CreateEx(this);
    //m_wndToolBar.LoadToolBar(IDR_MAINFRAME_256, 0, 0, TRUE, 0, 0, IDB_BITMAP1))
    m_toolbar.LoadToolBar(IDR_TOOLBAR1);          //加载工具栏资源  
    CRect rect;
    GetClientRect(&rect);                         //计算客户区大小  
    m_toolbar.MoveWindow(0, 0, rect.Width(), 24);   //必须设置工具栏显示位置 

    // 插入根节点   
    hRoot = m_treeCtrl.InsertItem(_T("实验"), 0, 0);
    // 在根节点下插入子节点   
    hCataItem = m_treeCtrl.InsertItem(_T("架次1"), 1, 1, hRoot, TVI_LAST);
    m_treeCtrl.SetItemData(hCataItem, 1);
    hArtItem = m_treeCtrl.InsertItem(_T("实验1"), 2, 2, hCataItem, TVI_LAST);
    m_treeCtrl.SetItemData(hArtItem, 2);
    hArtItem = m_treeCtrl.InsertItem(_T("实验2"), 2, 2, hCataItem, TVI_LAST);
    m_treeCtrl.SetItemData(hArtItem, 3);
 
    hCataItem = m_treeCtrl.InsertItem(_T("架次2"), 1, 1, hRoot, TVI_LAST);
    m_treeCtrl.SetItemData(hCataItem, 4);  
    hArtItem = m_treeCtrl.InsertItem(_T("实验1"), 2, 2, hCataItem, TVI_LAST);
    m_treeCtrl.SetItemData(hArtItem, 5); 
    hArtItem = m_treeCtrl.InsertItem(_T("实验2"), 2, 2, hCataItem, TVI_LAST); 
    m_treeCtrl.SetItemData(hArtItem, 6);
  
    hCataItem = m_treeCtrl.InsertItem(_T("架次3"), 1, 1, hRoot, TVI_LAST);
    m_treeCtrl.SetItemData(hCataItem, 7);
    hArtItem = m_treeCtrl.InsertItem(_T("实验1"), 2, 2, hCataItem, TVI_LAST); 
    m_treeCtrl.SetItemData(hArtItem, 8); 
    hArtItem = m_treeCtrl.InsertItem(_T("实验2"), 2, 2, hCataItem, TVI_LAST);
    m_treeCtrl.SetItemData(hArtItem, 9);

    m_listCtrl.ShowWindow(SW_SHOW);


    HBITMAP hBitmap;
    //关联图片ID    
    hBitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(),
                                 MAKEINTRESOURCE(IDB_PNG1),
                                 IMAGE_BITMAP, 0, 0,
                                 LR_LOADMAP3DCOLORS);
    //获得指向静态控件的指针      
    CStatic *pStatic = (CStatic *)GetDlgItem(IDC_STATIC1);//控件ID       
    //设置静态控件的样式，使其可以使用位图，并试位标显示使居中      
    pStatic->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
    //设置静态控件显示位图      
    pStatic->SetBitmap(hBitmap);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCUAVSimDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCUAVSimDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCUAVSimDemoDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO:  在此添加控件通知处理程序代码

    m_pDlg[m_curIndex]->ShowWindow(SW_HIDE);

    m_curIndex = m_tab1.GetCurSel();

    m_pDlg[m_curIndex]->ShowWindow(SW_SHOW);

    *pResult = 0;
}

void CCUAVSimDemoDlg::OnOpenFromFile()
{
    // TODO: Add your control notification handler code here   
    // 设置过滤器   
    TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||");
    // 构造打开文件对话框   
    CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
    CString strFilePath;

    // 显示打开文件对话框   
    if(IDOK == fileDlg.DoModal()) {
        // 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
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