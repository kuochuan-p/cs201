data = [1,4,0,5,0,1,3,0,9,0,6,1,1,1,1,1,1,1,7]
def findMaxSumSeq():
        start = 0
        end = 1
        bestPos = 0
        max = 0

        count = 0
        while (end < len(data)):
                while(count <= data[end] and start >= 0):
                    count += data[start]
                    if(count == data[end] and (end-start > max)):
                            max = end-start
                            bestPos = end
                    start -= 1
                end += 1
                start = end-1
                count = 0

        return bestPos

print(findMaxSumSeq())