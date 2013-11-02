import os
import sys
import threading
import time

i = int(sys.argv[1])
print(i)
p=0;
thread=[]
while p<=i:
    thread.append(threading.Thread(target=os.system,args=["C:\Users\Administrator\Documents\GitHub\Zhihu_Diedai\Project1.exe  "+"D:\MeRead"+str(p)+".txt",]))
    p+=1



for k in thread:
    print("1")
    k.start()
    time.sleep(10)
