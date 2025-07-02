#ifndef AVLOPERATIONS_H
#define AVLOPERATIONS_H

#include "Student.h"
#include <vector>
#include <iostream>

class AvlOperations {
public:
    AvlOperations(bool useCGPA);
    bool useCGPAp() ;  // Renamed for clarity
    void insertStudent(int rollNo, const std::string &name, float CGPA, int numSubjects, const std::vector<Course> &courses);
    void deleteStudent(int rollNo);
    void updateCGPA(int rollNo, float newCGPA);
    void addCourse(int rollNo, const std::string &courseCode, int marks);
    void updateCourseMarks(int rollNo, const std::string &courseCode, int newMarks);
    void deleteCourse(int rollNo, const std::string &courseCode);
    void displayTree() const;
    bool printStudentsWithRollNoGreaterThan(int rollNo) const;
    bool printStudentsWithRollNoLessThan(int rollNo) const;
    bool printStudentsWithRollNoBetween(int rollNo1, int rollNo2) const;
    bool printStudentsWithCGPAGreaterThan(float CGPA) const;
    bool printStudentsWithCGPALessThan(float CGPA) const;
    bool printStudentsWithCGPABetween(float CGPA1, float CGPA2) const;

private:
    Student* root;
    bool useCGPA;

    Student* insert(Student* node, int rollNo, const std::string &name, float CGPA, int numSubjects, const std::vector<Course> &courses);
    float getCGPA(Student* node, int rollNo);
    Student* getStudentWithCGPA(Student* node, float CGPA);
    Student* getStudentWithRollNo(Student* node, int rollNo);
    Student* deleteNode(Student* node, int rollNo, float CGPA);
    Student* updateNodeCGPA(Student* node, int rollNo, float newCGPA);
    Student* addCourseToNode(Student* node, int rollNo, const std::string &courseCode, int marks);
    Student* updateCourseMarksInNode(Student* node, int rollNo, const std::string &courseCode, int newMarks);
    Student* deleteCourseFromNode(Student* node, int rollNo, const std::string &courseCode);
    Student* rotateRight(Student* y);
    Student* rotateLeft(Student* x);
    int getHeight(const Student* node) const;
    int getBalance(const Student* node) const;
    void InOrder(const Student* root, std::vector<Student*> &In) const;
    void printStudents(const std::vector<Student*> &students) const;
    void printStudentsWithKeyGreaterThan(const Student* root, int rollNo, float CGPA) const;
    void printStudentsWithKeyLessThan(const Student* root, int rollNo, float CGPA) const;
    void printStudentsWithKeyBetween(const Student* root, int rollNo1, int rollNo2, float CGPA1, float CGPA2) const;
};

#endif // AVLOPERATIONS_H