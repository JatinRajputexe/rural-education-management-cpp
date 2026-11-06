#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

class Person {
protected: int id; string name;
public:
    Person(int i = 0, string n = "") : id(i), name(n) {}
    virtual ~Person() {}
    string getName() const { return name; }
    virtual string role() const = 0;
};
class Student : public Person {
public:
    vector<int> courses;                           // enrolled course IDs
    using Person::Person;
    string role() const override { return "Student"; }
};
class Teacher : public Person {
public:
    using Person::Person;
    string role() const override { return "Teacher"; }
};
struct Rec { int present = 0, total = 0; double marks = 0; };

class Centre {
    map<int, Student> students; vector<Teacher> teachers;
    map<int, string> courses; map<int, vector<string>> resources;
    map<pair<int,int>, Rec> rec;                   // (student, course) -> record
    static char grade(double m) { return m >= 80 ? 'A' : m >= 60 ? 'B' : m >= 40 ? 'C' : 'D'; }
public:
    void addTeacher(int i, string n) { teachers.push_back(Teacher(i, n)); }
    void addCourse(int c, string t) { courses[c] = t; }
    void addResource(int c, string r) { resources[c].push_back(r); }
    void registerStudent(int i, string n) {
        if (students.count(i)) { cout << "Duplicate ID\n"; return; }
        students[i] = Student(i, n);
    }
    void enroll(int s, int c) {
        auto& v = students[s].courses;
        if (find(v.begin(), v.end(), c) == v.end()) v.push_back(c);
    }
    void attend(int s, int c, bool p) { rec[{s, c}].total++; if (p) rec[{s, c}].present++; }
    void setMarks(int s, int c, double m) { rec[{s, c}].marks = m; }
    void report() {
        map<int, pair<double,int>> sum;
        for (auto& r : rec) {
            int s = r.first.first, c = r.first.second;
            cout << students[s].getName() << " | " << courses[c] << " | Attendance "
                 << 100.0 * r.second.present / r.second.total << "% | Marks " << r.second.marks
                 << " | Grade " << grade(r.second.marks) << "\n";
            sum[s].first += r.second.marks; sum[s].second++;
        }
        vector<pair<double, string>> rank;
        for (auto& s : sum) rank.push_back({s.second.first / s.second.second, students[s.first].getName()});
        sort(rank.rbegin(), rank.rend());
        cout << "\nRanking by average marks:\n";
        for (size_t i = 0; i < rank.size(); i++) cout << i + 1 << ". " << rank[i].second << " - " << rank[i].first << "\n";
        cout << "\nResources for " << courses[10] << ": ";
        for (auto& r : resources[10]) cout << r << "; ";
        cout << "\n";
    }
    void save(const string& f) {
        ofstream o(f);
        for (auto& s : students) {
            o << s.first << "," << s.second.getName();
            for (int c : s.second.courses) o << "," << c;
            o << "\n";
        }
    }
    void load(const string& f) {
        ifstream in(f); string l, a, n, c; students.clear();
        while (getline(in, l)) {
            stringstream ss(l); getline(ss, a, ','); getline(ss, n, ',');
            registerStudent(stoi(a), n);
            while (getline(ss, c, ',')) enroll(stoi(a), stoi(c));
        }
        cout << "Loaded " << students.size() << " students from " << f << "\n";
    }
};

int main() {
    Centre c;
    c.addTeacher(1, "Mr. Sharma"); c.addCourse(10, "Maths"); c.addCourse(20, "English");
    c.addResource(10, "Algebra Workbook"); c.addResource(10, "Fractions Video");
    c.registerStudent(201, "Asha"); c.registerStudent(202, "Ravi"); c.registerStudent(203, "Meena");
    c.enroll(201, 10); c.enroll(201, 20); c.enroll(202, 10); c.enroll(203, 20);
    bool a[5] = {1, 1, 0, 1, 1};                   // sample attendance pattern
    for (int i = 0; i < 5; i++) {
        c.attend(201, 10, a[i]); c.attend(201, 20, 1);
        c.attend(202, 10, i % 2 == 0); c.attend(203, 20, i < 4);
    }
    c.setMarks(201, 10, 82); c.setMarks(201, 20, 74);
    c.setMarks(202, 10, 45); c.setMarks(203, 20, 68);
    c.report();
    c.save("students.txt");
    c.load("students.txt");
}