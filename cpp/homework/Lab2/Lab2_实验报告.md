# 实验二：栈的表示与实现及栈的应用

**姓名：** [填写姓名]  
**学号：** [填写学号]  
**日期：** 2025 年 9 月 20 日  

---

## 一、实验目的

1. 掌握栈的顺序存储结构和链式存储结构及其基本操作的实现。
2. 掌握栈后进先出的特点，并利用其特性在解决实际问题中的应用。
3. 掌握用递归算法来解决一些问题。

---

## 二、实验内容

### 任务 1：编程实现链式存储的栈

#### 1. 数据结构定义

```c
typedef int ElemType;

typedef struct node {
    ElemType elem;          // 数据域
    struct node *next;      // 指针域
} Node;

typedef struct linkStack {
    Node *top;              // 栈顶指针
    int size;               // 栈的大小
} LinkStack;
```

#### 2. 基本操作实现

**（1）初始化栈**
```c
void InitStack(LinkStack *s) {
    s->top = NULL;
    s->size = 0;
}
```

**（2）判断栈是否为空**
```c
int StackEmpty(LinkStack *s) {
    return s->top == NULL;
}
```

**（3）入栈操作**
```c
void Push(LinkStack *s, ElemType x) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        puts("error: memory allocation failed!");
        return;
    }
    newNode->elem = x;
    newNode->next = s->top;  // 新节点指向原栈顶
    s->top = newNode;         // 更新栈顶指针
    s->size++;
}
```

**（4）出栈操作**
```c
void Pop(LinkStack *s, ElemType *x) {
    if (StackEmpty(s)) {
        puts("error: pop from an empty stack!");
        return;
    }
    Node *temp = s->top;
    *x = temp->elem;          // 取出栈顶元素
    s->top = s->top->next;    // 更新栈顶指针
    free(temp);               // 释放原栈顶节点
    s->size--;
}
```

**（5）获取栈顶元素**
```c
int GetTop(LinkStack *s, ElemType *x) {
    if (StackEmpty(s)) {
        return 0;
    }
    *x = s->top->elem;
    return 1;
}
```

**（6）清空栈**
```c
void StackClear(LinkStack *s) {
    ElemType temp;
    while (!StackEmpty(s)) {
        Pop(s, &temp);
    }
}
```

#### 3. 测试结果

```
========== 任务 1: 链式栈基本操作测试 ==========
Pushing: 10, 20, 30, 40, 50
Top element: 50, Stack size: 5

Popping all elements:
Popped: 50, Stack size: 4
Popped: 40, Stack size: 3
Popped: 30, Stack size: 2
Popped: 20, Stack size: 1
Popped: 10, Stack size: 0
```

---

### 任务 2：后缀表达式求值

#### 1. 算法思路

使用整数栈来计算后缀表达式的值：
1. 逐个扫描输入字符串
2. 遇到数字就入栈（支持多位数连续读取）
3. 遇到运算符就弹出两个数进行计算，将结果入栈
4. 字符串扫描完毕后，栈内唯一元素即为答案

#### 2. 核心代码

```c
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
```

#### 3. 测试结果

| 后缀表达式 | 对应中缀表达式 | 计算结果 |
|-----------|---------------|---------|
| `5 3 + 2 * 6 3 + +` | (5+3)*2+(6+3) | 25 |
| `5 3 +` | 5+3 | 8 |
| `9 3 /` | 9/3 | 3 |
| `5 1 2 + 4 * + 3 -` | 5+(1+2)*4-3 | 14 |

---

### 任务 3（提高部分）：中缀表达式转后缀表达式

#### 1. 算法思路

使用字符栈实现转换：
1. 遇到数字直接输出（支持多位数，用空格分隔）
2. 遇到左括号 `(` 入栈
3. 遇到右括号 `)` 弹出栈中元素直到左括号
4. 遇到运算符时：
   - 若栈顶运算符优先级 >= 当前运算符，弹出栈顶并输出
   - 重复上述过程直到条件不满足，然后当前运算符入栈
5. 扫描完成后，将栈中剩余运算符全部弹出

#### 2. 核心代码

```c
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
```

#### 3. 测试结果

| 中缀表达式 | 后缀表达式 | 计算结果 |
|-----------|-----------|---------|
| `(5+3)*2+(6+3)` | `5 3 + 2 * 6 3 + +` | 25 |
| `1+2*3-4/2` | `1 2 3 * + 4 2 / -` | 5 |
| `((1+2)*(3+4))-5` | `1 2 + 3 4 + * 5 -` | 16 |
| `12+34*2` | `12 34 2 * +` | 80 |

---

## 三、实验总结

### 1. 收获与体会

1. **链式栈的特点**：与顺序栈相比，链式栈不需要预先分配固定大小的空间，可以根据需要动态扩展，避免了栈满的问题。

2. **栈的应用广泛**：通过本次实验，我深刻体会到栈"后进先出"的特性在解决实际问题中的重要性，如表达式求值、括号匹配等。

3. **多位数处理**：在处理表达式时，通过连续读取数字字符并累加（`num = num * 10 + (*s - '0')`），成功实现了多位数的支持。

### 2. 遇到的问题及解决方法

1. **问题**：出栈计算时操作数顺序错误
   - **解决**：注意先弹出的是右操作数，后弹出的是左操作数，特别是减法和除法运算顺序很重要

2. **问题**：中缀转后缀时多位数没有正确分隔
   - **解决**：在输出多位数后添加空格作为分隔符

3. **问题**：链式队列清空后重新入队出现问题
   - **解决**：确保 rear 指针在队列为空时也置为 NULL

### 3. 改进方向

1. 可以添加浮点数支持，使表达式计算更加通用
2. 可以增加错误检测，如括号不匹配、非法字符等情况的处理
3. 可以实现更多运算符的支持，如幂运算、取模等

---

## 四、源代码

完整源代码见 `Lab2.c` 文件。
