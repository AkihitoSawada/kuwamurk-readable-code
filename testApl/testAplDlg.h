
// testAplDlg.h : ヘッダー ファイル
//

#pragma once
#include "afxwin.h"


// CtestAplDlg ダイアログ
class CtestAplDlg : public CDialogEx
{
// コンストラクション
public:
	CtestAplDlg(CWnd* pParent = NULL);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTAPL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;
    std::wstring m_dicFile; //!< 辞書ファイル

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

    //!< 指定したファイルから単語情報を読み込む
    // @param   dicFile [i]辞書ファイル名
    // @param   titleWord   [o]読み出した見出し語
    // @retval  true or false
    bool readDictionaryData(const std::wstring &dicFile,std::wstring &titleWord);

public:
    afx_msg void OnEnChangeEdit1();
    CEdit m_wordTitleEdit;
};
