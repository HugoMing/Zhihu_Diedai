import urllib.request
import urllib.parse
import gzip
import json#处理知乎返回的数据
import sys

def_HashID  =sys.argv[1]
def_ID    =sys.argv[2]
def_Begin   =sys.argv[3]
def_End     =sys.argv[4]
def_FileName =sys.argv[5]
#print("hashID=" +def_HashID)
#print("def_FileName="+def_FileName)
print("def_Begin="+def_Begin)
_xsrf ='70d29039e3e8481387e68ca8b5d24c55'#黄中华的浏览器标识符
hashid=def_HashID
#ID=def_Id
save=''#保存全部数值
PostHeader={
'Host':' www.zhihu.com'

,'User-Agent':' Mozilla/5.0 (Windows NT 6.1; WOW64; rv:24.0) Gecko/20100101 Firefox/24.0'

,'Accept':' */*'

,'Accept-Language':' zh-cn,zh;q=0.8,en-us;q=0.5,en;q=0.3'

,'Accept-Encoding':' gzip, deflate'

,'Content-Type':' application/x-www-form-urlencoded; charset=UTF-8'

,'X-Requested-With':' XMLHttpRequest'

#,'Referer':' http://www.zhihu.com/people/'+ID+'/followers'#测试，看去掉这个后是否还能继续读取

#,'Content-Length':' 172'#当数值从80变为100时，内容长度应该加一。。。之前一直都忘了，我勒个去

,'Cookie':' q_c1=084fdb2c2b2043cd927c0d05e53c30f0|1382849503000|1382849503000; __utma=51854390.1660221720.1382715035.1382861327.1382878945.15; __utmz=51854390.1382861327.14.6.utmcsr=zhihu.com|utmccn=(referral)|utmcmd=referral|utmcct=/question/21013006; zata=zhihu.com.084fdb2c2b2043cd927c0d05e53c30f0.691925; _ga=GA1.2.1660221720.1382715035; __utmv=51854390.100-1|2=registration_date=20130127=1^3=entry_date=20130127=1; q_c0="NTc1Mjk3OTkxMmM1NzU1N2MzZGQ5ZTMzMzRmNWVlMDR8MW9xU3hPdDF4U29BQlc4Qg==|1382855898|fa049faa61650e88122b85ede1872ddc5492ec3d"; _xsrf=70d29039e3e8481387e68ca8b5d24c55; __utmb=51854390.16.10.1382878945; __utmc=51854390; zatb=zhihu.com'

,'Connection':' keep-alive'

,'Pragma':' no-cache'

,'Cache-Control':' no-cache'
}
k={'msg':[1,2,3,4,5,1,2,3,4,5]}
Begin=int(def_Begin)
End  =int(def_End)
print("Read Follower ing")
print("Range From "+str(Begin)+" to "+str(End))
print("File Name is"+str(def_FileName))
filecontent=['begin']
charstring=''
while((len(k.get('msg'))==10 or len(k.get('msg'))==20 )and (len(filecontent)!=0) and(Begin<End)):
    url     =   "http://www.zhihu.com/node/ProfileFollowersListV2"
    oof     =   '%d' %Begin
    date1   =   'method=next&params={"hash_id":"'+hashid+'","order_by":"created","offset":'+oof+'}'+'&_xsrf='+_xsrf
    date1   =    urllib.parse.quote(date1).replace("%3D","=").replace("%26","&")
    date1   =    date1.encode(encoding="utf-8")
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
    Begin+=len(k.get('msg'))
    print(str(Begin)+" people has been read")
    save=charstring
#print(def_ID+"has readen")


file=open(def_FileName,'wb')
file.write(save.encode('gb18030'))
file.close()
#print(ID+" 's Follower Part"++"has been read")
