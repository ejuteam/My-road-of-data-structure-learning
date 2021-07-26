/*
Topic: Josephus问题
Description: 
            1.n个人围一圈，从第s个人开始报数。
            2.报到第m的人出列，然后从下一个人开始报数。
            3.循环第2步，直到所有人出列。
            4.输出所有人都出列的情况下的序列。
tips:
        1.Josephus问题可归结为线性表上多次删除的问题。（这里使用双链表的方式）
        2.关键在于从第s个点开始查找、输出、删除第m个结点，再从第m+1结点开始，重复。
Date: 2021/7/26
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
        doubleLinkList->headNode->Llink = doubleLinkList->rearNode;
        doubleLinkList->headNode->Rlink = doubleLinkList->rearNode;
        doubleLinkList->rearNode->Rlink = doubleLinkList->headNode;
        doubleLinkList->rearNode->Llink = doubleLinkList->headNode;
        printf("Null DoubleList created!\n");
    }
    else 
        printf("Out of space!\n");
    return doubleLinkList;
}

//打印双链表，从头结点开始
void printDoubleLinkList(DoubleLinkList doublelist,int nums)
{
    PDoubleNode temp = doublelist->headNode;
    if(nums == 0)
    {
        printf("Null List!\n");
    }
    else
    {
        printf("%d ",temp->info);
        while(nums > 1)
        {
            temp = temp->Rlink;
            printf("%d ",temp->info);
            nums--;
        }
    printf("\n");
    }
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
    int info,nums,pos,first_pos;        //定义变量info：结点数据；nums：总结点；pos：出列位置；first_pos：第一个结点
    int * result;                       //保存结果序列
    PDoubleNode node,node1;
    DoubleLinkList Jose_LinkList;
    //创建空链表
    printf("please enter '1' to create a Null Josephus List:  ");
    scanf("%d",&info);
    if( info == 1)
    {
        Jose_LinkList = createNullDoubleList();
        printf("Null Josephus List created!\n");
        //输入Josephus问题的总结点
        printf("How many people toally? please enter:  ");
        scanf("%d",&nums);
        result = (int)malloc(sizeof(int)*nums);  //动态开辟长度为nums的内存空间

        //如果总人数大于0
        if(nums > 0)
        {
            //输入Josephus问题的第一个报数结点、第m个出列的条件
            printf("who is the first reporter:  ");
            scanf("%d",&first_pos);
            printf("every 'pos' one will leave the line, enter your 'pos':  ");
            scanf("%d",&pos);

            //若输入均大于0，则输入结点数据
            if(first_pos > 0 && pos > 0)
            {
                printf("enter the info of each person\n");
                node = Jose_LinkList->headNode;
                //修改头结点的数据域
                scanf("%d",&info);
                node->info = info;
                //输入每个结点的数据域
                for(int i = 1; i < nums-1; i++)
                {
                    scanf("%d",&info);
                    insertNode_pos(Jose_LinkList,node,info);
                    node = locatNode_node(Jose_LinkList,info);
                }
                //修改尾结点的数据域
                scanf("%d",&info);
                node->Rlink->info = info;

                //打印
                printf("Josephus List created: ");
                printDoubleLinkList(Jose_LinkList,nums);
                printf("\n");
                printf("first reporter: %d\n",first_pos);
                printf("'pos': %d\n",pos);

                //删除
                //从头结点开始寻找first_pos位置所对应的结点
                node = Jose_LinkList->headNode;
                //从第first_pos个位置上的结点开始
                //若first_pos为1
                if(first_pos == 1)
                {
                    printf("data %d is reporting\n",node->info);
                }
                //first_pos不为1
                else
                {
                    for(int i = 1; i < first_pos; i++)
                        node = node->Rlink;
                        printf("data %d is reporting\n",node->info);
                }
                //删除
                //当总结点数量大于第m个报数的条件，按照原来规则执行
                int j = 1;
                while(nums >= pos)
                {
                    printf("data %d is reporting\n",node->info);
                    for(int i = 1; i < pos; i++)
                    {
                        node = node->Rlink;
                        node1 = node->Rlink;
                        printf("data %d is reporting\n",node->info);
                    }

                    //删除头结点需要进行处理
                    if(node == Jose_LinkList->headNode)
                    {
                        Jose_LinkList->headNode = node->Rlink;
                        printf("headNode is : %d\n",Jose_LinkList->headNode->info);
                    }
                    info = node->info;
                    result[j] = info;   //将结点数据存入结果集中
                    deleteNode_node(Jose_LinkList,node);
                    printf("data %d leave!\n",info);
                    nums--;
                    j++;
                    node = node1;
                    printDoubleLinkList(Jose_LinkList,nums);
                }
                //当总结点数量小于第m个报数的条件，按照下一个报数出列的规则执行
                if(nums < pos)
                {
                    while(nums != 0)
                    {
                        for(int i =1 ; i < 2; i++)
                        {
                            node = node->Rlink;
                            node1 = node->Rlink;
                            printf("data %d is reporting\n",node->info);
                        }
                        //删除头结点需要进行处理
                        if(node == Jose_LinkList->headNode)
                        {
                            Jose_LinkList->headNode = node->Rlink;
                            printf("headNode is : %d\n",Jose_LinkList->headNode->info);
                        }
                        printf("data %d is reporting\n",node->info);
                        info = node->info;
                        result[j] = info;  //将结点存入结果集中
                        deleteNode_node(Jose_LinkList,node);
                        printf("data %d leave!\n",info);
                        nums--;
                        j++;
                        node = node1;
                        printDoubleLinkList(Jose_LinkList,nums);
                    }
                }
                //输出结果序列
                for(int m = 1; m < j; m++)
                {
                    printf("%d ",result[m]);
                }
                printf("\n");
            }
            //若输入不大于0
            else
            {
                printf("numbers error!\n");
                system("pause");
                return 0;
            }
        }
        //如果总人数不大于0
        else
        {
            printf("numbers error!\n");
            system("pause");
            return 0;
        }
    }
    //空链表创建失败
    else
    {
        printf("Null Josephus List create failed!\n");
        system("pause");
        return 0;
    }
    system("pause");
}
/********主函数********/