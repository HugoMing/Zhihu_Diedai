#include <algorithm>
#include <iostream>
#define  LENGTH 200000
#define  READLENGTH 50
#define  TZKAS      agree
#define  TZKASs     "agree"
/**********************
 *可选项
 *follower
 *asks
 *answers
 *agree
 *********************/
#define  TZKASNUM   1
/*************
 *follower          4
 *asks              3
 *answers           2
 *agree             1
 ************/
#include <Map>
#include <String>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <set>
#include <io.h>
#define   AGREE     1
#define   ANSWER    2
#define   QUESTION  3
#define   FOLLOWER  4
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
        cout<<"ID       ="<<ID<<" Length = "<<ID.length()<<endl;
        cout<<"Name     ="<<Name<<" Length = "<<Name.length()<<endl;
        cout<<"Sign     ="<<Sign<<" Length = "<<Sign.length()<<endl;
        cout<<"agree  ="<<answers<<" Length = "<<agree.length()<<endl;
        cout<<"asks  ="<<answers<<" Length = "<<asks.length()<<endl;
        cout<<"answers  ="<<answers<<" Length = "<<answers.length()<<endl;
        cout<<"followers="<<follower<<" Length = "<<follower.length()<<endl;
        cout<<"HashID   ="<<HashID<<" Length = "<<HashID.length()<<endl;
        return;
    }
    string content(void)
    {
        string a;
        a=this->Name+'\t'+this->Sign+'\t'+this->agree+'\t'+this->answers+'\t'+this->asks+'\t'+this->follower+'\t'+this->ID+'\t'+this->HashID+'\n';
        return a;
    }
    string contentSort(int k)
    {
        /***************
         *agree     1
         *answer    2
         *question  3
         *follower  4
         **************/
        string a;
        a=Name+"\t\t\t\t";
        switch(k)
        {
                case 1:a+=agree;break;
                case 2:a+=answers;break;
                case 3:a+=asks;break;
                case 4:a+=follower;break;
                default:break;
        }
        a+="\n";
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

int main(int argc, char *argv[])
{
    map<string,Info> Map_all;
    int i=0;
    /***********读取历史纪录**************/
    FILE* historyRead=fopen("D:\\ZhihuMap.txt","r");//试试改用SSD速度能快点不,SSD读取24M的时候24秒 ， 机械硬盘也是24秒。表示不是读取的问题
    string  HisRead;
    char    read_file_his[LENGTH];
    cout<<"Start Running"<<endl;
    cout<<"Read Local Record"<<endl;
    if(historyRead==NULL)
    {
        cout<<"错误，无法检测到历史纪录"<<endl;
        cout<<"作为新文件进行读取"<<endl;
    }
    else
    {
        Info Buf_read;
        while(!feof(historyRead))
        {
            fgets(read_file_his,LENGTH,historyRead);//此处必须用fgets，否则读取不到‘\t’
            HisRead=read_file_his;
            Buf_read.readLine(HisRead);
            //Buf_read.show();
            if(Buf_read.Name.length()==0||Buf_read.ID.length()<3)
            {
                continue;
            }
            if(!(Buf_read.HashID.compare((Buf_read.follower))))
            {
                if(!(Buf_read.HashID.compare((Buf_read.ID))))
                {
                continue;
                }
            }
            if(atoi(Buf_read.answers.c_str())>5)
            Map_all[Buf_read.ID]=Buf_read;
            Buf_read.clear();
            i++;
            if(i%10000==0)
            {
                cout<<i<<" people has been readen"<<endl;
            }
        }
        fclose(historyRead);
    }
    /************备份数据*************/
    map<string,Info>::iterator readmap;
    FILE* SavetoFile;
    SavetoFile=fopen("d:\\ZhihuMapAnsWer5.txt","w+");
    string SavetoFile_String;
    i=0;
    for(readmap = Map_all.begin();readmap!=Map_all.end();readmap++)
    {
        SavetoFile_String=(readmap->second).content();
        fputs(SavetoFile_String.c_str(),SavetoFile);
        i++;
        if(i%10000==0)
        {
            cout<<i<<" people has been writen"<<endl;
        }
    }
    fclose(SavetoFile);
    cout<<"end"<<endl;
    /************备份完成***************/
}
