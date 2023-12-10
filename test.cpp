#include <bits/stdc++.h>
using namespace std;
#define TotalCourses 4
#define maxCredit 12
#define monday 0
#define tuesday 1
#define wednesday 3
#define thursday 4
#define friday 5


class HashNode{
    private:
        string s;
        int frequency;
    public:
        HashNode(string s){
        this->s=s;
        frequency=1;
        }
        void setfrequency(){
            frequency++;
        }
        
        int getfrequency(){
            return frequency;
        }
        
};

class HashMap{
    private:
        HashNode** htable;
        int size=1000000;
    public:
        HashMap(){
            htable = new HashNode*[size];
            for (int i = 0; i < size; i++)
                htable[i] = NULL;
        }
        ~HashMap(){
            delete []htable;
        }
        int hash(string s){
            int hashval=0;
            double sub;
            for(int i=1;s.length();i++){
                sub=pow(((s[0]-'0')%10),i);
				hashval+=sub;
                s.erase(s.begin());
            }
            return hashval%size;
        }
        void insert(string s){
            int hashval=hash(s);
            HashNode* Newnode = new HashNode(s);
            if(htable[hashval]==NULL){
                htable[hashval]=Newnode;
                //cout<<htable[hashval]->value<<endl;
            }
            else{
                htable[hashval]->setfrequency();
            }
        }
        int search(string s){
            int hashval=hash(s);
            if(htable[hashval]==NULL){
                return 0;
            }
            return htable[hashval]->getfrequency();
        }
        
};

struct Info{
    string tname;
    string sectionname;
    string sname;
    int hours;
};

void shufflequeue(queue<Info>&myq){
    
}
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
    int hours,type;//1-Core,2-Elective,3-Lab,4-Free Slot
    subject() {}
    void setname(string name)
    {
        this->name = name;
    }
    void setcode(string code)
    {
        this->code = code;
    }
    void sethours(int hours){
        this->hours=hours;
    }

    void settype(int type){
        this->type=type;
    }
};

class section
{

public:
    int strength;
    students *obj;
    string sectionname;
    subject courses[TotalCourses];
    section() {}
    section(string sectionname,int strength) : sectionname(sectionname),strength(strength) {}

    void assignSubjects(vector<string> &sub, vector<string> &code, vector<int> &hours,vector<int>&type)
    {
        for (int i = 0; i < TotalCourses; ++i)
        {
            courses[i].setname(sub[i]);
            courses[i].setcode(code[i]);
            courses[i].sethours(hours[i]);
            courses[i].settype(type[i]);
        }
    }

    void display()
    {
        cout << "SECTION: " << sectionname << endl;
        cout << "STUDENTS: " << strength << endl;
        for (int i = 0; i < TotalCourses; ++i)
        {
            cout << courses[i].name << endl;
        }
    }
};

class teacher
{
    int cntCourses=0;
    subject courses[TotalCourses];
    section no_of_sections[TotalCourses];
   
    string name;
    
public:
    int cntinfo=0;
    Info credit[maxCredit];
    int cntSec = 0;
    static int teachers;
    teacher(){
        teachers++;
    }
    teacher(string name):name(name){
        teachers++;
    }
    void setname(string name){
        this->name=name;
    }
    void assignSubjects(vector<string> &sub, vector<string> &code,vector<int> &hours)
    {
        for (int i = 0; i < sub.size(); ++i)
        {
            courses[i].setname(sub[i]);
            courses[i].setcode(code[i]);
            courses[i].sethours(hours[i]);
            cntCourses++;
        }
    }

    void passSection(section obj1)
    {
       if(cntSec>=TotalCourses)
        return;
       no_of_sections[cntSec++]=obj1;
    }

    void matching(){
 
        for(int i=0;i<cntSec;++i){
            //for each section
            for(int j=0;j<TotalCourses;++j){
                //for each course of the teacher
                for(int k=0;k<TotalCourses;k++){
                    //check each course of that section to find match
                    if(courses[j].name==no_of_sections[i].courses[k].name){
                        if(courses[j].type==1||courses[j].type==3){
                        for(int l=0;l<courses[j].hours;++l){
                        credit[cntinfo].sectionname=no_of_sections[i].sectionname;
                        credit[cntinfo].sname=courses[j].name;
                        credit[cntinfo].hours=courses[j].hours;
                        credit[cntinfo++].tname=name;
                        }
                        }
                        
                    }
                }
            }
        }
    }

};

int teacher::teachers=0;

class TimeTable{
    HashMap days[5];
    Info table[5][8][33];
    public:

    void fillTable(queue<Info>&allcourses){
        for(int i=0;i<5;++i){
            //numbers of days
            for(int j=0;j<8;++j){
                //for each time slot
                for(int k=0;k<33;++k){
                   if(table[i][j][k]!=empty){
                    //will make logic for table
                    continue;
                   }
                   Info current=allcourses.front();
                    //for each room
                   if(current.hours==1){
                    days[i].insert(current.sectionname);
                    days[i].insert(current.sectionname);
                    days[i].insert(current.sectionname);//three classes done for this section
                    table[i][j][k]=current;
                    table[i][j+1][k]=current;
                    table[i][j+2][k]=current;
                    allcourses.pop();
                    continue;
                   }
                   if(current.hours==3||current.hours==2){
                   bool allowed1= checkotherrooms(i,j,k,current.sectionname,current.tname);
                   bool allowed2=frequencyOFsectionORteacher(current.sectionname,current.tname,i);
                   bool allowed3=frequencyOFsectionANDteacher(current.tname+current.sectionname,i);
                   if(allowed1&&allowed2&&allowed3){
                    table[i][j][k]=current;
                    allcourses.pop();
                   }
                   else{
                    shufflequeue(allcourses);
                    k--;
                    continue;
                   }
                   }
                }
            }
        }
    }    

    bool checkotherrooms(int day,int slot,int room,string section, string teacher){
        for(int i=0;i<room;++i){
            if(table[day][slot][room].sectionname==section||table[day][slot][room].tname==teacher){
                return false;
            }
        }
        return true;
    }
    
    bool frequencyOFsectionORteacher(string section,string teacher,int currentday){
        int fSec=days[currentday].search(section);
        int fteacher=days[currentday].search(teacher);
        if(fSec>6||fteacher>6){
            return false;
        }
        
        days[currentday].insert(section);
        days[currentday].insert(teacher);
    }

     bool frequencyOFsectionANDteacher(string combined, int currentday){
        int fComb=days[currentday].search(combined);
        if(fComb==2){
            return false;
        }
        days[currentday].insert(combined);
    }
};


int main()
{   
    
    teacher t1[5];
    t1[0].setname("Moheez Ur Rehman");
    // forloop for semester
    // section wise
    vector<string> sub = {"COAL", "DS", "LA", "DISCRETE"};
    vector<int> type= {1,1,1,1};
    vector<string> code = {"EE1002", "CS1210", "MT101", "CS1001"};
    vector<int> hours = {3,2,3,2};
    //teacher subjects
    vector<string> subT={"LA"};
    vector<string> CodeT={"MT101"};
    vector<int> hoursT = {3};
    //assigning subjects to sections
    section h("3H",50);
    section g("3G",50);
    h.assignSubjects(sub, code,hours,type);
    g.assignSubjects(sub,code,hours,type);
    // assigning subjects and sections to teacher
    t1[0].passSection(h);
    t1[0].passSection(g);
    t1[0].assignSubjects(subT,CodeT,hoursT);
    t1[0].matching();
    //t1[0].PrintInfo();
    // Pushing every credit of every teacher in a queue
    queue<Info> teacherCredits;
    for(int i=0;i<t1->cntinfo;++i){
        teacherCredits.push(t1->credit[i]);
    }
    //checking queue 
    cout<<"\nqueue:"<<endl;
    
    //h.display();

}
