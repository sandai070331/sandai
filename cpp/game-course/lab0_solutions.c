/*
 * Lab 0: C 语言指针、动态内存与结构体综合练习
 * 数据结构与算法导论 - 上机实验
 *
 * 本文件包含所有必做题目 (1-10) 和选做题 (A, B) 的完整解答
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ==================== 任务 1: 通过指针交换两个数 ==================== */
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* ==================== 任务 2: 使用指针遍历数组 ==================== */
int maxValue(int *p, int n) {
    int max = *p;  // 假设第一个元素最大
    p++;           // 移动到下一个元素
    for (int i = 1; i < n; i++) {
        if (*p > max) {
            max = *p;
        }
        p++;       // 指针移动，不使用 p[i]
    }
    return max;
}

/* ==================== 任务 3: 通过指针修改数组元素 ==================== */
void doubleArray(int *p, int n) {
    for (int i = 0; i < n; i++) {
        *p = *p * 2;  // 通过指针修改元素值
        p++;
    }
}

/* ==================== 任务 4: 识别多级指针 ==================== */
void task4_pointer_analysis(void) {
    printf("\n===== 任务 4: 多级指针分析 =====\n");
    int a = 10;
    int *p = &a;
    int **pp = &p;

    printf("a = %d\n", a);           // 输出: 10
    printf("*p = %d\n", *p);         // 输出: 10 (p 指向 a)
    printf("**pp = %d\n", **pp);     // 输出: 10 (pp 指向 p, *pp 是 p, **pp 是 a)

    **pp = 20;                       // 通过多级指针修改 a 的值
    printf("执行 **pp = 20 后，a = %d\n", a);  // 输出: 20

    printf("\n分析:\n");
    printf("- p 中存储的是变量 a 的地址\n");
    printf("- pp 中存储的是指针 p 的地址\n");
    printf("- *pp 表示 pp 所指向的内容，即 p 的值 (也就是 a 的地址)\n");
    printf("- **pp 表示通过 p 间接访问 a 的值\n");
    printf("- 执行 **pp = 20 时，实际上是通过两级间接访问修改了 a 的值\n");
}

/* ==================== 任务 5: 通过二级指针修改指针的指向 ==================== */
void changePointer(int **pp, int *q) {
    /* 通过二级指针 pp 修改 main() 中 p 的指向 */
    *pp = q;  // 让 p 指向 b
}

/* ==================== 任务 6: 动态分配数组求平均值 ==================== */
float calculateAverage(void) {
    int n;
    printf("请输入数组大小 n: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("数组大小必须大于 0\n");
        return 0.0f;
    }

    // 动态分配内存，使用 sizeof *p 更推荐
    int *p = malloc(n * sizeof *p);
    if (p == NULL) {
        printf("内存分配失败!\n");
        exit(1);
    }

    printf("请输入 %d 个整数: ", n);
    int sum = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", p + i);  // 使用指针偏移
        sum += *(p + i);
    }

    float average = (float)sum / n;

    // 释放内存
    free(p);
    p = NULL;  // 避免悬空指针

    return average;
}

/* ==================== 任务 7: 动态数组原地逆序 ==================== */
void reverse(int *p, int n) {
    int *left = p;
    int *right = p + n - 1;

    while (left < right) {
        // 交换左右元素
        int temp = *left;
        *left = *right;
        *right = temp;

        left++;
        right--;
    }
}

/* ==================== 任务 8: 在函数中动态分配数组 (二级指针) ==================== */
void createArray(int **p, int n) {
    // 为 main() 中的指针 a 分配 n 个 int 的动态空间
    *p = malloc(n * sizeof(int));
    if (*p == NULL) {
        printf("内存分配失败!\n");
        exit(1);
    }

    printf("请输入 %d 个整数: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", *p + i);
    }
}

/* ==================== 任务 9: 结构体与结构体指针 ==================== */
struct Student {
    int id;
    char name[20];
    float score;
};

void task9_struct_analysis(void) {
    printf("\n===== 任务 9: 结构体指针分析 =====\n");

    struct Student stu = {1001, "张三", 95.5f};
    struct Student *p = &stu;

    printf("学生信息:\n");
    printf("  学号: %d (通过 p->id 访问)\n", p->id);
    printf("  姓名: %s (通过 p->name 访问)\n", p->name);
    printf("  成绩: %.2f (通过 p->score 访问)\n", p->score);

    printf("\n(*p).score 与 p->score 的关系:\n");
    printf("  (*p).score = %.2f\n", (*p).score);
    printf("  p->score   = %.2f\n", p->score);
    printf("  两者等价！p->score 是 (*p).score 的简写形式\n");
    printf("  -> 运算符用于通过指针访问结构体成员，更加简洁\n");
}

/* ==================== 任务 10: 综合题 - 动态学生数组 ==================== */
void task10_student_array(void) {
    printf("\n===== 任务 10: 动态学生数组 =====\n");

    int n;
    printf("请输入学生人数 n: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("学生人数必须大于 0\n");
        return;
    }

    // 动态分配学生数组
    struct Student *students = malloc(n * sizeof(struct Student));
    if (students == NULL) {
        printf("内存分配失败!\n");
        exit(1);
    }

    // 输入学生信息
    printf("请输入 %d 个学生的信息 (学号 姓名 成绩):\n", n);
    for (int i = 0; i < n; i++) {
        printf("  学生 %d: ", i + 1);
        scanf("%d %s %f",
              &(students[i].id),
              students[i].name,
              &(students[i].score));
    }

    // 输出学生信息
    printf("\n所有学生信息:\n");
    for (int i = 0; i < n; i++) {
        printf("  学号: %d, 姓名: %s, 成绩: %.2f\n",
               students[i].id, students[i].name, students[i].score);
    }

    // 计算平均成绩
    float totalScore = 0.0f;
    for (int i = 0; i < n; i++) {
        totalScore += students[i].score;
    }
    float avgScore = totalScore / n;
    printf("\n平均成绩: %.2f\n", avgScore);

    // 找出最高分学生
    int maxIndex = 0;
    for (int i = 1; i < n; i++) {
        if (students[i].score > students[maxIndex].score) {
            maxIndex = i;
        }
    }
    printf("最高分学生: 学号 %d, 姓名 %s, 成绩 %.2f\n",
           students[maxIndex].id, students[maxIndex].name, students[maxIndex].score);

    // 释放动态内存
    free(students);
    students = NULL;
    printf("内存已释放。\n");
}

/* ==================== 选做题 A: 动态分配结构体数组 ==================== */
struct Student *createStudent(void) {
    // 使用 malloc 在堆上分配一个 Student 结构体
    struct Student *s = malloc(sizeof(struct Student));
    if (s == NULL) {
        printf("内存分配失败!\n");
        exit(1);
    }

    // 初始化数据
    s->id = 1001;
    strcpy(s->name, "李四");
    s->score = 88.5f;

    return s;
}

void taskA_create_student_array(void) {
    printf("\n===== 选做题 A: 动态分配结构体数组 =====\n");

    int n;
    printf("请输入学生人数: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("人数必须大于 0\n");
        return;
    }

    // 动态分配结构体数组
    struct Student *students = malloc(n * sizeof(struct Student));
    if (students == NULL) {
        printf("内存分配失败!\n");
        exit(1);
    }

    // 输入学生信息
    printf("请输入 %d 个学生的信息 (学号 姓名 成绩):\n", n);
    for (int i = 0; i < n; i++) {
        printf("  学生 %d: ", i + 1);
        scanf("%d %s %f",
              &(students[i].id),
              students[i].name,
              &(students[i].score));
    }

    // 输出学生信息
    printf("\n学生信息列表:\n");
    for (int i = 0; i < n; i++) {
        printf("  [%d] 学号：%d, 姓名：%s, 成绩：%.2f\n",
               i, students[i].id, students[i].name, students[i].score);
    }

    // 释放内存
    free(students);
    printf("内存已释放。\n");

    printf("\n思考题答案:\n");
    printf("  不能在 createStudent() 中定义 struct Student s; 然后 return &s;\n");
    printf("  原因：s 是局部变量，存储在栈上。当函数返回时，栈帧被销毁，\n");
    printf("       s 的内存空间不再有效。返回其地址会导致悬空指针 (dangling pointer)，\n");
    printf("       后续通过该指针访问数据会造成未定义行为。\n");
    printf("  正确做法：使用 malloc() 在堆上分配内存，堆内存直到显式调用 free()\n");
    printf("         才会释放，可以安全地返回其指针。\n");
}

/* ==================== 选做题 B: 指针错误分析与修正 ==================== */
void taskB_pointer_errors(void) {
    printf("\n===== 选做题 B: 指针错误分析与修正 =====\n");

    printf("\n【错误代码分析】\n\n");

    printf("错误 1: 未初始化的指针\n");
    printf("  原代码: int *p; *p = 10;\n");
    printf("  问题：p 未初始化，指向随机地址。*p = 10 会向未知内存写入数据，\n");
    printf("       可能导致程序崩溃或数据损坏 (野指针问题)。\n");
    printf("  修正：先分配内存再使用\n\n");

    printf("错误 2: 对未分配的指针调用 free()\n");
    printf("  原代码: free(p);\n");
    printf("  问题：p 未通过 malloc/calloc/realloc 分配，free() 会导致未定义行为。\n");
    printf("  修正：只对动态分配的内存调用 free()\n\n");

    printf("【修正后的代码】\n");
    printf("  int *p = malloc(sizeof(int));  // 先分配内存\n");
    printf("  if (p != NULL) {\n");
    printf("      *p = 10;                   // 安全写入\n");
    printf("      printf(\"%%d\\n\", *p);      // 输出: 10\n");
    printf("      free(p);                   // 释放动态分配的内存\n");
    printf("      p = NULL;                  // 避免悬空指针\n");
    printf("  }\n\n");

    printf("【关键知识点】\n");
    printf("  1. 野指针：未初始化或已释放的指针，使用前必须确保指向有效内存\n");
    printf("  2. 内存泄漏：分配的内存忘记释放，应养成 malloc/free 配对的习惯\n");
    printf("  3. free() 只能用于释放 malloc/calloc/realloc 分配的内存\n");
    printf("  4. free() 后应将指针设为 NULL，避免重复释放或悬空指针\n");
}

/* ==================== 实验总结 ==================== */
void experiment_summary(void) {
    printf("\n==================== 实验总结 ====================\n\n");

    printf("1. 指针概念理解:\n");
    printf("   - 指针是存储内存地址的变量，通过*运算符可以访问指针指向的内容\n");
    printf("   - 直接访问：直接使用变量名读写数据\n");
    printf("   - 间接访问：通过指针读写数据，可以实现函数外修改参数、动态内存等\n\n");

    printf("2. 动态内存需要手动释放的原因:\n");
    printf("   - C 语言不像 Java/Python 有垃圾回收机制\n");
    printf("   - 堆内存不会自动释放，必须由程序员显式调用 free()\n");
    printf("   - 不释放会导致内存泄漏，长期运行可能耗尽系统内存\n");
    printf("   - 但也不能过早释放，否则会产生悬空指针\n\n");

    printf("3. 结构体指针在数据结构中的应用:\n");
    printf("   - 链表：节点结构体 + 指向下一节点的指针\n");
    printf("   - 树：节点结构体 + 指向子节点的指针数组\n");
    printf("   - 图：邻接表使用结构体指针构建边表\n");
    printf("   - 动态数组：用指针管理可变大小的元素集合\n");
    printf("   - -> 运算符使结构体指针访问成员更简洁\n\n");

    printf("4. 核心收获:\n");
    printf("   - 掌握了一级指针、二级指针的使用场景\n");
    printf("   - 理解了 malloc/free 的正确配对使用\n");
    printf("   - 学会了结构体指针和->运算符\n");
    printf("   - 为后续学习链表、树等动态数据结构打下基础\n");
}

/* ==================== 主菜单 ==================== */
void print_menu(void) {
    printf("\n========== Lab 0 指针与动态内存练习 ==========\n");
    printf("请选择要运行的任务:\n");
    printf("  1  - 任务 1: 指针交换两个数\n");
    printf("  2  - 任务 2: 指针遍历数组求最大值\n");
    printf("  3  - 任务 3: 指针修改数组元素 (翻倍)\n");
    printf("  4  - 任务 4: 多级指针分析\n");
    printf("  5  - 任务 5: 二级指针修改指针指向\n");
    printf("  6  - 任务 6: 动态数组求平均值\n");
    printf("  7  - 任务 7: 动态数组原地逆序\n");
    printf("  8  - 任务 8: 函数内动态分配数组\n");
    printf("  9  - 任务 9: 结构体指针分析\n");
    printf("  10 - 任务 10: 动态学生数组综合题\n");
    printf("  A  - 选做题 A: 动态分配结构体数组\n");
    printf("  B  - 选做题 B: 指针错误分析\n");
    printf("  S  - 实验总结\n");
    printf("  0  - 退出程序\n");
    printf("============================================\n");
}

int main(void) {
    char choice;

    do {
        print_menu();
        printf("请输入选择: ");
        scanf(" %c", &choice);  // 注意前面的空格，跳过空白符

        switch (choice) {
            case '1': {
                printf("\n===== 任务 1: 指针交换两个数 =====\n");
                int a, b;
                printf("请输入两个整数: ");
                scanf("%d %d", &a, &b);
                printf("交换前: a = %d, b = %d\n", a, b);
                swap(&a, &b);
                printf("交换后: a = %d, b = %d\n", a, b);
                break;
            }
            case '2': {
                printf("\n===== 任务 2: 指针遍历数组求最大值 =====\n");
                int n;
                printf("请输入数组大小 n: ");
                scanf("%d", &n);
                if (n <= 0) {
                    printf("n 必须大于 0\n");
                    break;
                }
                int arr[n];
                printf("请输入 %d 个整数: ", n);
                for (int i = 0; i < n; i++) {
                    scanf("%d", &arr[i]);
                }
                int max = maxValue(arr, n);
                printf("最大值: %d\n", max);
                break;
            }
            case '3': {
                printf("\n===== 任务 3: 指针修改数组元素 =====\n");
                int n;
                printf("请输入数组大小 n: ");
                scanf("%d", &n);
                if (n <= 0) {
                    printf("n 必须大于 0\n");
                    break;
                }
                int arr[n];
                printf("请输入 %d 个整数: ", n);
                for (int i = 0; i < n; i++) {
                    scanf("%d", &arr[i]);
                }
                printf("原数组: ");
                for (int i = 0; i < n; i++) {
                    printf("%d ", arr[i]);
                }
                printf("\n");
                doubleArray(arr, n);
                printf("翻倍后: ");
                for (int i = 0; i < n; i++) {
                    printf("%d ", arr[i]);
                }
                printf("\n");
                break;
            }
            case '4':
                task4_pointer_analysis();
                break;
            case '5': {
                printf("\n===== 任务 5: 二级指针修改指针指向 =====\n");
                int a = 10, b = 20;
                int *p = &a;
                printf("修改前: *p = %d\n", *p);
                changePointer(&p, &b);
                printf("修改后: *p = %d (应输出 20)\n", *p);
                break;
            }
            case '6': {
                printf("\n===== 任务 6: 动态数组求平均值 =====\n");
                float avg = calculateAverage();
                printf("平均值 = %.2f\n", avg);
                break;
            }
            case '7': {
                printf("\n===== 任务 7: 动态数组原地逆序 =====\n");
                int n;
                printf("请输入数组大小 n: ");
                scanf("%d", &n);
                if (n <= 0) {
                    printf("n 必须大于 0\n");
                    break;
                }
                int *arr = malloc(n * sizeof(int));
                if (arr == NULL) {
                    printf("内存分配失败!\n");
                    break;
                }
                printf("请输入 %d 个整数: ", n);
                for (int i = 0; i < n; i++) {
                    scanf("%d", arr + i);
                }
                printf("原数组: ");
                for (int i = 0; i < n; i++) {
                    printf("%d ", arr[i]);
                }
                printf("\n");
                reverse(arr, n);
                printf("逆序后: ");
                for (int i = 0; i < n; i++) {
                    printf("%d ", arr[i]);
                }
                printf("\n");
                free(arr);
                break;
            }
            case '8': {
                printf("\n===== 任务 8: 函数内动态分配数组 =====\n");
                int *a = NULL;
                int n;
                printf("请输入数组大小 n: ");
                scanf("%d", &n);
                if (n <= 0) {
                    printf("n 必须大于 0\n");
                    break;
                }
                createArray(&a, n);
                printf("输入的数组: ");
                for (int i = 0; i < n; i++) {
                    printf("%d ", a[i]);
                }
                printf("\n");
                free(a);
                a = NULL;

                printf("\n思考题答案:\n");
                printf("  不能直接写 int *p; 然后在函数内 p = malloc(...) 来改变 main() 中 a 的值。\n");
                printf("  原因：C 语言函数参数是值传递。如果传递 int *p，函数内修改的只是 p 的副本，\n");
                printf("       不会影响 main() 中原来的指针 a。\n");
                printf("  解决：必须传递二级指针 int **p，这样 *p = malloc(...) 才能修改 main() 中 a 的值。\n");
                break;
            }
            case '9':
                task9_struct_analysis();
                break;
            case '10':
                task10_student_array();
                break;
            case 'A':
            case 'a':
                taskA_create_student_array();
                break;
            case 'B':
            case 'b':
                taskB_pointer_errors();
                break;
            case 'S':
            case 's':
                experiment_summary();
                break;
            case '0':
                printf("程序退出。\n");
                break;
            default:
                printf("无效的选择，请重新输入。\n");
        }
    } while (choice != '0');

    return 0;
}
