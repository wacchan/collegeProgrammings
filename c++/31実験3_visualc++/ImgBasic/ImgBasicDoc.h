
// ImgBasicDoc.h : CImgBasicDoc クラスのインターフェイス
//


#pragma once


class CImgBasicDoc : public CDocument
{
protected: // シリアル化からのみ作成します。
	CImgBasicDoc();
	DECLARE_DYNCREATE(CImgBasicDoc)

// 属性
public:

	CImgPgm		*p_Pgm0;
	CImgPgm		*p_Pgm1;
	CImgPgm		*p_Pgm2;
	CImgPgm		*p_Pgm0_temp;
	CImgPgm		*p_Pgm1_temp;

	CImgBmp		m_Bmp0;
	CImgBmp		m_Bmp1;
	CImgBmp		m_Bmp2;

	CString		m_OpenFileName;

	CString		m_Kind_of_Proc;
	CString		m_Kind_of_Proc_temp;

	BOOL		m_busy;
	BOOL		m_MouseFirst;
	

// 操作
public:
	void Check_Backup_Pgm0() ;
	void Check_Backup_Pgm1() ;



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
	virtual ~CImgBasicDoc();
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
	afx_msg void OnFileOpen();
	afx_msg void OnImgReverse();
	afx_msg void OnUpdateImgReverse(CCmdUI *pCmdUI);
	afx_msg void OnImgHistMake();
	afx_msg void OnUpdateImgHistMake(CCmdUI *pCmdUI);
	afx_msg void OnImgHistBin();
	afx_msg void OnUpdateImgHistBin(CCmdUI *pCmdUI);
	afx_msg void OnImgHistLinearT();
	afx_msg void OnUpdateImgHistLinearT(CCmdUI *pCmdUI);
	afx_msg void OnImgHistEquiv();
	afx_msg void OnUpdateImgHistEquiv(CCmdUI *pCmdUI);
	///////////////////////////////////////////////////////////
	afx_msg void OnImgFilterMaskSmooth();
	afx_msg void OnUpdateImgFilterMaskSmooth(CCmdUI *pCmdUI);
	afx_msg void OnImgFilterMaskLaplace();
	afx_msg void OnUpdateImgFilterMaskLaplace(CCmdUI *pCmdUI);
	afx_msg void OnImgFilterMask1();
	afx_msg void OnUpdateImgFilterMask1(CCmdUI *pCmdUI);
	afx_msg void OnImgFilterMask2();
	afx_msg void OnUpdateImgFilterMask2(CCmdUI *pCmdUI);
	afx_msg void OnImgFilterMask3();
	afx_msg void OnUpdateImgFilterMask3(CCmdUI *pCmdUI);
	afx_msg void OnImgFilterMedian();
	afx_msg void OnUpdateImgFilterMedian(CCmdUI *pCmdUI);
	afx_msg void OnImgFilterWhiteGause();
	afx_msg void OnUpdateImgFilterWhiteGause(CCmdUI *pCmdUI);
	afx_msg void OnImgFilterWhiteImpulse();
	afx_msg void OnUpdateImgFilterWhiteImpulse(CCmdUI *pCmdUI);
	///////////////////////////////////////////////////////////
	afx_msg void OnImg1to0();
	afx_msg void OnUpdateImg1to0(CCmdUI *pCmdUI);
	afx_msg void OnImgBackup0();
	afx_msg void OnUpdateImgBackup0(CCmdUI *pCmdUI);
	afx_msg void OnImgBackup1();
	afx_msg void OnUpdateImgBackup1(CCmdUI *pCmdUI);
	///////////////////////////////////////////////////////////
	afx_msg void OnImgThinning();
	afx_msg void OnUpdateImgThinning(CCmdUI *pCmdUI);
	afx_msg void OnImgZeroCross();
	afx_msg void OnUpdateImgZeroCross(CCmdUI *pCmdUI);
	///////////////////////////////////////////////////////////
	afx_msg void OnImgFileSave0();
	afx_msg void OnUpdateImgFileSave0(CCmdUI *pCmdUI);
	afx_msg void OnImgFileSave1();
	afx_msg void OnUpdateImgFileSave1(CCmdUI *pCmdUI);
};
