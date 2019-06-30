
// TestDoc.h : CTestDoc �N���X�̃C���^�[�t�F�C�X
//


#pragma once


class CTestDoc : public CDocument
{
protected: // �V���A��������̂ݍ쐬���܂��B
	CTestDoc();
	DECLARE_DYNCREATE(CTestDoc)

// ����
public:
	BOOL m_DrawFlag;
    BOOL m_CharFlag;
	int m_Number;
	double m_Num2;


// ����
public:

// �I�[�o�[���C�h
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ����
public:
	virtual ~CTestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �����n���h���[�̌����R���e���c��ݒ肷��w���p�[�֐�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnMydraw();
	afx_msg void OnMyerase();
	afx_msg void OnUpdateMydraw(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMyerase(CCmdUI *pCmdUI);
	afx_msg void OnMychar();
};
