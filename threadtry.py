import threading
import time
import os
import sys

def  run(iz):
    os.system("C:\\Users\Administrator\Documents\GitHub\Zhihu_Diedai\Reader.py "+iz)
    return
string=sys.argv[1]
thread=[]

hang=[""]

string=string.replace("##","    ")
hang=string.split("$")

for i in hang:
    i.replace("##","  ")


for i in hang:
    #print(i)
    thread.append(threading.Thread(target=run,args=[i,]))
for k in thread:
    k.start()


    


