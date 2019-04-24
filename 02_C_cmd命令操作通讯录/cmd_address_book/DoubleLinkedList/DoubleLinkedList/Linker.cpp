#include "stdafx.h"
#include "Linker.h"

NODE *g_pHead = NULL;
NODE *g_pEnd = NULL;

void MyInputNode(NODE& pt)  //输入一个刚创建好的空白节点
{
	pt.m_pFront = NULL;
	pt.m_pNext = NULL;
	cout << "姓名:";      cin >> pt.m_szName;
	cout << "年龄:";      cin >> pt.m_Age;
	cout << "性别:";      cin >> pt.m_szSex;
	cout << "联系方式:";   cin >> pt.m_szTel;
	cout << "住址:";      cin >> pt.m_szAddr;
}

void MyOutputNode(NODE& pt)  //输出已有的节点
{
	cout << "姓名:" << pt.m_szName << endl;
	cout << "年龄:" << pt.m_Age << endl;
	cout << "性别:" << pt.m_szSex << endl;
	cout << "联系方式:" << pt.m_szTel << endl;
	cout << "住址:" << pt.m_szAddr << endl << endl;
}
void MyCreateList()
{
	NODE *pTemp = new NODE;

	if (NULL == pTemp)
	{
		cout << "创建链表失败！" << endl;
	}
	else
	{
		MyInputNode(*pTemp);
		cout << "创建链表成功！" << endl << endl;
	}

	g_pHead = pTemp;
	g_pEnd = pTemp;
}

//单独只是创建一个节点
NODE& MyAdd_Node()
{
	NODE* pTemp = new NODE;

	if (NULL != pTemp)
	{
		MyInputNode(*pTemp);
	}

	return *pTemp;
}

//在链表尾部添加一个节点
NODE* MyAddNode()
{
	if (NULL == g_pHead || NULL == g_pEnd)
	{
		cout << "该链表不存在，请从新创建链表再进行该项操作！" << endl;
	}

	NODE* pNew = &MyAdd_Node();  //引用的使用
	g_pEnd->m_pNext = pNew;
	pNew->m_pFront = g_pEnd;
	g_pEnd = pNew;
	return NULL;
}

void MyShowList()
{
	int nCount = 1;

	if (NULL != g_pHead && NULL != g_pEnd)
	{
		NODE* pt = g_pHead;

		cout << "------------------显示链表开始------------------" << endl;
		while (pt != NULL)
		{	
			cout << "第" << nCount << "个节点：" << endl;
			MyOutputNode(*pt);
			pt = pt->m_pNext;
			nCount++;
		}
		cout << "------------------显示链表结束------------------" << endl << endl;
	}
}

NODE& MyFindNode(char *FindName) //根据姓名查找
{
	NODE* pt = g_pHead;

	while (true)
	{
		if (NULL != pt)
		{
			if (0 == strcmp(FindName, pt->m_szName))
			{
				return *pt;
			}
			else
			{
				pt = pt->m_pNext;
			}
		}
		else
		{
			cout << "您查询的该节点不存在！" << endl << endl;
			return *pt;  //pt == NULL
		}		
	}

}

void MyShowNode()
{
	char szNameBuf[20] = "";
	cout << "请输入想要查询的姓名:";
	cin >> szNameBuf;
	MyOutputNode(MyFindNode(szNameBuf));
}

void MyInsertFront(char* ptName, NODE* pResFindNode, NODE* pNew) //前插（插在查询到的节点之前）
{
	if (pResFindNode == g_pHead)
	{
		pNew->m_pNext = g_pHead;
		g_pHead->m_pFront = pNew;
		g_pHead = pNew;
	}
	else //无论是中间还是最后一个节点，那么进行前插之后，g_pEnd的指向都不需要变化
	{
		pNew->m_pFront = pResFindNode->m_pFront;
		pNew->m_pNext = pResFindNode;
		pResFindNode->m_pFront->m_pNext = pNew;
		pResFindNode->m_pFront = pNew;	
	}
}

void MyInsertNext(char* ptName, NODE* pResFindNode, NODE* pNew)  //后插（插在查询到的节点之后）
{
	if (pResFindNode == g_pEnd)
	{
		pResFindNode->m_pNext = pNew;
		pNew->m_pFront = pResFindNode;
		g_pEnd = pNew;
	}
	else //无论是中间还是第一个节点，那么进行后之后，g_pHead的指向都不需要变化
	{
		pNew->m_pNext = pResFindNode->m_pNext;
		pNew->m_pFront = pResFindNode;
		pResFindNode->m_pNext->m_pFront = pNew;
		pResFindNode->m_pNext = pNew;
	}
}

void MyInsertNode()
{
	char szNameBuf[20] = "";
	cout << "请输入姓名（待会将会选择插入该节点之前或者之后）:";
	cin >> szNameBuf;

	cout << "-------------插入操作开始-------------" << endl;
	NODE *pNew = &MyAdd_Node();
	NODE *pResFindNode = &MyFindNode(szNameBuf);

	int nChoose = 1;
	cout << "前插还是后插：（1---前插； 2---后插）" << endl;
	cin >> nChoose;
	if (1 == nChoose)
	{
		MyInsertFront(szNameBuf, pResFindNode, pNew);
	}
	else if (2 == nChoose)
	{
		MyInsertNext(szNameBuf, pResFindNode, pNew);
	}
	else
	{
		cout << "请输入1或者2，请从新再次尝试输入！" << endl;
	}
	cout << "-------------插入操作结束-------------" << endl << endl;
}

void MyModifyNode()
{
	char szNameBuf[20] = "";
	cout << "请输入姓名（将会修改的节点信息）:";
	cin >> szNameBuf;

	cout << "-------------修改操作开始-------------" << endl;
	NODE *pResFindNode = &MyFindNode(szNameBuf);
	MyInputNode(*pResFindNode);
	cout << "-------------修改操作结束-------------" << endl << endl;
}

void MyDeleteNode()
{
	char szNameBuf[20] = "";
	cout << "请输入姓名（将会删除的节点信息）:";
	cin >> szNameBuf;

	cout << "-------------删除操作进行中....-------------" << endl;
	NODE *pResFindNode = &MyFindNode(szNameBuf);
	if (pResFindNode == g_pHead)
	{	
		g_pHead = pResFindNode->m_pNext;
		pResFindNode->m_pNext->m_pFront = NULL;
	}
	else if (pResFindNode == g_pEnd)
	{
		g_pEnd = pResFindNode->m_pFront;
		g_pEnd->m_pNext = NULL;
	}
	else
	{
		pResFindNode->m_pFront->m_pNext = pResFindNode->m_pNext;
	}

	delete [] pResFindNode;

	cout << "-------------删除操作结束-------------" << endl << endl;
}

void MyClearnList()
{
	NODE* pt = g_pHead;

	cout << "-------------清除链表进行中....-------------" << endl;
	while (NULL != pt)
	{
		delete [] pt;
		pt = pt->m_pNext;
	}

	g_pHead = NULL;
	g_pEnd = NULL;
	cout << "-------------清除链表结束-------------" << endl << endl;
}


void MyHelp()
{
	for (size_t i = 0; i < 80; i++)
		fputchar('=');
	cout << endl;

	void Create();
	void Add();
	void Insert();
	void Delete();
	void Clearn();
	void Modify();
	void Find();
	void Show();
	void Help();
	void Exit();
	cout << "命令            语句           操作含义" << endl;
	cout << "Create         创建         创建一个链表" << endl;
	cout << "Add            添加         在该链表结尾处添加一个新的节点" << endl;
	cout << "Insert         插入         在链表任意地方随意插入一个新节点" << endl;
	cout << "Delete         删除         在链表任意地方随意删除一个已有节点" << endl;
	cout << "Clearn         清空         清空整个链表" << endl;
	cout << "Modify         修改         在链表任意地方随意是修改一个已有节点" << endl;
	cout << "Show           显示         完整的显示该链表的所有节点的详细信息" << endl;
	cout << "Help           帮助         查看帮助说明文档" << endl;
	cout << "Exit           退出         退出，结束本程序" << endl;


	for (size_t i = 0; i < 80; i++)
		fputchar('=');

	cout << endl << endl;
}