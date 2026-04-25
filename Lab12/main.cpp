#include <print>
#include <string>
#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>

using std::string;
using std::print;
using std::vector;

// ─── Person (Task 1) ───────────────────────────────────────────────────────

class Person
{
protected:  // Task 3: protected instead of private
    string _name;
    int    _age;
    char   _gender;
    int    _height;

public:
    Person() : _name(""), _age(0), _gender('O'), _height(0) {}

    Person(const string& name, int age, char gender, int height)
        : _name(name), _age(age), _gender(gender), _height(height) {
    }

    Person(const Person& other) = default;
    Person& operator=(const Person& rhs) = default;
    virtual ~Person() = default;

    friend std::istream& operator>>(std::istream& in, Person& p);
    friend std::ostream& operator<<(std::ostream& out, const Person& p);

    string get_name()   const { return _name; }
    int    get_age()    const { return _age; }
    char   get_gender() const { return _gender; }
    int    get_height() const { return _height; }

    void set_name(const string& n) { _name = n; }
    void set_age(int a) { _age = a; }
    void set_gender(char g) { _gender = g; }
    void set_height(int h) { _height = h; }
};

std::ostream& operator<<(std::ostream& out, const Person& p)
{
    out << "Name: " << p._name
        << ", Age: " << p._age
        << ", Gender: " << p._gender
        << ", Height: " << p._height;
    return out;
}

std::istream& operator>>(std::istream& in, Person& p)
{
    in >> p._name >> p._age >> p._gender >> p._height;
    return in;
}

// ─── TestPerson (Task 2 & 3) ───────────────────────────────────────────────

class TestPerson : public Person
{
public:
    void test_default_constructor()
    {
        Person p;
        bool ok = p.get_name() == "" && p.get_age() == 0 &&
            p.get_gender() == 'O' && p.get_height() == 0;
        print("default_constructor: {}\n", ok ? "PASSED" : "FAILED");
    }

    void test_param_constructor()
    {
        Person p("Alice", 20, 'F', 165);
        bool ok = p.get_name() == "Alice" && p.get_age() == 20 &&
            p.get_gender() == 'F' && p.get_height() == 165;
        print("param_constructor:   {}\n", ok ? "PASSED" : "FAILED");
    }

    void test_copy_constructor()
    {
        Person p1("Bob", 25, 'M', 180);
        Person p2(p1);
        bool ok = p2.get_name() == p1.get_name() && p2.get_age() == p1.get_age() &&
            p2.get_gender() == p1.get_gender() && p2.get_height() == p1.get_height();
        print("copy_constructor:    {}\n", ok ? "PASSED" : "FAILED");
    }

    void test_assignment()
    {
        Person p1("Carol", 30, 'F', 170);
        Person p2;
        p2 = p1;
        bool ok = p2.get_name() == "Carol" && p2.get_age() == 30;
        print("assignment_op:       {}\n", ok ? "PASSED" : "FAILED");
    }

    void test_setters_getters()
    {
        Person p;
        p.set_name("Dave"); p.set_age(22); p.set_gender('M'); p.set_height(175);
        bool ok = p.get_name() == "Dave" && p.get_age() == 22 &&
            p.get_gender() == 'M' && p.get_height() == 175;
        print("setters/getters:     {}\n", ok ? "PASSED" : "FAILED");
    }

    // Task 3: protected members accessible directly in derived class
    void test_protected_access()
    {
        _name = "Eve"; _age = 19; _gender = 'F'; _height = 162;
        bool ok = get_name() == "Eve" && get_age() == 19;
        print("protected_access:    {}\n", ok ? "PASSED" : "FAILED");
    }

    void test_stream_insertion()
    {
        std::ostringstream oss;
        Person p("Frank", 40, 'M', 178);
        oss << p;
        bool ok = oss.str().find("Frank") != string::npos;
        print("stream_insertion:    {}\n", ok ? "PASSED" : "FAILED");
    }

    void run_all()
    {
        print("\n=== Person Tests ===\n");
        test_default_constructor();
        test_param_constructor();
        test_copy_constructor();
        test_assignment();
        test_setters_getters();
        test_protected_access();
        test_stream_insertion();
    }
};

// ─── Course struct ────────────────────────────────────────────────────────

struct Course
{
    string name;
    int    credits;
    float  grade;   // student: current grade | teacher: avg student grade
};

// ─── Student (Task 4) ─────────────────────────────────────────────────────

class Student : public Person
{
private:
    static constexpr int MAX = 10;
    Course _courses[MAX];
    int    _numCourses;
    int    _totalCredits;

public:
    Student()
        : Person(), _numCourses(0), _totalCredits(0) {
    }

    Student(const string& name, int age, char gender, int height)
        : Person(name, age, gender, height), _numCourses(0), _totalCredits(0) {
    }

    Student(const Student& o)
        : Person(o), _numCourses(o._numCourses), _totalCredits(o._totalCredits)
    {
        for (int i = 0; i < _numCourses; i++) _courses[i] = o._courses[i];
    }

    Student& operator=(const Student& rhs)
    {
        if (this != &rhs) {
            Person::operator=(rhs);
            _numCourses = rhs._numCourses;
            _totalCredits = rhs._totalCredits;
            for (int i = 0; i < _numCourses; i++) _courses[i] = rhs._courses[i];
        }
        return *this;
    }

    ~Student() override = default;

    bool add_course(const Course& c)
    {
        if (_numCourses >= MAX) return false;
        _courses[_numCourses++] = c;
        return true;
    }

    int get_num_courses()   const { return _numCourses; }
    int get_total_credits() const { return _totalCredits; }

    int compute_total_credits()
    {
        _totalCredits = 0;
        for (int i = 0; i < _numCourses; i++) _totalCredits += _courses[i].credits;
        return _totalCredits;
    }

    // GPA = weighted avg: sum(grade * credits) / sum(credits)
    float compute_gpa() const
    {
        float weight = 0; int creds = 0;
        for (int i = 0; i < _numCourses; i++) {
            weight += _courses[i].grade * _courses[i].credits;
            creds += _courses[i].credits;
        }
        return creds ? weight / creds : 0.0f;
    }

    friend std::ostream& operator<<(std::ostream& out, const Student& s)
    {
        out << static_cast<const Person&>(s)
            << ", Courses: " << s._numCourses
            << ", GPA: " << s.compute_gpa();
        return out;
    }
};

// ─── Teacher (Task 5) ─────────────────────────────────────────────────────

class Teacher : public Person
{
private:
    static constexpr int MAX = 10;
    Course _courses[MAX];
    int    _numCourses;
    int    _totalCredits;

public:
    Teacher()
        : Person(), _numCourses(0), _totalCredits(0) {
    }

    Teacher(const string& name, int age, char gender, int height)
        : Person(name, age, gender, height), _numCourses(0), _totalCredits(0) {
    }

    Teacher(const Teacher& o)
        : Person(o), _numCourses(o._numCourses), _totalCredits(o._totalCredits)
    {
        for (int i = 0; i < _numCourses; i++) _courses[i] = o._courses[i];
    }

    Teacher& operator=(const Teacher& rhs)
    {
        if (this != &rhs) {
            Person::operator=(rhs);
            _numCourses = rhs._numCourses;
            _totalCredits = rhs._totalCredits;
            for (int i = 0; i < _numCourses; i++) _courses[i] = rhs._courses[i];
        }
        return *this;
    }

    ~Teacher() override = default;

    bool add_course(const Course& c)
    {
        if (_numCourses >= MAX) return false;
        _courses[_numCourses++] = c;
        return true;
    }

    const Course* get_courses()  const { return _courses; }
    int  get_num_courses()       const { return _numCourses; }
    int  get_total_credits()     const { return _totalCredits; }

    int compute_total_credits()
    {
        _totalCredits = 0;
        for (int i = 0; i < _numCourses; i++) _totalCredits += _courses[i].credits;
        return _totalCredits;
    }

    float compute_avg_grade() const
    {
        if (!_numCourses) return 0.0f;
        float sum = 0;
        for (int i = 0; i < _numCourses; i++) sum += _courses[i].grade;
        return sum / _numCourses;
    }

    friend std::ostream& operator<<(std::ostream& out, const Teacher& t)
    {
        out << static_cast<const Person&>(t)
            << ", Courses taught: " << t._numCourses
            << ", Avg student grade: " << t.compute_avg_grade();
        return out;
    }
};

// ─── Task 6: registration app ─────────────────────────────────────────────

void registration_app()
{
    print("\n=== Course Registration (Task 6) ===\n");

    Teacher prof("Dr. Smith", 45, 'M', 175);
    prof.add_course({ "CptS122", 3, 88.5f });
    prof.add_course({ "CptS223", 3, 91.0f });
    prof.add_course({ "CptS317", 3, 85.0f });

    print("Teacher: {}\n", prof.get_name());
    print("Available courses:\n");
    for (int i = 0; i < prof.get_num_courses(); i++) {
        const Course& c = prof.get_courses()[i];
        print("  [{}] {} ({} credits)\n", i, c.name, c.credits);
    }

    Student stu("Jane Doe", 20, 'F', 165);
    print("\nRegistering {} for CptS122 and CptS223...\n", stu.get_name());
    stu.add_course({ "CptS122", 3, 3.5f });
    stu.add_course({ "CptS223", 3, 3.8f });

    print("Credits enrolled: {}\n", stu.compute_total_credits());
    print("Current GPA:      {:.2f}\n", stu.compute_gpa());
}

// ─── main ─────────────────────────────────────────────────────────────────

int main()
{
    // Tasks 1-3
    TestPerson tp;
    tp.run_all();

    // Task 4
    print("\n=== Student Demo (Task 4) ===\n");
    Student s("Alice", 21, 'F', 163);
    s.add_course({ "CptS122", 3, 3.7f });
    s.add_course({ "Math101", 4, 3.3f });
    print("Credits: {}\n", s.compute_total_credits());
    print("GPA:     {:.2f}\n", s.compute_gpa());

    // Task 5
    print("\n=== Teacher Demo (Task 5) ===\n");
    Teacher t("Prof. Jones", 50, 'M', 180);
    t.add_course({ "CptS122", 3, 87.0f });
    t.add_course({ "CptS223", 3, 92.0f });
    print("Credits taught:    {}\n", t.compute_total_credits());
    print("Avg student grade: {:.1f}\n", t.compute_avg_grade());

    // Task 6
    registration_app();

    return 0;
}