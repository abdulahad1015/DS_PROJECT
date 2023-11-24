#include <bits/stdc++.h>
using namespace std;


struct info{
    string tname;
    string sectionname;
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
    int semester, strength;
    students *obj;
    char name;
    subject all[4];

public:
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
    subject courses[4];
    section no_of_sections[4];

    int cntSec = 0, max = 4;

public:
    void assignSubjects(vector<string> &sub, vector<string> &code)
    {
        for (int i = 0; i < sub.size(); ++i)
        {
            courses[i].setname(sub[i]);
            courses[i].setcode(code[i]);
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
       if(cntSec+3<=4)
        return;
       no_of_sections[cntSec++]=obj1;
       no_of_sections[cntSec++]=obj2;
       no_of_sections[cntSec++]=obj3;
    }

    void passSection(section obj1,section obj2)
    {
       if(cntSec+2<=4)
        return;
       no_of_sections[cntSec++]=obj1;
       no_of_sections[cntSec++]=obj2;
    }

    void passSection(section obj1)
    {
       if(cntSec+1<=4)
        return;
       no_of_sections[cntSec++]=obj1;
    }

    void matching(){
        int counterForSection=0,counterForSubject=0;
        for(int i=counterForSection;i<4;++i){
            for(int j=counterForSubject;j<4;++j){
                //matching
            }
        }
    }
};




int main()
{
    // forloop for semester
    // section wise
    vector<string> sub = {"COAL", "DS", "LA", "DISCRETE"};
    vector<string> code = {"EE1002", "CS1210", "MT101", "CS1005"};
    section h(3, 50, 'H');
    section g(3, 50, 'G');
    h.assignSubjects(sub, code);
    h.display();
    teacher numteachers[4];
    cout<<"hello"<<endl;
}
