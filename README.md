# sandai

Windows 与 Mac 共用的代码仓库。

## 目录

| 目录 / 文件 | 说明 | 来源机器 |
|---|---|---|
| `visual/` | Visual Studio 解决方案 `ConsoleApplication1`（课程设计、按功能分类） | Windows |
| `PyProject/` | Python 项目骨架（main.py / requirements.txt / src / tests） | Windows |
| `cpp/` | C++ 封装系列练习 | Mac |
| `课程设计 社交软件/` | 社交软件课程设计（Mac 版，878 行） | Mac |
| `aaa.cpp` | 综合练习 | Mac |
| `05构造函数和析构函数.cpp` | 构造函数/析构函数练习 | Mac |
| `basics/` | C / C++ / Python 三语言最小示例 | Mac |
| `python/` | Python 脚本 | Mac |

> 注意：`visual/课程设计.cpp`（1525 行，Windows 版）与 `课程设计 社交软件/社交软件aaa.cpp`（878 行，Mac 版）是同一课的**两个不同版本**，都保留了，需要的时候自己比对合并。

## 在 Windows 上

用 Visual Studio 打开 `visual/ConsoleApplication1/ConsoleApplication1.slnx`。

## 在 Mac 上

```bash
cd ~/Desktop/sandai
code .                      # 用 VS Code 打开
```

- 编译运行：`⌘⇧B` 编译当前文件；右键 → Run Code 直接跑
- 断点调试：`F5` → 选 **C 调试** / **C++ 调试** / **Python · 当前文件**

## 日常同步

```bash
git pull          # 开工前先拉
git add -A
git commit -m "说明"
git push
```

`.gitignore` 已排除编译产物（`*.dSYM`、`aaa`、`__pycache__`、`build/`、`.DS_Store`、`.vscode/`），不会把二进制塞进仓库。
