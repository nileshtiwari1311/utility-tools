# the filename here means the filename without extension, e.g. 'file 1' in 'file 1.txt' 
bad_chars = ['|', '/', '<', '>', ':', '\"', '\\', '?', '*', '%']
avoidable_chars = ['.', ',', ';', '=', '#', '&', '{', '}', '[', ']', '$', '!', '\'', '@', '+', '`', '~']

filename = ' .xyz | abcd : no. 1 '

modFileName = filename.strip()
modFileName = ''.join(i for i in filename if not i in bad_chars)
modFileName = ' '.join(modFileName.split())

print('\''+filename+'\'')
print('\''+modFileName+'\'')