// ConsoleApplication6.cpp : 定义控制台应用程序的入口点。
//
//#include <thread>
#include "handle.h"


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
    FILE* historyRead=fopen("D:\\ZhihuMap.txt","r");//试试改用SSD速度能快点不,SSD读取24M的时候24秒 ， 机械硬盘也是24秒。表示不是读取的问题
    string  HisRead;
    char    read_file_his[LENGTH];
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
            Map_all[Buf_read.ID]=Buf_read;
            Buf_read.clear();
            i++;
        }
        fclose(historyRead);
    }
    historyRead=fopen("D:\\NextHashToRead.txt","r");
    int test=1;
    if(historyRead==NULL)
    {
        cout<<"错误，无法检测到已读取纪录"<<endl;
        return 0;
    }
    else
    {
        while(!feof(historyRead))
        {
            //test++;
            fscanf(historyRead,"%s",read_file_his);//应该用fscanf，以避免读取到换行符，而且fgets读取到的换行符还没法检测！！！but fscanf读取不到‘\t’所以必须要用==去判断是否已读取之文件结尾
            ReadyToRead.HashID=read_file_his;
            //cout<<read_file_his<<endl;
            fgets(read_file_his,LENGTH,historyRead);//去除\r\n囧
            fgets(read_file_his,LENGTH,historyRead);//当ID间存在空格时，会导致读取失败，所以，这里也应该用fgets！
            ReadyToRead.ID=read_file_his;
            if(ReadyToRead.ID.length()>=2)
            {
                ReadyToRead.ID.erase((ReadyToRead.ID.length()-2),(ReadyToRead.ID.length()-1));
            }
            //cout<<ReadyToRead.ID<<" test="<<test<<endl;
            fscanf(historyRead,"%s",read_file_his);
            ReadyToRead.follower=read_file_his;
            //cout<<read_file_his<<endl;
            //cout<<"**********************************"<<endl;

            if(ReadyToRead.HashID==ReadyToRead.ID&&ReadyToRead.ID==ReadyToRead.follower)
            {
                continue;
            }
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
    int NeedCut=0;

    map<string,Info> &y=Map_all;
    while(NeedToCut.size()!=0)
    {
    int ibuffer=i;
    NeedCut= Read(NeedToRead,y);
    NeedToRead=cut(NeedCut,y,i);
    cout<<i-ibuffer<<" has been added"<<endl;
    ibuffer=i;
    /************备份数据*************/
    map<string,Info>::iterator readmap;
    FILE* SavetoFile;
    SavetoFile=fopen("D:\\ZhihuMap.txt","w+");
    string SavetoFile_String;
    for(readmap = Map_all.begin();readmap!=Map_all.end();readmap++)
    {
        SavetoFile_String=(readmap->second).content();
        fputs(SavetoFile_String.c_str(),SavetoFile);
    }
    fclose(SavetoFile);


    if(!NeedToRead.empty())
    {
        SavetoFile = fopen("d:\\NextHashToRead.txt","w");
        string k("1");
        set<Info>::iterator ak=NeedToRead.begin();
        while (ak!=NeedToRead.end())
        {
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
    SavetoFile=fopen("d:\\ZhihuMap.txt","w+");
    string SavetoFile_String;
    for(readmap = Map_all.begin();readmap!=Map_all.end();readmap++)
    {
        (readmap->second).show();
        SavetoFile_String=(readmap->second).content();
        fputs(SavetoFile_String.c_str(),SavetoFile);
    }
    fclose(SavetoFile);
    /************备份完成***************/
    cout<<"Zhihu has readen"<<endl;
    return 0;
}

