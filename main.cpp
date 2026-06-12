#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

struct Student {
    string id;
    string name;
    int score;
};

int findStudentIndex(const vector<Student>& students, const string& id) {
    for (size_t i = 0; i < students.size(); ++i) {
        if (students[i].id == id) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int readInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            clearInput();
            return value;
        }
        cout << "輸入格式錯誤，請輸入整數。\n";
        clearInput();
    }
}

void addStudent(vector<Student>& students) {
    Student student;

    cout << "請輸入學號：";
    getline(cin, student.id);

    if (findStudentIndex(students, student.id) != -1) {
        cout << "新增失敗：學號已存在。\n";
        return;
    }

    cout << "請輸入姓名：";
    getline(cin, student.name);

    student.score = readInt("請輸入成績：");
    students.push_back(student);

    cout << "學生資料新增成功。\n";
}

void printHeader() {
    cout << left << setw(12) << "學號"
         << setw(16) << "姓名"
         << setw(8) << "成績" << '\n';
    cout << string(36, '-') << '\n';
}

void listStudents(const vector<Student>& students) {
    if (students.empty()) {
        cout << "目前沒有學生資料。\n";
        return;
    }

    printHeader();
    for (const Student& student : students) {
        cout << left << setw(12) << student.id
             << setw(16) << student.name
             << setw(8) << student.score << '\n';
    }
}

void sortStudentsByScore(vector<Student>& students) {
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.score > b.score;
    });

    cout << "已依成績由高到低排序。\n";
    listStudents(students);
}

void searchStudent(const vector<Student>& students) {
    string id;
    cout << "請輸入要查詢的學號：";
    getline(cin, id);

    int index = findStudentIndex(students, id);
    if (index == -1) {
        cout << "查無此學號。\n";
        return;
    }

    printHeader();
    cout << left << setw(12) << students[index].id
         << setw(16) << students[index].name
         << setw(8) << students[index].score << '\n';
}

void showStatistics(const vector<Student>& students) {
    if (students.empty()) {
        cout << "目前沒有學生資料，無法統計。\n";
        return;
    }

    int total = 0;
    int highest = students[0].score;
    int lowest = students[0].score;
    int passCount = 0;
    int failCount = 0;

    for (const Student& student : students) {
        total += student.score;
        highest = max(highest, student.score);
        lowest = min(lowest, student.score);

        if (student.score >= 60) {
            ++passCount;
        } else {
            ++failCount;
        }
    }

    double average = static_cast<double>(total) / students.size();

    cout << fixed << setprecision(2);
    cout << "全班平均：" << average << '\n';
    cout << "最高分：" << highest << '\n';
    cout << "最低分：" << lowest << '\n';
    cout << "及格人數：" << passCount << '\n';
    cout << "不及格人數：" << failCount << '\n';
}

void showMenu() {
    cout << "\n===== 學生資料管理系統 =====\n";
    cout << "1. 新增學生資料\n";
    cout << "2. 列出所有學生\n";
    cout << "3. 依成績排序\n";
    cout << "4. 查詢學生\n";
    cout << "5. 統計成績\n";
    cout << "0. 離開\n";
    cout << "請選擇功能：";
}

int main() {
    vector<Student> students;
    int choice;

    while (true) {
        showMenu();
        if (!(cin >> choice)) {
            cout << "輸入格式錯誤，請輸入選單編號。\n";
            clearInput();
            continue;
        }
        clearInput();

        switch (choice) {
            case 1:
                addStudent(students);
                break;
            case 2:
                listStudents(students);
                break;
            case 3:
                sortStudentsByScore(students);
                break;
            case 4:
                searchStudent(students);
                break;
            case 5:
                showStatistics(students);
                break;
            case 0:
                cout << "程式結束。\n";
                return 0;
            default:
                cout << "沒有這個選項，請重新輸入。\n";
                break;
        }
    }
}