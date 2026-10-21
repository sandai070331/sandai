/*****************************************************
 * Lab2 - 栈的表示与实现及栈的应用
 * 任务 1: 实现链式存储的栈
 * 任务 2: 用栈计算后缀表达式的值
 * 提高：实现中缀表达式转后缀表达式
 *****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

/* ========== 链式栈的定义和实现 ========== */
typedef int ElemType;

typedef struct node {
  ElemType elem;
  struct node *next;
} Node;

typedef struct linkStack {
  Node *top;
  int size;
} LinkStack;

// 初始化栈
void InitStack(LinkStack *s) {
  s->top = NULL;
  s->size = 0;
}

// 判断栈是否为空
int StackEmpty(LinkStack *s) {
  return s->top == NULL;
}

// 入栈
void Push(LinkStack *s, ElemType x) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  if (newNode == NULL) {
    puts("error: memory allocation failed!");
    return;
  }
  newNode->elem = x;
  newNode->next = s->top;
  s->top = newNode;
  s->size++;
}

// 出栈
void Pop(LinkStack *s, ElemType *x) {
  if (StackEmpty(s)) {
    puts("error: pop from an empty stack!");
    return;
  }
  Node *temp = s->top;
  *x = temp->elem;
  s->top = s->top->next;
  free(temp);
  s->size--;
}

// 获取栈顶元素
int GetTop(LinkStack *s, ElemType *x) {
  if (StackEmpty(s)) {
    return 0;
  }
  *x = s->top->elem;
  return 1;
}

// 清空栈
void StackClear(LinkStack *s) {
  ElemType temp;
  while (!StackEmpty(s)) {
    Pop(s, &temp);
  }
}

// 销毁栈
void StackDestroy(LinkStack *s) {
  StackClear(s);
}

/* ========== 任务 2: 后缀表达式求值 ========== */
// 判断是否为运算符
int isOperator(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}

// 执行运算
int calculate(int a, int b, char op) {
  switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/':
      if (b == 0) {
        puts("error: division by zero!");
        return 0;
      }
      return a / b;
    default: return 0;
  }
}

// 计算后缀表达式的值
int CalcPostfix(char *s) {
  LinkStack stack;
  InitStack(&stack);
  int num, a, b, result;

  while (*s != '\0') {
    // 跳过空格
    if (*s == ' ') {
      s++;
      continue;
    }

    // 遇到数字，入栈（支持多位数）
    if (isdigit(*s)) {
      num = 0;
      while (isdigit(*s)) {
        num = num * 10 + (*s - '0');
        s++;
      }
      Push(&stack, num);
      continue;
    }

    // 遇到运算符，弹出两个数进行计算
    if (isOperator(*s)) {
      Pop(&stack, &b);  // 注意顺序：先弹出的是右操作数
      Pop(&stack, &a);
      result = calculate(a, b, *s);
      Push(&stack, result);
    }

    s++;
  }

  Pop(&stack, &result);
  StackDestroy(&stack);
  return result;
}

/* ========== 提高：中缀表达式转后缀表达式 ========== */
// 获取运算符优先级
int getPriority(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

// 中缀表达式转后缀表达式
void InfixToPostfix(char *infix, char *postfix) {
  LinkStack stack;
  InitStack(&stack);
  char op, topOp;
  int i = 0, j = 0;

  while (infix[i] != '\0') {
    // 跳过空格
    if (infix[i] == ' ') {
      i++;
      continue;
    }

    // 遇到数字（支持多位数），直接输出
    if (isdigit(infix[i])) {
      while (isdigit(infix[i])) {
        postfix[j++] = infix[i++];
      }
      postfix[j++] = ' ';  // 用空格分隔数字
      continue;
    }

    // 遇到左括号，入栈
    if (infix[i] == '(') {
      Push(&stack, infix[i]);
      i++;
      continue;
    }

    // 遇到右括号，弹出栈中元素直到左括号
    if (infix[i] == ')') {
      while (GetTop(&stack, &topOp) && topOp != '(') {
        Pop(&stack, &op);
        postfix[j++] = op;
        postfix[j++] = ' ';
      }
      Pop(&stack, &op);  // 弹出左括号（不输出）
      i++;
      continue;
    }

    // 遇到运算符
    if (isOperator(infix[i])) {
      while (GetTop(&stack, &topOp) &&
             getPriority(topOp) >= getPriority(infix[i])) {
        Pop(&stack, &op);
        postfix[j++] = op;
        postfix[j++] = ' ';
      }
      Push(&stack, infix[i]);
      i++;
      continue;
    }

    i++;
  }

  // 将栈中剩余运算符全部弹出
  while (!StackEmpty(&stack)) {
    Pop(&stack, &op);
    postfix[j++] = op;
    postfix[j++] = ' ';
  }

  postfix[j] = '\0';
  StackDestroy(&stack);
}

/* ========== 测试主函数 ========== */
int main() {
  printf("========== 任务 1: 链式栈基本操作测试 ==========\n");
  LinkStack ls;
  InitStack(&ls);

  printf("Pushing: 10, 20, 30, 40, 50\n");
  Push(&ls, 10);
  Push(&ls, 20);
  Push(&ls, 30);
  Push(&ls, 40);
  Push(&ls, 50);

  ElemType top;
  GetTop(&ls, &top);
  printf("Top element: %d, Stack size: %d\n", top, ls.size);

  printf("\nPopping all elements:\n");
  ElemType val;
  while (!StackEmpty(&ls)) {
    Pop(&ls, &val);
    printf("Popped: %d, Stack size: %d\n", val, ls.size);
  }
  StackDestroy(&ls);

  printf("\n========== 任务 2: 后缀表达式求值 ==========\n");
  char postfix1[100] = "5 3 + 2 * 6 3 + +";  // (5+3)*2+(6+3) = 25
  char postfix2[100] = "3 5 +";              // 3+5 = 8
  char postfix3[100] = "9 3 /";              // 9/3 = 3
  char postfix4[100] = "5 1 2 + 4 * + 3 -";  // 5+(1+2)*4-3 = 14

  printf("Postfix: %s\n", postfix1);
  printf("Result: %d\n\n", CalcPostfix(postfix1));

  printf("Postfix: %s\n", postfix2);
  printf("Result: %d\n\n", CalcPostfix(postfix2));

  printf("Postfix: %s\n", postfix3);
  printf("Result: %d\n\n", CalcPostfix(postfix3));

  printf("Postfix: %s\n", postfix4);
  printf("Result: %d\n\n", CalcPostfix(postfix4));

  printf("========== 提高：中缀表达式转后缀表达式 ==========\n");
  char infix[100];
  char result[100];

  strcpy(infix, "(5+3)*2+(6+3)");
  printf("Infix:   %s\n", infix);
  InfixToPostfix(infix, result);
  printf("Postfix: %s\n", result);
  printf("Calc result: %d\n\n", CalcPostfix(result));

  strcpy(infix, "1+2*3-4/2");
  printf("Infix:   %s\n", infix);
  InfixToPostfix(infix, result);
  printf("Postfix: %s\n", result);
  printf("Calc result: %d\n\n", CalcPostfix(result));

  strcpy(infix, "((1+2)*(3+4))-5");
  printf("Infix:   %s\n", infix);
  InfixToPostfix(infix, result);
  printf("Postfix: %s\n", result);
  printf("Calc result: %d\n\n", CalcPostfix(result));

  // 测试多位数表达式
  strcpy(infix, "12+34*2");
  printf("Infix:   %s\n", infix);
  InfixToPostfix(infix, result);
  printf("Postfix: %s\n", result);
  printf("Calc result: %d\n", CalcPostfix(result));

  return 0;
}
