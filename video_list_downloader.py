import os
import time

f = open('links.txt', 'r')
links = f.read().split('\n')
f.close()

f = open('names.txt', 'r')
names = f.read().split('\n')
f.close()

n_files = len(links)

for i in range(n_files):
	print('--------------------------------')
	print('Processing Video No ' + str(i+1))
	print('--------------------------------')
	os.system('wget -O ' + names[i] + '.mp4 ' + links[i])
	print('\nSuccess!\n')
	time.sleep(1)