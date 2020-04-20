
// CalcDataDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


#ifndef _SPLIT_STRING
#define _SPLIT_STRING

inline int SplitString(const CString& string, CStringArray& strary, LPCTSTR lpszSeps, BOOL bOmitNullString = FALSE)
{
	strary.RemoveAll();
	CString str = string;
	str.TrimRight(lpszSeps);
	if(str.IsEmpty())
		return 0;
	int n = str.Find(lpszSeps, 0);
	int nCount = 0;
	while(n != -1)
	{
		CString strAdd = str.Left(n);
		strAdd.TrimLeft();
		strAdd.TrimRight();
		if(!bOmitNullString || !strAdd.IsEmpty())
		{
			strary.Add(strAdd);
			nCount++;
		}
		str = str.Mid(n + 1); 
		n = str.Find(lpszSeps, 0);
		
	}
	str.TrimLeft();
	str.TrimRight();
	if(!bOmitNullString || !str.IsEmpty())
	{
		strary.Add(str);
		nCount++;
	}
	return nCount;
}
#endif


// CCalcDataDlg 对话框
class CCalcDataDlg : public CDialog
{
// 构造
public:
	CCalcDataDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CALCDATA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnAnalyze();
	
	CString m_csFileName;
	CString m_csTime;
	int m_iLayerCount;
	int m_iTimeCount;
	CStringArray m_arDataString;
	CEdit m_edTimeValue;
	CComboBox m_comboItems;
	CEdit m_edStartTime;
	CEdit m_edTimeSpan;
	CEdit m_edRow;
	CEdit m_edColumn;
	afx_msg void OnBnClickedBtnCalc();
	afx_msg void OnBnClickedBtnFilepath();
	CEdit m_edFilePath;
};
