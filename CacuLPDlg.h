
// CacuLPDlg.h: 头文件
//

#pragma once


typedef struct NAMEVALUE_T
{
	LPCSTR pName;
	LPCSTR pValue;
}NameValue_t;

//WorkFileItem
typedef struct _ITEM_T {

	UINT		Index;
	LPCSTR		pName;
	CString 	pValue;
	int			vInt;
	float		vFloat;
}_Item_t;

// CCacuLPDlg 对话框
class CCacuLPDlg : public CDialogEx
{
// 构造
public:
	CCacuLPDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CACULP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
#define I_OutputPath			(0)//默认存储路径
#define I_Index					(1)//索引
#define I_FileName				(2)//索引
#define I_Number				(3)//索引


#define  DefConfTblSize		(4)
	const NameValue_t DefConfTbl[DefConfTblSize] =
	{
		{"DefPath"," "},
		{"Index","1"},
		{"FileName","宝贝的习题"},
		{"Number","36"},
	};

	_Item_t  m_Conf[DefConfTblSize];//默认配置文件缓存

	int A;
	int B;
	int C;
	int Result;
	int Index;

	CString m_MyWorkPath;
	CString m_OutputPath;
	CString m_DefConfPath;



	int IsInitOk = 0;
public:

	//加法0
	void GetAddition(int& a, int& b, int& Result);
	//减法1
	void GetSubtraction(int& a, int& b, int& Result);
	//乘法2
	void GetMultiplication(int& a, int& b, int& Result);
	//除法3
	void GetDivision(int& a, int& b, int& Result);

	//加加4
	void GetAddAdd(int& a, int& b, int& c, int& Result);
	//加减5
	void GetAddSub(int& a, int& b, int& c, int& Result);
	//减加6
	void GetSubAdd(int& a, int& b, int& c, int& Result);
	//减减7
	void GetSubSub(int& a, int& b, int& c, int& Result);
	//乘加8
	void GetMulAdd(int& a, int& b, int& c, int& Result);
	//加乘9
	void GetAddMul(int& a, int& b, int& c, int& Result);
	//除加10
	void GetDivAdd(int& a, int& b, int& c, int& Result);
	//加除11
	void GetAddDiv(int& a, int& b, int& c, int& Result);
	//乘减12
	void GetMulSub(int& a, int& b, int& c, int& Result);
	//减乘13
	void GetSubMul(int& a, int& b, int& c, int& Result);
	//除减14
	void GetDivSub(int& a, int& b, int& c, int& Result);
	//减除15
	void GetSubDiv(int& a, int& b, int& c, int& Result);



	void GetEquation(CString& Equation, CString& EquationWithAnswer);
	void CreatAWork(void);
	void RepairSpace(CString& Src, int TotalSize);


	void FileInit(void);

	//从字符串 中找到 换行或火车
	int ReplaceEndLine(char* pSrc, int* SOffeset);
	//从字符串 中找到 换行或火车
	int FindEndLineNum(char* pSrc, int vSize, int* Num);
	//
	int GetNameAndValue(char* pSrc, char** Value);


	void CreateConf(void);
	int DefConfRead(void);
	int DefConfWrite(void);
	BOOL FileTest();
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
	afx_msg void OnBnClickedOk();
	CMFCEditBrowseCtrl m_EditBrowse;
	CString m_EditBrowseValue;
	CString m_FileName;
	CEdit m_EditFileName;
	CEdit m_Number;
	CButton m_Add;
	CButton m_Sub;
	CButton m_Mul;
	CButton m_Div;
	CButton m_AddAdd;
	CButton m_AddSub;
	CButton m_SubAdd;
	CButton m_SubSub;
	CButton m_MulAdd;
	CButton m_AddMul;
	CButton m_DivAdd;
	CButton m_AddDiv;
	CButton m_MulSub;
	CButton m_SubMul;
	CButton m_DivSub;
	CButton m_SubDiv;
	afx_msg void OnEnChangeMfceditbrowse1();
	CButton m_AddSeq;
};
