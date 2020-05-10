
// CacuLPDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "CacuLP.h"
#include "CacuLPDlg.h"
#include "afxdialogex.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CCacuLPDlg 对话框

static int GetRand(int MIN, int MAX)//产生随机数
{
	int max;
	max = RAND_MAX;//rand()函数随机数的最大值
	return (int)(rand() * (MAX - MIN) / max + MIN);
}

CCacuLPDlg::CCacuLPDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CACULP_DIALOG, pParent)
	, m_EditBrowseValue(_T(""))
	, m_FileName(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	for (int i = 0; i < DefConfTblSize; i++)
	{
		m_Conf[i].Index = i;
		m_Conf[i].vFloat = 0.0;
		m_Conf[i].vInt = 0;
		m_Conf[i].pValue = _T("");
		m_Conf[i].pName = DefConfTbl[i].pName;
	}

	FileInit();//文件系统更新
}

void CCacuLPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCEDITBROWSE1, m_EditBrowse);
	DDX_Text(pDX, IDC_MFCEDITBROWSE1, m_EditBrowseValue);
	DDX_Control(pDX, IDC_EDIT1, m_EditFileName);
	DDX_Text(pDX, IDC_EDIT1, m_FileName);
	DDX_Control(pDX, IDC_EDIT2, m_Number);
	DDX_Control(pDX, IDC_CHECK1, m_Add);
	DDX_Control(pDX, IDC_CHECK2, m_Sub);
	DDX_Control(pDX, IDC_CHECK3, m_Mul);
	DDX_Control(pDX, IDC_CHECK4, m_Div);
	DDX_Control(pDX, IDC_CHECK5, m_AddAdd);
	DDX_Control(pDX, IDC_CHECK6, m_AddSub);
	DDX_Control(pDX, IDC_CHECK7, m_SubAdd);
	DDX_Control(pDX, IDC_CHECK16, m_SubSub);
	DDX_Control(pDX, IDC_CHECK8, m_MulAdd);
	DDX_Control(pDX, IDC_CHECK9, m_AddMul);
	DDX_Control(pDX, IDC_CHECK10, m_DivAdd);
	DDX_Control(pDX, IDC_CHECK11, m_AddDiv);
	DDX_Control(pDX, IDC_CHECK12, m_MulSub);
	DDX_Control(pDX, IDC_CHECK13, m_SubMul);
	DDX_Control(pDX, IDC_CHECK14, m_DivSub);
	DDX_Control(pDX, IDC_CHECK15, m_SubDiv);
	DDX_Control(pDX, IDC_CHECK17, m_AddSeq);
}

BEGIN_MESSAGE_MAP(CCacuLPDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CCacuLPDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_MFCEDITBROWSE1, &CCacuLPDlg::OnEnChangeMfceditbrowse1)
END_MESSAGE_MAP()


// CCacuLPDlg 消息处理程序

BOOL CCacuLPDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	m_EditBrowse.SetReadOnly(true);
	m_EditBrowse.EnableFolderBrowseButton(0, BIF_RETURNONLYFSDIRS | BIF_USENEWUI);
	m_EditBrowse.SetWindowText(m_Conf[I_OutputPath].pValue);//show default directory, when you click open,the dialog will whit this directory

	//m_EditBrowse.EnableFileBrowseButton(_T(""),
	//	_T("test File(*.txt)|*.txt|所有文件(*.*)|*.*||"));


	m_Add.SetCheck(1);
	m_Sub.SetCheck(1);
	m_Mul.SetCheck(1);
	m_Div.SetCheck(1);
	m_AddAdd.SetCheck(1);
	m_AddSub.SetCheck(1);
	m_SubAdd.SetCheck(1);
	m_SubSub.SetCheck(1);

	m_MulAdd.SetCheck(1);
	m_AddMul.SetCheck(1);
	m_DivAdd.SetCheck(1);
	m_AddDiv.SetCheck(1);

	m_MulSub.SetCheck(1);
	m_SubMul.SetCheck(1);
	m_DivSub.SetCheck(1);
	m_SubDiv.SetCheck(1);





	m_EditFileName.SetWindowText(m_Conf[I_FileName].pValue);
	m_Number.SetWindowText(m_Conf[I_Number].pValue);
	srand((unsigned int)time(NULL));


	IsInitOk = 1;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCacuLPDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}


int CCacuLPDlg::ReplaceEndLine(char* pSrc, int* SOffeset) {
	char* pNextSrc = pSrc;
	int DataLenth = 0;
	*SOffeset = 0;

	if (!(*pSrc))
	{
		return 0;
	}
	//除去数据前 \r \n
	while ((*pSrc == '\n') || (*pSrc == '\r'))
	{
		*pSrc = 0;
		pSrc++;
		(*SOffeset)++;
	}
	//获取数据
	while ((*pSrc != '\n') && (*pSrc != '\r'))
	{
		if (!(*pSrc))
		{
			break;
		}
		pSrc++;
		DataLenth++;
	}
	*pSrc = 0;
	return DataLenth;
}


int CCacuLPDlg::FindEndLineNum(char* pSrc, int vSize, int* Num)
{
	int tNum = 0;
	for (int i = 0; i < vSize; i++)
	{
		if (pSrc[i] == '\n')
		{
			tNum++;
		}
	}
	*Num = tNum;
	return  tNum;
}

int CCacuLPDlg::GetNameAndValue(char* pSrc, char** Value) {

	int tStatus = 0;

	while ((*pSrc))
	{
		if ((*pSrc) != ':') {
			pSrc++;
		}
		else
		{
			*pSrc = 0;
			*Value = pSrc + 1;
			tStatus++;
			break;
		}
	}
	return tStatus;
}



void CCacuLPDlg::CreateConf(void)
{

	CFile MyFile;
	CString tData;
	CFileException e;

	if (!MyFile.Open(m_DefConfPath, CFile::modeCreate | CFile::modeWrite, &e))
	{
		TRACE(_T("File could not be opened %d\n"), e.m_cause);
	}
	else
	{
		for (int i = 0; i < DefConfTblSize; i++) {
			if (i == I_OutputPath)
			{
				tData.Format("%s:%s\n", DefConfTbl[i].pName, m_MyWorkPath.GetString());//设置默认路径为当前文件所在路径
			}
			else
			{
				tData.Format("%s:%s\n", DefConfTbl[i].pName, DefConfTbl[i].pValue);
			}
			MyFile.Write(tData, tData.GetLength());
		}
		MyFile.Close();
		//3.读取conf.conf
		DefConfRead();
	}
}


//从默认配置文件 读取到 成员变量
int CCacuLPDlg::DefConfRead(void)
{
	CFile MyFile;
	CFileException e;
	int SOffset, datalen;
	ULONGLONG tStatus;
	char* pName, * pValue;
	char* tBuff, * tHead;


	if (!MyFile.Open(m_DefConfPath, CFile::modeRead, &e))
	{
		TRACE(_T("File could not be opened %d\n"), e.m_cause);
	}
	else
	{


		CString tData;

		tStatus = MyFile.GetLength();//获取长度
		tStatus += 2;//多余2字节，避免错误修改
		tBuff = new char[tStatus];
		if (tBuff)
		{
			memset(tBuff, 0, tStatus);
		}
		else
		{
			TRACE(_T("tBuff = new char[tStatus] Fail\n"));
		}
		MyFile.Read(tBuff, (UINT)MyFile.GetLength());//读取数据
		tHead = tBuff;
		do
		{
			//从读取的数据中 截取一个【名-值】 对
			datalen = ReplaceEndLine(tHead, &SOffset);
			if (datalen)
			{
				char MachedTimes = 0;
				//从【名-值】获取名字和值指针 
				pName = tHead + SOffset;
				tStatus = GetNameAndValue(pName, (char**)(&pValue));
				if (tStatus)
				{
					for (int i = 0; i < DefConfTblSize; i++)
					{
						if (!strcmp(pName, DefConfTbl[i].pName)) //匹配
						{
							MachedTimes++;
							m_Conf[i].pValue.Format("%s", pValue);
							break;
						}
					}
					if (!MachedTimes)
					{
						TRACE("未匹配，%s\n", pName);
					}
				}
				else
				{
					TRACE(_T("GetNameAndValue() Fail\n"));
				}
			}
			else
			{

			}
			tHead = tHead + SOffset + datalen + 1;
		} while (datalen);


		MyFile.Close();
		delete[] tBuff;
	}
	return 0;
}

//从成员变量 写入到 默认配置文件
int CCacuLPDlg::DefConfWrite(void)
{
	CFile MyFile;
	CFileException e;

	if (!MyFile.Open(m_DefConfPath, CFile::modeCreate | CFile::modeWrite, &e))
	{
		TRACE(_T("File could not be opened %d\n"), e.m_cause);
	}
	else
	{
		CString tData;

		for (int i = 0; i < DefConfTblSize; i++) {
			tData.Format("%s:%s\n", m_Conf[i].pName, m_Conf[i].pValue.GetString());
			MyFile.Write(tData, tData.GetLength());
		}
		MyFile.Close();
	}
	return 0;
}


void CCacuLPDlg::FileInit(void)
{
	//1.check the UserData Dictory
	CString tPath;
	CString tData;

	CFile MyFile;
	CFileException e;
	char pPath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, pPath);
	m_MyWorkPath.Format("%s", pPath);//1.获取 UserData目录
	m_DefConfPath = m_MyWorkPath + "\\Conf.conf";  //2.获取 Conf.conf目录


	//判断目录是否存在
	if (PathFileExists(m_DefConfPath.GetString()))//存在
	{
		//3.读取Conf.conf
		DefConfRead();

	}
	else//目录不存在
	{
		//创建文件夹
		CreateConf();
		
	}
	return;
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCacuLPDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCacuLPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



#define MinResult	(8)
//找到一个 a x b的组合
void CCacuLPDlg::GetMultiplication(int& a, int& b, int& Result)
{


	do
	{
		a = GetRand(2, 9);//2-9
		b = GetRand(2, 9);//2-9

	} while (0);//(a == b);

	Result = a * b;
}

//找到一个 a ÷ b的组合
void CCacuLPDlg::GetDivision(int& a, int& b, int& Result)
{

	do
	{
		Result = GetRand(2, 9);//2-9

		b = GetRand(2, 9);//2-9

	} while (0);// (Result == b);

	a = Result * b;

}


void CCacuLPDlg::GetAddition(int& a, int& b, int& Result)
{
	do
	{
		Result = GetRand(MinResult, 100);//2-9
		a = GetRand(2, 100);//2-9

	} while ((Result - a) < MinResult);

	b = Result - a;
}

void CCacuLPDlg::GetSubtraction(int& a, int& b, int& Result)
{

	do
	{
		a = GetRand(10, 100);//2-9
		b = GetRand(2, 100);//2-9

	} while ((a - b) < MinResult);
	Result = a - b;
}

//加加
void CCacuLPDlg::GetAddAdd(int& a, int& b, int& c, int& Result)
{
	do
	{
		GetAddition(a, b, Result);
		c = GetRand(MinResult, 100);//

	} while ((Result + c) > 100);
	Result += c;
}

//加减
void CCacuLPDlg::GetAddSub(int& a, int& b, int& c, int& Result)
{
	do
	{
		GetAddition(a, b, Result);
		c = GetRand(MinResult, 100);

	} while (((Result - c) > 100) || ((Result - c) < MinResult));
	Result -= c;
}
//减加
void CCacuLPDlg::GetSubAdd(int& a, int& b, int& c, int& Result)
{
	do
	{
		GetSubtraction(a, b, Result);
		c = GetRand(MinResult, 100);

	} while (((Result + c) > 100) || ((Result + c) < MinResult));
	Result += c;
}
//减减
void CCacuLPDlg::GetSubSub(int& a, int& b, int& c, int& Result)
{
	do
	{
		GetSubtraction(a, b, Result);
		c = GetRand(MinResult, 100);

	} while (((Result - c) > 100) || ((Result - c) < MinResult));
	Result -= c;
}


//乘加
void CCacuLPDlg::GetMulAdd(int& a, int& b, int& c, int& Result)
{

	do
	{
		GetMultiplication(a, b, Result);
		c = GetRand(MinResult, 100);

	} while ((Result + c) > 100);
	Result += c;

}

//加乘
void CCacuLPDlg::GetAddMul(int& a, int& b, int& c, int& Result)
{

	do
	{
		GetMultiplication(b, c, Result);
		a = GetRand(MinResult, 100);
	} while ((Result + a) > 100);
	Result += a;
}

//除加
void CCacuLPDlg::GetDivAdd(int& a, int& b, int& c, int& Result)
{

	do
	{
		GetDivision(a, b, Result);
		c = GetRand(MinResult, 100);

	} while ((c + a) > 100);
	Result += c;

}

//加除
void CCacuLPDlg::GetAddDiv(int& a, int& b, int& c, int& Result)
{

	do
	{
		GetDivision(b, c, Result);
		a = GetRand(MinResult, 100);

	} while ((b + a) > 100);
	Result += a;
}

//乘减
void CCacuLPDlg::GetMulSub(int& a, int& b, int& c, int& Result)
{
	do
	{
		GetMultiplication(a, b, Result);
		c = GetRand(MinResult, 100);

	} while (((Result - c) > 100)|| ((Result - c)< MinResult));
	Result -= c;
}

//减乘
void CCacuLPDlg::GetSubMul(int& a, int& b, int& c, int& Result)
{
	do
	{
		GetMultiplication(b, c, Result);
		a = GetRand(MinResult, 100);

	} while (((a - Result) > 100) || ((a - Result) < MinResult));
	Result = a - Result;
}

//除减
void CCacuLPDlg::GetDivSub(int& a, int& b, int& c, int& Result)
{

	do
	{
		GetDivision(a, b, Result);
		c = GetRand(1, 9);//2-9

	} while (((Result - c) > 10) || ((Result - c) < 2));
	Result -= c;
}

//减除
void CCacuLPDlg::GetSubDiv(int& a, int& b, int& c, int& Result)
{
	do
	{
		a = GetRand(10,91);//2-9
		GetDivision(b, c, Result);

	} while (((a - Result) > 91) || ((a - Result) < 2));
	Result = a - Result;
}

//
void CCacuLPDlg::GetEquation(CString& Equation, CString& EquationWithAnswer)
{
	int IsGeneratedEqu = 0;
	do
	{
		Index = GetRand(0, 15);
		switch (Index)
		{
		case 0://加法
		{
			if (m_Add.GetCheck())
			{
				IsGeneratedEqu = 1;
				GetAddition(A, B, Result);
				Equation.Format(" %d ＋ %d =", A, B);
				EquationWithAnswer.Format(" %d ＋ %d = %d", A, B, Result);
			}
		}
		break;
		case 1://减法
		{
			if (m_Sub.GetCheck())
			{
				IsGeneratedEqu = 1;
				GetSubtraction(A, B, Result);
				Equation.Format(" %d － %d =", A, B);
				EquationWithAnswer.Format(" %d － %d = %d", A, B, Result);
			}
		}
		break;
		case 2://乘法
		{
			if (m_Mul.GetCheck())
			{
				IsGeneratedEqu = 1;
				GetMultiplication(A, B, Result);
				Equation.Format(" %d × %d =", A, B);
				EquationWithAnswer.Format(" %d × %d = %d", A, B, Result);
			}
		}
		break;
		case 3://除法
		{
			if (m_Div.GetCheck())
			{
				IsGeneratedEqu = 1;
				GetDivision(A, B, Result);
				Equation.Format(" %d ÷ %d =", A, B);
				EquationWithAnswer.Format(" %d ÷ %d = %d", A, B, Result);
			}
		}
		break;
		case 4://加加
		{
			if (m_AddAdd.GetCheck())
			{
				IsGeneratedEqu = 1;
				GetAddAdd(A, B, C, Result);
				Equation.Format(" %d ＋ %d ＋ %d =", A, B, C);
				EquationWithAnswer.Format(" %d ＋ %d ＋ %d = %d", A, B, C, Result);
			}
		}
		break;
		case 5://加减
		{
			if (m_AddSub.GetCheck())
			{
				IsGeneratedEqu = 1;
				GetAddSub(A, B, C, Result);
				Equation.Format(" %d ＋ %d － %d =", A, B, C);
				EquationWithAnswer.Format(" %d ＋ %d － %d = %d", A, B, C, Result);
			}
		}
		break;
		case 6://减加
		{
			if (m_SubAdd.GetCheck())
			{
				IsGeneratedEqu = 1;
				GetSubAdd(A, B, C, Result);
				Equation.Format(" %d － %d ＋ %d =", A, B, C);
				EquationWithAnswer.Format(" %d － %d ＋ %d = %d", A, B, C, Result);
			}
		}
		break;
		case 7://减减
		{
			if (m_SubSub.GetCheck())
			{
				IsGeneratedEqu = 1;
				GetSubSub(A, B, C, Result);
				Equation.Format(" %d － %d － %d =", A, B, C);
				EquationWithAnswer.Format(" %d － %d － %d = %d", A, B, C, Result);
			}
		}
		break;
		case 8://乘加
		{
			if (m_MulAdd.GetCheck())
			{
				IsGeneratedEqu = 1;
				GetMulAdd(A, B, C, Result);
				Equation.Format(" %d × %d ＋ %d =", A, B, C);
				EquationWithAnswer.Format(" %d × %d ＋ %d = %d", A, B, C, Result);
			}
		}
		break;
		case 9://加乘
		{
			if (m_AddMul.GetCheck())
			{
				IsGeneratedEqu = 1;
				GetAddMul(A, B, C, Result);
				Equation.Format(" %d ＋ %d × %d =", A, B, C);
				EquationWithAnswer.Format(" %d ＋ %d × %d = %d", A, B, C, Result);
			}
		}
		break;
		case 10://除加
		{
			if (m_DivAdd.GetCheck())
			{
				IsGeneratedEqu = 1;
				GetDivAdd(A, B, C, Result);
				Equation.Format(" %d ÷ %d ＋ %d =", A, B, C);
				EquationWithAnswer.Format(" %d ÷ %d ＋ %d = %d", A, B, C, Result);
			}
		}
		break;
		case 11://加除
		{
			if (m_AddDiv.GetCheck())
			{
				IsGeneratedEqu = 1;
				GetAddDiv(A, B, C, Result);
				Equation.Format(" %d ＋ %d ÷ %d =", A, B, C);
				EquationWithAnswer.Format(" %d ＋ %d ÷ %d = %d", A, B, C, Result);
			}
		}
		break;
		case 12://乘减
		{
			if (m_MulSub.GetCheck())
			{
				IsGeneratedEqu = 1;
				GetMulSub(A, B, C, Result);
				Equation.Format(" %d × %d － %d =", A, B, C);
				EquationWithAnswer.Format(" %d × %d － %d = %d", A, B, C, Result);
			}
		}
		break;
		case 13://减乘
		{
			if (m_SubMul.GetCheck())
			{
				IsGeneratedEqu = 1;
				GetSubMul(A, B, C, Result);
				Equation.Format(" %d － %d × %d =", A, B, C);
				EquationWithAnswer.Format(" %d － %d × %d = %d", A, B, C, Result);
			}
		}
		break;
		case 14://除减
		{
			if (m_DivSub.GetCheck())
			{
				IsGeneratedEqu = 1;
				GetDivSub(A, B, C, Result);
				Equation.Format(" %d ÷ %d － %d =", A, B, C);
				EquationWithAnswer.Format(" %d ÷ %d － %d = %d", A, B, C, Result);
			}
		}
		break;
		case 15://减除
		{
			if (m_SubDiv.GetCheck())
			{
				IsGeneratedEqu = 1;
				GetDivSub(A, B, C, Result);
				Equation.Format(" %d － %d ÷ %d =", A, B, C);
				EquationWithAnswer.Format(" %d － %d ÷ %d = %d", A, B, C, Result);
			}
		}
		break;

		default:
			break;
		}
	} while (!IsGeneratedEqu);
	
}


void CCacuLPDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	int a, b, c, d;

	//GetAddition(a, b, c);
	//TRACE("找到 %d ＋ %d = %d\n", a, b, c);
	//GetSubtraction(a, b, c);
	//TRACE("找到 %d － %d = %d\n", a, b, c);
	//GetMultiplication(a, b, c);
	//TRACE("找到 %d × %d = %d\n", a, b, c);
	//GetDivision(a, b, c);
	//TRACE("找到 %d ÷ %d = %d\n", a, b, c);
	//TRACE("\n");


	//GetMulAdd(a, b, c, d);
	//TRACE("找到 %d × %d ＋ %d = %d\n", a, b, c, d);
	//GetAddMul(a, b, c, d);
	//TRACE("找到 %d ＋ %d × %d = %d\n", a, b, c, d);
	//TRACE("\n");

	//GetDivAdd(a, b, c, d);
	//TRACE("找到 %d ÷ %d ＋ %d = %d\n", a, b, c, d);
	//GetAddDiv(a, b, c, d);
	//TRACE("找到 %d ＋ %d ÷ %d = %d\n", a, b, c, d);
	//TRACE("\n");


	//GetMulSub(a, b, c, d);
	//TRACE("找到 %d × %d － %d = %d\n", a, b, c, d);
	//GetSubMul(a, b, c, d);
	//TRACE("找到 %d － %d × %d = %d\n", a, b, c, d);
	//TRACE("\n");


	//GetDivSub(a, b, c, d);
	//TRACE("找到 %d ÷ %d － %d = %d\n", a, b, c, d);
	//GetSubDiv(a, b, c, d);
	//TRACE("找到 %d ＋ %d ÷ %d = %d\n", a, b, c, d);
	//TRACE("\n");
	//

	//GetAddAdd(a, b, c, d);
	//TRACE("找到 %d ＋ %d ＋ %d = %d\n", a, b, c, d);
	//GetAddSub(a, b, c, d);
	//TRACE("找到 %d ＋ %d － %d = %d\n", a, b, c, d);
	//GetSubAdd(a, b, c, d);
	//TRACE("找到 %d － %d ＋ %d = %d\n", a, b, c, d);
	//GetSubSub(a, b, c, d);
	//TRACE("找到 %d － %d － %d = %d\n", a, b, c, d);
	//TRACE("---------------------\n");
	//CString tEq, tEqAnswer;
	//GetEquation(tEq, tEqAnswer);
	//TRACE("%s  %s\n", tEq, tEqAnswer);

	//CDialogEx::OnOK();



	//CFile MyFile;
	//CFileException e;


	//if (!MyFile.Open(m_PrjInfoFile.GetString(), CFile::modeCreate | CFile::modeWrite, &e))
	//{
	//	TRACE(_T("File could not be opened %d\n"), e.m_cause);
	//}
	//else
	//{
	//	CString tData;
	//	for (int i = 0; i < WFPrjInfoNum; i++) {
	//		tData.Format("%s:%s\n", m_PrjInfo[i].pName, m_PrjInfo[i].pValue.GetString());
	//		MyFile.Write(tData, tData.GetLength());
	//	}
	//	//MyFile.Flush();
	//	MyFile.Close();
	//}
	CreatAWork();
}

void CCacuLPDlg::RepairSpace(CString &Src, int TotalSize )
{
	int tSize = Src.GetLength();
	CString Space(" ");

	for (int i = 0; i < TotalSize - tSize;i++)
	{
		Src = Src + " ";
	}
}

void CCacuLPDlg::CreatAWork(void)
{
	CString strTime;
	CTime tm;
	CFile FileHomework;
	CFile FileAnswer;
	CString* OldHomework = 0;

	CFileException e0, e1;

	CString tPath;
	CString Equ, Answer, SNumber;
	int Number = 0;

	m_EditFileName.GetWindowText(m_FileName);
	m_EditBrowse.GetWindowText(m_MyWorkPath);
	m_Number.GetWindowText(SNumber);
	sscanf_s(SNumber, "%d", &Number);




	//修改索引
	int FileIndex = 0;
	sscanf_s(m_Conf[I_Index].pValue, "%d", &FileIndex);

	tPath.Format("%s\\%s", m_MyWorkPath, m_FileName);//1.获取 UserData目录
	Equ.Format("%s-%d-题目.txt", tPath, FileIndex);
	Answer.Format("%s-%d-答案.txt", tPath, FileIndex);




	//修改索引
	m_Conf[I_Index].pValue.Format("%d", FileIndex+1);
	m_Conf[I_FileName].pValue.Format("%s", m_FileName);
	m_Conf[I_Number].pValue.Format("%s", SNumber);
	DefConfWrite();

	tm = CTime::GetCurrentTime();
	strTime = tm.Format("20%y年%m月%d日 %X");

	//判断目录是否存在
	//if (PathFileExists(Equ.GetString()))//存在
	//{
	//	TRACE("文件存在！\n");
	//	AfxMessageBox("文件已存在，请重新输入文件名！");
	//}
	//else
	//直接覆盖
	{
		TRACE("文件不存在！\n");
		if ((!FileHomework.Open(Equ, CFile::modeCreate | CFile::modeWrite, &e0)) ||
			(!FileAnswer.Open(Answer, CFile::modeCreate | CFile::modeWrite, &e1)))
		{
			TRACE(_T("File could not be opened %d\n"), e0.m_cause);
			TRACE(_T("File could not be opened %d\n"), e1.m_cause);
		}
		else
		{
			CString ResultHomework, ResultAnswer;
			CString tHomework0, tAnswer0;
			CString tHomework1, tAnswer1;
			CString tHomework0x, tAnswer0x;
			CString tHomework1x, tAnswer1x;
			int tNumber = Number % 2;
			int tIndex;
			int IsDuplicatedW0 = 1, IsDuplicatedW1 = 1 ;
			OldHomework = new CString[Number];

			ResultHomework.Format("生成日期 :%s\r\n\r\n", strTime);

			FileHomework.Write(ResultHomework, ResultHomework.GetLength());
			FileAnswer.Write(ResultHomework, ResultHomework.GetLength());

			for (int i = 0; i < (Number - tNumber) / 2; i++)
			{
				IsDuplicatedW0 = 1;
				IsDuplicatedW1 = 1;
				do
				{
					if (IsDuplicatedW0)
					{
						GetEquation(tHomework0, tAnswer0);
						IsDuplicatedW0 = 0;
					}
					if (IsDuplicatedW1)
					{
						GetEquation(tHomework1, tAnswer1);
						IsDuplicatedW1 = 0;
					}
					for (int j = 0; j < i*2; j++)
					{

						if (!IsDuplicatedW0)
						{
							if (!strcmp(tHomework0, OldHomework[j]))//已经出现过的题目
							{
								IsDuplicatedW0 = 1;
							}
							else
							{

							}
						}
						if (!IsDuplicatedW1)
						{
							if (!strcmp(tHomework1, OldHomework[j]))//已经出现过的题目
							{
								IsDuplicatedW1 = 1;
							}
							else
							{

							}
						}
					}
				} 
				while (IsDuplicatedW0 || IsDuplicatedW1);

				OldHomework[i*2] = tHomework0;
				OldHomework[i*2 + 1] = tHomework1;
				if (m_AddSeq.GetCheck())
				{
					tHomework0x.Format("(%d) %s", i * 2 + 1, tHomework0.GetString());
					tHomework1x.Format("(%d) %s", i * 2 + 2, tHomework1.GetString());

					tAnswer0x.Format("(%d) %s", i * 2 + 1, tAnswer0.GetString());
					tAnswer1x.Format("(%d) %s", i * 2 + 2, tAnswer1.GetString());
					RepairSpace(tHomework0x, 80);
					RepairSpace(tAnswer0x, 80);
				}
				else
				{
					tHomework0x = tHomework0;
					tHomework1x = tHomework1;
					tAnswer0x = tAnswer0;
					tAnswer1x = tAnswer1;

					RepairSpace(tHomework0x, 80);
					RepairSpace(tAnswer0x, 80);

				}

				TRACE("tHomework0 = %d\n", tHomework0x.GetLength());
				TRACE("tAnswer0 = %d\n", tAnswer0x.GetLength());
				ResultHomework.Format("%s\t%s\r\n\r\n", tHomework0x, tHomework1x);
				ResultAnswer.Format  ("%s\t%s\r\n\r\n", tAnswer0x, tAnswer1x);

				FileHomework.Write(ResultHomework, ResultHomework.GetLength());
				FileAnswer.Write(ResultAnswer, ResultAnswer.GetLength());
			}
			IsDuplicatedW0 = 1;
			if (tNumber)
			{
				do
				{
					if (IsDuplicatedW0)
					{
						GetEquation(tHomework0, tAnswer0);
						IsDuplicatedW0 = 0;
					}
					
					for (int j = 0; j < tNumber - 1; j++)
					{
						if (!strcmp(tHomework0, OldHomework[j]))//已经出现过的题目
						{
							IsDuplicatedW0 = 1;
						}
						else
						{

						}
					}
				} while (IsDuplicatedW0);


				if (m_AddSeq.GetCheck())
				{
					tHomework0x.Format("(%d) %s", Number, tHomework0.GetString());
					tAnswer0x.Format("(%d) %s", Number, tAnswer0.GetString());
					RepairSpace(tHomework0x, 80);
					RepairSpace(tAnswer0x, 80);
				}
				else
				{
					tHomework0x = tHomework0;
					tAnswer0x = tAnswer0;

					RepairSpace(tHomework0x, 80);
					RepairSpace(tAnswer0x, 80);
				}


				ResultHomework.Format("%s\r\n\r\n", tHomework0x);
				ResultAnswer.Format("%s\r\n\r\n", tAnswer0x);

				FileHomework.Write(ResultHomework, ResultHomework.GetLength());
				FileAnswer.Write(ResultAnswer, ResultAnswer.GetLength());
			}

			//MyFile.Flush();
			FileHomework.Close();
			FileAnswer.Close();

			if (OldHomework)
			{
				delete[]OldHomework;
			}
			CString rResu;
			rResu.Format("习题已经生成《%s-%d-题目.txt》, 关闭此窗口，将打开生成目录！", m_FileName, FileIndex);
			AfxMessageBox(rResu);
		}
	}
	ShellExecute(NULL, "open", m_MyWorkPath, NULL, NULL, SW_SHOWDEFAULT);

}

BOOL CCacuLPDlg::FileTest() {
	return 0;
}



void CCacuLPDlg::OnEnChangeMfceditbrowse1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	
		m_EditBrowse.GetWindowText(m_OutputPath);
		if (m_OutputPath.GetLength() > 1)
		{
			m_Conf[I_OutputPath].pValue = m_OutputPath;
			DefConfWrite();

		}
	// TODO:  在此添加控件通知处理程序代码
}
