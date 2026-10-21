/*****************************************************
 * HW4 - 队列的实现与应用
 * 任务 1: 使用顺序队列解决实际问题
 * 任务 2: 实现不带头结点的链式队列
 *****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
typedef int ElemType;

/* ========== 任务 1: 顺序循环队列 (带 size) ========== */
typedef struct seqQue {
  ElemType a[MAX];
  int front;
  int rear;
  int size;
} SeqQue;

void InitQue(SeqQue **p) {
  *p = malloc(sizeof(SeqQue));
  (*p)->front = 0;
  (*p)->rear  = -1;
  (*p)->size = 0;
}

int QueEmpty(SeqQue *p) {
  return p->size == 0;
}

int QueFull(SeqQue *p) {
  return p->size == MAX;
}

void EnQue(SeqQue *p, ElemType x) {
  if (QueFull(p)) {
    puts("error: enqueue to a full queue!");
    return;
  }
  p->rear = (p->rear + 1) % MAX;
  p->a[p->rear] = x;
  p->size += 1;
}

void DeQue(SeqQue *p, ElemType *q) {
  if (QueEmpty(p)) {
    puts("error: dequeue from an empty queue!");
    return;
  }
  *q = p->a[p->front];
  p->front = (p->front + 1) % MAX;
  p->size -= 1;
}

void PrintQue(SeqQue *p) {
  if (QueEmpty(p)) return;
  printf("Queue: ");
  int i = p->front;
  for (int j = 0; j < p->size; j++) {
    printf("%5d", p->a[i]);
    i = (i + 1) % MAX;
  }
  printf("\n");
}

void QueClear(SeqQue *p) {
  p->front = 0;
  p->rear = -1;
  p->size = 0;
}

void QueDestroy(SeqQue **p) {
  free(*p);
  *p = NULL;
}

/* ========== 任务 2: 不带头结点的链式队列 ========== */
typedef struct node {
  ElemType elem;
  struct node *next;
} Node;

typedef struct linkQueue {
  Node *front;
  Node *rear;
} LinkQue;

// 初始化链式队列
void LinkQueInit(LinkQue *q) {
  q->front = NULL;
  q->rear = NULL;
}

// 判断队列是否为空
int LinkQueEmpty(LinkQue *q) {
  return q->front == NULL;
}

// 入队
void LinkQueEnQueue(LinkQue *q, ElemType x) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  if (newNode == NULL) {
    puts("error: memory allocation failed!");
    return;
  }
  newNode->elem = x;
  newNode->next = NULL;

  if (q->rear == NULL) {
    // 空队列，新节点既是队头也是队尾
    q->front = newNode;
    q->rear = newNode;
  } else {
    // 非空队列，新节点接在队尾后面
    q->rear->next = newNode;
    q->rear = newNode;
  }
}

// 出队
void LinkQueDeQueue(LinkQue *q, ElemType *x) {
  if (q->front == NULL) {
    puts("error: dequeue from an empty queue!");
    return;
  }

  Node *temp = q->front;
  *x = temp->elem;
  q->front = q->front->next;

  // 如果出队后队列为空，需要更新 rear
  if (q->front == NULL) {
    q->rear = NULL;
  }

  free(temp);
}

// 获取队头元素
int LinkQueGetFront(LinkQue *q, ElemType *x) {
  if (q->front == NULL) {
    return 0;
  }
  *x = q->front->elem;
  return 1;
}

// 打印队列
void LinkQuePrint(LinkQue *q) {
  if (q->front == NULL) {
    printf("Queue is empty\n");
    return;
  }

  printf("Queue: ");
  Node *current = q->front;
  while (current != NULL) {
    printf("%5d", current->elem);
    current = current->next;
  }
  printf("\n");
}

// 清空队列
void LinkQueClear(LinkQue *q) {
  ElemType temp;
  while (q->front != NULL) {
    LinkQueDeQueue(q, &temp);
  }
}

/* ========== 测试主函数 ========== */
int main() {
  printf("========== 任务 1: 顺序循环队列测试 ==========\n");
  SeqQue *p;
  ElemType a[5] = {11, 22, 33, 44, 55};

  InitQue(&p);
  printf("Enqueueing: 11, 22, 33, 44, 55\n");
  for (int i = 0; i < 5; i++) {
    EnQue(p, a[i]);
    PrintQue(p);
  }

  printf("\nDequeueing all elements:\n");
  for (int i = 0; i < 5; i++) {
    DeQue(p, &a[i]);
    printf("Dequeued: %d, ", a[i]);
    PrintQue(p);
  }
  QueDestroy(&p);

  printf("\n========== 任务 2: 不带头结点的链式队列测试 ==========\n");
  LinkQue lq;
  LinkQueInit(&lq);

  printf("Enqueueing: 100, 200, 300, 400\n");
  LinkQueEnQueue(&lq, 100);
  LinkQuePrint(&lq);
  LinkQueEnQueue(&lq, 200);
  LinkQuePrint(&lq);
  LinkQueEnQueue(&lq, 300);
  LinkQuePrint(&lq);
  LinkQueEnQueue(&lq, 400);
  LinkQuePrint(&lq);

  printf("\nDequeueing all elements:\n");
  ElemType val;
  while (!LinkQueEmpty(&lq)) {
    LinkQueDeQueue(&lq, &val);
    printf("Dequeued: %d, ", val);
    LinkQuePrint(&lq);
  }

  // 测试全部出队后再入队
  printf("\nRe-enqueueing after empty: 555, 666\n");
  LinkQueEnQueue(&lq, 555);
  LinkQuePrint(&lq);
  LinkQueEnQueue(&lq, 666);
  LinkQuePrint(&lq);

  LinkQueClear(&lq);
  printf("\nQueue cleared.\n");

  return 0;
}
