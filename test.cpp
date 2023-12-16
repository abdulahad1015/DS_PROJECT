#include <iostream>
#include<vector>
#include<queue>
#include<ctime>
#include<cmath>
#include <fstream>
#include <sstream>
using namespace std;
#define TotalSections 32
#define TotalElectives 10
#define TotalTeachers 71
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
    string subsection[2]={"",""};
    string sname;
    int type=1;
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
    string subsection[2]={"",""};
    string sectionname;
    int type=1;
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

    bool checkOtherRooms(int,int,int,string,string,string [],int);

    bool frequencyOFsectionORteacher(string, string, int );

    bool frequencyOFsectionANDteacher(string , int);

    bool checkOffDay(int ,string);

    void backtrackerCore(Info ,int ,int room,int slot);

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
        t1->courses[j].sethours(stoi(all[j+2+counter]));
    }
    int sections=stoi(all[2+2*counter]);
    //t1->cntSec=sections;
    for(int j=0;j<sections;j++){
        for(int k=0;k<TotalSections+TotalElectives;k++){
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
void breakElectives(const string& line,section *s1)
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
    s1->maxcourses=1;
    s1->subsection[0]=all[2];
    s1->subsection[1]=all[3];
    s1->courses[0].name=all[4];
    s1->type=2;

}

void readElectives(section s1[])
{
    int i=TotalSections;
    string line;
    ifstream fin("electives.csv");

    if (!fin.is_open())
    {
        cerr << "Error opening the file." << endl;
        return;
    }

    while (getline(fin, line))
    {
        breakElectives(line,&s1[i]);
        i++;
    }

    fin.close();
}


int main()
{   
    //----------------------------------------
    section s1[TotalSections+TotalElectives];
    readSections(s1);
    readElectives(s1);
    
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
        for(int j=0;j<t1[i].cntinfo;++j){
             teacherCredits.push(t1[i].credit[j]);
     }
     }
    Info freeslot;
    freeslot.hours=0;
    freeslot.sectionname="-";
    freeslot.sname="-";
    freeslot.tname="-";
    
    TimeTable mytable;
    cout<<"HELooooooooooooooooooooooooooooooooooooooooooooooooooo"<<endl;
    mytable.fillTable(teacherCredits);
    //mytable.display();
    mytable.Monday();
    mytable.Tuesday();
    mytable.Wednesday();
    mytable.Thursday();
    mytable.Friday();



    //mytable.display();
  

    
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
	Info *arr=new Info[size];
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
                        if(no_of_sections[i].type==2){
                            for(int m=0;m<2;++m)
                                credit[cntinfo].subsection[m]=no_of_sections[i].subsection[m];
                        }
                        credit[cntinfo].sectionname = no_of_sections[i].sectionname;
                        credit[cntinfo].sname = courses[j].name;
                        credit[cntinfo].hours = courses[j].hours;
                        credit[cntinfo].type=no_of_sections[j].type;
                        credit[cntinfo++].tname = name;
                    }
                }
            }
        }
    }
}

///////////////////////HASHMAP CLASS///////////////

void TimeTable::fillTable(queue<Info>& allcourses) {
    //Add free slots
    int num_free_slots= no_rooms*no_slots*no_rooms - allcourses.size();
    Info freeslot;
    freeslot.hours=0;
    freeslot.sectionname="-";
    freeslot.sname="-";
    freeslot.tname="-";
    // for(int i=0;i<num_free_slots;++i){
    //     allcourses.push(freeslot);
    // }
    //End adding free slots
    shufflequeue(allcourses);
    //Start filling
    int a=allcourses.size();
    while(!allcourses.empty()){
        if(a==0){
            break;
        }
        
        a--;
        
        backtrackerCore(allcourses.front(),0,0,0);
        allcourses.pop();
    }
       
}

void TimeTable::backtrackerCore(Info current,int day,int room,int slot){
   
   day=rand()%no_days;
   room=rand()%no_rooms;
   slot=rand()%no_slots;
    if(day>=no_days||room>=no_rooms||slot>=no_slots){
        return;
    }
    if((checkOffDay(day,current.sectionname))||!(frequencyOFsectionANDteacher(current.tname+current.sectionname,day))||!frequencyOFsectionORteacher(current.sectionname,current.tname,day)){
        backtrackerCore(current,day+1,room,slot);
        return;
    }
    else if(!checkOtherRooms(day,room,slot,current.sectionname,current.tname,current.subsection,current.type)){
        backtrackerCore(current,day,room,slot+1);
        return;
    }
    else if(table[day][room][slot].hours>0){
        backtrackerCore(current,day,room+1,slot);
        return;
    }
    table[day][room][slot]=current;
    days[day].insert(current.sname);
    days[day].insert(current.tname);
    days[day].insert(current.tname+current.sectionname);
    return;
}
bool TimeTable::checkOtherRooms(int day, int room,int slot, std::string section, std::string teacher, string subsec[], int type) {
    
    if(type==1){
    for (int i = 0; i < no_rooms; ++i) {
        if (table[day][i][slot].sectionname == section || table[day][i][slot].tname == teacher) {
            return false;
        }
    }
    return true;
    }
    else{
        cout<<"here"<<endl;
        for (int i = 0; i < no_rooms; ++i) {
        if( table[day][i][slot].tname == teacher){
            return false;
        }
        if (table[day][i][slot].sectionname == subsec[0] ||(table[day][i][slot].sectionname == subsec[1])) {
            if(table[day][i][slot].type==1){
                return false;
            }
        }
        }
        return true;
    }
}
bool TimeTable::checkOffDay(int day,string section) {
    if(section[0]=='1'&&day==0){
        return true;
    }
    if(section[0]=='3'&&day==1){
        return true;
    }
    if(section[0]=='5'&&day==2){
        return true;
    }
    if(section[0]=='7'&&day==3){
        return true;
    }
    return false;
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
        ofstream file;
        file.open("monday.csv");
        file<<"Class Room,";
        for(int j=0;j<4;j++)
        file << j+8<<":00-"<<j+9<<":00,";	
        for(int j=4;j<8;j++)
        file << j+8<<":00-"<<j+9<<":00,";
        file <<endl;
        for(int i=0;i<33;i++)
        {
            file << i+1<<",";	
            for(int j=1;j<9;j++)
            {
                if(table[0][i][j-1].type==1)
                file<<table[0][i][j-1].tname<<" "<<table[0][i][j-1].sectionname<<" "<<table[0][i][j-1].sname<<",";
                else{
                    file<<table[0][i][j-1].tname<<" "<<table[0][i][j-1].subsection[0]<<" "<<table[0][i][j-1].subsection[1]<<",";
                }
            }
            file <<endl;
        } 
        file.close();
}
void TimeTable::Tuesday()
{
        ofstream file;
        file.open("tuesday.csv");
        file<<"Class Room,";
        for(int j=0;j<4;j++)
        file << j+8<<":00-"<<j+9<<":00,";	
        for(int j=4;j<8;j++)
        file << j+8<<":00-"<<j+9<<":00,";
        file <<endl;
        for(int i=0;i<33;i++)
        {
            file << i+1<<",";	
            for(int j=1;j<9;j++)
            {
                if(table[1][i][j-1].type==1)
                file<<table[1][i][j-1].tname<<" "<<table[1][i][j-1].sectionname<<" "<<table[1][i][j-1].sname<<",";
                else{
                    file<<table[1][i][j-1].tname<<" "<<table[1][i][j-1].subsection[0]<<" "<<table[1][i][j-1].subsection[1]<<",";
                }
            }
            file <<endl;
        } 
        file.close();
}
void TimeTable::Wednesday()
{
        ofstream file;
        file.open("wednesday.csv");
        file<<"Class Room,";
        for(int j=0;j<4;j++)
        file << j+8<<":00-"<<j+9<<":00,";	
        for(int j=4;j<8;j++)
        file << j+8<<":00-"<<j+9<<":00,";
        file <<endl;
        for(int i=0;i<33;i++)
        {
            file << i+1<<",";	
            for(int j=1;j<9;j++)
            {
                if(table[2][i][j-1].type==1)
                file<<table[2][i][j-1].tname<<" "<<table[2][i][j-1].sectionname<<" "<<table[2][i][j-1].sname<<",";
                else{
                    file<<table[2][i][j-1].tname<<" "<<table[2][i][j-1].subsection[0]<<" "<<table[2][i][j-1].subsection[1]<<",";
                }
            }
            file <<endl;
        } 
        file.close();
}
void TimeTable::Thursday()
{
        ofstream file;
        file.open("thursday.csv");
        for(int j=0;j<4;j++)
        file << j+8<<":00-"<<j+9<<":00,";	
        for(int j=4;j<8;j++)
        file << j+8<<":00-"<<j+9<<":00,";
        file <<endl;
        for(int i=0;i<33;i++)
        {
            file << i+1<<",";	
            for(int j=1;j<9;j++)
            {
                if(table[3][i][j-1].type==1)
                file<<table[3][i][j-1].tname<<" "<<table[3][i][j-1].sectionname<<" "<<table[3][i][j-1].sname<<",";
                else{
                    file<<table[3][i][j-1].tname<<" "<<table[3][i][j-1].subsection[0]<<" "<<table[3][i][j-1].subsection[1]<<",";
                }
            }
            file <<endl;
        } 
        file.close();
}    
void TimeTable::Friday()
{
        ofstream file;
        file.open("friday.csv");
        file<<"Class Room,";
        for(int j=0;j<4;j++)
        file << j+8<<":00-"<<j+9<<":00,";	
        for(int j=4;j<8;j++)
        file << j+8<<":00-"<<j+9<<":00,";
        file <<endl;
        for(int i=0;i<33;i++)
        {
            file << i+1<<",";	
            for(int j=1;j<9;j++)
            {
                if(table[4][i][j-1].type==1)
                file<<table[4][i][j-1].tname<<" "<<table[4][i][j-1].sectionname<<" "<<table[4][i][j-1].sname<<",";
                else{
                   
                    file<<table[4][i][j-1].tname<<" "<<table[4][i][j-1].subsection[0]<<" "<<table[4][i][j-1].subsection[1]<<",";
                }
            }
            file <<endl;
        } 
        file.close();
}
