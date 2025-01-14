
// testAplDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "testApl.h"
#include "testAplDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CtestAplDlg ダイアログ



CtestAplDlg::CtestAplDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TESTAPL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    // 辞書ファイルのデフォルト名を取得する
    m_dicFile.append(L"c:\\data\\dictionary-data.txt");
}

void CtestAplDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT1, m_wordTitleEdit);
}

BEGIN_MESSAGE_MAP(CtestAplDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_EN_CHANGE(IDC_EDIT1, &CtestAplDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CtestAplDlg メッセージ ハンドラー

BOOL CtestAplDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // "バージョン情報..." メニューをシステム メニューに追加します。

    // IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL) {
        BOOL bNameValid;
        CString strAboutMenu;
        bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
        ASSERT(bNameValid);
        if (!strAboutMenu.IsEmpty()) {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
    //  Framework は、この設定を自動的に行います。
    SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
    SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

    // TODO: 初期化をここに追加します。
    // dictionary-data.txtから単語情報を読み込む
    std::wstring titleWord;
    do {    // ループしていません。エラー時に抜けるためにdo while を使用します
        if (false == readDictionaryData(m_dicFile, titleWord)) {
            break;
        }
        // 見出し語Editを初期化
        m_wordTitleEdit.SetWindowText(titleWord.c_str());

        return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
    } while (false);
    return FALSE;
}

void CtestAplDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX) {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    } else {
        CDialogEx::OnSysCommand(nID, lParam);
    }
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CtestAplDlg::OnPaint()
{
    if (IsIconic()) {
        CPaintDC dc(this); // 描画のデバイス コンテキスト

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // クライアントの四角形領域内の中央
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // アイコンの描画
        dc.DrawIcon(x, y, m_hIcon);
    } else {
        CDialogEx::OnPaint();
    }
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CtestAplDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}



bool CtestAplDlg::readDictionaryData(const std::wstring & dicFile, std::wstring &titleWord)
{
    CStdioFile cFile;
    if (!cFile.Open(dicFile.c_str(), CFile::modeRead)) {
        AfxMessageBox(L"単語ファイルの読み込みに失敗しました。");
        return false;
    }

    // todo：↓のコードでは、ファイルが開けない
    CString readStr;
    BYTE byRead[1024];
    ZeroMemory(byRead, sizeof(byRead));
    cFile.Read(byRead, _countof(byRead));
    cFile.Close();

    readStr = reinterpret_cast<LPCTSTR>(byRead);
    
    LPCWSTR pSeparator = nullptr;
    LPCWSTR pLast = readStr;
    while (pSeparator = wcsstr(readStr, L"\r\n")) {
        size_t szLength = pSeparator - pLast;
        pLast = pSeparator;
    }

    return true;
}

void CtestAplDlg::OnEnChangeEdit1()
{
    // TODO: これが RICHEDIT コントロールの場合、このコントロールが
    // この通知を送信するには、CDialogEx::OnInitDialog() 関数をオーバーライドし、
    // CRichEditCtrl().SetEventMask() を
    // OR 状態の ENM_CHANGE フラグをマスクに入れて呼び出す必要があります。

    // TODO: ここにコントロール通知ハンドラー コードを追加してください。
}
