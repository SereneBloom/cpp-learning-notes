// 第 05 课：结构体与指针
// 目标：struct 的定义与访问、结构体数组、指针、new / delete

#include <iostream>
#include <string>
using namespace std;

// 结构体定义写在 main 外面，后面所有函数都能用
struct Student {
    string name;
    int age;
    double score;
};

int main() {
    // 1. 定义变量，用 . 访问成员
    Student s1;
    s1.name = "Tom";
    s1.age = 21;
    s1.score = 89.5;
    cout << s1.name << " " << s1.age << " " << s1.score << endl;

    // 也可以按成员顺序一次性初始化
    Student s2 = {"Jerry", 20, 92.0};
    cout << s2.name << " " << s2.score << endl;

    // 2. 结构体数组：每个格子都是一整个结构体
    Student cls[3] = {
        {"Tom", 21, 89.5},
        {"Jerry", 20, 92.0},
        {"Spike", 22, 66.5}
    };
    double sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += cls[i].score;
        cout << cls[i].name << " " << cls[i].score << endl;
    }
    cout << "avg = " << sum / 3 << endl;

    // 3. 指针：& 取地址，* 顺着地址取值
    int a = 10;
    int *p = &a;          // p 保存 a 的地址
    cout << a << " " << *p << endl;
    *p = 99;              // 通过地址改值，a 自己也变了
    cout << a << endl;

    // 4. 指针指向结构体：成员用 ->，等价于 (*ps).成员
    Student *ps = &s1;
    cout << ps->name << " " << (*ps).age << endl;
    ps->age = 22;
    cout << s1.age << endl;

    // 5. new 在堆上开一块空间，用完 delete 还给系统
    Student *q = new Student;
    q->name = "Tyke";
    q->age = 18;
    cout << q->name << " " << q->age << endl;
    delete q;
    q = NULL;

    return 0;
}
