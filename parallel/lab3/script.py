import subprocess
s = [5, 10, 100,500,1000,5000,10000]
n_p = [1,2,4,8,16,32]
for i in s:
	for j in n_p:
		a="time ./matmul_parallel "+str(i)+" "+str(j)
		subprocess.call(a,shell=True)
