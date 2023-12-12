#include <iostream>
#include<vector>
#include<queue>
#include<ctime>
#include<cmath>
#include <fstream>
#include <sstream>
using namespace std;
#define TotalSections 35
#define TotalTeachers 4
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
        HashMap();
        int hash(string );
        void insert(string);
        int search(string);
        ~HashMap();
        
};

struct Info{
    string tname;
    string sectionname;
    string sname;
    int hours=0;
};


void swapper(Info *,Info *);

void shufflequeue(queue<Info> &myq);

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

    int hours,type;//1-Core,2-Elective,3-Lab,4-Free Slot
    subject() {}
    void setname(string);
    void sethours(int);
    void settype(int);
};

class section
{

public:
    int maxcourses=0;
    int strength;
    string sectionname;
    subject courses[TotalCourses];
    section() {}
    section(int strength,string sectionname) : sectionname(sectionname),strength(strength) {}
    void display()
    {
        cout << "SECTION: " << sectionname << endl;
        cout << "STUDENTS: " << strength << endl;
        for (int i = 0; i < maxcourses; ++i)
        {
            cout << courses[i].name << endl;
        }
    }
};

class teacher {

public:
    int cntCourses = 0;
    subject courses[TotalCourses];
    section no_of_sections[TotalCourses];

    string name;
    int cntinfo = 0;
    Info credit[maxCredit];
    int cntSec = 0;
    static int teachers;

    // Constructors
    teacher();
    teacher(string);

    // Member functions
    void setname(string);
    void passSection(section);
    void matching();
};

int teacher::teachers=0;

class TimeTable {
    const int no_days = 5, no_slots=8, no_rooms=33;
    HashMap days[5];
    Info table[5][33][8];

public:
    

    void fillTable(queue<Info>&);

    bool checkOtherRooms(int,int,int,string,string);

    bool frequencyOFsectionORteacher(string, string, int );

    bool frequencyOFsectionANDteacher(string , int);

    void display();
    
    void Monday();

    void Tuesday();

    void Wednesday();

    void Thursday();

    void Friday();
};

void breakSections(const string& line,section *s1)
{
    //cout << "Original Line: " << line << endl;

    stringstream ss(line);
    vector<string> all;
    string token;

    while (getline(ss, token, ','))
    {
        all.push_back(token);
    }
    s1->sectionname=all[0];
    s1->strength=stoi(all[1]);
    int counter=stoi(all[2]);
    s1->maxcourses=counter;
    for(int j=0;j<counter;j++)
    s1->courses[j].name=all[j+3];

}

void readSections(section s1[])
{
    int i=0;
    string line;
    ifstream fin("sections.csv");

    if (!fin.is_open())
    {
        cerr << "Error opening the file." << endl;
        return;
    }

    while (getline(fin, line))
    {
        breakSections(line,&s1[i]);
        i++;
    }

    fin.close();
}
void breakTeachers(const string& line,teacher *t1,section s1[])
{
    //cout << "Original Line: " << line << endl;

    stringstream ss(line);
    vector<string> all;
    string token;

    while (getline(ss, token, ','))
    {
        all.push_back(token);
    }
    t1->setname(all[0]);
    int counter=stoi(all[1]);
    t1->cntCourses=counter;
    for(int j=0;j<counter;j++){
        t1->courses[j].name=all[j+2];
        t1->courses[j].sethours(stoi(all[j+2+4]));
    }
    int sections=stoi(all[2+2*counter]);
    //t1->cntSec=sections;
    for(int j=0;j<sections;j++){
        for(int k=0;k<TotalSections;k++){
            if(s1[k].sectionname==all[3+(2*counter)+j]){
                t1->passSection(s1[k]);
                break;
            }
        }
    }
    t1->matching();
    

}
void readTeachers(teacher t1[],section s1[])
{
    int i=0;
    string line;
    ifstream fin("teachers.csv");

    if (!fin.is_open())
    {
        cerr << "Error opening the file." << endl;
        return;
    }

    while (getline(fin, line))
    {
        breakTeachers(line,&t1[i],s1);
        i++;
    }

    fin.close();
}


int main()
{   
    //----------------------------------------
    section s1[TotalSections];
    readSections(s1);
    //for(int i=0;i<10;i++)
    //s1[i].display();
    //-----------------------------------------


    teacher t1[TotalTeachers];
    readTeachers(t1,s1);
    
    // for(int i=0;i<TotalTeachers;i++){
    //     cout<<t1[i].name<<" ----------------------"<<endl;
    //     for(int j=0;j<t1[i].cntSec;j++){
    //         t1[i].no_of_sections[j].display();
    //     }
    // }
    // for(int i=0;i<TotalTeachers;i++){
    //     cout<<t1[i].name<<"---------------------------"<<endl;
    //     for(int j=0;j<t1[i].cntCourses;j++){
    //         cout<<t1[i].courses[j].name<<endl;
    //     }
    // }
    

    //-----------------------------------------
    // t1[0].setname("MOHEEZ");
    // vector<string>sub={"LA"};
    // vector<int>hours={3};
    // t1[0].assignSubjects(sub,hours);

    // t1[1].setname("Atiya Jhokio");
    // vector<string>sub1={"COAL"};
    // vector<int>hours1={3};
    // t1[1].assignSubjects(sub1,hours1);

    // t1[2].setname("MAFAZA");
    // vector<string>sub2={"DISCRETE"};
    // vector<int>hours2={3};
    // t1[2].assignSubjects(sub2,hours2);

    // vector<string>Subs={"ECC","DS","DISCRETE","COAL"};
    // vector<int>type1={1,1,1,1};
    // vector<string>Subs2={"DS","LA","DISCRETE","COAL"};
    // vector<int>type2={1,1,1,1};
   
    // section a1(48,"1A");
    // a1.assignSubjects(Subs,type1);
	// section b1(47,"1B");
    // b1.assignSubjects(Subs,type1);
	// section c1(45,"1C");
    // c1.assignSubjects(Subs,type1);
	// section d1(49,"1D");
    // d1.assignSubjects(Subs2,type2);
	// section e1(53,"1E");
    // e1.assignSubjects(Subs2,type2);
	// section f1(51,"1F");
    // f1.assignSubjects(Subs2,type2);
	// t1[0].passSection(d1);
    // t1[0].passSection(e1);
    // t1[0].matching();
    // cout<<t1[0].cntinfo<<endl;
    // t1[1].passSection(a1);
    // t1[1].passSection(b1);
    // t1[1].passSection(f1);
    // t1[1].matching();
    // cout<<t1[1].cntinfo<<endl;
    // t1[2].passSection(d1);
    // t1[2].passSection(f1);
    // t1[2].passSection(a1);
    // t1[2].matching();
    // cout<<t1[2].cntinfo<<endl;
	queue<Info> teacherCredits;
    
     for(int i=0;i<TotalTeachers;++i){
        cout<<t1[i].cntinfo<<endl;
        for(int j=0;j<t1[i].cntinfo;++j){
             teacherCredits.push(t1[i].credit[j]);
     }
     }
    Info freeslot;
    freeslot.hours=0;
    freeslot.sectionname="-";
    freeslot.sname="-";
    freeslot.tname="-";
    
    // for(int i=0;i<teacherCredits.size();i++){
    //     Info a=teacherCredits.front();
    //     cout<<a.sectionname<<" "<<a.sname<<" "<<a.hours<<" "<<a.tname<<endl;
    //     teacherCredits.pop();
    //     teacherCredits.push(a);
    // }
    for(int i=0;i<1287;++i)teacherCredits.push(freeslot);
    cout<<"HElooooooooo"<<teacherCredits.size()<<endl;
   // shufflequeue(teacherCredits);
    TimeTable mytable;
    mytable.fillTable(teacherCredits);
    mytable.display();
    mytable.Monday();
    mytable.Tuesday();
    mytable.Wednesday();
    mytable.Thursday();
    mytable.Friday();



    mytable.display();
  

    
    //h.display();

}



////////////////////HASHMAP CLASS////////////////
HashMap::HashMap(){
            htable = new HashNode*[size];
            for (int i = 0; i < size; i++)
                htable[i] = NULL;
        }
int HashMap::hash(string s){

    long long hashval=0;
    double sub;
    for(int i=1;s.length();i++){
        sub=pow(((s[0]-'0')%10),i);
        hashval+=sub;
        s.erase(s.begin());
    }
    return hashval%size;
}
void HashMap:: insert(string s){
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
int HashMap:: search(string s){
            int hashval=hash(s);
            if(htable[hashval]==NULL){
                return 0;
            }
            return htable[hashval]->getfrequency();
        }

HashMap:: ~HashMap(){
            delete []htable;
        }

//UTILITY FUNCTIONS

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

//////////////////////SUBJECT CLASS/////////////////////////
void subject::setname(string name)
    {
        this->name = name;
    }

void subject::sethours(int hours){
        this->hours=hours;
    }

void subject:: settype(int type){
        this->type=type;
    }

/////////////////TEACHER CLASS////////////////////
teacher::teacher() {
    teachers++;
}

teacher::teacher(string name) : name(name) {
    teachers++;
}

void teacher::setname(string name) {
    this->name = name;
}

void teacher::passSection(section obj1) {
    if (cntSec >= TotalCourses)
        return;
    no_of_sections[cntSec++] = obj1;
}

void teacher::matching() {
    for (int i = 0; i < cntSec; ++i) {
        bool flag = false;
        for (int j = 0; j < this->cntCourses && !flag; ++j) {
            for (int k = 0; (k < no_of_sections[i].maxcourses) && !flag; ++k) {
                if (courses[j].name == no_of_sections[i].courses[k].name) {
                    flag = true;
                    for (int l = 0; l < courses[j].hours; ++l) {
                        credit[cntinfo].sectionname = no_of_sections[i].sectionname;
                        credit[cntinfo].sname = courses[j].name;
                        credit[cntinfo].hours = courses[j].hours;
                        credit[cntinfo++].tname = name;
                    }
                }
            }
        }
    }
}

///////////////////////HASHMAP CLASS///////////////

void TimeTable::fillTable(queue<Info>& allcourses) {
    shufflequeue(allcourses);
    for(int i=0;i<5;++i){
            //numbers of days
            for(int j=0;j<no_rooms;++j){
                //for each time slot
                for(int k=0;k<no_slots;++k){
                //    if(i==4&&j==32&&k==7&&!allcourses.empty()){
                //         i=0;
                //         break;
                //     } 
                   Info current=allcourses.front();
                    if(table[i][j][k].hours>0){
                        continue;
                    }
                   if(current.hours==0){
                    table[i][j][k]=current;
                    allcourses.pop();
                    continue;
                   }
                   if(current.hours==3||current.hours==2){
                   
                   bool allowed1= checkOtherRooms(i,j,k,current.sectionname,current.tname);
                   bool allowed2=frequencyOFsectionORteacher(current.sectionname,current.tname,i);
                   bool allowed3=frequencyOFsectionANDteacher(current.tname+current.sectionname,i);
                   if(allowed1&&allowed2&&allowed3){
                    table[i][j][k]=current;
                    days[i].insert(current.sname);
                    days[i].insert(current.tname);
                    days[i].insert(current.tname+current.sectionname);
                    allcourses.pop();
                   }
                   else{
                    allcourses.pop();
                    allcourses.push(current);
                    k--;
                    continue;
                   }
                   }
                }
            }
        }
}

bool TimeTable::checkOtherRooms(int day, int slot, int room, std::string section, std::string teacher) {
    for (int i = 0; i < room; ++i) {
        if (table[day][i][slot].sectionname == section || table[day][i][slot].tname == teacher) {
            return false;
        }
    }
    return true;
}

bool TimeTable::frequencyOFsectionORteacher(std::string section, std::string teacher, int currentDay) {
    int fSec = days[currentDay].search(section);
    int fTeacher = days[currentDay].search(teacher);
    if (fSec > 6 || fTeacher > 6) {
        return false;
    }
    return true;
}

bool TimeTable::frequencyOFsectionANDteacher(string combined, int currentDay) {
    int fComb = days[currentDay].search(combined);
    if (fComb == 2) {
        return false;
    }

    return true;
}

void TimeTable::display() {
    for (int i = 0; i < 4; ++i) {
        cout << "\t\t\t\tMONDAY\n\n\n";
        for (int j = 0; j < 33; ++j) {
            for (int k = 0; k < 8; ++k) {
                cout << table[i][j][k].sectionname << table[i][j][k].sname << table[i][j][k].tname << "\t";
            }
            cout << "\n\n\n";
        }
    }
}
void TimeTable::Monday()
{
        fstream file;
        file.open("monday.csv");
        for(int i=0;i<33;i++)
        {
            //file << i+8<<"-"<<i+9<<",";	
            for(int j=0;j<8;j++)
            {
                file<<table[0][i][j].tname<<" "<<table[0][i][j].sectionname<<" "<<table[0][i][j].sname<<",";
            }
            file <<endl;
        } 
        file.close();
}
void TimeTable::Tuesday()
{
        fstream file;
        file.open("tuesday.csv");
        for(int i=0;i<33;i++)
        {
            //file << i+8<<"-"<<i+9<<",";	
            for(int j=0;j<8;j++)
            {
                file<<table[1][i][j].tname<<" "<<table[1][i][j].sectionname<<" "<<table[1][i][j].sname<<",";
            }
            file <<endl;
        } 
        file.close();
}
void TimeTable::Wednesday()
{
        fstream file;
        file.open("wednesday.csv");
        for(int i=0;i<33;i++)
        {
            file << i+8<<"-"<<i+9<<",";	
            for(int j=0;j<8;j++)
            {
                file<<table[2][i][j].tname<<" "<<table[2][i][j].sectionname<<" "<<table[2][i][j].sname<<",";
            }
            file <<endl;
        } 
        file.close();
}
void TimeTable::Thursday()
{
        fstream file;
        file.open("thursday.csv");
        for(int i=0;i<33;i++)
        {
            //file << i+8<<"-"<<i+9<<",";	
            for(int j=0;j<8;j++)
            {
                file<<table[3][i][j].tname<<" "<<table[3][i][j].sectionname<<" "<<table[3][i][j].sname<<",";
            }
            file <<endl;
        } 
        file.close();
}    
void TimeTable::Friday()
{
        fstream file;
        file.open("friday.csv");
        for(int i=0;i<33;i++)
        {
            //file << i+8<<"-"<<i+9<<",";	
            for(int j=0;j<8;j++)
            {
                file<<table[4][i][j].tname<<" "<<table[4][i][j].sectionname<<" "<<table[4][i][j].sname<<",";
            }
            file <<endl;
        } 
        file.close();
}
