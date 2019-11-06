import math

f = open("data.txt","w")
nData = 50
f.write(str(nData)+'\n')
for i in range(nData):
    f.write(str(i%10)+"\n")

f.close()