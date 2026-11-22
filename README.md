# C++ 408 数据结构练习记录

从零开始用 C++ 写 408 考研数据结构算法题的过程记录。每课一个讲义文件 `NN_topic.cpp`，加一个练习文件 `NN_topic_ex.cpp`。

练习文件里保留了**写错的原代码注释**，方便对照「错在哪 → 怎么改」。

## 目录结构

```
cpp/
  01_io.cpp              讲义：输入输出
  01_io_ex.cpp           练习：输入输出
  ...
  12_level_order.cpp     讲义：层序遍历
  12_level_order_ex.cpp  练习：层序遍历
.vscode/                 VS Code 的编译/调试配置
```

## 编译方式

```bash
g++ -std=c++11 -Wall -fexec-charset=GBK -o run.exe 08_seqlist_ex.cpp
./run.exe
```

- `-Wall`：打开常用警告，很多错误（未初始化变量、无符号比较）靠警告就能发现
- `-fexec-charset=GBK`：源码是 UTF-8，Windows 控制台是 GBK，加这个避免中文乱码

## 课程进度

| 课 | 主题 | 文件 | 核心知识点 | 状态 |
|---|---|---|---|---|
| 01 | 输入输出 | `cpp/01_io.cpp` / `_ex.cpp` | `cin` / `cout`、变量、算术运算 | ✅ |
| 02 | 分支结构 | `cpp/02_branch.cpp` / `_ex.cpp` | `if / else`、`switch`、三目运算符 | ✅ |
| 03 | 循环结构 | `cpp/03_loop.cpp` / `_ex.cpp` | `for`、`while`、嵌套循环、`break` / `continue` | ✅ |
| 04 | 数组与字符串 | `cpp/04_array_string.cpp` / `_ex.cpp` | 一维数组、字符数组、`string` | ✅ |
| 05 | 结构体与指针 | `cpp/05_struct_pointer.cpp` / `_ex.cpp` | `struct`、指针、引用传参 | ✅ |
| 06 | 单链表 | `cpp/06_linked_list.cpp` / `_ex.cpp` | 带头结点、头插尾插、遍历、删除 | ✅ |
| 07 | 综合复习 | `cpp/07_review.cpp` / `_ex.cpp` | 前六课综合 | ✅ |
| 08 | 顺序表算法 | `cpp/08_seqlist.cpp` / `_ex.cpp` | 删除最小值、逆置、删除所有 x、归并 | ✅ |
| 09 | 栈与队列 | `cpp/09_stack_queue.cpp` / `_ex.cpp` | 顺序栈、进制转换、括号匹配、循环队列、两栈实现队列 | ✅ |
| 10 | 链表高频算法 | `cpp/10_linked_list_algo.cpp` / `_ex.cpp` | 倒数第 k 个、环入口、有序去重、链表相交 | ✅ |
| 11 | 二叉树基础 | `cpp/11_binary_tree.cpp` / `_ex.cpp` | 二叉链表、先/中/后序遍历、结点数、叶子数、深度、交换子树 | ✅ |
| 12 | 层序遍历 | `cpp/12_level_order.cpp` / `_ex.cpp` | BFS、按层输出、树的宽度、完全二叉树判定 | 🚧 练习 1–2 完成，3–4 待做 |

## 后续计划

| 内容 | 409 考点 |
|---|---|
| 二叉排序树 BST | 插入、查找、删除（三种情况） |
| 平衡二叉树 AVL 与堆 | 四种旋转、建堆与向下调整 |
| 哈夫曼树 | WPL 计算、编码 |
| 图 | 邻接矩阵 / 邻接表、DFS / BFS |
| 最小生成树与最短路径 | Prim / Kruskal、Dijkstra / Floyd |
| 查找 | 折半查找判定树、散列表 ASL |
| 排序 | 八大排序的稳定性与复杂度 |

## 约定

- 每个 `cin` 前都打印提示，说明要输入什么
- 显式 `#include`，不依赖头文件间接包含
- 不超出当课范围提前用没学过的语法
