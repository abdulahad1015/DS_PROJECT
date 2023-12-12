#include <iostream>
#include<vector>
#include<queue>
#include<ctime>
#include<cmath>
using namespace std;
#define TotalCourses 4
#define maxCredit 12
#define monday 0
#define tuesday 1
#define wednesday 3
#define thursday 4
#define friday 5
#define no_labs 12


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
            long long hashval=0;
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


void swapper(Info *a,Info *b)
{
	swap(a->tname,b->tname);
	swap(a->sectionname,b->sectionname);
	swap(a->sname,b->sname);
	swap(a->hours,b->hours);
}

void shufflequeue(queue<Info> &myq)
{
	srand(time(0));
    int size=myq.size();
	Info arr[size];
	for(int i=0;i<size;i++)
	{
		arr[i]=myq.front();
		myq.pop();
	}
	int random1;
    int random2;
	for(int i=0;i<size;i++)
	{
		random1=rand()%size;
        random2=rand()%size;
		swapper(&arr[random1],&arr[random2]);
	}
    for(int i=0;i<size;i++)
	{
		random1=rand()%size;
        random2=rand()%size;
		swapper(&arr[random1],&arr[random2]);
	}
	for(int i=0;i<size;i++)
	{
		myq.push(arr[i]);
	}
	
	
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
    section(int strength,string sectionname) : sectionname(sectionname),strength(strength) {}

    void assignSubjects(vector<string> &sub,vector<int>&type)
    {
        for (int i = 0; i < TotalCourses; ++i)
        {
            courses[i].setname(sub[i]);
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

};

int teacher::teachers=0;

class TimeTable{
    const int no_days=5;
    HashMap days[5];
    bool visited[5][8][33+no_labs];
    
    public:
    Info table[5][8][33];

    void fillTable(queue<Info>&allcourses){
        
        for(int i=0;i<no_days;++i){
            //numbers of days
            for(int j=0;j<8;++j){
                //for each time slot
                for(int k=0;k<33;++k){
                   Info current=allcourses.front();
                   if(current.hours==0){
                    table[i][j][k]=current;
                    allcourses.pop();
                    continue;
                   }
                   if(current.hours==3||current.hours==2){
                   
                   bool allowed1= checkotherrooms(i,j,k,current.sectionname,current.tname);
                   bool allowed2=frequencyOFsectionORteacher(current.sectionname,current.tname,i);
                   bool allowed3=frequencyOFsectionANDteacher(current.tname+current.sectionname,i);
                   if(allowed1&&allowed2&&allowed3){
                    table[i][j][k]=current;
                    visited[i][j][k]=true;
                    days[i].insert(current.sname);
                    days[i].insert(current.tname);
                    days[i].insert(current.tname+current.sectionname);
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
            if(table[day][slot][i].sectionname==section||table[day][slot][i].tname==teacher){
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
        return true;
    }

     bool frequencyOFsectionANDteacher(string combined, int currentday){
        int fComb=days[currentday].search(combined);
        if(fComb==2){
            return false;
        }
        
        return true;
    }

    void display(){
        for(int i=0;i<1;++i){
            cout<<"\t\t\t\tMONDAY\n\n\n";
            for(int j=0;j<8;++j){
                cout<<"SLOT "<<j+8<<":\t";
                for(int k=0;k<33+no_labs;++k){
                    cout<<table[i][j][k].sectionname<<table[i][j][k].sname<<table[i][j][k].tname<<"\t";
                }
                cout<<"\n\n\n";
            }

        }
    }
};


int main()
{   
    
    teacher t1[5];
    t1[0].setname("MOHEEZ");
    vector<string>sub={"LA"};
    vector<string>code={"MT1002"};
    vector<int>hours={3};
    t1[0].assignSubjects(sub,code,hours);

    t1[1].setname("Atiya Jhokio");
    vector<string>sub1={"COAL"};
    vector<string>code1={"XXXXX"};
    vector<int>hours1={3};
    t1[1].assignSubjects(sub1,code1,hours1);

    t1[2].setname("MAFAZA");
    vector<string>sub2={"DISCRETE"};
    vector<string>code2={"XXXXX"};
    vector<int>hours2={3};
    t1[2].assignSubjects(sub2,code2,hours2);

    vector<string>Subs={"ECC","DS","DISCRETE","COAL"};
    vector<int>type1={1,1,1,1};
    vector<string>Subs2={"DS","LA","DISCRETE","COAL"};
    vector<int>type2={1,1,1,1};
   
    section a1(48,"1A");
    a1.assignSubjects(Subs,type1);
	section b1(47,"1B");
    b1.assignSubjects(Subs,type1);
	section c1(45,"1C");
    c1.assignSubjects(Subs,type1);
	section d1(49,"1D");
    d1.assignSubjects(Subs2,type2);
	section e1(53,"1E");
    e1.assignSubjects(Subs2,type2);
	section f1(51,"1F");
    f1.assignSubjects(Subs2,type2);
	t1[0].passSection(d1);
    t1[0].passSection(e1);
    t1[0].matching();
    cout<<t1[0].cntinfo<<endl;
    t1[1].passSection(a1);
    t1[1].passSection(b1);
    t1[1].passSection(f1);
    t1[1].matching();
    cout<<t1[1].cntinfo<<endl;
    t1[2].passSection(d1);
    t1[2].passSection(f1);
    t1[2].passSection(a1);
    t1[2].matching();
    cout<<t1[2].cntinfo<<endl;
	queue<Info> teacherCredits;
     for(int i=0;i<3;++i){
        for(int j=0;j<t1[i].cntinfo;++j){
             teacherCredits.push(t1[i].credit[j]);
     }
     }
    Info freeslot;
    freeslot.hours=0;
    freeslot.sectionname="free";
    freeslot.sname="free";
    freeslot.tname="free";
    for(int i=0;i<1296;++i)teacherCredits.push(freeslot);
   // shufflequeue(teacherCredits);
    TimeTable mytable;
    mytable.fillTable(teacherCredits);
    mytable.display();

  

    
    //h.display();

}
