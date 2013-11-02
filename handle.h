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
#include <io.h>

#define   MAXCONNECT   60//最大连接数
#define   LESSGROUP    100//最小组距
#define   CELLLENTH    6000 //分界线
#define   READFOLLOWERLENGTH 300000//最小文件记录长度
#define   MAXFILENAMECOUNT  40//最长合并文件长度
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
        cout<<"ID       ="<<ID<<endl;
        cout<<"Name     ="<<Name<<endl;
        cout<<"Sign     ="<<Sign<<endl;
        cout<<"answers  ="<<answers<<endl;
        cout<<"followers="<<follower<<endl;
        cout<<"HashID   ="<<HashID<<endl;
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
    a="d:\\1\\"+ID+"_flower.txt";
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
    string Path="D:\\2\\";
    //cout<<ID.Name<<" has "<<number<<" followEr to read"<<endl;
    int length = (number<CELLLENTH)?LESSGROUP:(number/MAXCONNECT);
        while(number>length)
        {
            Command+="##"+ID.HashID+"##"+ID.ID+"##"+convertToChar(number-length)+"##"+convertToChar(number)+"##"+Path+ID.ID+"("+convertToChar(int(number/length)+(number%length?1:0))+").txt"+"##$";
            number-=length;
        }

    Command+="##"+ID.HashID+"##"+ID.ID+"##"+convertToChar(0)+"##"+convertToChar(length)+"##"+Path+ID.ID+"("+convertToChar(int(number/length)+(number%length?1:0))+").txt\n";
    //合并文件
    //cout<<"Command = "<<Command<<endl;
    return Command;

}
string returnCopyBuf(Info ID)//调用自己写的函数进行合并
{
    string Command;
    int    number=atoi(ID.follower.c_str());
    int length = (number<CELLLENTH)?LESSGROUP:number/MAXCONNECT;
    string Path="D:\\2\\";
    if(number<=length)
    {
       Command+=Path+ID.ID+"("+convertToChar(int(number/length)+(number%length?1:0))+").txt###&&&"+"d:\\1\\"+ID.ID+"_flower.txt";
    }
    else
    {
       Command+="";
       while(number>length)
       {
           Command+=Path+ID.ID+"("+convertToChar(int(number/length)+(number%length?1:0))+").txt###";
           number-=length;
       }
       Command+=Path+ID.ID+"("+convertToChar((number%length?1:0))+").txt###";
       Command+="&&&d:\\1\\"+ID.ID+"_flower.txt";
    }
    Command+="\n";
    //cout<<"Copy_Command = "<<Command<<endl;
    return Command;
}
string returnDelBuf(Info ID)//调用自己写的函数将文件合并为同一个值，NeedToCut.txt
{
    string Command;
    string Path="D:\\1\\";
    Command+=Path+ID.ID+"_flower.txt###";
    //cout<<"Del_Command = "<<Command<<endl;
    return Command;
}
set<Info> cut(int CutCount,map<string,Info> &Map,int &i)
{
    set<Info>     NeedToRead;
    Info          Buf;
    char          readfile[LENGTH];
    int           count=0;
    while(count<=CutCount)
    {
        string read;
        /*************************************/
        FILE *file;
        string::size_type PosBegin,PosEnd;
        PosBegin=0;
        /*************************************/
        sprintf(readfile,"%d",count);
        string  ReadCount=readfile;
        ReadCount="D:\\NeedToCut"+ReadCount+".txt";
        file=fopen(ReadCount.c_str(),"r");
        if(file==NULL)
        {
            count++;//文件不存在时跳出
            continue;
        }
        while(!feof(file))
        {
            fgets(readfile,LENGTH,file);
            read+=readfile;
        }
       // cout<<read<<endl;
        fclose(file);
        /*************************************/
        while(read.length()>200)
        {
        PosBegin= read.find("tf-",PosBegin);
        Buf.HashID=read.substr(PosBegin+3,32);
        //cout<<"HashID="<<Buf.HashID<<endl;
        PosBegin= read.find("title=",PosBegin)+7;
        PosEnd  = read.find("\"",PosBegin);
        Buf.Name= read.substr(PosBegin,PosEnd-PosBegin);
        //cout<<"Name="<<Buf.Name<<endl;

        PosBegin= read.find("p$t$",PosBegin)+4;
        PosEnd  = read.find("\"",PosBegin);
        Buf.ID= read.substr(PosBegin,PosEnd-PosBegin);
        //cout<<"ID="<<Buf.ID<<endl;

        PosBegin= read.find("gray\">",PosBegin)+6;
        PosEnd  = read.find("</div>",PosBegin);
        Buf.Sign= read.substr(PosBegin,PosEnd-PosBegin);
        //cout<<"Sign="<<Buf.Sign<<endl;

        PosBegin= read.find("normal",PosBegin)+8;
        //cout<<"Begin = "<<PosBegin<<endl;
        PosEnd  = read.find(" ",PosBegin);
        //cout<<"End   = "<<PosEnd<<endl;//因为使用了%s导致所有的空格都被滤掉了
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
        //cout<<"************************************************************"<<endl;
        if(Map.count(Buf.ID)==0)
        {
            if((atoi(Buf.answers.c_str()))>1&&atoi(Buf.follower.c_str())>0)
            {
                NeedToRead.insert(Buf);
            }
            else
            {
                Map[Buf.ID]=Buf;
            }
        }
        Buf.clear();
        PosBegin=read.find("zg-right",PosBegin)+8;
        if((PosBegin-8)==string::npos)
        {
            PosEnd=read.length();
            read.erase(0,PosEnd);
        }

        i++;
            if(i%1000==0)
            {
                cout<<i<<" people has read "<<endl;
                /*if(i%3000000==0)
                {
                    map<string,Info>::iterator readmap;
                    FILE* SavetoFile;
                    SavetoFile=fopen("D:\\ZhihuMap.txt","w+");
                    string SavetoFile_String;
                    for(readmap = Map.begin();readmap!=Map.end();readmap++)
                    {
                        SavetoFile_String=(readmap->second).content();
                        fputs(SavetoFile_String.c_str(),SavetoFile);
                    }
                    fclose(SavetoFile);
                }*/
            }
        }
        count++;
    }
    return NeedToRead;
}
int Read(set<Info> NeedToRead,map<string,Info> &Map)
{
    set<Info> NeedToCut;
    set<Info>::iterator a;
    a=NeedToRead.begin();
    FILE    *pyRead,*CpRead,*MeRead;
    pyRead=fopen("d:\\pyRead.txt","w");
    CpRead=fopen("d:\\CpRead.txt","w");

    cout<<"Read Function Begin"<<endl;
    int                 followercount=0;
    string              MeCommandLine;
    string              PyCommandLine;
    string              CyCommandLine;
    string              MePath;
    for(;a!=NeedToRead.end();a++)
    {
        string path="d:\\1\\"+a->ID+"_flower.txt";
        if(access(path.c_str(),F_OK)!=0&&Map.count(a->ID)==0)
        {
        PyCommandLine+=returnErpyCommand(*a);
        CyCommandLine+=returnCopyBuf(*a);
        }
        else
        {
            int test;
            test=1;
        }

        followercount+=atoi(a->follower.c_str());
        (Map)[a->ID]=*a;
        NeedToCut.insert(*a);
    }
    fputs(PyCommandLine.c_str(),pyRead);
    fputs(CyCommandLine.c_str(),CpRead);
    fclose(pyRead);
    fclose(CpRead);
    system("C:\\Users\\Administrator\\Documents\\GitHub\\Zhihu_Diedai\\threadtry.py");//启动py
    system("C:\\Users\\Administrator\\Documents\\GitHub\\Zhihu_Diedai\\Project1.exe  d:\\CpRead.txt   0");
    cout<<followercount<<" relation has been read"<<endl;
    followercount=0;
    int filecount=0;
    char    IntToChar[1000];

    cout<<"Merage Begin"<<endl;
    MePath="D:\\MeRead";
    sprintf(IntToChar,"%d",filecount);
    MePath+=IntToChar;
    MePath+=".txt";
    MeRead=fopen(MePath.c_str(),"w");
    MeCommandLine="";

    for(a=NeedToRead.begin();a!=NeedToRead.end();a++)
    {
        if(followercount<READFOLLOWERLENGTH)
        {
            followercount+=atoi(a->follower.c_str());
            MeCommandLine+="d:\\1\\"+a->ID+"_flower.txt###";
        }
        else
        {
            followercount=0;
            sprintf(IntToChar,"%d",filecount);
            MeCommandLine+="&&&D:\\NeedToCut";
            MeCommandLine+=IntToChar;
            MeCommandLine+=".txt";
            fputs(MeCommandLine.c_str(),MeRead);
            fclose(MeRead);
            filecount++;
            MePath="D:\\MeRead";
            sprintf(IntToChar,"%d",filecount);
            MePath+=IntToChar;
            MePath+=".txt";
            MeRead=fopen(MePath.c_str(),"w");
            MeCommandLine="";
        }
    }
    if(MeCommandLine.length()>0)
    {
        sprintf(IntToChar,"%d",filecount);
        MeCommandLine+="&&&D:\\NeedToCut";
        MeCommandLine+=IntToChar;
        MeCommandLine+=".txt";
        fputs(MeCommandLine.c_str(),MeRead);
    }
    fclose(MeRead);
    sprintf(IntToChar,"%d",filecount);
    string systemLine="C:\\Users\\Administrator\\Documents\\GitHub\\Zhihu_Diedai\\ThreadCopy.exe  ";
    systemLine+=IntToChar;
    systemLine+="   1";
    system(systemLine.c_str());

    return filecount;

}
#endif // HANDLE_H
