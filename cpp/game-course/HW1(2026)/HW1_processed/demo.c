#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 20

typedef double ElemType;

typedef struct list {
    ElemType a[MAXSIZE + 1];
    int len;
} SeqList;

/* 函数声明 */
SeqList* InitList(void);
void InitList2(SeqList **ppList);
int ListFull(SeqList *pList);
int ListEmpty(SeqList *pList);
int ListLen(SeqList *pList);
void Error(const char *msg);
int GetElem(SeqList *pList, int i, ElemType *pElm);
int InsertElem(SeqList *pList, int i, ElemType elm);
int DelElem(SeqList *pList, int i, ElemType *pElm);
void PrintList(SeqList *pList);

int main() {
    int i;
    SeqList *pList;
    ElemType x;
    ElemType a[11] = {0.1, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.9};

    /* 初始化顺序表 */
    InitList2(&pList);

    /* 插入元素 */
    for (i = 1; i <= 10; i++) {
        InsertElem(pList, i, a[i]);
    }

    printf("初始顺序表: ");
    PrintList(pList);

    /* 测试删除第 4 个元素 */
    DelElem(pList, 4, &x);
    printf("删除第 4 个元素：%.2lf\n", x);
    printf("删除后顺序表: ");
    PrintList(pList);

    /* 测试删除最后一个元素 */
    DelElem(pList, pList->len, &x);
    printf("删除最后一个元素：%.2lf\n", x);
    printf("删除后顺序表: ");
    PrintList(pList);

    /* 测试删除第一个元素 */
    DelElem(pList, 1, &x);
    printf("删除第一个元素：%.2lf\n", x);
    printf("删除后顺序表: ");
    PrintList(pList);

    return 0;
}

/* 初始化顺序表 - 方法一：利用返回值 */
SeqList* InitList(void) {
    SeqList *pList;
    pList = (SeqList *)malloc(sizeof(SeqList));
    pList->len = 0;
    return pList;
}

/* 初始化顺序表 - 方法二：利用二级指针 */
void InitList2(SeqList **ppList) {
    *ppList = (SeqList *)malloc(sizeof(SeqList));
    (*ppList)->len = 0;
}

/* 判断顺序表是否为满 */
int ListFull(SeqList *pList) {
    return (pList->len == MAXSIZE) ? 1 : 0;
}

/* 判断顺序表是否为空 */
int ListEmpty(SeqList *pList) {
    return (pList->len == 0) ? 1 : 0;
}

/* 返回顺序表长度 */
int ListLen(SeqList *pList) {
    return pList->len;
}

/* 出错提示 */
void Error(const char *msg) {
    printf("error: %s\n", msg);
}

/* 获取 i 位置的元素 */
int GetElem(SeqList *pList, int i, ElemType *pElm) {
    if (ListEmpty(pList)) {
        Error("Get element from empty list");
        return 0;
    }
    if (i < 1 || i > MAXSIZE) {
        Error("Get element from illegal position!");
        return 0;
    }
    *pElm = pList->a[i];
    return 1;
}

/* 在 i 位置插入元素 */
int InsertElem(SeqList *pList, int i, ElemType elm) {
    int k;
    if (ListFull(pList)) {
        Error("Insert element to a full list!");
        return 0;
    }
    if (i < 1 || i > pList->len + 1) {
        Error("insert element out of range!");
        return 0;
    }
    for (k = pList->len; k >= i; k--) {
        pList->a[k + 1] = pList->a[k];
    }
    pList->a[i] = elm;
    pList->len += 1;
    return 1;
}

/* 删除 i 位置的元素（已修复） */
int DelElem(SeqList *pList, int i, ElemType *pElm) {
    int k;
    if (ListEmpty(pList)) {
        Error("delete element from an empty list");
        return 0;
    }
    if (i < 1 || i > pList->len) {
        Error("delete element out of range");
        return 0;
    }
    *pElm = pList->a[i];
    /* 将被删元素后面的所有元素向前移动一位 */
    for (k = i + 1; k <= pList->len; k++) {
        pList->a[k - 1] = pList->a[k];
    }
    pList->len -= 1;
    return 1;
}

/* 打印顺序表 */
void PrintList(SeqList *pList) {
    int i;
    for (i = 1; i <= pList->len; i++) {
        printf("%.2lf ", pList->a[i]);
    }
    putchar('\n');
}
