// ConsoleApplication6.cpp : 定义控制台应用程序的入口点。
//

#include <iostream>
#define  LENGTH 200000
#define  READLENGTH 50
#include <Map>
#include <String>
#include <fstream>
#include <vector>
#include <stdlib.h>
using namespace std;
class Info
{
public:
    string  ID;//知乎帐户名
    string  HashID;
    string  Name;//帐户名
    string  Sign;//签名
    string  follower;//关注
    string  asks;//提问
    string  answers;//回答
    string  agree;//赞同
    Info()
    {
       /* ID="";
        HashID="";
        Name="";
        Sign="";
        follower="";
        asks="";
        answers="";
        agree="";*/
    }
    void show(void)
    {
        cout<<"ID="<<ID<<endl;
        cout<<"Name="<<Name<<endl;
        cout<<"Sign="<<Sign<<endl;
        cout<<"HashID="<<HashID<<endl;
        return;
    }
    string content(void)
    {
        string a;
        a=this->Name+'\t'+this->Sign+'\t'+this->agree+'\t'+this->answers+'\t'+this->asks+'\t'+this->follower+'\t'+this->ID+'\t'+this->HashID+'\n';
        return a;
    }
};

int Read(string hashid,string ID,int Flag,map<string,Info> &Map,int &count)
{

    cout<<"hashid="<<hashid<<endl;
    cout<<"ID="<<ID<<endl;
    cout<<"Flag="<<Flag<<endl;
    char Flag_;
    if(Flag)
    {
        Flag_='1';
    }
    else
    {
        Flag_='0';
    }
    string aca="C:\\Python33\\READFolloweetest.py   "+hashid+"  "+ID+"  " +Flag_;
    FILE* file1;
    string filename1="c:\\1\\"+ID+".txt";
    file1=fopen(filename1.c_str(),"r");
    if(file1==NULL)
    {
    system(aca.c_str());
    fclose(file1);
    }
    else
    {
     fclose(file1);
    }
    cout<<aca;
    //system("chrome");r
    char readfile[LENGTH];
    string   a;
    /*****************/
    //打开文件
    FILE* file;
    string filename="c:\\1\\"+ID+".txt";
    file=fopen(filename.c_str(),"r");
        if(file==NULL||(count)>READLENGTH)
    {
        if(file==NULL)
            {cout<<ID<<"hasn't exist";
            }
        else
        {
            cout<<"People read end,the count is "<<count<<endl;
        }
        return 1;
    }
    while(!feof(file))
    {
        fgets(readfile,LENGTH-2,file);
        a+=readfile;
    }
    fclose(file);
    /****************/

    string::size_type PosBegin=0;
    string::size_type PosEnd=0;
    int i = 0;
    while(a.length()>200)
    {
        cout<<endl;
    Info    *tk=new Info;
    PosBegin= a.find("tf-");
    tk->HashID=a.substr(PosBegin+3,32);
    //cout<<"HashID="<<tk->HashID<<endl;
    PosBegin= a.find("title=")+7;
    PosEnd  = a.find("\"",PosBegin);
    tk->Name= a.substr(PosBegin,PosEnd-PosBegin);
    cout<<"Name="<<tk->Name<<endl;

    PosBegin= a.find("p$t$")+4;
    PosEnd  = a.find("\"",PosBegin);
    tk->ID= a.substr(PosBegin,PosEnd-PosBegin);
    cout<<"ID="<<tk->ID<<endl;

    PosBegin= a.find("gray\">")+6;
    PosEnd  = a.find("</div>",PosBegin);
    tk->Sign= a.substr(PosBegin,PosEnd-PosBegin);
    //cout<<"Sign="<<tk->Sign<<endl;

    PosBegin= a.find("normal")+8;
    PosEnd  = a.find(" ",PosBegin);
    tk->follower= a.substr(PosBegin,PosEnd-PosBegin);
    //cout<<"folloewe="<<tk->follower<<endl;

    PosBegin= a.find("normal",PosEnd)+8;
    PosEnd  = a.find(" ",PosBegin);
    tk->asks= a.substr(PosBegin,PosEnd-PosBegin);
    //cout<<"asks="<<tk->asks<<endl;

    PosBegin= a.find("normal",PosEnd)+8;
    PosEnd  = a.find(" ",PosBegin);
    tk->answers= a.substr(PosBegin,PosEnd-PosBegin);
    //cout<<"answer="<<tk->answers<<endl;

    PosBegin= a.find("normal",PosEnd)+8;
    PosEnd  = a.find(" ",PosBegin);
    tk->agree= a.substr(PosBegin,PosEnd-PosBegin);
    //cout<<"agree="<<tk->agree<<endl;
    count++;
    cout<<"People has Readen is "<<count<<endl;
    if(count==4)
    {
        int test;
        test=1;
    }
    cout<<"************************************************************"<<endl;
    if(Map.count(tk->ID)==0)
    {
        string pk=tk->ID;
        (Map)[pk]=*tk;
        if(atoi(tk->follower.c_str())==0)
        {
            cout<<atoi(tk->follower.c_str());

            cout<<"Ready to read"<<tk->Name<<endl;
            tk->show();
            Read(tk->HashID,tk->ID,0,Map,count);

        }
        else
        {
            cout<<"Ready to read"<<tk->Name<<endl;
            tk->show();
            Read(tk->HashID,tk->ID,1,Map,count);
            cout<<"follwer=1"<<tk->ID;
        }
    }
    else
    {

    }

    PosEnd=a.find("zg-right",PosBegin)+8;

    if((a.find("zg-right",PosBegin))==string::npos)
    {
        PosEnd=a.length();
    }
    a.erase(0,PosEnd);
    i++;
    cout<<i;
    }

    cout<<ID<<"has readen";
    return 0;
}
int main(void)
{
    string hashid,ID;
    hashid="57842aac37ccd0de3965f9b6e17cb555";
    hashid="172bdd3dc7eb563194150c423a6014d4";
    ID="yao-ze-yuan";
    ID="gayscript";
    map<string,Info> Map_all;
    map<string,Info> &y=Map_all;
    int *i;
    int b=0;
    i=&b;

    Read(hashid,ID,1,y,b);//指针是被复制过去的，递归时调用的是复制的地址的值，并不是真实的地址

    getchar();
    map<string,Info>::iterator readmap;
    FILE* SavetoFile;
    SavetoFile=fopen("d:\\123.txt","w+");
    string SavetoFile_String;
    for(readmap = Map_all.begin();readmap!=Map_all.end();readmap++)
    {
        SavetoFile_String=readmap->second.content();
        fputs(SavetoFile_String.c_str(),SavetoFile);
    }
    fclose(SavetoFile);


    return 0;
}

