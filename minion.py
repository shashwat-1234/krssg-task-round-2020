import socket 
import pickle
import sys

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('127.0.0.1', 8082))

arr = s.recv(512)
final_arr = pickle.loads(arr)
print(final_arr)

ans = sum(final_arr)
final_ans = pickle.dumps(ans)
print(str(ans))
s.send(final_ans)