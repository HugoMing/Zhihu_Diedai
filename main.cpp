// ConsoleApplication6.cpp : 定义控制台应用程序的入口点。
//

#include "handle.h"



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

    Info ReadyToRead;
    set<Info> NeedToRead;
    set<Info> NeedToCut;
    ReadyToRead.ID=ID;
    ReadyToRead.Name="GayScript";
    ReadyToRead.HashID=hashid;
    ReadyToRead.follower=convertToChar(5700);

    NeedToRead.insert(ReadyToRead);
    NeedToCut.insert(ReadyToRead);
    while(NeedToCut.size()!=0)
    {
    NeedToCut= Read(NeedToRead,y);
    NeedToRead=cut(NeedToCut,Map_all);
    }
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

