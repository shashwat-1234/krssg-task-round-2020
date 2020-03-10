import socket 
import pickle
import sys

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('127.0.0.1', 8082))

mes1 = s.recv(32)
print( mes1 )
numini = int(input())
m = pickle.dumps(numini)
s.send(m)

mes = s.recv(32)
print( mes )

lst = []

n = int(input("enter: "))

for i in range(int(n)):
	ele = int(input())
	lst.append(ele)

msg1 = pickle.dumps(lst)
s.send(msg1)

k1 = s.recv(16)

answer = pickle.loads(k1)

print(str(answer))



