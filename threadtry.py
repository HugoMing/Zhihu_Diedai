import threading
import time
import os
import sys

def  run(iz):
    os.system("C:\\Users\Administrator\Documents\GitHub\Zhihu_Diedai\Reader.py "+iz)
    return

string=sys.argv[1]
print()
print(string)
thread=[]

hang=[""]
print()
string=string.replace("##","    ")
hang=string.split("$")
print(hang)
print()
for i in hang:
    i.replace("##","  ")
print()
print("new hang")
print(hang)
print()
for i in hang:
    thread.append(threading.Thread(target=run,args=[i,]))
for k in thread:
    k.start()


    


