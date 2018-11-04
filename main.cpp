#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <fstream>
/*
 * 2018-11-04
 * 张贺
 * 学生成绩管理
 * */
using namespace std;

class Course {
public:
    virtual ~Course() = 0;
};

Course::~Course() {}

class Math : public Course {
private:
    double score;
public:
    Math() {}

    Math(double _score) : score(_score) {}

    double getscore() const { return score; }

    double getScore() const {
        return score;
    }

    void setScore(double score) {
        Math::score = score;
    }

};

class Physics : public Course {
private:
    double score;
public:
    Physics() {}

    Physics(double _score) : score(_score) {}

    double getscore() const { return score; }

    void set(double score) { this->score = score; }
};

class Score {
private:
    Math math;
    Physics physics;
public:
    Score() {}

    Score(Math _math, Physics _physice) : math(_math), physics(_physice) {}

    void setScore(Math _math, Physics _physice) {
        math = _math;
        physics = _physice;
    }

    const double getMath() const {
        return math.getScore();
    }

    void setMath(const Math &math) {
        Score::math = math;
    }

    const double getPhysics() const {
        return physics.getscore();
    }

    void setPhysics(const Physics &physics) {
        Score::physics = physics;
    }
};

class Student {
private:
    string name;
    string num;
    Score score;
    double average;
public:
    Student() {}

    Student(string _name, string _num) : name(_name), num(_num) {}

    const string &getName() const {
        return name;
    }

    void setName(const string &name) {
        Student::name = name;
    }

    string getNum() const {
        return num;
    }

    void setNum(string num) {
        Student::num = num;
    }

    void setScore(double math, double phycise) {
        this->score.setScore(math, phycise);
        this->average = (math + phycise) / 2;
    }

    Score getSocre() {
        return score;
    }

    double getAverage() const {
        return average;
    }

};

class ScoreManager {
private:
    vector<Student> students;
public:
    ScoreManager() {};

    ~ScoreManager();

    void addStudent(string name, string num);

    void delStudent(string name);

    void setStudentScore(string num, double math, double physice);

    void printStudentByNum(string num);

    void sortByCourse();

    void sortByAve();

    void statisAve();

    void PrintStudentInfo();

    void printAllStudentInfo();
};

ScoreManager::~ScoreManager() {
    ofstream outfile("data.txt");
    cout << "保存中...." << endl;
    for (Student student:students) {
        outfile << student.getName() << "\t" << student.getNum() << "\t" << student.getSocre().getMath() << "\t\t"
                << student.getSocre().getPhysics() << endl;
    }
    cout << "保存成功" << endl;
}

void ScoreManager::PrintStudentInfo() {
    for (Student student:students) {
        cout << student.getName() << "   " << student.getNum() << "  " << endl;
    }
}

void ScoreManager::addStudent(string name, string num) {
    Student student(name, num);
    students.push_back(student);
}

void ScoreManager::delStudent(string num) {
    int flag = 0;
    for (Student student:students) {
        if (student.getNum() == num) {
            break;
        }
        flag++;
    }
    students.erase(students.begin() + flag);
    cout << "删除成功" << endl;
}

void ScoreManager::setStudentScore(string num, double math, double physice) {
    int flag = 0;
    for (Student student:students) {
        if (student.getNum() == num) {
            break;
        }
        flag++;
    }
    students[flag].setScore(math, physice);
    cout << math << "  " << physice << endl;
}

void ScoreManager::printStudentByNum(string num) {

    for (Student student:students) {
        if (student.getNum() == num) {
            cout << "姓名" << "\t" << "学号" << "\t\t" << "数学成绩" << "\t" << "物理成绩" << endl;
            cout << student.getName() << "\t" << student.getNum() << "\t" << student.getSocre().getMath() << "\t\t"
                 << student.getSocre().getPhysics() << endl;
        }
    }
}

void ScoreManager::printAllStudentInfo() {
    cout << "姓名" << "\t" << "学号" << "\t\t" << "数学成绩" << "\t" << "物理成绩\t" << "平均成绩" << endl;
    for (Student student:students) {
        cout << student.getName() << "\t" << student.getNum() << "\t" << student.getSocre().getMath() << "\t\t"
             << student.getSocre().getPhysics() << "\t\t" << student.getAverage() << endl;
    }
}

void ScoreManager::sortByCourse() {
    cout << "请输入排序科目  物理 or 数学" << endl;
    string chiose;
    cin >> chiose;
    if (chiose == "物理") {
        sort(students.begin(), students.end(), [](Student &s1, Student s2) {
            return s1.getSocre().getPhysics() > s2.getSocre().getPhysics();
        });
        cout << "-----------------------物理成绩排名------------------" << endl;
        printAllStudentInfo();
    }
    if (chiose == "数学") {
        sort(students.begin(), students.end(), [](Student &s1, Student s2) {
            return s1.getSocre().getMath() > s2.getSocre().getMath();
        });
        cout << "-----------------------数学成绩排名------------------" << endl;
        printAllStudentInfo();
    }

}

void ScoreManager::sortByAve() {
    sort(students.begin(), students.end(), [](Student &s1, Student s2) {
        return s1.getAverage() > s2.getAverage();
    });
    cout << "-----------------------平均成绩排名------------------" << endl;
    printAllStudentInfo();
}

void ScoreManager::statisAve() {
    double mathAverage = 0;
    double physicsAverage = 0;
    double mathSum = 0;
    double physiceSum = 0;
    for (Student student:students) {
        mathSum += student.getSocre().getMath();
        physiceSum += student.getSocre().getPhysics();
    }
    physicsAverage = physiceSum / students.size();
    mathAverage = mathSum / students.size();
    cout << "-----------------------平均分统计------------------" << endl;
    cout << "数学平均分" << "\t" << "物理平均分" << endl;
    cout << mathAverage << "\t\t" << physicsAverage << endl;
}

int main() {
    ScoreManager scoreManager;
    cout << "换用使用学生管理系统" << endl;
    while (true) {
        cout << "-----------------请选择功能-------------------" << endl;
        cout << "0.  增加学生" << endl;
        cout << "1.  删除学生" << endl;
        cout << "2.  设置学生成绩" << endl;
        cout << "3.  输出指定学生成绩" << endl;
        cout << "4.  按课程分类进行排序" << endl;
        cout << "5.  按学生成绩平均分排序" << endl;
        cout << "6.  统计各科成绩平均分" << endl;
        cout << "7.  退出并保存" << endl;
        int choise;
        cin >> choise;
        switch (choise) {
            case 0: {
                scoreManager.addStudent("张贺", "201512300045");
                scoreManager.addStudent("臭宝宝", "201512300037");
                scoreManager.addStudent("香宝宝", "201512300031");
                scoreManager.addStudent("酸宝宝", "201512300032");
                scoreManager.addStudent("苦宝宝", "201512300033");
                scoreManager.addStudent("辣宝宝", "201512300034");
                break;
            }
            case 1: {
                cout << "请输入删除学生学号" << endl;
                string num;
                cin >> num;
                scoreManager.delStudent(num);
                break;
            }
            case 2: {
                scoreManager.setStudentScore("201512300045", 99, 99);
                scoreManager.setStudentScore("201512300037", 98, 93);
                scoreManager.setStudentScore("201512300031", 67, 12);
                scoreManager.setStudentScore("201512300032", 76, 17);
                scoreManager.setStudentScore("201512300033", 33, 78);
                scoreManager.setStudentScore("201512300034", 87, 91);
                break;
            }
            case 3: {
                cout << "请输入查找学生学号" << endl;
                string num;
                cin >> num;
                scoreManager.printStudentByNum(num);
                break;
            }
            case 4: {
                scoreManager.sortByCourse();
                break;
            }
            case 5: {
                scoreManager.sortByCourse();
                break;
            }
            case 6: {
                scoreManager.statisAve();
                break;
            }
            case 7: {
                return 0;
            }
        }


    }

}