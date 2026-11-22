// 第 05 课：练习
// 练习 1：定义 struct Point { int x; int y; }; 读入两个点的坐标，输出它们的中点坐标（整数除法即可）。
// 练习 2：定义 struct Student { string name; int score; }; 读入 n 个学生，输出分数最高的学生姓名。
// 练习 3：用 new 创建一个 Point，读入坐标，通过指针把它的 x 改成 x + 1，再输出两个坐标。

#include <iostream>
#include <string>
using namespace std;

struct Point {
    int x;
    int y;
};

struct Student {
    string name;
    int score;
};

int main() {
    // 练习 1：两个点的中点，横纵坐标分别求平均
    Point p1, p2;
    cout << "练习 1：请输入两个点的坐标 x1 y1 x2 y2：" << endl;
    cin >> p1.x >> p1.y >> p2.x >> p2.y;
    // 原写法只读了一个点 P1，再算 (P1.x + P1.y) / 2：
    //   struct Point P1;
    //   cin >> P1.x >> P1.y;
    //   cout << (P1.x + P1.y) / 2 << endl;
    cout << (p1.x + p2.x) / 2 << " " << (p1.y + p2.y) / 2 << endl;

    // 练习 2：读入 n 个学生，输出最高分者的姓名
    int n = 0;
    cin >> n;
    Student Stu[100]; // 原写法：struct Student Stu[n]; 变长数组不符合标准 C++
    int ma = 0;
    string ma_n;
    for (int i = 0; i < n; i++) {
        // 原写法：cout << 'student' << i << 'name' << endl;
        // 单引号只能包一个字符，'student' 会被当成整数输出乱码
        cout << "student " << i << " name: ";
        cin >> Stu[i].name;
        cout << "student " << i << " score: ";
        cin >> Stu[i].score;
        if (Stu[i].score > ma) {
            ma_n = Stu[i].name;
            ma = Stu[i].score;
        }
    }
    cout << ma_n << endl; // 原写法漏了这句，最高分姓名从未输出

    // 练习 3：在堆上建一个点，通过指针把 x 加 1
    Point *p = new Point;
    cout << "练习 3：请输入一个点的坐标 x y：" << endl;
    cin >> p->x >> p->y;
    // 原写法是写死坐标、直接赋值，且没有 delete：
    //   struct Point P2 = { 18, 19};
    //   struct Point *p = &P2;
    //   p->x = 20;
    p->x = p->x + 1;
    cout << p->x << " " << p->y << endl;
    delete p;
    p = NULL;

    return 0;
}
