#include <bits/stdc++.h>
using namespace std;
#define max 2

struct CreditHour{
    string tname;
    char sectionname;
    int semester;
    string sname;
};

class students
{
public:
    string name;
    char elective;
};
class subject
{
public:
    string name;
    string code;
    subject() {}
    void setname(string name)
    {
        this->name = name;
    }
    void setcode(string code)
    {
        this->code = code;
    }
};

class section
{

public:
    int semester, strength;
    students *obj;
    char name;
    subject all[4];
    section() {}
    section(int semester, int strength, char name) : semester(semester), strength(strength), name(name) {}

    void assignSubjects(vector<string> &sub, vector<string> &code)
    {
        for (int i = 0; i < 4; ++i)
        {
            all[i].setname(sub[i]);
            all[i].setcode(code[i]);
        }
    }

    void display()
    {
        cout << "SECTION: " << semester << name << endl;
        cout << "STUDENTS: " << strength << endl;
        for (int i = 0; i < 4; ++i)
        {
            cout << all[i].name << endl;
        }
    }
};

class teacher
{
    int cntSec = 0,cntCourses=0;
    subject courses[max];
    section no_of_sections[max];
    CreditHour printing[max];
    int cntinfo=0;
    string name;

public:
    teacher(string name):name(name){}
    void assignSubjects(vector<string> &sub, vector<string> &code)
    {
        for (int i = 0; i < sub.size(); ++i)
        {
            courses[i].setname(sub[i]);
            courses[i].setcode(code[i]);
            cntCourses++;
        }
    }

    void passSection(section obj1,section obj2,section obj3,section obj4)
    {
       if(cntSec!=0)
        return;
       no_of_sections[0]=obj1;
       no_of_sections[1]=obj2;
       no_of_sections[2]=obj3;
       no_of_sections[3]=obj4;
       cntSec=4;
    }

    void passSection(section obj1,section obj2,section obj3)
    {
       if(cntSec+3<=max)
        return;
       no_of_sections[cntSec++]=obj1;
       no_of_sections[cntSec++]=obj2;
       no_of_sections[cntSec++]=obj3;
    }

    void passSection(section obj1,section obj2)
    {
       
       if(cntSec+2>max)
        return;
       no_of_sections[cntSec++]=obj1;
       no_of_sections[cntSec++]=obj2;
    }

    void passSection(section obj1)
    {
       if(cntSec+1<=max)
        return;
       no_of_sections[cntSec++]=obj1;
    }

    void matching(){
        bool flag=true;
        for(int i=0;i<cntSec;++i){
            for(int j=0;j<cntCourses;++j){
                for(int k=0;k<4;k++){
                    if(courses[j].name==no_of_sections[i].all[k].name){
                        printing[cntinfo].sectionname=no_of_sections[i].name;
                        printing[cntinfo].semester=no_of_sections[i].semester;
                        printing[cntinfo].sname=courses[j].name;
                        printing[cntinfo++].tname=name;
                    }
                }
            }
        }
    }
    void PrintInfo(){
        cout<<name<<endl;
        for(int i=0;i<2;i++){        
            cout<<printing[i].semester<<printing[i].sectionname<<" "<<printing[i].sname<<endl;
        }
    }
};

class TimeTable{
    //3D solve 
    
};


int main()
{
    // forloop for semester
    // section wise
    vector<string> sub = {"COAL", "DS", "LA", "DISCRETE"};
    vector<string> code = {"EE1002", "CS1210", "MT101", "CS1001"};
    vector<string> subT={"LA"};
    vector<string> CodeT={"MT101"};
    section h(3, 50, 'H');
    section g(3, 50, 'G');
    h.assignSubjects(sub, code);
    g.assignSubjects(sub,code);
    teacher t1("MOHEEZ");
    t1.passSection(h,g);
    t1.assignSubjects(subT,CodeT);
    t1.matching();
    t1.PrintInfo();
    //h.display();

}
