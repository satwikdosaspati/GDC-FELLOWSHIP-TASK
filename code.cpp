#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<string.h>
using namespace std;

std::string trim(const std::string &s)
{
    auto start = s.begin();
    while (start != s.end() && std::isspace(*start)) {
        start++;
    }
 
    auto end = s.end();
    do {
        end--;
    } while (std::distance(start, end) > 0 && std::isspace(*end));
 
    return std::string(start, end + 1);
}





int main(int argc,char *argv[])
{
    vector<pair<int,string>> vect;
    const int size=100;
    int a;
    char s[size];
    if(argc==1 || strcmp(argv[1],"help")==0)
    {
        printf("Usage  :-\n");
        printf("$ ./task add 2 hello world      # Add a new item with priority 2 and text \"hello world\" to the list\n");
        printf("$ ./task ls                     # Show incomplete priority list items sorted by priority in ascending order\n");
        printf("$ ./task del NUMBER    # Delete the incomplete item with the given priority number\n");
        printf("$ ./task done NUMBER   # Mark the incomplete item with the given PRIORITY_NUMBER as complete\n");
        printf("$ ./task help                   # Show usage\n");
        printf("$ ./task report                 # Statistics\n");
    }
    else if(strcmp(argv[1],"add")==0)
        {
            int i=0;
            ofstream f;
            f.open("task.txt",ios::app);
            f<<atoi(argv[2])<<" "<<argv[3]<<endl;
            f.close();
            
            ifstream fin;
            fin.open("task.txt");
            while(fin.eof()==0)
             {
                fin>>a;
                fin.getline(s,size);
                vect.push_back( make_pair(a,s));
                i++;
             }
            fin.close();
            vect.pop_back();
            sort(vect.begin(),vect.end());
            f.open("task.txt",ios::trunc);
            for(int j=0;j<i-1;j++)
            {
                f<<vect[j].first<<" "<<trim(vect[j].second)<<endl;
            }
            printf("Added task: \"%s\" with priority %d",argv[3],atoi(argv[2]));
        }
        else if(strcmp(argv[1],"ls")==0)
        {
            int i=0;
            ifstream fin;
            fin.open("task.txt");
            while(fin.eof()==0)
             {
                fin>>a;
                fin.getline(s,size);
                vect.push_back( make_pair(a,s));
                i++;
             }
            fin.close();
            vect.pop_back();
            for(int j=1;j<=i-1;j++)
            {
                cout<<j<<". "<<vect[j-1].second<<" ["<<vect[j-1].first<<"]\n";
            }
        }
        else if(strcmp(argv[1],"del")==0)
        {
            int i=0;
            ifstream fin;
            fin.open("task.txt");
            while(fin.eof()==0)
             {
                fin>>a;
                fin.getline(s,size);
                vect.push_back( make_pair(a,s));
                i++;
             }
            fin.close();
            vect.pop_back();
            int b=atoi(argv[2])-1;
            if(b>=0 && b<vect.size())
         {
            vector<pair<int,string>>::iterator it;
            it = vect.begin()+b;
            vect.erase(it);
            ofstream f;
            f.open("task.txt",ios::trunc);
            for(int j=0;j<i-2;j++)
            {
                f<<vect[j].first<<" "<<trim(vect[j].second)<<endl;
            }
            f.close();
            printf("Deleted item with index %d",atoi(argv[2]));
         }
         else
         {
             printf("Error: item with index %d does not exist. Nothing deleted.",b+1);
         }
            
        }
        else if(strcmp(argv[1],"done")==0)
        {
            int i=0;
            ifstream fin;
            fin.open("task.txt");
            while(fin.eof()==0)
             {
                fin>>a;
                fin.getline(s,size);
                vect.push_back( make_pair(a,s));
                i++;
             }
            fin.close();
            vect.pop_back();
            int b=atoi(argv[2])-1;
            if(b>=0 && b<vect.size())
         {
            vector<pair<int,string>>::iterator it;
            it = vect.begin()+b;
            ofstream f1;
            f1.open("completed.txt",ios::app);
            f1<<trim(vect[b].second)<<endl;
            vect.erase(it);
            ofstream f;
            f.open("task.txt",ios::trunc);
            for(int j=0;j<i-2;j++)
            {
                f<<vect[j].first<<" "<<trim(vect[j].second)<<endl;
            }
            f.close();
            printf("Marked item as done.");
         }
         else
         {
             printf("Error: no incomplete item with index %d exists.",b+1);
         }
        }
        else if(strcmp(argv[1],"report")==0)
        {
            int i=0;
            ifstream fin,fin1;
            fin.open("task.txt");
            while(fin.eof()==0)
             {
                fin>>a;
                fin.getline(s,size);
                vect.push_back( make_pair(a,s));
                i++;
             }
            fin.close();
            vect.pop_back();
            printf("Pending : %d\n",(int)vect.size());
            for(int j=0;j<i-1;j++)
            {
                cout<<(j+1)<<". "<<trim(vect[j].second)<<" ["<<vect[j].first<<"]"<<endl;
            }
            vector<string> st;
            fin1.open("completed.txt");
            i=0;
            while(fin1.eof()==0)
            {
                fin1.getline(s,size);
                st.push_back(s);
                i++;
            }
            fin1.close();
            st.pop_back();
            printf("\nCompleted : %d\n",(int)st.size());
            for(int j=0;j<i-1;j++)
            {
                cout<<(j+1)<<". "<<trim(st[j])<<endl;
            }
            
        }
    
}
