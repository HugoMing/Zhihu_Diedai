import threading
import os
import sys
import urllib.request
import urllib.parse
import gzip
import json#处理知乎返回的数据
import sys
import time

#########################################################
def READZHIHU(def_NULL,def_HashID,def_ID,def_Begin,def_End,def_FileName,def_NoName):
    global ThreadCount
    global ErrorCount 
    ThreadCount+=1
    #print("NULL =       "+def_NULL)
    #print("def_HashID=  "+def_HashID)
    #print("def_Begin=   "+def_Begin )
    #print("def_End=     "+def_End )
    '''print("def_FileName ="+ def_FileName)
    print("def_NoName = "+def_NoName )'''
    _xsrf ='70d29039e3e8481387e68ca8b5d24c55'#黄中华的浏览器标识符
    hashid=def_HashID
    save=''#保存全部数值
    PostHeader={
'Host':' www.zhihu.com'

,'User-Agent':' Mozilla/5.0 (Windows NT 6.1; WOW64; rv:24.0) Gecko/20100101 Firefox/24.0'

,'Accept':' */*'

,'Accept-Language':' zh-cn,zh;q=0.8,en-us;q=0.5,en;q=0.3'

,'Accept-Encoding':' gzip, deflate'

,'Content-Type':' application/x-www-form-urlencoded; charset=UTF-8'

,'X-Requested-With':' XMLHttpRequest'

,'Cookie':' q_c1=084fdb2c2b2043cd927c0d05e53c30f0|1382849503000|1382849503000; __utma=51854390.1660221720.1382715035.1383140776.1383148468.21; __utmz=51854390.1383148468.21.8.utmcsr=zhihu.com|utmccn=(referral)|utmcmd=referral|utmcct=/people/gayscript; zata=zhihu.com.084fdb2c2b2043cd927c0d05e53c30f0.82107; _ga=GA1.2.1660221720.1382715035; __utmv=51854390.100-1|2=registration_date=20130127=1^3=entry_date=20130127=1; q_c0="NTc1Mjk3OTkxMmM1NzU1N2MzZGQ5ZTMzMzRmNWVlMDR8MW9xU3hPdDF4U29BQlc4Qg==|1382855898|fa049faa61650e88122b85ede1872ddc5492ec3d"; _xsrf=70d29039e3e8481387e68ca8b5d24c55; __utmc=51854390; zatb=zhihu.com; __utmb=51854390.2.10.1383148468'

,'Connection':' keep-alive'

,'Pragma':' no-cache'

,'Cache-Control':' no-cache'
}
    k={'msg':[1,2,3,4,5,1,2,3,4,5]}
    Begin=int(def_Begin)
    End  =int(def_End)
    #print("Read "+def_ID+"'s Follower ing "+"Range From "+str(Begin)+" to "+str(End))
    #print("Range From "+str(Begin)+" to "+str(End))
    #print("File Name is "+str(def_FileName))
    filecontent=['begin']
    charstring=''
    try:
        while(Begin<End):
            url     =   "http://www.zhihu.com/node/ProfileFollowersListV2"
            date1   =   'method=next&params={"hash_id":"'+hashid+'","order_by":"created","offset":'+str(Begin)+'}'+'&_xsrf='+_xsrf
            date1   =    urllib.parse.quote(date1).replace("%3D","=").replace("%26","&")
            date1   =    date1.encode(encoding="utf-8")
            #print("date1=")
            #print(date1)
            Post  =urllib.request.Request(url,data=date1,headers=PostHeader)
            f = urllib.request.urlopen(Post)
            if f.info().get('Content-Encoding') == 'gzip':
                k=gzip.decompress(f.read())
                k=k.decode('gb18030')
                k=json.loads(k)
                filecontent=k.get('msg')[:]
                charstring+="".join(filecontent)
            else:
                filecontent=""
            f.close()
            #print(filecontent)
            #Begin每次至少会加10，所以不用担心
            Begin+=len(k.get('msg'))
            #print(str(Begin)+" people has been read")
    except:
            ErrorCount +=1
            print("Error  at "+def_ID+" part "+def_FileName+" good luck")
            pass
    save=charstring
            #print(def_ID+"has readen")


    file=open(def_FileName,'wb')
    file.write(save.encode('gb18030'))
    file.close()
    #print(def_FileName+" has writen")
    ThreadCount-=1
    return
#print(ID+" 's Follower Part"++"has been read")
#########################################################
ThreadCount=0
ErrorCount =0
thread=[]
f =open("d:\pyRead.txt","r");
lines = f.readlines(100000)
while  lines:
    for line in lines:
        #print(line)
        buffer=line.split("\n")
        line="".join(buffer)+"##"
        #print(line)
        hang = line.split("$")
        for    content  in  hang:
                paramter =   content.split("##")
                thread.append(threading.Thread(target=READZHIHU,args=paramter))
                
    lines = f.readlines(100000)
i=0
tcountappend=len(thread)-50
print("Thread begin and all of thread number is "+str(len(thread)))
for k in thread:
    i+=1
    if ThreadCount <70:
        k.start()
    else:
        while ThreadCount >=70:
            time.sleep(5)
        k.start()
    if i%50==0  :      
        print(str(i)+" process has done")    
print("All Error is"+str(ErrorCount))        
while ThreadCount>10 :
    print("Process nearly end,Now there are "+str(ThreadCount)+"thread running ")
    time.sleep(15)
