# sandai · 代码总仓库

这是这台电脑上 **所有编程代码的唯一入口**。
远程仓库：<https://github.com/sandai070331/sandai>

## 目录结构

| 目录 | 内容 | 建议打开方式 |
| --- | --- | --- |
| `cpp/visual/` | C++ 课程设计、LeetCode 练习（27/704）、社交系统网页 | Visual Studio 打开 `.slnx` |
| `cpp/lessons/` | C++ 基础语法分主题练习（变量、循环、函数……） | Visual Studio |
| `cpp/practice/` | 控制台小项目（三子棋、Project1-5 等） | Visual Studio |
| `cpp/exercises/` | 算法初步练习（插入、递归、数组逆序、扑克牌算法） | Visual Studio |
| `cpp/homework/` | C 语言作业 HW3 / HW4 / Lab2 | VS Code 或任意编辑器 |
| `cpp/project1/` | 最早的 Visual Studio 控制台工程 | Visual Studio |
| `cpp/game-course/` | 游戏程序设计课 HW1–HW4、Lab2（C 语言） | VS Code |
| `python/PyProject/` | Python 主项目（含 venv、tests） | PyCharm |
| `python/scripts/` | 零散脚本（v3 数据处理等） | PyCharm / VS Code |
| `cpp/*.cpp`（根目录） | Mac 端 C++ 封装练习（封装、构造/析构） | VS Code |
| `课程设计 社交软件/` | 社交软件课程设计 Mac 版（878 行） | VS Code |
| `_archives/` | 作业原始 zip 包（**不入库**，仅本地留存） | 资源管理器 |

## 日常使用

```powershell
# 进入总仓库
cd D:\Code

# 看改了什么
git status

# 提交并推送（唯一需要记住的三行）
git add -A
git commit -m "说明这次改了什么"
git push
```

首次推送会由 Windows 凭据管理器自动完成 GitHub 认证，不需要输密码。

| `basics/` | Mac 端 C / C++ / Python 三语言最小示例 | VS Code |
| `aaa.cpp`、`05构造函数和析构函数.cpp` | Mac 端综合练习与构造/析构练习 | VS Code |

## 双机协作（Windows / Mac）

这个仓库同时供 Windows 和 Mac 使用：

- **Mac 端**提交了 `cpp/` 根目录下的封装练习、`课程设计 社交软件/`、`basics/`、`aaa.cpp`。
- **Windows 端**的 `visual/` 已移动到 `cpp/visual/`；`cpp/visual/课程设计.cpp`（1525 行）与 `课程设计 社交软件/社交软件aaa.cpp`（878 行）是同一门课的两个版本，**都保留**，需要时自行比对。
- 同步习惯：开工前 `git pull`，收工前 `git add -A && git commit -m "说明" && git push`。

Mac 上打开：`cd ~/Desktop/sandai && code .`（按你 Mac 上的实际目录名调整）。

## 接入 DeepSeek

- **VS Code / PyCharm**：已安装 Continue 插件，配置文件在 `C:\Users\sandai\.continue\config.yaml`，模型为 `deepseek-flash`、`deepseek-v4-pro`。
- **Visual Studio**：见 `D:\编程工具\使用说明.md`。
- **终端 / Claude Code**：`claude` 命令已通过 Anthropic 兼容端点接入 DeepSeek。

> API Key 只存在本机配置中，**不要**写进任何代码或提交到 git。
