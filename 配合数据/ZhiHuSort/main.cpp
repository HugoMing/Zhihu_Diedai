#include <algorithm>
#include <iostream>
#define  LENGTH 200000
#define  READLENGTH 50
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
int compareagree(Info a,Info b)
{
    int ai=atoi(a.agree.c_str());
    int bi=atoi(b.agree.c_str());
    return (int)(ai>bi);
}
int compareasks(Info a,Info b)
{
    int ai=atoi(a.asks.c_str());
    int bi=atoi(b.asks.c_str());
    return (int)(ai>bi);
}
int comparefollower(Info a,Info b)
{
    int ai=atoi(a.follower.c_str());
    int bi=atoi(b.follower.c_str());
    return (int)(ai>bi);
}
int compareanswers(Info a,Info b)
{
    int ai=atoi(a.answers.c_str());
    int bi=atoi(b.answers.c_str());
    return (int)(ai>bi);
}
int main(int argc, char *argv[])
{
    vector<Info> Vector_all;
    int i=0;
    /***********读取历史纪录**************/
    FILE* historyRead=fopen("D:\\ZhihuMapAnsWer5.txt","r");
    string  HisRead;
    char    read_file_his[LENGTH];
    cout<<"Start Running"<<endl;
    cout<<"Read Local Record"<<endl;
    if(historyRead==NULL)
    {
        cout<<"Sorry,The file isn't exist"<<endl;
    }
    else
    {
        Info Buf_read;
        while(!feof(historyRead))
        {
            fgets(read_file_his,LENGTH,historyRead);//此处必须用fgets，否则读取不到‘\t’
            HisRead=read_file_his;
            Buf_read.readLine(HisRead);
            Vector_all.push_back(Buf_read);
            Buf_read.clear();
            i++;
        }
        fclose(historyRead);
    }

    /***************
     *agree     1
     *answer    2
     *question  3
     *follower  4
     **************/
    sort(Vector_all.begin(),Vector_all.end(),compareagree);
    vector<Info>::iterator Vector_ite=Vector_all.begin();
    string scout;
    while(Vector_ite!=Vector_all.end())
    {
        scout+=Vector_ite->contentSort(1);
        Vector_ite++;
    }
    string filename;
    filename=filename="D:\\ZhiHu_AnsWer5_";
    filename+="agree";
    filename+=".txt";
    historyRead=fopen(filename.c_str(),"w");
    fputs(scout.c_str(),historyRead);
    fclose(historyRead);
    scout.clear();
    /**********************************************************/
    sort(Vector_all.begin(),Vector_all.end(),comparefollower);
    Vector_ite=Vector_all.begin();
    while(Vector_ite!=Vector_all.end())
    {
        scout+=Vector_ite->contentSort(4);
        Vector_ite++;
    }
    filename=filename="D:\\ZhiHu_AnsWer5_";
    filename+="follower";
    filename+=".txt";
    historyRead=fopen(filename.c_str(),"w");
    fputs(scout.c_str(),historyRead);
    fclose(historyRead);
    scout.clear();
    /**********************************************************/
    sort(Vector_all.begin(),Vector_all.end(),compareasks);
    Vector_ite=Vector_all.begin();
    while(Vector_ite!=Vector_all.end())
    {
        scout+=Vector_ite->contentSort(3);
        Vector_ite++;
    }
    filename=filename="D:\\ZhiHu_AnsWer5_";
    filename+="ask";
    filename+=".txt";
    historyRead=fopen(filename.c_str(),"w");
    fputs(scout.c_str(),historyRead);
    fclose(historyRead);
    scout.clear();
    /**********************************************************/
    sort(Vector_all.begin(),Vector_all.end(),compareanswers);
    Vector_ite=Vector_all.begin();
    while(Vector_ite!=Vector_all.end())
    {
        scout+=Vector_ite->contentSort(2);
        Vector_ite++;
    }
    filename=filename="D:\\ZhiHu_AnsWer5_";
    filename+="answers";
    filename+=".txt";
    historyRead=fopen(filename.c_str(),"w");
    fputs(scout.c_str(),historyRead);
    fclose(historyRead);
    scout.clear();

    cout<<"Endl"<<endl;
    return 1;
}
