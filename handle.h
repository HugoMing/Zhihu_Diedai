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

#define   MAXCONNECT   60//最大连接数
#define   LESSGROUP    100//最小组距
#define   CELLLENTH    6000 //分界线
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
    void readLine(string cin)
    {

        int PosEnd=0;

        PosEnd=cin.find('\t');
        this->Name=cin.substr(0,PosEnd);
        cin.erase(0,PosEnd+1);
        PosEnd=cin.find('\t');
        this->Sign=cin.substr(0,PosEnd);
        cin.erase(0,PosEnd+1);
        PosEnd=cin.find('\t');
        this->agree=cin.substr(0,PosEnd);
        cin.erase(0,PosEnd+1);
        PosEnd=cin.find('\t');
        this->answers=cin.substr(0,PosEnd);
        cin.erase(0,PosEnd+1);
        PosEnd=cin.find('\t');
        this->asks=cin.substr(0,PosEnd);
        cin.erase(0,PosEnd+1);
        PosEnd=cin.find('\t');
        this->follower=cin.substr(0,PosEnd);
        cin.erase(0,PosEnd+1);
        PosEnd=cin.find('\t');
        this->ID=cin.substr(0,PosEnd);
        cin.erase(0,PosEnd+1);
        PosEnd=cin.find('\t');
        this->HashID=cin.substr(0,PosEnd);
        cin.erase(0,PosEnd+1);
        return;
    }
};

string  returnErFileName(string ID)
{
    string a;
    a="c:\\1\\"+ID+"_flower.txt";
    return a;
}
string  convertToChar(int a)
{
    string k;
    char *t=new char[100];
    sprintf(t,"%d",a);//内存泄漏
    k+=t;
    return k;
}
string  returnErpyCommand(Info  ID)
{
    string Command;
    int    number=atoi(ID.follower.c_str());
    //cout<<ID.Name<<" has "<<number<<" followEr to read"<<endl;
    int length = (number<CELLLENTH)?LESSGROUP:(number/MAXCONNECT);
        while(number>length)
        {
            Command+="##"+ID.HashID+"##"+ID.ID+"##"+convertToChar(number-length)+"##"+convertToChar(number)+"##"+ID.ID+"("+convertToChar(int(number/length)+(number%length?1:0))+").txt"+"##$";
            number-=length;
        }

    Command+="##"+ID.HashID+"##"+ID.ID+"##"+convertToChar(0)+"##"+convertToChar(length)+"##"+ID.ID+"("+convertToChar(int(number/length)+(number%length?1:0))+").txt\n";
    //合并文件
    cout<<"Command = "<<Command<<endl;
    return Command;

}
string returnCopyBuf(Info ID)
{
    string Command;
    int    number=atoi(ID.follower.c_str());
    int length = (number<CELLLENTH)?LESSGROUP:number/MAXCONNECT;
    if(number<=length)
    {
       Command+="copy  "+ID.ID+"("+convertToChar(int(number/length)+(number%length?1:0))+").txt  "+"c:\\1\\"+ID.ID+"_flower.txt";
    }
    else
    {
       Command+="copy  ";
       while(number>length)
       {
           Command+=""+ID.ID+"("+convertToChar(int(number/length)+(number%length?1:0))+").txt+";
           number-=length;
       }
       Command+=ID.ID+"("+convertToChar((number%length?1:0))+").txt";
       Command+=" c:\\1\\"+ID.ID+"_flower.txt";
    }
    Command+="\n";
    cout<<"Copy_Command = "<<Command<<endl;
    return Command;
}
string returnDelBuf(Info ID)
{
    string Command;
    int    number=atoi(ID.follower.c_str());
    int length = (number<CELLLENTH)?LESSGROUP:number/MAXCONNECT;
    if(number<=length)
    {
       Command+="del  "+ID.ID+"("+convertToChar(int(number/length)+(number%length?1:0))+").txt  ";
    }
    else
    {
       Command+="del  ";
       while(number>length)
       {
           Command+=ID.ID+"("+convertToChar(int(number/length)+(number%length?1:0))+").txt    +  ";
           number-=length;
       }
       Command+=        ID.ID+"("+convertToChar((number%length?1:0))+").txt  ";
    }
    Command+="\n";
    cout<<"Del_Command = "<<Command<<endl;
    return Command;
}
set<Info> cut(set<Info> NeedToCut,map<string,Info> &Map,int &i)
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
        string::size_type PosBegin,PosEnd;
        /*************************************/
        file=fopen(returnErFileName(a->ID).c_str(),"r");
        if(file==NULL)
        {
            continue;
        }
        while(!feof(file))
        {
            fscanf(file,"%s",readfile);
            read+=readfile;
        }
       // cout<<read<<endl;
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
            if((atoi(Buf.answers.c_str()))>1)
            {NeedToRead.insert(Buf);}
            else
            {
                Map[Buf.ID]=Buf;
            }
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
    FILE    *pyRead,*CpRead;
    pyRead=fopen("d:\\pyRead.txt","w");
    CpRead=fopen("d:\\CpRead.txt","w");
    for(;a!=NeedToRead.end();a++)
    {
        string path="c:\\1\\"+a->ID+"_flower.txt";
        FILE *file=fopen(path.c_str(),"r");
        fclose(file);
        if(file==NULL&&Map.count(a->ID)==0)
        {
        fputs(returnErpyCommand(*a).c_str(),pyRead);
        fputs(returnCopyBuf(*a).c_str(),CpRead);
        fputs(returnDelBuf(*a).c_str(),CpRead);
        }

        (Map)[a->ID]=*a;
        NeedToCut.insert(*a);
    }
    fclose(pyRead);
    fclose(CpRead);
    system("C:\\Users\\Administrator\\Documents\\GitHub\\Zhihu_Diedai\\threadtry.py");//启动py
   /*************************************/
    CpRead=fopen("d:\\CpRead.txt","r");
    char          readfile[LENGTH];
    while(!feof(CpRead))
    {
        fgets(readfile,LENGTH-2,CpRead);//此处只能用gets
        cout<<"Copy Command = "<<readfile<<endl;
        system(readfile);
        fgets(readfile,LENGTH-2,CpRead);
        cout<<"Del Command = "<<readfile<<endl;
        system(readfile);
        fgetc(CpRead);
    }
    fclose(CpRead);
    /**********************************/
    return NeedToCut;

}
#endif // HANDLE_H
