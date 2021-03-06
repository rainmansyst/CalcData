
// CalcDataDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CalcData.h"
#include "CalcDataDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CCalcDataDlg 对话框




CCalcDataDlg::CCalcDataDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCalcDataDlg::IDD, pParent)
	, m_csTime(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalcDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_TIME, m_edTimeValue);
	DDX_Control(pDX, IDC_COMBO_ITEM, m_comboItems);
	DDX_Control(pDX, IDC_EDIT_STARTTIME, m_edStartTime);
	DDX_Control(pDX, IDC_EDIT_TIMESPAN, m_edTimeSpan);
	DDX_Control(pDX, IDC_EDIT2, m_edRow);
	DDX_Control(pDX, IDC_EDIT3, m_edColumn);
	DDX_Control(pDX, IDC_EDIT_FILEPATH, m_edFilePath);
}

BEGIN_MESSAGE_MAP(CCalcDataDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_ANALYZE, &CCalcDataDlg::OnBnClickedBtnAnalyze)
	ON_BN_CLICKED(IDC_BTN_CALC, &CCalcDataDlg::OnBnClickedBtnCalc)
	ON_BN_CLICKED(IDC_BTN_FILEPATH, &CCalcDataDlg::OnBnClickedBtnFilepath)
END_MESSAGE_MAP()

// CCalcDataDlg 消息处理程序

BOOL CCalcDataDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCalcDataDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCalcDataDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCalcDataDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCalcDataDlg::OnBnClickedBtnAnalyze()
{
	// TODO: Add your control notification handler code here
	for(int i=m_comboItems.GetCount()-1;i>=0;i--)
		m_comboItems.DeleteString(i);
	CStdioFile fileData;
	CString str;
	//m_csFileName = _T("d://1.txt");
	if(fileData.Open(m_csFileName,CFile::modeNoTruncate|CFile::modeRead) == false)
	{
		AfxMessageBox(_T("文件不存在！"));
	}
	else
	{
		while(fileData.ReadString(str))
		{
			if(str.Find(_T("Time")) != -1)
				m_edTimeValue.SetWindowTextW(str);
			if(str.Find(_T("NoDynamicItems")) != -1)
			{
				int iItemPos = str.Find(_T(" "));
				int iItemCount = _ttoi(str.Mid(iItemPos, str.GetLength() - iItemPos));
				while(iItemCount--)
				{
					fileData.ReadString(str);
					m_comboItems.AddString(str);
				}
				m_comboItems.SetCurSel(0);
			}
			if(str.Find(_T("NoGridPoints")) != -1)
			{
				int iItemPos = str.ReverseFind(' ');
				m_iLayerCount = _ttoi(str.Mid(iItemPos, str.GetLength()-iItemPos));
			}
			if(str == _T(""))
				break;
		}
		fileData.Close();
	}

}

void CCalcDataDlg::OnBnClickedBtnCalc()
{
	// TODO: Add your control notification handler code here
	CStdioFile fileData;
	m_arDataString.RemoveAll();
	int iItemIndex = m_comboItems.GetCurSel()+1;
	CString str = _T("");
	m_edStartTime.GetWindowText(str);
	int iStartTime = _ttoi(str);
	m_edTimeSpan.GetWindowText(str);
	int iTimeSpan = _ttoi(str);

	if(fileData.Open(m_csFileName,CFile::modeNoTruncate|CFile::modeRead) == false)
	{
		AfxMessageBox(_T("文件不存在！"));
	}
	else
	{		
		CString csContentIndex = _T("");
		int iLayerCount = 0;
		csContentIndex.Format(_T("\"tstep\" %d \"item\" %d \"layer\" %d"), iStartTime, iItemIndex, iLayerCount);
		BOOL bFindOne = false;
		
		CString strData = _T("");
		while(fileData.ReadString(str))
		{
			if(bFindOne)
			{
				strData += str;
			}
			if(str.Find(csContentIndex) != -1)
			{
				bFindOne = true;
			}
			if(str == _T("") && bFindOne)
			{
				CStringArray arStrData;
				SplitString(strData, arStrData, _T(" "));
				CString csRow, csColumn;
				m_edRow.GetWindowText(csRow);
				m_edColumn.GetWindowText(csColumn);
				int nDataIndex = (85-_ttoi(csRow))*57 + _ttoi(csColumn);
				CString csTemp = arStrData.GetAt(nDataIndex);
				m_arDataString.Add(csTemp);
				strData = _T("");
				iLayerCount++;
				if(iLayerCount >= m_iLayerCount)
				{
					iStartTime += iTimeSpan;
					iLayerCount = 0;
				}
				csContentIndex.Format(_T("\"tstep\" %d \"item\" %d \"layer\" %d"), iStartTime, iItemIndex, iLayerCount);
				bFindOne = false;		
			}
		}	
		fileData.Close();
	}
	CStdioFile fileOutput;
	CString csFile = _T("d://resultOut.txt");
	//记录数组的顺序， tstep 0 layer 0 tstep 0 layer 1...
	if(fileOutput.Open(csFile , CFile::modeCreate|CFile::modeReadWrite))
	{
		int nSize = m_arDataString.GetSize();
		int nTimeStepSize = nSize/m_iLayerCount;
		for(int i=m_iLayerCount-1;i>=0;i--)
		{
			CString csTempData = _T("");
			for(int j=0;j<nTimeStepSize;j++)
			{
				csTempData += m_arDataString.GetAt(j*m_iLayerCount+i);
				csTempData += _T(" ");
			}
			fileOutput.WriteString(csTempData);
			fileOutput.WriteString(_T("\n"));
		}
		AfxMessageBox(_T("写入成功"));
	}

}

void CCalcDataDlg::OnBnClickedBtnFilepath()
{
	// TODO: Add your control notification handler code here
	BOOL isOpen = TRUE;
	CString defaultDir = _T("D:\\");
	CString defaultFile = L"test.txt";
	CString filter = L"文本(*.txt)|*.txt|所有类型(*.*)|*.*||";
	CFileDialog openFileDlg(isOpen, NULL, defaultDir + "\\" + defaultFile, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, NULL);
	INT_PTR result = openFileDlg.DoModal();//是否选中文件，或取消了选择
	if (result == IDOK)
	{
		CString pathName, fileName,titleName,extName;
		pathName = openFileDlg.GetPathName();//得到完整的文件名，包括目录名和扩展名如：c:/test/test1.txt
		fileName = openFileDlg.GetFileName();//得到完整的文件名，包括扩展名如：test1.txt
		titleName=openFileDlg.GetFileTitle();//得到完整的文件名，不包括目录名和扩展名如：test1
		extName = openFileDlg.GetFileExt();// 得到完整的文件扩展名，如：txt
		m_edFilePath.SetWindowText(pathName);
		m_csFileName = pathName;
	}

}
