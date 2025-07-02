# StudentDataHandling

====================================================================
            STUDENT RECORDS MANAGEMENT SYSTEM - AVL TREE
====================================================================

MY CONTRIBUTIONS:

Name: YUVAN RAJ (Roll: 24CSB1A74)
----------------------------------------------------------------
- The modularity layout of project:
  File - main.cpp
       - FileHandler.cpp
       - FileHandler.h
       - AvlOperations.cpp
       - AvlOperations.h
       - Student.h  
- Focused on Implementing Functions when called from FileHandler.cpp

AVL OPERATIONS FUNCTION SPECIFICATIONS
======================================
DATA MEMBERS:
--------------
1. Student* root
2. bool useCGPA

PUBLIC FUNCTIONS: // Can access from Filehandler.cpp where we included "AvlOperations.h"
----------------
1. Constructor: AvlOperations(bool) // Updates whether to use CGPA as key or not
2. bool useCGPAp()
3. void insertStudent(int, const string&, float, int, const vector<Course>&) // Calls private member function to insert Student
4. void deleteStudent(int) // Calls private delete function
5. void updateCGPA(int, float) // Calls private updateNodeCGPA() function
6. void addCourse(int, const string&, int) // Calls addCouresToNode()
7. void updateCourseMarks(int, const string&, int) // Calls updateCoursemarksInNode()
8. void deleteCourse(int, const string&) // Calls deleteNode()
9. void displayTree() const
10. bool printStudentsWithRollNoGreaterThan(int) const // Calls printStudentsWithKeyGreaterThan()
11. bool printStudentsWithRollNoLessThan(int) const // Calls printStudentsWithKeyLessThan()
12. bool printStudentsWithRollNoBetween(int, int) const // Calls printStudentsWithKeyBetween()
13. bool printStudentsWithCGPAGreaterThan(float) const // Calls printStudentsWithKeyGreaterThan()
14. bool printStudentsWithCGPALessThan(float) const // Calls printStudentsWithKeyLessThan()
15. bool printStudentsWithCGPABetween(float, float) const // Calls printStudentsWithKeyBetween()


PRIVATE FUNCTIONS:
-----------------
1. Student* insert(Student*, int, const string&, float, int, const vector<Course>&) // Flexible for both rollno and CGPA as key and inserts in AVL tree
2. float getCGPA(Student*, int) // When CGPA as key, if rollNo is given, returns CGPA
3. Student* getStudentWithCGPA(Student*, float) // When CGPA as key, search for student
4. Student* getStudentWithRollNo(Student*, int) // When rollNo as key, search for student
5. Student* deleteNode(Student*, int, float) // Flexible for both rollno and CGPA as key and deletes node in AVL tree
6. Student* updateNodeCGPA(Student*, int, float) // Flexible for both rollno and CGPA as key and updates CGPA
7. Student* addCourseToNode(Student*, int, const string&, int) // Flexible for both rollno and CGPA as key and adds course to student
8. Student* updateCourseMarksInNode(Student*, int, const string&, int) // Flexible for both rollno and CGPA as key and updates course marks
9. Student* deleteCourseFromNode(Student*, int, const string&) // Flexible for both rollno and CGPA as key and deletes course from Student
10. Student* rotateRight(Student*) // Right rotate 
11. Student* rotateLeft(Student*) // Left rotate
12. int getHeight(const Student*) const 
13. int getBalance(const Student*) const
14. void InOrder(const Student*, vector<Student*>&) const
15. void printStudents(const vector<Student*>&) const
16. void printStudentsWithKeyGreaterThan(const Student*, int, float) const // Flexible for both rollno and CGPA as key and prints students greater than key
17. void printStudentsWithKeyLessThan(const Student*, int, float) const // Flexible for both rollno and CGPA as key and prints students lesser than key
18. void printStudentsWithKeyBetween(const Student*, int, int, float, float) const // Flexible for both rollno and CGPA as key and prints students between the two keys


FILE PROCESSING & USER INTERFACE
================================

Command System:
- Made a system to read files and run commands.
- Created a function to handle different commands.
- Added error checks for more than 15 possible mistakes.
- Wrote the whole filehandler.cpp file and tested some functions in AVLoperations.cpp.

User Interaction:
- Designed how the output looks when shown.
- Made messages to confirm when something is done.
- Built a system to show data as a tree.

Technical Highlights:
- Can handle commands spread over multiple lines.
- Checks if all inputs are valid.
- Makes sure actions are done fully or not at all (to avoid partial errors).


ABOUT MAIN.CPP & STUDENT.H FILES
================================

- Main.cpp --
  - 3 arguments passed to main function: exe filename "main.exe", key type "r or c", input filename "input.txt"
  - Objects of data structures of AvlOperations and Filehandler are created in main file.

- Student.h --
  - Two Structures are made to store Student Info and Course Info.
  - Data members of Student structure:
      int rollNo;
      string name;
      float CGPA;
      int numSubjects;
      vector<Course> courses;
      Student *left;
      Student *right;
      int height;
  - Data members of Course Structure:
      string courseCode;
      int marks;


====================================================================

COMPILATION INSTRUCTIONS:

1. Compile:
   g++ main.cpp AvlOperations.cpp FileHandler.cpp -o main // Creates a main.exe executable file

2. Execute:
   • When rollNo as a key:
     ./main r input.txt
   • When CGPA as a key:
     ./main c input.txt
   • input.txt - Basic operations
   • input_avl.txt - Stress test (100+ ops)