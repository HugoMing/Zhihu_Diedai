#ifndef HANDLE_H
#define HANDLE_H
#include <iostream>
#define  LENGTH 200000
#define  READLENGTH 50
#include <Map>
#include <String>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <set>
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
friend    bool operator < (Info a,Info b)
    {
        return a.ID<b.ID;
    }
    void clear()
    {
         ID="";
         HashID="";
         Name="";
         Sign="";
         follower="";
         asks="";
         answers="";
         agree="";
         return;
    }
};

string  returnErFileName(string ID)
{
    string a;
    a="c:\\1\\"+ID+"_flower.txt";
    return a;
}
char*  convertToChar(int a)
{
    char *t;
    t=new char[100];
    sprintf(t,"%d",a);//内存泄漏
    return t;
}
string  returnErpyCommand(Info  ID)
{
    string Command;
    int    number=atoi(ID.follower.c_str());
    cout<<ID.Name<<" has "<<number<<" followEr to read"<<endl;
    if(number>500)
    {
        while(number>500)
        {
            Command+="  C:\\Users\\Administrator\\Documents\\GitHub\\Zhihu_Diedai\\Reader.py     "+ID.HashID+"    "+ID.ID+"    "+convertToChar(number-500)+"     "+convertToChar(number)+"   "+ID.ID+"("+convertToChar(int(number/500)+(number%500?1:0))+").txt"+"   &";
            number-=500;
        }
    }
    Command+="C:\\Users\\Administrator\\Documents\\GitHub\\Zhihu_Diedai\\Reader.py      "+ID.HashID+"    "+ID.ID+"    "+convertToChar(0)+"     "+convertToChar(500)+"   "+ID.ID+"("+convertToChar(int(number/500)+(number%500?1:0))+").txt"+"&";
    //合并文件
    number=atoi(ID.follower.c_str());

    if(number<500)
    {
       Command+="&copy  "+ID.ID+"("+convertToChar(int(number/500)+(number%500?1:0))+").txt  "+"c:\\1\\"+ID.ID+"_flower.txt";
    }
    else
    {
       Command+="&copy  "+ID.ID+"("+convertToChar((number%500?1:0))+").txt  ";
       while(number>500)
       {
           Command+="+ "+ID.ID+"("+convertToChar(int(number/500)+(number%500?1:0))+").txt   ";
           number-=500;
           cout<<"number ="<<number<<endl;
           cout<<"number/500+(number%500?1:0)"<<((number/500)+((number%500?1:0)))<<endl;
       }
       Command+="c:\\1\\"+ID.ID+"_flower.txt";
    }
    cout<<"Command="<<Command<<endl;
    return Command;

}
set<Info> cut(set<Info> NeedToCut,map<string,Info> Map)
{
    set<Info>     NeedToRead;
    Info          Buf;
    char          readfile[LENGTH];
    set<Info>::iterator a=NeedToCut.begin();
    for(;a!=NeedToCut.end();a++)
    {
        string read;
        /*************************************/
        FILE *file;
        int i=0;//&&记录总数
        string::size_type PosBegin,PosEnd;
        /*************************************/
        file=fopen(returnErFileName(a->ID).c_str(),"r");
        while(!feof(file))
        {
            fgets(readfile,LENGTH-2,file);
            read+=readfile;
        }
        fclose(file);
        /*************************************/
        while(read.length()>200)
        {
        PosBegin= read.find("tf-");
        Buf.HashID=read.substr(PosBegin+3,32);
        //cout<<"HashID="<<Buf.HashID<<endl;
        PosBegin= read.find("title=")+7;
        PosEnd  = read.find("\"",PosBegin);
        Buf.Name= read.substr(PosBegin,PosEnd-PosBegin);
        cout<<"Name="<<Buf.Name<<endl;

        PosBegin= read.find("p$t$")+4;
        PosEnd  = read.find("\"",PosBegin);
        Buf.ID= read.substr(PosBegin,PosEnd-PosBegin);
        cout<<"ID="<<Buf.ID<<endl;

        PosBegin= read.find("gray\">")+6;
        PosEnd  = read.find("</div>",PosBegin);
        Buf.Sign= read.substr(PosBegin,PosEnd-PosBegin);
        //cout<<"Sign="<<Buf.Sign<<endl;

        PosBegin= read.find("normal")+8;
        PosEnd  = read.find(" ",PosBegin);
        Buf.follower= read.substr(PosBegin,PosEnd-PosBegin);
        //cout<<"folloewe="<<Buf.follower<<endl;

        PosBegin= read.find("normal",PosEnd)+8;
        PosEnd  = read.find(" ",PosBegin);
        Buf.asks= read.substr(PosBegin,PosEnd-PosBegin);
        //cout<<"asks="<<Buf.asks<<endl;

        PosBegin= read.find("normal",PosEnd)+8;
        PosEnd  = read.find(" ",PosBegin);
        Buf.answers= read.substr(PosBegin,PosEnd-PosBegin);
        //cout<<"answer="<<Buf.answers<<endl;

        PosBegin= read.find("normal",PosEnd)+8;
        PosEnd  = read.find(" ",PosBegin);
        Buf.agree= read.substr(PosBegin,PosEnd-PosBegin);
        //cout<<"agree="<<Buf.agree<<endl;
        cout<<"************************************************************"<<endl;
        if(Map.count(Buf.ID)==0)
        {
            NeedToRead.insert(Buf);
        }
        Buf.clear();
        PosEnd=read.find("zg-right",PosBegin)+8;
        if((read.find("zg-right",PosBegin))==string::npos)
        {
            PosEnd=read.length();
        }
        read.erase(0,PosEnd);
        i++;
        cout<<i;
        }
    }
    return NeedToRead;
}
set<Info> Read(set<Info> NeedToRead,map<string,Info> &Map)
{
    set<Info> NeedToCut;
    set<Info>::iterator a;
    a=NeedToRead.begin();
    for(;a!=NeedToRead.end();a++)
    {
        string path="c:\\1\\"+a->ID+"_flower.txt";
        FILE *file=fopen(path.c_str(),"r");
        fclose(file);
        if(file==NULL)
        {
        system(returnErpyCommand(*a).c_str());
        }

        (Map)[a->ID]=*a;
        NeedToCut.insert(*a);

    }
    return NeedToCut;

}
#endif // HANDLE_H
