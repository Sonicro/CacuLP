﻿
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
}

BEGIN_MESSAGE_MAP(CCacuLPDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CCacuLPDlg::OnBnClickedOk)
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

	CString tData;

	CFile MyFile;
	CFileException e;
	char pPath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, pPath);
	m_MyWorkPath.Format("%s", pPath);
	m_EditBrowse.EnableFolderBrowseButton(0, BIF_RETURNONLYFSDIRS | BIF_USENEWUI);
	m_EditBrowse.SetWindowText(m_MyWorkPath);//show default directory, when you click open,the dialog will whit this directory
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



	CString strTime;
	CTime tm;
	tm = CTime::GetCurrentTime();
	strTime = tm.Format("20%y%m%d-01");

	m_EditFileName.SetWindowText(strTime);
	m_Number.SetWindowText("36");


	srand((unsigned int)time(NULL));

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

//找到一个 a x b的组合
void CCacuLPDlg::GetMultiplication(int& a, int& b, int& Result)
{


	do
	{
		a = GetRand(2, 9);//2-9
		b = GetRand(2, 9);//2-9

	} while (a == b);

	Result = a * b;
}

//找到一个 a ÷ b的组合
void CCacuLPDlg::GetDivision(int& a, int& b, int& Result)
{

	do
	{
		Result = GetRand(2, 9);//2-9

		b = GetRand(2, 9);//2-9

	} while (Result == b);

	a = Result * b;

}


void CCacuLPDlg::GetAddition(int& a, int& b, int& Result)
{
	do
	{
		Result = GetRand(9, 100);//2-9
		a = GetRand(2, 100);//2-9

	} while ((Result - a) < 5);

	b = Result - a;
}

void CCacuLPDlg::GetSubtraction(int& a, int& b, int& Result)
{

	do
	{
		a = GetRand(11, 100);//2-9
		b = GetRand(2, 100);//2-9

	} while ((a - b) < 5);
	Result = a - b;
}

//加加
void CCacuLPDlg::GetAddAdd(int& a, int& b, int& c, int& Result)
{
	do
	{
		GetAddition(a, b, Result);
		c = GetRand(2, 100);//2-9

	} while ((Result + c) > 100);
	Result += c;
}

//加减
void CCacuLPDlg::GetAddSub(int& a, int& b, int& c, int& Result)
{
	do
	{
		GetAddition(a, b, Result);
		c = GetRand(2, 100);//2-9

	} while (((Result - c) > 100) || ((Result - c) < 6));
	Result -= c;
}
//减加
void CCacuLPDlg::GetSubAdd(int& a, int& b, int& c, int& Result)
{
	do
	{
		GetSubtraction(a, b, Result);
		c = GetRand(2, 100);//2-9

	} while (((Result + c) > 100) || ((Result + c) < 6));
	Result += c;
}
//减减
void CCacuLPDlg::GetSubSub(int& a, int& b, int& c, int& Result)
{
	do
	{
		GetSubtraction(a, b, Result);
		c = GetRand(2, 100);//2-9

	} while (((Result - c) > 100) || ((Result - c) < 6));
	Result -= c;
}


//乘加
void CCacuLPDlg::GetMulAdd(int& a, int& b, int& c, int& Result)
{

	do
	{
		GetMultiplication(a, b, Result);
		c = GetRand(2, 100);//2-9

	} while ((Result + c) > 100);
	Result += c;

}

//加乘
void CCacuLPDlg::GetAddMul(int& a, int& b, int& c, int& Result)
{

	do
	{
		GetMultiplication(b, c, Result);
		a = GetRand(2, 100);//2-9

	} while ((Result + a) > 100);
	Result += a;
}

//除加
void CCacuLPDlg::GetDivAdd(int& a, int& b, int& c, int& Result)
{

	do
	{
		GetDivision(a, b, Result);
		c = GetRand(2, 100);//2-9

	} while ((c + a) > 100);
	Result += c;

}

//加除
void CCacuLPDlg::GetAddDiv(int& a, int& b, int& c, int& Result)
{

	do
	{
		GetDivision(b, c, Result);
		a = GetRand(2, 100);//2-9

	} while ((b + a) > 100);
	Result += a;
}

//乘减
void CCacuLPDlg::GetMulSub(int& a, int& b, int& c, int& Result)
{
	do
	{
		GetMultiplication(a, b, Result);
		c = GetRand(2, 100);//2-9

	} while (((Result - c) > 100)|| ((Result - c)<6));
	Result -= c;
}

//减乘
void CCacuLPDlg::GetSubMul(int& a, int& b, int& c, int& Result)
{
	do
	{
		GetMultiplication(b, c, Result);
		a = GetRand(2, 100);//2-9

	} while (((a - Result) > 100) || ((a - Result) < 8));
	Result = a - Result;
}

//除减
void CCacuLPDlg::GetDivSub(int& a, int& b, int& c, int& Result)
{

	do
	{
		GetDivision(a, b, Result);
		c = GetRand(1, 8);//2-9

	} while (((Result - c) > 59) || ((Result - c) < 1));
	Result -= c;
}

//减除
void CCacuLPDlg::GetSubDiv(int& a, int& b, int& c, int& Result)
{
	do
	{
		GetDivision(b, c, Result);
		a = GetRand(10,91);//2-9

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

	tPath.Format("%s\\%s", m_MyWorkPath, m_FileName);//1.获取 UserData目录
	Equ.Format("%s-题目.txt", tPath);
	Answer.Format("%s-答案.txt", tPath);


	TRACE("名字：%s %d \n", m_FileName, Number);
	TRACE("题目：%s\n", Equ);
	TRACE("答案：%s\n", Answer);



	//判断目录是否存在
	if (PathFileExists(Equ.GetString()))//存在
	{
		TRACE("文件存在！\n");
		AfxMessageBox("文件已存在，请重新输入文件名！");
	}
	else
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
			int tNumber = Number % 2;
			int tIndex;
			int IsDuplicatedW0 = 1, IsDuplicatedW1 = 1 ;
			OldHomework = new CString[Number];
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

				RepairSpace(tHomework0, 80);
				RepairSpace(tAnswer0, 80);
				TRACE("tHomework0 = %d\n", tHomework0.GetLength());
				TRACE("tAnswer0 = %d\n", tAnswer0.GetLength());
				ResultHomework.Format("%s\t%s\r\n\r\n", tHomework0, tHomework1);
				ResultAnswer.Format  ("%s\t%s\r\n\r\n", tAnswer0, tAnswer1);

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

				RepairSpace(tHomework0, 80);
				RepairSpace(tAnswer0, 80);

				ResultHomework.Format("%s\r\n\r\n", tHomework0);
				ResultAnswer.Format("%s\r\n\r\n", tAnswer0);

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
			AfxMessageBox("Homework 已完成，打印吧！");
		}
	}
	ShellExecute(NULL, "open", m_MyWorkPath, NULL, NULL, SW_SHOWDEFAULT);

}

BOOL CCacuLPDlg::FileTest() {
	return 0;
}
