// ConsoleApplication6.cpp : 定义控制台应用程序的入口点。
//
//#include <thread>
#include "handle.h"

void hello()
{
    cout<<"hello world"<<endl;
    return;
}

int main(void)
{
    map<string,Info> Map_all;
    int z=0;
    int &i=z;
    string hashid,ID;
    Info ReadyToRead;
    set<Info> NeedToRead;
    set<Info> NeedToCut;
    /***********读取历史纪录**************/
    FILE* historyRead=fopen("D:\\123.txt","r");
    string  HisRead;
    char    read_file_his[LENGTH];
    if(historyRead==NULL)
    {
        cout<<"错误，无法检测到历史纪录"<<endl;
        return 0;
    }
    Info Buf_read;
    while(!feof(historyRead))
    {
        fscanf(historyRead,"%s",read_file_his);
        HisRead=read_file_his;
        Buf_read.readLine(HisRead);
        Map_all[Buf_read.ID]=Buf_read;
        Buf_read.clear();
        i++;
    }
    fclose(historyRead);
    historyRead=fopen("D:\\NextHashToRead.txt","r");
    if(historyRead==NULL)
    {
        cout<<"错误，无法检测到已读取纪录"<<endl;
        return 0;
    }
    else
    {
        while(!feof(historyRead))
        {
            fscanf(historyRead,"%s",read_file_his);//应该用fscanf，以避免读取到换行符，而且fgets读取到的换行符还没法检测！！！
            if(read_file_his[0]!='\0'||read_file_his[0]!='\n')
            {
                continue;
            }
            ReadyToRead.HashID=read_file_his;
            fscanf(historyRead,"%s",read_file_his);
            ReadyToRead.ID=read_file_his;
            fscanf(historyRead,"%s",read_file_his);
            ReadyToRead.follower=read_file_his;
            NeedToRead.insert(ReadyToRead);
            NeedToCut.insert(ReadyToRead);//无意义，只是为了能让程序运行起来。
            ReadyToRead.clear();
        }

    }
    fclose(historyRead);
    /*************读取完毕**************/

/**/
   // hashid="57842aac37ccd0de3965f9b6e17cb555";
   // hashid="172bdd3dc7eb563194150c423a6014d4";
  //  ID="yao-ze-yuan";
  //  ID="gayscript";


    map<string,Info> &y=Map_all;


/*

    ReadyToRead.ID=ID;

    ReadyToRead.Name="GayScript";

    ReadyToRead.HashID=hashid;


    ReadyToRead.follower=convertToChar(3300);

    NeedToRead.insert(ReadyToRead);
    NeedToCut.insert(ReadyToRead);*/


    while(NeedToCut.size()!=0)
    {
    NeedToCut= Read(NeedToRead,y);
    NeedToRead=cut(NeedToCut,y,i);
    /************备份数据*************/
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


    if(!NeedToRead.empty())
    {
        SavetoFile = fopen("d:\\NextHashToRead.txt","w");
        string k("1");
        set<Info>::iterator ak=NeedToRead.begin();
        while (ak!=NeedToRead.end()) {
            k=ak->HashID+"\n"+ak->ID+" \n"+ak->follower+"\n";
            fputs(k.c_str(),SavetoFile);
            ak++;
        }
        fclose(SavetoFile);
    }
    /************备份完成***************/

    }
    /************备份数据*************/
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
    /************备份完成***************/
    cout<<"Zhihu has readen"<<endl;
    return 0;
}

