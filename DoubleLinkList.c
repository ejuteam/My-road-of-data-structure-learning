/*
Topic: 数据结构学习之双链表
Description: 
            每个结点有一个数据域，两个指针域
Date: 2021/7/24--7/25
Author: zg
*/

#include "stdio.h"
#include "stdlib.h"

/********双链表********/
//双链表类型结点
struct DoubleNode;
//双链表结点指针类型
typedef struct DoubleNode* PDoubleNode;
typedef struct DoubleLinkList* DoubleLinkList;
//双链表结点结构
struct DoubleNode
{
    int info;   //数据域
    PDoubleNode Llink,Rlink;  //左右指针域
};
//双链表类型结构
struct DoubleLinkList
{
    PDoubleNode headNode;
    PDoubleNode rearNode;
};

//双链表操作
//创建空双链表
DoubleLinkList createNullDoubleList()
{
    //创建链表
    DoubleLinkList doubleLinkList = (DoubleLinkList)malloc(sizeof(struct DoubleNode));
    //为头结点和尾结点分配内存空间
    doubleLinkList->headNode = (PDoubleNode)malloc(sizeof(struct DoubleNode));
    doubleLinkList->rearNode = (PDoubleNode)malloc(sizeof(struct DoubleNode));
    //若得到空间
    if(doubleLinkList != NULL)
    {
        doubleLinkList->headNode->info = 0;
        doubleLinkList->rearNode->info = 999;
        doubleLinkList->headNode->Llink = NULL;
        doubleLinkList->rearNode->Rlink = NULL;
        doubleLinkList->headNode->Rlink = doubleLinkList->rearNode;
        doubleLinkList->rearNode->Llink = doubleLinkList->headNode;
        printf("Null DoubleList created!\n");
    }
    else 
        printf("Out of space!\n");
    return doubleLinkList;
}
//判断空双链表
int isNullDoubleList(DoubleLinkList doublelist)
{
    return (doublelist->headNode == doublelist->rearNode);
}

//打印双链表，从头结点开始
void printDoubleLinkList(DoubleLinkList doublelist)
{
    PDoubleNode temp = doublelist->headNode;
    printf("%d ",temp->info);
    while(temp->Rlink)
    {
        temp = temp->Rlink;
        printf("%d ",temp->info);
    }
    printf("\n");
}

//查找结点，返回位置
//从头结点开始遍历查找到数据域为info的结点，返回
int locatNode_pos(DoubleLinkList doublelinklist,int info)
{
    //若双链表为空
    if(doublelinklist == NULL)
    {
        printf("doublelinklist is Null!\n");
        return 0;
    }
    //若双链表不为空
    else
    {
        int i = 0;
        PDoubleNode node = doublelinklist->headNode;
        while(node->info != info)
        {
            node = node->Rlink;
            i++;
        }
        return i;
    }
}

//查找结点，返回结点
//从头结点开始遍历查找到数据域为info的结点，返回结点
PDoubleNode locatNode_node(DoubleLinkList doublelinklist,int info)
{
    //若双链表为空
    if(doublelinklist == NULL)
    {
        printf("doublelinklist is Null!\n");
        return NULL;
    }
    //若双链表不为空，删除
    else
    {
        int i = 0;
        PDoubleNode node = doublelinklist->headNode;
        while(node->info != info)
        {
            node = node->Rlink;
            i++;
        }
        return node;
    }
}

//插入结点，后插
int insertNode_pos(DoubleLinkList doublelist,PDoubleNode node,int info)
{
    //为新结点分配空间
    PDoubleNode newNode = (PDoubleNode)malloc(sizeof(struct DoubleNode));
    PDoubleNode temp= (PDoubleNode)malloc(sizeof(struct DoubleNode));
    if(doublelist == NULL)
    {
        printf("DoubleLinkList is Null! insert failed!\n");
        return 0;
    }
    else
    {
        //数据域赋值
        newNode->info = info;
        //插入
        newNode->Llink = node;
        newNode->Rlink = node->Rlink;

        node->Rlink->Llink = newNode;
        node->Rlink = newNode;
        return 1;
    }
}

//删除结点，删除某个确定的结点
//通过查找结点函数得到该结点，然后删除
int deleteNode_node(DoubleLinkList doublelinklist,PDoubleNode node)
{
    //若双链表为空
    if(doublelinklist == NULL)
    {
        printf("doublelinklist is Null!\n");
        return 0;
    }
    //若双链表不为空
    else
    {
        node->Llink->Rlink = node->Rlink;
        node->Rlink->Llink = node->Llink;
        free(node);
        return 1;   
    }
}
/********双链表********/

/********主函数********/
int main(void)
{
    DoubleLinkList doublelist;
    PDoubleNode node;

    doublelist = createNullDoubleList();
    //判断双链表是否为空
    if(isNullDoubleList(createNullDoubleList))
        printf("DoubleLinkList is Null!\n");
    else
        printf("DoubleLinkList isn't Null!\n");
    printDoubleLinkList(doublelist);
    
    //在头结点之后插入值为20的新结点
    if(insertNode_pos(doublelist,doublelist->headNode,20))
    {
        printf("node inserted!\n");
    }
    else
        printf("inserted failed!\n");
    printDoubleLinkList(doublelist);

    //查找结点20的位置
    printf("node's position: %d\n",locatNode_pos(doublelist,20));

    //在20结点之后插入值为233的新结点
    node = locatNode_node(doublelist,20);  //找到20结点
    if(insertNode_pos(doublelist,node,233))
    {
        printf("node inserted!\n");
    }
    else
        printf("inserted failed!\n");
    printDoubleLinkList(doublelist);

    //删除233结点
    node = locatNode_node(doublelist,233);  //找到233结点
    if(deleteNode_node(doublelist,node))
    {
        printf("node deleted!\n");
    }
    else
        printf("deleted failed!\n");
    printDoubleLinkList(doublelist);
    system("pause");
}
/********主函数********/