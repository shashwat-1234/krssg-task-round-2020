import socket 
import pickle
import threading

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('127.0.0.1', 8082))
s.listen(100)

conn, addr = s.accept()
conn.send(bytes("number of minions:", "utf-8"))

numini = conn.recv(16)
m = pickle.loads(numini)

conn.send(bytes("type your array", "utf-8"))

data = conn.recv(1024)
given_array = pickle.loads(data)
print( given_array )
n = len( given_array )
k = int(n/m)
z = n%m
sum_list = []
thread_list = []
minionl = []

for q in range(m-z):
	x = k
	minionl.append(k)

for p in range(m-z, m):
	q = k+1
	minionl.append(q)

def on_minion(i, g):
	minionsocket_i, address_i = s.accept()
	minilst = []
	
	for j in range(k+g):
		minilst.append(given_array[i+j])

	minionlist_send = pickle.dumps(minilst)
	minionsocket_i.send(minionlist_send)
	before_sum = minionsocket_i.recv(256)
	sume = pickle.loads(before_sum)
	sum_list.append(sume)

for a in range(m-z):
	t_a = threading.Thread(target = on_minion, args = (a*k,0,))
	thread_list.append(t_a)
	t_a.start()

for a in range(m-z, m-z+1):
	t_a = threading.Thread(target = on_minion, args = (a*k,1,))
	thread_list.append(t_a)
	t_a.start()

for a in range(m-z+1,m):
	t_a = threading.Thread(target = on_minion, args = ((a*k)+1,1,))
	thread_list.append(t_a)
	t_a.start()	

for a in range(k):
	k_a = thread_list[a]
	print(2)
	k_a.join()
	print( 1 )	

print( sum_list )
summation = sum(sum_list)

print('' + str(summation) )
to_send = pickle.dumps(summation)
conn.send(to_send)

