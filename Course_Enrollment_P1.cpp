#include <bits/stdc++.h>
using namespace std;
class Coursereg;
class Coursedetails{
    private:
       string Coursename;
       int no_of_credits;
       int capacity;
       vector<string> prerequisites;
       char timeslot;
       public:
       Coursedetails(string s,int n,int c,char t,vector<string>& p){
        Coursename=s;
        no_of_credits=n;
        capacity=c;
        prerequisites=p;
        timeslot=t;
       }
       friend class Coursereg;
};
class Studentdetails{
    private:
    string Studentname;
    int yr_of_study;
    vector<string> Completedcourses;
    vector<string> Enrolledcourses;
    public:
    Studentdetails(string s,int yr,vector<string>& cc,vector<string>& ec){
     Studentname=s;
     yr_of_study=yr;
     Completedcourses=cc;
     Enrolledcourses=ec;
    }
    friend class Coursereg;
};
class Coursereg{
      unordered_map<string,Coursedetails> m1;
      unordered_map<string,Studentdetails> m2;
      unordered_map<string,vector<string>> m3;
      public:
    //   Coursereg(){
    //     m1.clear();
    //     m2.clear();
    //     m3.clear();
    //   }
      void add_student(string& s,const Studentdetails& sd){
        m2.insert({s,sd});
      }
      void add_course(string& s,const Coursedetails& cd){
        bool ch=true;
        int presize=cd.prerequisites.size();
        for(int i=0;i<presize;i++){
            string p=cd.prerequisites[i];
            if(m1.find(p)==m1.end()){
                ch=false;
                break;
            }
        }
        if(ch){
            m1.insert({s,cd});
        }
      }
      void enroll(string& s1,string& s2){
        if(m1.find(s1)!=m1.end()&&m2.find(s2)!=m2.end()){
            auto itr1=m1.find(s1);
            auto itr2=m2.find(s2);
            bool ch=true;
            int len=itr1->second.prerequisites.size();
            for(int i=0;i<len;i++){
                vector<string>& v=itr2->second.Completedcourses;
                if(find(v.begin(),v.end(),itr1->second.prerequisites[i])==v.end()){
                 ch=false;
                 break;
                }
            }
            if(ch){
                if(itr1->second.capacity!=0){
                    char p=itr1->second.timeslot;
                    bool ch1=true;
                    vector<string>& vec=itr2->second.Enrolledcourses;
                    int len=vec.size();
                    for(int i=0;i<len;i++){
                        auto itr=m1.find(vec[i]);
                        if(itr->second.timeslot==p){
                            ch1=false;
                            break;
                        }
                    }
                    if(ch1){
                        m3[s1].push_back(s2);
                        itr1->second.capacity--;
                        itr2->second.Enrolledcourses.push_back(s1);
                    }
                }
            }
        }

      }
      void print(string& s){
           auto itr=m3.find(s);
           if(itr!=m3.end()){
              cout<<"Enrolled students in "<<s<<" :"<<endl;
              int len=itr->second.size();
              for(int i=0;i<len;i++){
                cout<<itr->second[i]<<" ";
              }
              cout<<endl;
           }else{
            cout<<"Invalid Course "<<s<<endl;
           }
      }
};
int main(){
    Coursereg IITM;
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        string s;
        cin>>s;
        if(s.compare("add_student")==0){
            string id,name;
            cin>>id>>name;
            int yr,num;
            cin>>yr>>num;
            vector<string> v1(num),v2;
            for(int i=0;i<num;i++){
                cin>>v1[i];
            }
            v2.resize(0);
            IITM.add_student(id,Studentdetails(name,yr,v1,v2));
        }else if(s.compare("add_course")==0){
            string id,name;
            cin>>id>>name;
            char c;
            int credits,capacity,prereq_no;
            cin>>credits>>capacity>>c>>prereq_no;
            vector<string> v1(prereq_no);
            for(int i=0;i<prereq_no;i++){
                cin>>v1[i];
            }
            IITM.add_course(id,Coursedetails(name,credits,capacity,c,v1));
        }else if(s.compare("enroll")==0){
            string s1,s2;
            cin>>s1>>s2;
            IITM.enroll(s2,s1);
        }else{
            string s;
            cin>>s;
            IITM.print(s);
        }
    }
    
}
