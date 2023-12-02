#include <iostream>
#include <vector>
#include <math.h>
#include <queue>
using namespace std;
#define max 2
#define monday 0
#define tuesday 1
#define wednesday 3
#define thursday 4
#define friday 5

class HashNode{
    public:
    int key;
	int value;
	HashNode* next;
        HashNode(int key, int value){
        this->key = key;
	    this->value = value;
	    this->next = NULL;
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
        int hash(int num){
            int hashval=0;
            double sub;
            for(int i=1;num>0;i++){
                sub=pow((num%10),i);
				hashval+=sub;
                num=num/10;
            }
            return hashval%size;
        }
        void insert(int num){
            int hashval=hash(num);
            HashNode* Newnode = new HashNode(hashval,num);
            if(htable[hashval]==NULL){
                htable[hashval]=Newnode;
                //cout<<htable[hashval]->value<<endl;
            }
            else{
                HashNode *temp=htable[hashval];
                while(temp->next!=NULL){
                    temp=temp->next;
                }
                temp->next=Newnode;
                //cout<<Newnode->value<<endl;
            }
        }
        int search(int val){
            int hashval=hash(val);
            HashNode *temp=htable[hashval];
            while(temp!=NULL&&temp->value!=val){
                temp=temp->next;
            }
            if(temp==NULL){
                return 0;
            }
            return 1;
        }
        void display(){
            for(int i=0;i<size;i++){
                HashNode *temp=htable[i];
                if(temp==NULL){
                    cout<<"NULL";
                }
                while(temp!=NULL){
                    cout<<temp->value<<"->";
                    temp=temp->next;
                }
                cout<<endl;
            }
        }
        void deleteVal(int val){
            int hashval=hash(val);
            if(htable[hashval]==NULL){
                return;
            }
            if(htable[hashval]->value==val){
               HashNode* temp=htable[hashval];
               htable[hashval]=htable[hashval]->next;
               temp->next=NULL;
               delete temp;
            }
            else{
                HashNode* temp=htable[hashval];
                while(temp!=NULL&&temp->next!=NULL&&temp->next->value!=val){
                    temp=temp->next;
                }
                HashNode* temp2=temp->next;
                if(temp2!=NULL){
                    temp->next=temp2->next;
                    temp2->next=NULL;
                }
                delete temp2;
                return;
            }
        } 
        
};
struct CreditHour{
    string tname;
    char sectionname;
    int semester;
    string sname;
    int hours;
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
    int hours;
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
};

class section
{

public:
    int semester, strength;
    students *obj;
    char name;
    subject courses[4];
    section() {}
    section(int semester, int strength, char name) : semester(semester), strength(strength), name(name) {}

    void assignSubjects(vector<string> &sub, vector<string> &code, vector<int> &hours)
    {
        for (int i = 0; i < 4; ++i)
        {
            courses[i].setname(sub[i]);
            courses[i].setcode(code[i]);
            courses[i].sethours(hours[i]);
        }
    }

    void display()
    {
        cout << "SECTION: " << semester << name << endl;
        cout << "STUDENTS: " << strength << endl;
        for (int i = 0; i < 4; ++i)
        {
            cout << courses[i].name << endl;
        }
    }
};

class teacher
{
    int cntCourses=0;
    subject courses[max];
    section no_of_sections[max];
   
    int cntinfo=0;
    string name;
    
public:
    CreditHour credit[max];
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
                    if(courses[j].name==no_of_sections[i].courses[k].name){
                        credit[cntinfo].sectionname=no_of_sections[i].name;
                        credit[cntinfo].semester=no_of_sections[i].semester;
                        credit[cntinfo].sname=courses[j].name;
                        credit[cntinfo].hours=courses[j].hours;
                        credit[cntinfo++].tname=name;
                    }
                }
            }
        }
    }
    void PrintInfo(){
        cout<<name<<endl;
        for(int i=0;i<2;i++){        
            cout<<credit[i].semester<<credit[i].sectionname<<" "<<credit[i].sname<<" Credit hours: "<<credit[i].hours<<endl;
        }
    }
};
int teacher::teachers=0;
class TimeTable{
    HashMap days[5];
    CreditHour table[5][8][33];    
    
};


int main()
{   
    
    teacher t1[5];
    t1[0].setname("Moheez Ur Rehman");
    // forloop for semester
    // section wise
    vector<string> sub = {"COAL", "DS", "LA", "DISCRETE"};
    vector<string> code = {"EE1002", "CS1210", "MT101", "CS1001"};
    vector<int> hours = {3,2,3,2};
    //teacher subjects
    vector<string> subT={"LA"};
    vector<string> CodeT={"MT101"};
    vector<int> hoursT = {3};
    //assigning subjects to sections
    section h(3, 50, 'H');
    section g(3, 50, 'G');
    h.assignSubjects(sub, code,hours);
    g.assignSubjects(sub,code,hours);
    // assigning subjects and sections to teacher
    t1[0].passSection(h,g);
    t1[0].assignSubjects(subT,CodeT,hoursT);
    t1[0].matching();
    //t1[0].PrintInfo();
    // Pushing every credit of every teacher in a queue
    queue<CreditHour> teacherCredits;
    for(int i=0;i<t1->teachers;i++){
        for(int j=0;j<t1[i].cntSec;j++){
            CreditHour temp=t1[i].credit[j];
            for(int k=0;k<temp.hours;k++){
                teacherCredits.push(temp);
            }
        }
    }
    //checking queue 
    cout<<"\nqueue:"<<endl;
    while(!teacherCredits.empty()){
        CreditHour temp=teacherCredits.front();
        cout<<temp.semester<<temp.sectionname<<" "<<temp.sname<<" Credit hours: "<<temp.hours<<endl;
        teacherCredits.pop();
    }
    
    //h.display();

}
