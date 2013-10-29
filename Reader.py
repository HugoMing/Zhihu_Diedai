import urllib.request
import urllib.parse
from http  import cookies
from http.cookiejar import CookieJar
import gzip
import json#处理知乎返回的数据
import string#字符串转换
import time#休眠，模拟浏览器
import sys
'''
tk          ='q_c1=084fdb2c2b2043cd927c0d05e53c30f0|1382849503000|1382849503000;__utma=51854390.1660221720.1382715035.1382837316.1382849712.12;__utmz=51854390.1382837316.10.5.utmcsr=zhihu.com|utmccn=(referral)|utmcmd=referral|utmcct=/people/blueblood/followers;zata=zhihu.com.084fdb2c2b2043cd927c0d05e53c30f0.914346;_ga=GA1.2.1660221720.1382715035;__utmv=51854390.100-1|2=registration_date=20130127=1^3=entry_date=20130127=1;_xsrf=951059d8bbab42018d797aca0fcbdd53;__utmc=51854390;checkcode=$2a$10$V1RmQUQdM7astC.5u8VxluinlaYAtELD3lkYi6oXs14QaxFmY8ac2;q_c0="NTc1Mjk3OTkxMmM1NzU1N2MzZGQ5ZTMzMzRmNWVlMDR8MW9xU3hPdDF4U29BQlc4Qg==|1382855898|fa049faa61650e88122b85ede1872ddc5492ec3d";__utmb=51854390.5.10.1382849712;zatb=zhihu'
url1         ='http://www.zhihu.com/people/yao-ze-yuan/followers'
header1      ={'Host':'www.zhihu.com'
,'User-Agent':"Mozilla/5.0(WindowsNT6.1;WOW64;rv':'24.0)Gecko/20100101Firefox/24.0"
,"Cookie":tk
,'Accept':'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8'
,'Accept-Language':'zh-cn,zh;q=0.8,en-us;q=0.5,en;q=0.3'
,'Accept-Encoding':'gzip,deflate'
,'Connection':'keep-alive'
,'Cache-Control':'max-age=0'}
req = urllib.request.Request(url=url1,headers=header1)
f = urllib.request.urlopen(req)

if f.info().get('Content-Encoding') == 'gzip':
    print("gzip")
    file=open("c:/2.txt",'wb')
    k=gzip.decompress(f.read())
    file.write(k)
    file.close() 
    print(k[3:4])
    hashid_yao='57842aac37ccd0de3965f9b6e17cb555'#姚泽源的hashID
    hashid='e385231c82d1e73e8a3352214be3defb'#yskin的hash
'''

def_HashID =sys.argv[1]
def_Id=sys.argv[2]
Flag    =sys.argv[3]
#Flag=int(Flag)
#print("firest="+def_HashID)
#print("end="+ Flag)
if 1:
    _xsrf ='70d29039e3e8481387e68ca8b5d24c55'#黄中华的浏览器标识符
    ID='yskin'#不必要
    hashid=def_HashID
    ID=def_Id
    save=''#保存全部数值
    PostHeader={
'Host':' www.zhihu.com'

,'User-Agent':' Mozilla/5.0 (Windows NT 6.1; WOW64; rv:24.0) Gecko/20100101 Firefox/24.0'

,'Accept':' */*'

,'Accept-Language':' zh-cn,zh;q=0.8,en-us;q=0.5,en;q=0.3'

,'Accept-Encoding':' gzip, deflate'

,'Content-Type':' application/x-www-form-urlencoded; charset=UTF-8'

,'X-Requested-With':' XMLHttpRequest'

,'Referer':' http://www.zhihu.com/people/'+ID+'/followers'

#,'Content-Length':' 172'#当数值从80变为100时，内容长度应该加一。。。之前一直都忘了，我勒个去

,'Cookie':' q_c1=084fdb2c2b2043cd927c0d05e53c30f0|1382849503000|1382849503000; __utma=51854390.1660221720.1382715035.1382861327.1382878945.15; __utmz=51854390.1382861327.14.6.utmcsr=zhihu.com|utmccn=(referral)|utmcmd=referral|utmcct=/question/21013006; zata=zhihu.com.084fdb2c2b2043cd927c0d05e53c30f0.691925; _ga=GA1.2.1660221720.1382715035; __utmv=51854390.100-1|2=registration_date=20130127=1^3=entry_date=20130127=1; q_c0="NTc1Mjk3OTkxMmM1NzU1N2MzZGQ5ZTMzMzRmNWVlMDR8MW9xU3hPdDF4U29BQlc4Qg==|1382855898|fa049faa61650e88122b85ede1872ddc5492ec3d"; _xsrf=70d29039e3e8481387e68ca8b5d24c55; __utmb=51854390.16.10.1382878945; __utmc=51854390; zatb=zhihu.com'

,'Connection':' keep-alive'

,'Pragma':' no-cache'

,'Cache-Control':' no-cache'
        }
    k={'msg':[1,2,3,4,5,1,2,3,4,5]}
    offset=0
    if Flag is '1':#需要同时读取关注者和被关注者
        #读取其关注的人
        print("Read Follower ing")
        filecontent=['begin']
        charstring='' 
        while((len(k.get('msg'))==10 or len(k.get('msg'))==20 )and (len(filecontent)!=0) ):
            url   ="http://www.zhihu.com/node/ProfileFollowersListV2"
            oof   ='%d' %offset
            date1  ='method=next&params={"hash_id":"'+hashid+'","order_by":"created","offset":'+oof+'}'+'&_xsrf='+_xsrf
            date1  =  urllib.parse.quote(date1).replace("%3D","=").replace("%26","&")
            date1  =  date1.encode(encoding="utf-8")
            Post  =urllib.request.Request(url,data=date1,headers=PostHeader)
            f = urllib.request.urlopen(Post)
            if f.info().get('Content-Encoding') == 'gzip':
                k=gzip.decompress(f.read())
                k=k.decode('gb18030')
                k=json.loads(k)
                filecontent=k.get('msg')[:]
                #print(len(k.get('msg')))
                charstring+="".join(filecontent)
                #print("charlength=")
                #print(len(charstring))
                #print('filecontent gzip='+str(len(filecontent)))
            else:
                filecontent=""
                #print('filecontent='+str(len(filecontent)))
            
            offset+=len(k.get('msg'))
            print(oof+" people has been read")
        save=charstring
        charstring=""
    ######################################
    filecontent=['begin']
    charstring=''
    buf=""
    print("Read Followee ing")
    while((len(k.get('msg'))==10 or len(k.get('msg'))==20) and( len(filecontent)!=0) ):
        url   ="http://www.zhihu.com/node/ProfileFolloweesListV2"
        oof   ='%d' %offset
        date1  ='method=next&params={"hash_id":"'+hashid+'","order_by":"created","offset":'+oof+'}'+'&_xsrf='+_xsrf
        date1  =  urllib.parse.quote(date1).replace("%3D","=").replace("%26","&")
        date1  =  date1.encode(encoding="utf-8")
        Post  =urllib.request.Request(url,data=date1,headers=PostHeader)
        f = urllib.request.urlopen(Post)
        if f.info().get('Content-Encoding') == 'gzip':
            k=gzip.decompress(f.read())
            k=k.decode('gb18030')
            k=json.loads(k)
            filecontent=k.get('msg')[:]
            #print(len(k.get('msg')))
            charstring+="".join(filecontent)
            #print("charlength=")
            #print(len(charstring))
            #print(len(charstring))
            #print('filecontent gzip='+str(len(filecontent)))
        else:
            filecontent=""
            #print('filecontent='+str(len(filecontent)))
        #print(charstring)
        offset+=len(k.get('msg'))
        print(oof+" people has been read")
    save+=charstring
    file=open("c:/1/"+ID+'.txt','wb')
    file.write(save.encode('gb18030'))
    file.close()
    print(ID+"has been read")
 
#file=open("c:/2.txt",'wb')
#file.write(charstring.encode('utf-8'))
#file.close()
