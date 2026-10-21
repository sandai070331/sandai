/*************************************************************
 * Created by David Song in 2016-4-26                        *
 * Updated by David Song in 2025-9-12                        *
 * 提问：你能从函数的首行定义中看出，调用初始化函数的调用方，            *
 *       应该准备什么样的变量吗？                                 *
 *                                                           *
 * Note:                                                     *
 *   1. Sequencial implementation of stack                   *
 ***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
typedef char ElemType;
typedef struct stack {
  ElemType a[MAX];
  int top;
} Stack;

void InitStack(Stack *p) {
  p->top = -1;
}

int StackEmpty(Stack *p) {
  return p->top == -1;
}

int StackFull(Stack *p) {
  return p->top == MAX - 1;
}

void Push(Stack *p, ElemType x) {
  if (StackFull(p)) {
    puts("error: push to a full stack!");
    return;
  }
  p->top++;
  p->a[p->top] = x;
}

void Pop(Stack *p, ElemType *q) {
  if (StackEmpty(p)) {
    puts("error: pop from an empty stack!");
    return;
  }
  *q = p->a[p->top];
  p->top--;
}

int StackTop(Stack *p, ElemType *q) {
  if (StackEmpty(p)) {
    return 0;
  }
  *q = p->a[p->top];
  return 1;
}

void StackClear(Stack *p) {
  p->top = -1;
}

// 待判断的字符串保存在数组 a 中，数组的有效长度保存在 n 中
// 通过计算返回 0，表示括号不匹配，返回 1 表示匹配
int Match(char a[], int n) {
  Stack s;
  InitStack(&s);
  char temp;

  for (int i = 0; i < n; i++) {
    // 左括号入栈
    if (a[i] == '(' || a[i] == '[' || a[i] == '{') {
      Push(&s, a[i]);
    }
    // 右括号匹配
    else if (a[i] == ')' || a[i] == ']' || a[i] == '}') {
      if (StackEmpty(&s)) {
        return 0;  // 没有左括号匹配
      }
      Pop(&s, &temp);
      // 检查括号类型是否匹配
      if ((a[i] == ')' && temp != '(') ||
          (a[i] == ']' && temp != '[') ||
          (a[i] == '}' && temp != '{')) {
        return 0;
      }
    }
  }

  // 栈空表示所有括号都匹配
  return StackEmpty(&s);
}


int main() {
  char str[100];
  int result;

  // 测试用例 1
  strcpy(str, "()[]{}");
  result = Match(str, strlen(str));
  printf("String: %s, Match: %s\n", str, result ? "YES" : "NO");

  // 测试用例 2
  strcpy(str, "{[()][(()())]}");
  result = Match(str, strlen(str));
  printf("String: %s, Match: %s\n", str, result ? "YES" : "NO");

  // 测试用例 3
  strcpy(str, "([)]{}");
  result = Match(str, strlen(str));
  printf("String: %s, Match: %s\n", str, result ? "YES" : "NO");

  // 测试用例 4
  strcpy(str, "{[)(]{}}");
  result = Match(str, strlen(str));
  printf("String: %s, Match: %s\n", str, result ? "YES" : "NO");

  return 0;
}
