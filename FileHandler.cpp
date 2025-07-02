#include "FileHandler.h"
#include "AvlOperations.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void FileHandler::handleInput(AvlOperations &records,const string &filename){
    ifstream inputFile(filename);
    if(!inputFile.is_open()){
        cerr<<"Failed to open input file."<<endl;
        return;
    }
    string line;
    while(getline(inputFile,line)){
        
        if(processLine(line,records,inputFile)){
            cout<<"***** Inorder traversal:\n";
            records.displayTree();
            cout<<"-----------------------------------------------------------------------------------------------------------------------------------------------------\n";
        }
    }
    inputFile.close();
}

bool FileHandler::processLine(const string &line,AvlOperations &records,ifstream &inputFile){
    if(line.empty()){
        cerr<<"Invalid comd: Empty line"<<endl;
        return false;
    }
    stringstream ss(line);
    char has;
    int comd;
    ss>>has>>comd;
    if(has!='#'||ss.fail()){
        cerr<<"Invalid comd: "<<line<<endl;
        return false;
    }
    int rollNo,rollNo2,numSubjects,marks;
    string name,courseCode;
    float CGPA,CGPA2;
    switch(comd){
        case 1:{
            string studentLine;
            if(!getline(inputFile,studentLine)){
                cerr<<"Missing student data for comd #1"<<endl;
                return false;
            }
            stringstream ss(studentLine);
            string token;
            getline(ss,token,',');
            rollNo=stoi(token);
            getline(ss,name,',');
            getline(ss,token,',');
            CGPA=stof(token);
            getline(ss,token,',');
            numSubjects=stoi(token);
            vector<Course> courses(numSubjects);
            for(int i=0;i<numSubjects;++i){
                string courseLine;
                if(!getline(inputFile,courseLine)){
                    cerr<<"Missing course data for comd #1"<<endl;
                    return false;
                }
                stringstream ssCourse(courseLine);
                getline(ssCourse,courseCode,',');
                getline(ssCourse,token,',');
                marks=stoi(token);
                courses[i]={courseCode,marks};
            }
            records.insertStudent(rollNo,name,CGPA,numSubjects,courses);
            cout<<"***** Inserted Student having RollNo: "<<rollNo<<endl;
            break;
        }
        case 2:{
            string updateLine;
            if(!getline(inputFile,updateLine)){
                cerr<<"Missing data for comd #2"<<endl;
                return false;
            }
            stringstream ss(updateLine);
            string token;
            getline(ss,token,',');
            rollNo=stoi(token);
            getline(ss,token,',');
            CGPA=stof(token);
            records.updateCGPA(rollNo,CGPA);
            cout<<"***** Updated CGPA of "<<rollNo<<" to "<<CGPA<<endl;
            break;
        }
        case 3:{
            string addCourseLine;
            if(!getline(inputFile,addCourseLine)){
                cerr<<"Missing data for comd #3"<<endl;
                return false;
            }
            stringstream ss(addCourseLine);
            string token;
            getline(ss,token,',');
            rollNo=stoi(token);
            getline(ss,courseCode,',');
            getline(ss,token,',');
            marks=stoi(token);
            records.addCourse(rollNo,courseCode,marks);
            cout<<"***** Added Course to Student "<<rollNo<<endl;
            break;
        }
        case 4:{
            string updateMarksLine;
            if(!getline(inputFile,updateMarksLine)){
                cerr<<"Missing data for comd #4"<<endl;
                return false;
            }
            stringstream ss(updateMarksLine);
            string token;
            getline(ss,token,',');
            rollNo=stoi(token);
            getline(ss,courseCode,',');
            getline(ss,token,',');
            marks=stoi(token);
            records.updateCourseMarks(rollNo,courseCode,marks);
            cout<<"***** Updated Course marks for "<<rollNo<<endl;
            break;
        }
        case 5:{
            string deleteCourseLine;
            if(!getline(inputFile,deleteCourseLine)){
                cerr<<"Missing data for comd #5"<<endl;
                return false;
            }
            stringstream ss(deleteCourseLine);
            string token;
            getline(ss,token,',');
            rollNo=stoi(token);
            getline(ss,courseCode,',');
            records.deleteCourse(rollNo,courseCode);
            cout<<"***** Deleted Course of "<<rollNo<<endl;
            break;
        }
        case 6:{
            string deleteStudentLine;
            if(!getline(inputFile,deleteStudentLine)){
                cerr<<"Missing data for comd #6"<<endl;
                return false;
            }
            stringstream ss(deleteStudentLine);
            string token;
            getline(ss,token,',');
            rollNo=stoi(token);
            records.deleteStudent(rollNo);
            cout<<"***** Deleted Student "<<rollNo<<endl;
            break;
        }
        case 7: {
            string printLine;
            if (!getline(inputFile, printLine)) {
                cerr<<"Missing data for command #7"<<endl;
                return false;
            }
            istringstream ss(printLine);
            string token;
            getline(ss, token, ',');
            rollNo=stoi(token);
            if(!records.useCGPAp()) cout<<"***** Students with RollNo Greater than "<<rollNo<<" :"<<endl;
            return records.printStudentsWithRollNoGreaterThan(rollNo);
        }
        case 8: {
            string printLine;
            if (!getline(inputFile, printLine)) {
                cerr<<"Missing data for command #8"<<endl;
                return false;
            }
            istringstream ss(printLine);
            string token;
            getline(ss, token, ',');
            rollNo=stoi(token);
            if(!records.useCGPAp()) cout<<"****** Students with RollNo Lesser than "<<rollNo<<" :"<<endl;
            return records.printStudentsWithRollNoLessThan(rollNo);
        }
        case 9: {
            string printLine;
            if (!getline(inputFile, printLine)) {
                cerr<<"Missing data for command #9"<<endl;
                return false;
            }
            istringstream ss(printLine);
            string token;
            getline(ss, token, ',');
            rollNo=stoi(token);
            getline(ss, token, ',');
            rollNo2=stoi(token);
            if(!records.useCGPAp()) cout<<"****** Students with RollNo Between "<<rollNo<<" and "<<rollNo2<<" :"<<endl;
            return records.printStudentsWithRollNoBetween(rollNo, rollNo2);
        }
        case 10: {
            string printLine;
            if (!getline(inputFile, printLine)) {
                cerr<<"Missing data for command #10"<<endl;
                return false;
            }
            istringstream ss(printLine);
            string token;
            getline(ss, token, ',');
            CGPA=stof(token);
            if(records.useCGPAp()) cout<<"****** Students with CGPA Greater than "<<CGPA<<" :"<<endl;
            return records.printStudentsWithCGPAGreaterThan(CGPA);
        }
        case 11: {
            string printLine;
            if (!getline(inputFile, printLine)) {
                cerr<<"Missing data for command #11"<<endl;
                return false;
            }
            istringstream ss(printLine);
            string token;
            getline(ss, token, ',');
            CGPA=stof(token);
            if(records.useCGPAp()) cout<<"***** Students with CGPA Lesser than "<<CGPA<<" :"<<endl;
            return records.printStudentsWithCGPALessThan(CGPA);
        }
        case 12: {
            string printLine;
            if (!getline(inputFile, printLine)) {
                cerr<<"Missing data for command #12"<<endl;
                return false;
            }
            istringstream ss(printLine);
            string token;
            getline(ss, token, ',');
            CGPA=stof(token);
            getline(ss, token, ',');
            CGPA2=stof(token);
            if(records.useCGPAp()) cout<<"***** Students with CGPA Between "<<CGPA<<" and "<<CGPA2<<" :"<<endl;
            return records.printStudentsWithCGPABetween(CGPA, CGPA2);
        }
    
        default:
            cerr<<"Invalid comd: #"<<comd<<endl;
            return false;
    }
    return true;
}