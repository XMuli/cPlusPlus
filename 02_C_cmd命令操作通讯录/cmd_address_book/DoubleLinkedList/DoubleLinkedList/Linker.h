#pragma once

struct NODE
{
	char m_szName[20];
	int  m_Age;
	char m_szSex[4];
	char m_szAddr[100];
	char m_szTel[20];

	NODE *m_pNext;
	NODE *m_pFront;
};
//写完之后记得把Struct拆成Data+Linker的形式


void MyInputNode(NODE& pt);  //输入一个刚创建好的空白节点
void MyOutputNode(NODE& pt);  //输出已经存在的节点
void MyCreateList();   
NODE& MyAdd_Node();  //单独只是创建一个节点
NODE* MyAddNode();   //在链表尾部添加一个节点
void MyShowList();   
void MyShowNode();   //等价于 MyFindNode（）+MyShowNode（）
NODE& MyFindNode(char *FindName);
void MyInsertFront(char* ptName, NODE* pResFindNode, NODE* pNew); //前插（插在查询到的节点之前）
void MyInsertNext(char* ptName, NODE* pResFindNode, NODE* pNew);  //后插（插在查询到的节点之后）
void MyInsertNode();
void MyModifyNode();
void MyDeleteNode();
void MyClearnList();
void MyHelp();

