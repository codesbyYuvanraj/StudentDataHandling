#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Course {
    string courseCode;
    int marks;
};

struct Student {
    int rollNo;
    string name;
    float CGPA;
    int numSubjects;
    vector<Course> courses;
    Student *left;
    Student *right;
    int height;
};

#endif // STUDENT_H