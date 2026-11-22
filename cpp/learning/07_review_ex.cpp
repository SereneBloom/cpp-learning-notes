// 第 07 课：综合练习
// 练习 1：读入 n 个学生（姓名 分数），输出平均分（保留小数）和最高分学生的姓名。
// 练习 2：读入一行带空格的句子，统计其中空格的数量（用 getline）。
// 练习 3：不断读入整数直到没有数据（while (cin >> x)），输出其中最大值与最小值。

#include <iostream>
#include <string>
#include <climits>
using namespace std;

struct Student
{
    string name;
    int score;
};

int main()
{
    // 练习 1：结构体数组 + 平均分 + 最高分
    // TODO:
    //   1) 提示并读入 n
    //   2) 循环读入 stu[i].name 和 stu[i].score（姓名不含空格）
    //   3) 求总分，输出 (double)sum / n
    //   4) 记录最高分对应的下标，输出该学生姓名
    cout << "input n1:" << endl;
    int n1;
    cin >> n1;
    double sum = 0;
    Student stu[100];
    if (n1 == 0)
    {
        cout << "empty" << endl;
    }
    else
    {
        int ma = 0;
        for (int i = 0; i < n1; i++)
        {
            cout << "name:" << endl;
            cin >> stu[i].name;
            cout << "score:" << endl;
            cin >> stu[i].score;
            if(stu[i].score > stu[ma].score){
                ma = i;
            }
            sum += stu[i].score;
        }
        cout << "平均分：" << sum / n1 << endl;
        cout << "最高分：" << stu[ma].name << " " << stu[ma].score << endl;
    }
    // 练习 2：getline 读整行
    // TODO:
    //   1) 注意：前面用 cin >> 读过数字，缓冲区里还留着一个换行
    //   2) 用 getline(cin >> ws, line) 或先 cin.ignore() 清掉
    //   3) 遍历 line，统计空格个数并输出
    string line;
    cout << "input: " << endl;
    getline(cin >> ws, line);
    int space = 0;
    for (int i = 0; i < (int)line.size(); i++) {
        if (line[i] == ' ') space++;
    }
    cout << "空格数：" << space << endl;
    
    // 练习 3：多组输入
    // TODO:
    //   1) while (cin >> x) 循环，边读边更新最大值 mx 与最小值 mi
    //   2) 第一个数要特殊处理：把 mx 和 mi 都初始化成它
    //   3) 循环结束后输出 mx 和 mi
    int x;
    int mx = INT_MIN;
    int mi = INT_MAX;
    while(cin >> x){
        if(x > mx){
            mx = x;
        }
        if(x < mi){
            mi = x;
        }
    }
    cout << mx << " " << mi << endl;
    return 0;
}
