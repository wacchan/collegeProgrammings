
// TestDoc.h : CTestDoc クラスのインターフェイス
//


#pragma once


class CTestDoc : public CDocument
{
protected: // シリアル化からのみ作成します。
	CTestDoc();
	DECLARE_DYNCREATE(CTestDoc)

// 属性
public:
	BOOL m_DrawFlag;
    BOOL m_CharFlag;
	int m_Number;
	double m_Num2;


// 操作
public:

// オーバーライド
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 実装
public:
	virtual ~CTestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成された、メッセージ割り当て関数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 検索ハンドラーの検索コンテンツを設定するヘルパー関数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnMydraw();
	afx_msg void OnMyerase();
	afx_msg void OnUpdateMydraw(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMyerase(CCmdUI *pCmdUI);
	afx_msg void OnMychar();
};
