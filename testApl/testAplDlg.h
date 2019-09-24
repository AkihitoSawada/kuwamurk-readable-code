
// testAplDlg.h : �w�b�_�[ �t�@�C��
//

#pragma once
#include "afxwin.h"


// CtestAplDlg �_�C�A���O
class CtestAplDlg : public CDialogEx
{
// �R���X�g���N�V����
public:
	CtestAplDlg(CWnd* pParent = NULL);	// �W���R���X�g���N�^�[

// �_�C�A���O �f�[�^
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTAPL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �T�|�[�g


// ����
protected:
	HICON m_hIcon;
    std::wstring m_dicFile; //!< �����t�@�C��

	// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

    //!< �w�肵���t�@�C������P�����ǂݍ���
    // @param   dicFile [i]�����t�@�C����
    // @param   titleWord   [o]�ǂݏo�������o����
    // @retval  true or false
    bool readDictionaryData(const std::wstring &dicFile,std::wstring &titleWord);

public:
    afx_msg void OnEnChangeEdit1();
    CEdit m_wordTitleEdit;
};
