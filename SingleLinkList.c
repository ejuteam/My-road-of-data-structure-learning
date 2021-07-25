/*
Topic: 数据结构学习之单链表
Description: 
             1.通过指针指示元素之间的逻辑关系和后继元素的位置
             2.包含数据域和指针域
             3.不在乎元素在存储器中的实际位置，只关心元素之间的逻辑顺序
             4.不要求逻辑上相邻的元素在物理位置也相邻
Date: 2021/7/16--7/24
Author: zg
*/

#include "stdio.h"
#include "stdlib.h"

//单链表结点类型
struct Node;

/********单链表********/
//下面定义了同样是Node类型的PNode和LinkList指针，据课本描述是为了方便
//具体方便了什么，这里按下不表
//Node类型节点
typedef struct Node* PNode;
//Node类型链表
typedef struct Node* LinkList;

//单链表结点结构
struct Node
{
    int info;    //数据域，存放该结点的信息
    PNode link;       //指针域，存放下一个结点的地址
};

//单链表操作
//创建空链表（带头结点）
LinkList createNullList()
{
    //为申请表头结点的内存空间
    LinkList headList = (LinkList)malloc(sizeof(struct Node));
    //若表头结点获得了内存空间
    if(headList != NULL)
    {
        headList->info = 0;   //数据域：写入头结点的信息
        headList->link = NULL;     //指针域：因为是空单链表，下一个结点地址为空
        printf("Null List created!\n");
    }
    //表头结点未获得内存空间，创建失败
    else
        printf("Out of space!\n");
    return headList;
}

//判断空链表
int isNullList(LinkList headList)
{
    return (headList->link == NULL);
}

//查询结点位置
//从头结点开始，匹配到第一个数据域与Info相同的，返回结点的存储地址
PNode locatNode(LinkList headList,int Info)
{
    PNode node;
    //若单链表为空，无法查找
    if(headList == NULL)
    {
        printf("LinkList is Null, Can not find node!\n");
        return NULL;
    }
    else
    {
        node = headList->link;
        while(node != NULL && node->info != Info)
        {
            node = node->link;
        }
    }
    printf("node found!\n");
    return node;
}

//查询前驱结点
//查询p结点的前驱结点并且返回该结点
PNode locatNode_pre(LinkList headlist,PNode p)
{
    //判断链表是否为空
     if(headlist == NULL)
    {
        printf("LinkList is Null! locate failed!\n");
        return NULL;
    }
    PNode preNode;
    preNode = headlist;
    while(preNode != NULL && preNode->link !=p)
    {
        preNode = preNode->link;
    }
    return preNode;
}

/********插入结点********/
//插入结点
//把新结点插到i结点之后，i-1结点之前
//申请新节点，将i结点的指针域指向新结点的数据域；将新结点的指针域指向i-1结点的数据域
int inserLinkList_pos(LinkList headlist,PNode node,int info)
{
    //为新结点申请内存空间
    PNode newNode = (PNode)malloc(sizeof(struct Node));
    //判断链表是否为空
    if(headlist == NULL)
    {
        printf("LinkList is Null! insert failed!\n");
        return 0;
    }
    //若未申请到内存空间
    if(newNode == NULL)
    {
        printf("insert failed!\n");
        return 0;
    }   
    //若申请到内存空间
    else
    {
        newNode->info = info;   //写入结点信息
        newNode->link = node->link;   //将i结点指针域赋值给新结点的指针域，使新结点指针域指向i-1的数据域
        node->link = newNode;  //将i结点的指针域指向新结点的数据域
        return 1;
    }
}

//插入结点
//把新结点插到i结点之前，i-1结点之后
//首先查找到i-1结点，然后调用insert_pos的方法，在i-1之后插入结点
int insertLinkList_pre(LinkList headlist,PNode node,int info)
{
    //判断链表是否为空
    if(headlist == NULL)
    {
        printf("LinkList is Null! insert failed\n");
        return 0;
    }
    //要插入的结点
    PNode newNode;
    //前驱结点i-1
    PNode preNode;
    //将查找到相应位置的结点返值给preNode
    preNode = locatNode_pre(headlist,node);
    //在前驱结点之后插入
    newNode = inserLinkList_pos(headlist,preNode,info);
    return 1;
}
/********插入结点********/
/********删除结点********/
//删除某值结点
//从头结点开始查找，直到找到某值的结点
//设i为要删除的结点，将i-1的指针域赋值给i；将i的指针域赋值给i-1的指针域；将i结点free
int deleteNode_info(LinkList headlist,int info)
{
    //判断链表是否为空
    if(headlist == NULL)
    {
        printf("LinkList is Null! can't delete!\n");
        return 0;
    }
    else
    {
        //preNode前驱结点（从头结点开始），node要删除的结点
        PNode preNode,node;
        preNode = headlist;
        //找到某值结点的前驱结点存储位置
        while(preNode->link != NULL && preNode->link->info != info)
        {
            preNode = preNode->link;
        }
        //若未找到某值结点
        if(preNode->link == NULL)
        {
            printf("node doesn't exist!\n");
            return 0;
        }
        //找到了某值结点
        else
        {
            node = preNode->link;
            preNode->link = node->link;
            free(node);
            return 1;
        }
    }
}

//删除某结点
//找到该结点前驱进行删除
int deleteNode(LinkList headlist,PNode node)
{
     //判断链表是否为空
    if(headlist == NULL)
    {
        printf("LinkList is Null! can't delete!\n");
        return 0;
    }
    else
    {
        PNode preNode;
        //从头结点开始查找
        preNode = headlist;
        //找到某值结点的前驱结点存储位置
        while(preNode->link != NULL && preNode->link != node)
        {
            preNode = preNode->link;
        }
        //若该结点不是空的
        if(preNode->link != NULL)
        {
            node = preNode->link;
            preNode->link = node->link;
            free(node);
            return 1;
        }
        else
            printf("node doesn't exist!\n");
    }
}
/********删除结点********/

//打印单链表
void printLinkList(LinkList headList)
{
    LinkList temp = headList;
    printf("%d ",temp->info);
    while(temp->link)
    {
        temp = temp->link;
        printf("%d ",temp->info);
    }
    printf("\n");
}

/********单链表********/

/********主函数********/
int main(void)
{
    LinkList SingleLinkList;
    //创建新结点
    PNode node;
    PNode node1;

    //创建空单链表
    SingleLinkList = createNullList();
    printLinkList(SingleLinkList);

    //判断单链表是否为空
    printf("Judging the LinkList is Null or not...\n");
    if(isNullList(SingleLinkList))
        printf("LinkList is Null!\n");
    else   
        printf("LinkList isn't Null!\n");

    //插入结点，在头结点之后插入数据域值为1的结点
    printf("inserting the node that it's date equals '1' after headnode...\n");
    if(inserLinkList_pos(SingleLinkList,SingleLinkList,1))
        printf("Node inserted!\n");
    else
        printf("insert failed!\n");
    printLinkList(SingleLinkList);

    //在数据域值为1的结点之前插入新结点
    //查找数据域值为1的结点并且赋值给新结点
    printf("finde a node's data equals '1' and insert a new node before it...\n");
    node = locatNode(SingleLinkList,1);
    if(insertLinkList_pre(SingleLinkList,node,2))
        printf("Node inserted!\n");
    else
        printf("insert failed!\n");
    printLinkList(SingleLinkList);

    //删除值为1的结点
    printf("delete the node that data equals '1'...\n");
    if(deleteNode_info(SingleLinkList,1))
        printf("Node deleted!\n");
    else
        printf("deleted failed!\n");
    printLinkList(SingleLinkList);

    //删除node1结点
    printf("find node1 and delete it..\n");
    node1 = locatNode(SingleLinkList,2);
    if(deleteNode(SingleLinkList,node1))
        printf("Node deleted!\n");
    else
        printf("deleted failed!\n");
    printLinkList(SingleLinkList);

    //释放单链表
    free(SingleLinkList);
    system("pause");
}
/********主函数********/