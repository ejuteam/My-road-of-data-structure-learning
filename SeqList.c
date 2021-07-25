/*
Topic: 数据结构学习之顺序表
Description: 
            1.该顺序表按内存中得到的物理地址顺序存放一组double类型的数
            2.通过指针指向数组第一个元素，之后以数组的形式访问元素
Date: 2021/7/16/19:58
Author: zg
*/

#include "stdio.h"
#include "stdlib.h"

/********顺序表********/
//顺序表及其顺序表类型的指针
typedef struct SeqList 
{
    int MaxNum;     //表的最大个数
    int num;       //存放线性表中元素的个数
    int* element; //element为表中的元素

}* PSeqList;

//顺序表操作
//创建空顺序表
PSeqList createNullSeqList(int max)
{
    //开辟一块内存给顺序表，指针palist指向顺序表
    PSeqList palist = (PSeqList)malloc(sizeof(struct SeqList));  
    //若得到了相应的内存，则创建顺序表
    if(palist != NULL)
    {
        //动态开辟长度为max的double类型数组
        //顺序表结构中的的元素指针element指向将数组首地址
        palist->element = (int* )malloc(sizeof(int) * max);
        //若获得了数组首地址，则创建顺序表
        if(palist->element)
        {
            palist->MaxNum = max;
            palist->num = 0;       //空表的元素个数为0
            printf("SeqList created! \n");
            return palist;
        }
        //没有获得数组首地址，直接释放存有顺序表的内存
        else
            free(palist);
    }
    //若顺序表没有获得内存，则输出相应信息
    else
        printf("Out of space! \n");    //顺序表存储分配失败
    return NULL;
}

//判断顺序表是否为空
//空返回1，否则返回0
int isNullSeqList(PSeqList palist)
{
    return (palist->num == 0);
}

//寻找某个double类型元素（值）的下标
int locateSeqList(PSeqList palist,int data)
{
    for(int i = 0; i < palist->num; i++)
    {
        if(palist->element[i] == data)
        {
            return i;
        }
    }
    return -1;
}

//顺序表插入
//在下标为i的元素之前插入一个值
//插入过程中，下标为n-1到i的元素均向后移动一个位置
//返回结果为判断插入成功与否的标志
int insertSeqList(PSeqList palist,int pos,int data)
{
    int i;
    //若存放的元素个数大于顺序表数组最大个数，溢出
    //因为在插入数据时将反复调用该方法，若最后的num大于数组长度，则无法再继续插入了
    if(palist->num >= palist->MaxNum)
    {
        printf("OverFlow!\n");
        return 0;
    }
    //若下标小于0或大于存放元素的个数
    //查找不到相应pos的元素，插入失败
    if(pos < 0 || pos > palist->num)
    {
        printf("Failed! data not exist!\n");
        return 0;
    }
    //从num-1开始均向后移动一个位置
    for(i = palist->num - 1; i >= pos; i--)
    {
        palist->element[i+1] = palist->element[i];
    }
    palist->element[pos] = data;   //插入
    palist->num = palist->num + 1;  //存放元素个数加1
    return 1;
}

//删除元素
//删除第i个位置上的元素；从n-1开始到i，元素均向前移动一个位置
int delete_data(PSeqList palist,int pos)
{
    //判断顺序表是否为空，判断要删除的位置i是否存在
    if(palist == NULL || pos < 0 || pos > palist->num)
    {
        printf("delete failed!\n");
    }
    else
    {
        int i = 0;
        for(i = pos; i <= palist->num-1; i++)
        {
            palist->element[i-1] = palist->element[i];
        }
        palist->num = palist->num - 1;
        return 1;
    }
}
//打印顺序表
void printSeqList(PSeqList palist)
{
    for(int i = 1; i <= palist->num; i++)
    {
        printf("%d ",palist->element[i - 1]);
    }   
    printf("\n");
}


/********顺序表********/

/********主函数********/
int main(void)
{
    PSeqList palist;
    int max,pos,i,num,maxNum;       //max表的最大个数，pos下标
    int data;       //插入元素
    
    printf("enter the max number of SeqList: ");
    //创建空顺序表
    scanf("%d",&maxNum);
    palist = createNullSeqList(maxNum);
    //判断顺序表是否为空
    if(isNullSeqList(palist))
    {
        printf("SeqList is Null!\n");
    }
    else
        printf("SeqList isn't Null! \n");
    //打印顺序表
    printSeqList(palist);

    i = 1;
    //给顺序表赋值
    while(scanf("%d",&data))
    {
        if(data == 0)
        {
            break;
        }
        palist->element[i - 1] = data;
        palist->num = palist->num + 1;
        i++;
    }

    //打印顺序表
    printSeqList(palist);
    
    //插入元素
    printf("enter the position and data which you want to insert \n");
    scanf("%d",&pos);
    scanf("%d",&data);
    if(insertSeqList(palist,pos,data))
    {
        printf("data inserted! \n");
    }
    else
        printf("data insert failed! \n");
    
    //判断顺序表是否为空
    if(isNullSeqList(palist))
    {
        printf("SeqList is Null!\n");
    }
    else
        printf("SeqList isn't Null! \n");
    //打印顺序表
    printSeqList(palist);

    //删除元素
    printf("enter the position you want to delete \n");
    scanf("%d",&pos);
    if(delete_data(palist,pos))
    {
        printf("data deleted! \n");
    }
    else
        printf("data deleted failed! \n");
    
    //打印顺序表
    printSeqList(palist);

    //释放顺序表
    free(palist);
    system("pause");
}
/********主函数********/

