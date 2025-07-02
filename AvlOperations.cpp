#include "AvlOperations.h"
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

AvlOperations::AvlOperations(bool useCGPA) : root(nullptr), useCGPA(useCGPA) {}

bool AvlOperations::useCGPAp()
{
    return useCGPA? true : false;
}

void AvlOperations::insertStudent(int rollNo, const std::string &name, float CGPA, int numSubjects, const std::vector<Course> &courses) {
    root = insert(root, rollNo, name, CGPA, numSubjects, courses);
}

void AvlOperations::deleteStudent(int rollNo) {
    float CGPA = getCGPA(root, rollNo);
    root = deleteNode(root, rollNo, CGPA);
}

void AvlOperations::updateCGPA(int rollNo, float newCGPA) {
    root = updateNodeCGPA(root, rollNo, newCGPA);
}

void AvlOperations::addCourse(int rollNo, const std::string &courseCode, int marks) {
    root = addCourseToNode(root, rollNo, courseCode, marks);
}

void AvlOperations::updateCourseMarks(int rollNo, const std::string &courseCode, int newMarks) {
    root = updateCourseMarksInNode(root, rollNo, courseCode, newMarks);
}

void AvlOperations::deleteCourse(int rollNo, const std::string &courseCode) {
    root = deleteCourseFromNode(root, rollNo, courseCode);
}

void AvlOperations::displayTree() const {
    std::vector<Student*> res;
    InOrder(root, res);
    printStudents(res);
}

bool AvlOperations::printStudentsWithRollNoGreaterThan(int rollNo) const {
    if(useCGPA) return false;
    else{
        printStudentsWithKeyGreaterThan(root, rollNo, -1.0f);
        return true;
    }
}

bool AvlOperations::printStudentsWithRollNoLessThan(int rollNo) const {
    if(useCGPA) return false;
    else{
        printStudentsWithKeyLessThan(root, rollNo, -1.0f);
        return true;
    }
}

bool AvlOperations::printStudentsWithRollNoBetween(int rollNo1, int rollNo2) const {
    if(useCGPA) return false;
    else{
        printStudentsWithKeyBetween(root, rollNo1, rollNo2, -1.0f, -1.0f);
        return true;
    }
}

bool AvlOperations::printStudentsWithCGPAGreaterThan(float CGPA) const {
    if(!useCGPA) return false;
    else{
        printStudentsWithKeyGreaterThan(root, -1, CGPA);
        return true;
    }
}

bool AvlOperations::printStudentsWithCGPALessThan(float CGPA) const {
    if(!useCGPA) return false;
    else{
        printStudentsWithKeyLessThan(root, -1, CGPA);
        return true;
    }
}

bool AvlOperations::printStudentsWithCGPABetween(float CGPA1, float CGPA2) const {
    if(!useCGPA) return false;
    else{
        printStudentsWithKeyBetween(root, -1, -1, CGPA1, CGPA2);
        return true;
    }
}

// Private member functions
Student* AvlOperations::insert(Student* node, int rollNo, const string &name, float CGPA, int numSubjects, const vector<Course> &courses) {
    if (node == nullptr) {
        node = new Student{rollNo, name, CGPA, numSubjects, courses, nullptr, nullptr, 1};
        return node;
    }

    float key = (useCGPA ? CGPA : rollNo);

    if (key < (useCGPA ? node->CGPA : node->rollNo)) node->left = insert(node->left, rollNo, name, CGPA, numSubjects, courses);

    else node->right = insert(node->right, rollNo, name, CGPA, numSubjects, courses);


    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);

    if (balance > 1 && getBalance(node->left) >= 0) return rotateRight(node);
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && getBalance(node->right) <= 0) return rotateLeft(node);
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
   
    return node;
}

float AvlOperations::getCGPA(Student* node, int rollNo)
{
    // when cgpa as a key....
    if(node == nullptr) return 0.0;  

    if(node->rollNo == rollNo) return node->CGPA;
    
    float left = getCGPA(node->left, rollNo);
    if(left != 0.0) return left;
    
    float right = getCGPA(node->right, rollNo);
    if(right != 0.0) return right;

    return 0.0;
}

Student* AvlOperations::getStudentWithCGPA(Student* node, float CGPA)
{
    //when cgpa as key..
    if (node == NULL) return NULL;

    if(node->CGPA == CGPA) return node;
    else if(CGPA < node->CGPA) {
        return getStudentWithCGPA(node->left, CGPA);
    } else {
        return getStudentWithCGPA(node->right, CGPA);
    }
}

Student* AvlOperations::getStudentWithRollNo(Student* node, int rollNo)
{
    //when rollNo as key...
    if(node == nullptr) return node;
    if(node->rollNo == rollNo) return node;

    else if(rollNo < node->rollNo) {
        return getStudentWithRollNo(node->left, rollNo);
    } else {
        return getStudentWithRollNo(node->right, rollNo);
    }
}

Student* AvlOperations::deleteNode(Student* node, int rollNo, float CGPA) {
    if (!node) return nullptr;

    float key = useCGPA ? CGPA : rollNo;

    if (key < (useCGPA ? node->CGPA : node->rollNo))
        node->left = deleteNode(node->left, rollNo, CGPA);
    else if (key > (useCGPA ? node->CGPA : node->rollNo))
        node->right = deleteNode(node->right, rollNo, CGPA);
    else {
        if (!node->left || !node->right) {
            Student* temp = node->left ? node->left : node->right;
            delete node;
            return temp;
        }

        Student* temp = node->right;
        while (temp->left) temp = temp->left;

        node->rollNo = temp->rollNo;
        node->CGPA = temp->CGPA;
        node->name = temp->name;
        node->numSubjects = temp->numSubjects;
        node->courses = temp->courses;

        node->right = deleteNode(node->right, temp->rollNo, temp->CGPA);
    }

    if (!node) return node;

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);

    if (balance > 1 && getBalance(node->left) >= 0) return rotateRight(node);
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && getBalance(node->right) <= 0) return rotateLeft(node);
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// working. .   .   .
Student* AvlOperations::updateNodeCGPA(Student* node, int rollNo, float newCGPA)
{
    if(!useCGPA){
        if(node == nullptr) {
            cout << "Error: Student tree is empty" << endl;
            return node;
        }
        if(node->rollNo == rollNo){
            node->CGPA = newCGPA;
        } else if(node->rollNo < rollNo){
            node->right = updateNodeCGPA(node->right, rollNo, newCGPA);
        } else{
            node->left = updateNodeCGPA(node->left, rollNo, newCGPA); 
        }
        return node;
    } else{
        float CGPA = getCGPA(node, rollNo);
        Student* temp = getStudentWithCGPA(node, CGPA);
        if(temp == nullptr) {
            cout << "Error: Student with roll number " << rollNo << " not found" << endl;
            return node;
        }
        int studentRollNo = temp->rollNo;
        string studentName = temp->name;
        float oldCGPA = temp->CGPA;
        int studentNumSubjects = temp->numSubjects;
        vector<Course> studentCourses = temp->courses;

        node = deleteNode(node, studentRollNo, oldCGPA);
        node = insert(node, studentRollNo, studentName, newCGPA, studentNumSubjects, studentCourses);
        return node;
    }
}

Student* AvlOperations::addCourseToNode(Student* node, int rollNo, const std::string &courseCode, int marks)
{
    if(node == nullptr) {
        cout << "Error: Student tree is empty" << endl;
        return node;
    }

    if(useCGPA){
        float CGPA = getCGPA(node, rollNo);
        Student* temp = getStudentWithCGPA(node, CGPA);
        if(temp == nullptr) {
            cout << "Error: Student with roll number " << rollNo << " not found" << endl;
            return node;
        }
        temp->numSubjects++;
        Course tempcourse = {courseCode, marks};
        temp->courses.push_back(tempcourse);
    } else {
        Student* temp = getStudentWithRollNo(node, rollNo);
        if(temp == nullptr) {
            cout << "Error: Student with roll number " << rollNo << " not found" << endl;
            return node;
        }
        temp->numSubjects++;
        Course tempcourse = {courseCode, marks};
        temp->courses.push_back(tempcourse);
    }
    return node;
}


Student* AvlOperations::updateCourseMarksInNode(Student* node, int rollNo, const std::string &courseCode, int newMarks) {
    if (useCGPA) {
        float CGPA = getCGPA(node, rollNo);
        Student* temp = getStudentWithCGPA(node, CGPA);
        if(temp == NULL) {
            cout << "Error: Student with roll number " << rollNo << " not found.\n";
            return node;
        }
        bool courseFound = false;
        for (Course &course : temp->courses) {
            string code1 = courseCode;
            string code2 = course.courseCode;
            code1.erase(0, code1.find_first_not_of(" \t\n"));
            code1.erase(code1.find_last_not_of(" \t\n") + 1);
            code2.erase(0, code2.find_first_not_of(" \t\n"));
            code2.erase(code2.find_last_not_of(" \t\n") + 1);
            
            if (code1 == code2) {
                course.marks = newMarks;
                courseFound = true;
                break;
            }
        }
        if (!courseFound) {
            cout << "Error: Course " << courseCode << " not found for student " << rollNo << ".\n";
        }
    } else {
        Student* temp = getStudentWithRollNo(node, rollNo);
        if(temp == NULL) {
            cout << "Error: Student with roll number " << rollNo << " not found.\n";
            return node;
        }
        bool courseFound = false;
        for (Course &course : temp->courses) {
            string code1 = courseCode;
            string code2 = course.courseCode;
            code1.erase(0, code1.find_first_not_of(" \t\n"));
            code1.erase(code1.find_last_not_of(" \t\n") + 1);
            code2.erase(0, code2.find_first_not_of(" \t\n"));
            code2.erase(code2.find_last_not_of(" \t\n") + 1);
            
            if (code1 == code2) {
                course.marks = newMarks;
                courseFound = true;
                break;
            }
        }
        if (!courseFound) {
            cout << "Error: Course " << courseCode << " not found for student " << rollNo << ".\n";
        }
    }
    return node;
}

Student* AvlOperations::deleteCourseFromNode(Student* node, int rollNo, const string &courseCode) {
    Student* temp = useCGPA ? getStudentWithCGPA(node, getCGPA(node, rollNo)) 
                            : getStudentWithRollNo(node, rollNo);

    if (temp == nullptr) {
        cout << "Error: Student with roll number " << rollNo << " not found.\n";
        return node;
    }

    size_t originalSize = temp->courses.size();
    vector<Course> updatedCourses;
    
    // Trim the input courseCode
    string searchCode = courseCode;
    searchCode.erase(0, searchCode.find_first_not_of(" \t\n\r\f\v"));
    searchCode.erase(searchCode.find_last_not_of(" \t\n\r\f\v") + 1);
    
    for (const Course &c : temp->courses) {
        // Trim the current course code
        string currentCode = c.courseCode;
        currentCode.erase(0, currentCode.find_first_not_of(" \t\n\r\f\v"));
        currentCode.erase(currentCode.find_last_not_of(" \t\n\r\f\v") + 1);
        
        if (currentCode != searchCode) {
            updatedCourses.push_back(c);
        }
    }
    
    if (updatedCourses.size() == originalSize) {
        cout << "Error: Course " << courseCode << " not found for student " << rollNo << ".\n";
        return node;
    }
    
    temp->courses = updatedCourses;
    temp->numSubjects = updatedCourses.size(); // Update the number of subjects
    return node;
}

// Other private member functions like : rotateRight, rotateLeft, getHeight, getBalance, etc 
Student* AvlOperations::rotateRight(Student* y) {
    Student* x = y->left;
    Student* t2 = x->right;
    x->right = y;
    y->left = t2;
    y->height = 1 + max(AvlOperations::getHeight(y->left), AvlOperations::getHeight(y->right));
    x->height = 1 + max(AvlOperations::getHeight(x->left), AvlOperations::getHeight(x->right));
    return x;
}

Student* AvlOperations::rotateLeft(Student* x) {
    Student* y = x->right;
    Student* t2 = y->left;
    y->left = x;
    x->right = t2;
    x->height = 1 + max(AvlOperations::getHeight(x->left), AvlOperations::getHeight(x->right));
    y->height = 1 + max(AvlOperations::getHeight(y->left), AvlOperations::getHeight(y->right));
    return y;
}

int AvlOperations::getHeight(const Student* node) const {
    if (node == nullptr) return 0;
    return node->height;
}

int AvlOperations::getBalance(const Student* node) const {
    if (node == nullptr) return 0;
    return AvlOperations::getHeight(node->left) - AvlOperations::getHeight(node->right);
}

void AvlOperations::InOrder(const Student* root, vector<Student*>& In) const {
    if (root == nullptr) return;
    InOrder(root->left, In);
    In.push_back(const_cast<Student*>(root));
    InOrder(root->right, In);
}

void AvlOperations::printStudents(const vector<Student*>& students) const {
    for (const Student* student : students) {
        cout<<"Roll No:"<<student->rollNo<<"\n"
            <<"Name:"<<student->name<<"\n"
            <<"CGPA:"<<student->CGPA<<"\n"
            <<"Number of Subjects:"<<student->numSubjects<<"\n"
            <<"BF:"<<AvlOperations::getBalance(student)<<"\n"
            <<"Courses:\n";
        for (const Course &course : student->courses) {
            cout<<"  "<<course.courseCode<<" - Marks:"<<course.marks<<"\n";
        }
        cout<<"----------------------------\n";
    }
}

// functions for # no. > 6 .. . . .   .     . 

void AvlOperations::printStudentsWithKeyGreaterThan(const Student* root, int rollNo, float CGPA) const {
    vector<Student*> res;
    InOrder(root, res);
    for (const Student* student : res) {
        if ((!useCGPA && student->rollNo > rollNo) || (useCGPA && student->CGPA > CGPA)) {
            cout<<"Roll No:"<<student->rollNo<<"\n"
                <<"Name:"<<student->name<<"\n"
                <<"CGPA:"<<student->CGPA<<"\n"
                <<"Number of Subjects:"<<student->numSubjects<<"\n"
                <<"BF:"<<AvlOperations::getBalance(student)<<"\n"
                <<"Courses:\n";
            for (const Course &course : student->courses) {
                cout<<"  "<<course.courseCode<<" - Marks:"<<course.marks<<"\n";
            }
            cout<<"----------------------------\n";
        }
    }
}

void AvlOperations::printStudentsWithKeyLessThan(const Student* root, int rollNo, float CGPA) const {
    vector<Student*> res;
    InOrder(root, res);
    for (const Student* student : res) {
        if ((!useCGPA && student->rollNo < rollNo) || (useCGPA && student->CGPA < CGPA)) {
            cout<<"Roll No:"<<student->rollNo<<"\n"
                <<"Name:"<<student->name<<"\n"
                <<"CGPA:"<<student->CGPA<<"\n"
                <<"Number of Subjects:"<<student->numSubjects<<"\n"
                <<"BF:"<<AvlOperations::getBalance(student)<<"\n"
                <<"Courses:\n";
            for (const Course &course : student->courses) {
                cout<<"  "<<course.courseCode<<" - Marks:"<<course.marks<<"\n";
            }
            cout<<"----------------------------\n";
        }
    }
}

void AvlOperations::printStudentsWithKeyBetween(const Student* root, int rollNo1, int rollNo2, float CGPA1, float CGPA2) const {
    vector<Student*> res;
    InOrder(root, res);
    for (const Student* student : res) {
        if ((!useCGPA && student->rollNo > rollNo1 && student->rollNo < rollNo2) ||
            (useCGPA && student->CGPA > CGPA1 && student->CGPA < CGPA2)) {
            cout<<"Roll No:"<<student->rollNo<<"\n"
                <<"Name:"<<student->name<<"\n"
                <<"CGPA:"<<student->CGPA<<"\n"
                <<"Number of Subjects:"<<student->numSubjects<<"\n"
                <<"BF:"<<AvlOperations::getBalance(student)<<"\n"
                <<"Courses:\n";
            for (const Course &course : student->courses) {
                cout<<"  "<<course.courseCode<<" - Marks:"<<course.marks<<"\n";
            }
            cout<<"----------------------------\n";
        }
    }
}