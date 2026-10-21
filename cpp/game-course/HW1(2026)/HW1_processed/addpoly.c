#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 20
#define M 12
#define N 8

/* 定义多项式项的结构体：包含系数和指数 */
typedef struct {
    double coefficient;  /* 系数 */
    int exponent;        /* 指数 */
} PolyTerm;

/* 顺序表结构，存储多项式项 */
typedef struct list {
    PolyTerm a[MAXSIZE + 1];  /* 从下标 1 开始存储 */
    int len;
} SeqList;

/* 函数声明 */
SeqList* InitList(void);
void InitList2(SeqList **ppList);
int ListFull(SeqList *pList);
int ListEmpty(SeqList *pList);
int ListLen(SeqList *pList);
void Error(const char *msg);
int GetElem(SeqList *pList, int i, PolyTerm *pElm);
int InsertElem(SeqList *pList, int i, PolyTerm elm);
int DelElem(SeqList *pList, int i, PolyTerm *pElm);
void PrintList(SeqList *pList);
SeqList* AddPoly(SeqList *A, SeqList *B);

int main() {
    int i, sizeA, sizeB;
    SeqList *A, *B, *C;
    PolyTerm term;

    /* 原始输入数据 */
    double a[M] = {0, 0, 7, 0, 3, 1, 9, 8, 5, 17, -8, 100};
    double b[N] = {0, 0, 8, 1, 22, 7, -9, 8};

    /* 初始化三个多项式 */
    InitList2(&A);
    InitList2(&B);
    InitList2(&C);

    sizeA = sizeof(a) / sizeof(a[0]);
    sizeB = sizeof(b) / sizeof(b[0]);

    /* 将数组 a 转换为多项式 A（只存储非零系数的项） */
    for (i = 0; i < sizeA; i++) {
        if (a[i] != 0) {
            term.coefficient = a[i];
            term.exponent = i;
            InsertElem(A, A->len + 1, term);
        }
    }

    /* 将数组 b 转换为多项式 B（只存储非零系数的项） */
    for (i = 0; i < sizeB; i++) {
        if (b[i] != 0) {
            term.coefficient = b[i];
            term.exponent = i;
            InsertElem(B, B->len + 1, term);
        }
    }

    printf("多项式 A: ");
    PrintList(A);

    printf("多项式 B: ");
    PrintList(B);

    /* 计算 C = A + B */
    C = AddPoly(A, B);

    printf("多项式 C = A + B: ");
    PrintList(C);

    return 0;
}

/* 输入：无
   返回：指向顺序表的指针，通过返回值，把申请到的、指向内存空间的指针带回调用方。
   功能：为顺序表申请内存空间，并把顺序表的大小置为 0。
*/
SeqList* InitList(void) {
    SeqList *pList;
    pList = (SeqList *)malloc(sizeof(SeqList));
    pList->len = 0;
    return pList;
}

/* 输入：指向顺序表结构体的二级指针
   返回：无
   功能：为顺序表申请内存空间，并把顺序表的大小置为 0。
*/
void InitList2(SeqList **ppList) {
    *ppList = (SeqList *)malloc(sizeof(SeqList));
    (*ppList)->len = 0;
}

/* 判断顺序表是否已满 */
int ListFull(SeqList *pList) {
    return (pList->len == MAXSIZE) ? 1 : 0;
}

/* 判断顺序表是否已空 */
int ListEmpty(SeqList *pList) {
    return (pList->len == 0) ? 1 : 0;
}

/* 返回顺序表有效元素个数 */
int ListLen(SeqList *pList) {
    return pList->len;
}

/* 输出自定义的出错消息 */
void Error(const char *msg) {
    printf("[错误]: %s\n", msg);
}

/* 获取 i 位置的元素 */
int GetElem(SeqList *pList, int i, PolyTerm *pElm) {
    if (ListEmpty(pList)) {
        Error("从空表中读取数据元素");
        return 0;
    }
    if (i < 1 || i > MAXSIZE) {
        Error("读取位置错误！");
        return 0;
    }
    *pElm = pList->a[i];
    return 1;
}

/* 在 i 位置插入元素 */
int InsertElem(SeqList *pList, int i, PolyTerm elm) {
    int k;
    if (ListFull(pList)) {
        Error("无法向已经满了的顺序表插入数据元素!");
        return 0;
    }
    if (i < 1 || i > pList->len + 1) {
        Error("插入位置越界!");
        return 0;
    }
    for (k = pList->len; k >= i; k--) {
        pList->a[k + 1] = pList->a[k];
    }
    pList->a[i] = elm;
    pList->len += 1;
    return 1;
}

/* 删除 i 位置的元素 */
int DelElem(SeqList *pList, int i, PolyTerm *pElm) {
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

/* 打印多项式 */
void PrintList(SeqList *pList) {
    int i;
    for (i = 1; i <= pList->len; i++) {
        if (i > 1 && pList->a[i].coefficient >= 0) {
            printf("+");
        }
        printf("%.0fX^%d", pList->a[i].coefficient, pList->a[i].exponent);
    }
    putchar('\n');
}

/*
 * 多项式加法：C = A + B
 * 假设 A 和 B 都按指数递增顺序排列
 */
SeqList* AddPoly(SeqList *A, SeqList *B) {
    SeqList *C;
    int i, j;
    PolyTerm termA, termB, newTerm;

    InitList2(&C);

    i = 1;  /* A 的当前位置 */
    j = 1;  /* B 的当前位置 */

    /* 合并两个有序多项式 */
    while (i <= A->len && j <= B->len) {
        GetElem(A, i, &termA);
        GetElem(B, j, &termB);

        if (termA.exponent < termB.exponent) {
            /* A 的当前项指数小，直接加入 C */
            InsertElem(C, C->len + 1, termA);
            i++;
        } else if (termA.exponent > termB.exponent) {
            /* B 的当前项指数小，直接加入 C */
            InsertElem(C, C->len + 1, termB);
            j++;
        } else {
            /* 指数相同，系数相加 */
            newTerm.exponent = termA.exponent;
            newTerm.coefficient = termA.coefficient + termB.coefficient;
            /* 如果系数和不为 0，才加入 C */
            if (newTerm.coefficient != 0) {
                InsertElem(C, C->len + 1, newTerm);
            }
            i++;
            j++;
        }
    }

    /* 处理 A 中剩余的项 */
    while (i <= A->len) {
        GetElem(A, i, &termA);
        InsertElem(C, C->len + 1, termA);
        i++;
    }

    /* 处理 B 中剩余的项 */
    while (j <= B->len) {
        GetElem(B, j, &termB);
        InsertElem(C, C->len + 1, termB);
        j++;
    }

    return C;
}
