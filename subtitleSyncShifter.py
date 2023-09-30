# Resync Subtitles
# add fixed delay to a subtitle file (srt encoded in utf-8) from start to end (whole video long)

import re
import sys

def validDelay(delay) :
	return delay.isdecimal() or (delay[0]=='-' and delay[1:].isdecimal())

argSize = len(sys.argv)
if argSize < 4 :
	print("Insufficient arguments. Program requires the following 3 arguments in the order stated - inputFileName, outputFileName, delayInMilliSeconds")
	sys.exit(0)
elif not(isinstance(sys.argv[1], str) and isinstance(sys.argv[2], str) and validDelay(sys.argv[3])) :
	print("Invalid arguments. Program requires the following 3 arguments in the order stated - inputFileName, outputFileName, delayInMilliSeconds")
	sys.exit(0)

inFile = sys.argv[1]
outFile = sys.argv[2]
delayInMS = int(sys.argv[3]) # subtitle delay in milliseconds

f = open(inFile, mode='r', encoding='utf-8-sig')
data = f.read()
f.close()

res = re.split('\n', data)
dataSize = len(res)

counter = 1
outputString = res[0] + '\n'

while counter < dataSize :
	if res[counter-1].isdecimal() and '-->' in res[counter] :
		timeSplit = res[counter].split(' ')
		fromTime = timeSplit[0]
		toTime = timeSplit[2]
		splitList = fromTime.split(':')
		msecList = splitList[2].split(',')
		fromHH = splitList[0]
		fromMM = splitList[1]
		fromSS = msecList[0]
		fromMS = msecList[1]
		splitList = toTime.split(':')
		msecList = splitList[2].split(',')
		toHH = splitList[0]
		toMM = splitList[1]
		toSS = msecList[0]
		toMS = msecList[1]

		fromTimeStamp = int(fromMS) + 1000*(int(fromSS) + 60*(int(fromMM) + 60*int(fromHH)))
		fromTimeStamp += delayInMS
		fromMS = fromTimeStamp%1000
		fromTimeStamp //= 1000
		fromSS = fromTimeStamp%60
		fromTimeStamp //= 60
		fromMM = fromTimeStamp%60
		fromTimeStamp //= 60
		fromHH = fromTimeStamp

		toTimeStamp = int(toMS) + 1000*(int(toSS) + 60*(int(toMM) + 60*int(toHH)))
		toTimeStamp += delayInMS
		toMS = toTimeStamp%1000
		toTimeStamp //= 1000
		toSS = toTimeStamp%60
		toTimeStamp //= 60
		toMM = toTimeStamp%60
		toTimeStamp //= 60
		toHH = toTimeStamp

		fromTime = str(f"{fromHH:02d}") + ":" + str(f"{fromMM:02d}") + ':' + str(f"{fromSS:02d}") + ',' + str(f"{fromMS:03d}")
		toTime = str(f"{toHH:02d}") + ":" + str(f"{toMM:02d}") + ':' + str(f"{toSS:02d}") + ',' + str(f"{toMS:03d}")
		outputString += fromTime + ' --> ' + toTime + '\n'
	else :
		outputString += res[counter] + '\n'
	counter += 1

f = open(outFile, 'w')
f.write(outputString)
f.close()