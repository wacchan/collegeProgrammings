
// ImgFFTDoc.h : CImgFFTDoc クラスのインターフェイス
//


#pragma once


class CImgFFTDoc : public CDocument
{
protected: // シリアル化からのみ作成します。
	CImgFFTDoc();
	DECLARE_DYNCREATE(CImgFFTDoc)

// 属性
public:
	CImgPgm		*p_Pgm0;
	CImgPgm		*p_Pgm1;
	CImgPgm		*p_Pgm2;
	CImgPgm		*p_Pgm0_temp;
	CImgPgm		*p_Pgm1_temp;
	
	CImgBmp		m_Bmp0;
	CImgBmp		m_Bmp1;
	CImgBmp		m_Bmp1_rev;

	CString		m_OpenFileName;

	double		m_freq1;
	double		m_freq2;
	double		m_rotate;
	int			m_kind;

	CCompMat	*Comp_mat;
	CCompMat	*Comp_mat_temp;

	int			m_disp_kind; // 0:Power, 1:Real, 2:Imag
	BOOL		m_FFT_Flag;

	BOOL		m_FFTImgGainFlag;
	double		m_FftMax;
	double		m_FftMin;

	BOOL		m_Reverse_Flag;
	float		m_gain;


// 操作
public:
	void	Check_Backup_Pgm0() ;
	void	Check_Backup_Pgm1() ;
	void	Check_Backup_CMat() ;

	void	MakeReal(); 
	void	MakeImag(); 
	void	MakePower(); 

	CImgBmp		*GetBmp();

	void ReDrawPgm1();


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
	virtual ~CImgFFTDoc();
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
	afx_msg void OnImg1Reverse();
	afx_msg void OnUpdateImg1Reverse(CCmdUI *pCmdUI);
	afx_msg void OnImgFFT();
	afx_msg void OnUpdateImgFFT(CCmdUI *pCmdUI);
	afx_msg void OnImgIFFT();
	afx_msg void OnUpdateImgIFFT(CCmdUI *pCmdUI);
	afx_msg void OnImgFilter1();
	afx_msg void OnUpdateImgFilter1(CCmdUI *pCmdUI);
	afx_msg void OnImgFilter2();
	afx_msg void OnUpdateImgFilter2(CCmdUI *pCmdUI);
	afx_msg void OnImgFilter3();
	afx_msg void OnUpdateImgFilter3(CCmdUI *pCmdUI);
	afx_msg void OnImg1Real();
	afx_msg void OnUpdateImg1Real(CCmdUI *pCmdUI);
	afx_msg void OnImg1Power();
	afx_msg void OnUpdateImg1Power(CCmdUI *pCmdUI);
	afx_msg void OnImg1Ima();
	afx_msg void OnUpdateImg1Ima(CCmdUI *pCmdUI);
	afx_msg void OnImgfileMakeFig();
	afx_msg void OnImg1GainFix();
	afx_msg void OnUpdateImg1GainFix(CCmdUI *pCmdUI);
	afx_msg void OnImgBackup0();
	afx_msg void OnUpdateImgBackup0(CCmdUI *pCmdUI);
	afx_msg void OnImgBackup1();
	afx_msg void OnUpdateImgBackup1(CCmdUI *pCmdUI);
	afx_msg void OnImgFileSave0();
	afx_msg void OnUpdateImgFileSave0(CCmdUI *pCmdUI);
	afx_msg void OnImgFileSave1();
	afx_msg void OnUpdateImgFileSave1(CCmdUI *pCmdUI);
};
