// ImageStatic.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CUAVSimDemo.h"
#include "ImageStatic.h"


// CImageStatic

IMPLEMENT_DYNAMIC(CImageStatic, CStatic)

CImageStatic::CImageStatic()
{

}

CImageStatic::~CImageStatic()
{
}


BEGIN_MESSAGE_MAP(CImageStatic, CStatic)
END_MESSAGE_MAP()



// CImageStatic ��Ϣ�������

BOOL CImageStatic::SetImage(LPCTSTR szFileName)
{
    BOOL bRet = FALSE;
    m_Image.Destroy(); //���ͷ���ǰ��Դ  
    bRet = (m_Image.Load(szFileName) == S_OK); //��������Դ  
    if(m_hWnd)
        Invalidate(FALSE);
    return bRet;
}


LRESULT CImageStatic::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    // TODO: �ڴ����ר�ô����/����û���  
    switch(message) {
        case(WM_ERASEBKGND) :
            return 1;
        case(WM_PAINT) :
        {
            PAINTSTRUCT ps;
            CDC *pDstDC = BeginPaint(&ps);

            //�ͻ���λ��  
            CRect rcClient;
            GetClientRect(&rcClient);

            //˫�����ͼ  
            {
                CMemDC memDC(*pDstDC, rcClient);
                CDC *pDC = &memDC.GetDC();

                //��䱳��ɫ  
                pDC->FillSolidRect(&rcClient, RGB(100, 100, 100));
                pDC->SetStretchBltMode(HALFTONE);

                if(!m_Image.IsNull()) {
                    //ԭͼ��С  
                    CRect rcSrc(0, 0, m_Image.GetWidth(), m_Image.GetHeight());
                    //����ԭͼ����  
                    double fZoomRate = min((double)rcClient.Width() / (double)rcSrc.Width(),
                                            (double)rcClient.Height() / (double)rcSrc.Height());
                    int cx = (int)(rcSrc.Width()*fZoomRate), cy = (int)(rcSrc.Height()*fZoomRate);
                    CRect rcDst(0, 0, cx, cy); //Ŀ���С  
                    rcDst.OffsetRect((rcClient.Width() - cx) / 2, (rcClient.Height() - cy) / 2);//����  

                    //��ͼ  
                    m_Image.Draw(pDC->m_hDC, rcDst, rcSrc);
                }
            }

            EndPaint(&ps);
            return 0;
        }
    }
    return CStatic::WindowProc(message, wParam, lParam);
}
