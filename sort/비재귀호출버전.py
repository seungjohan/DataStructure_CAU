import random
from copy import copy
import time

# 스택 구현

class Stack:
    def __init__(self):
        self.items = []

    def push(self, val):
        self.items.append(val)

    def pop(self):
        try:
            return self.items.pop()
        except IndexError:
            print("Stack is empty")

    def top(self):
        try:
            return self.items[-1]
        except:
            print("Stack is empty")

    def __len__(self):
        return len(self.items)

    def isEmpty(self):
        return self.__len__() == 0

# 퀵 정렬 (재귀 사용)
def RQuickSort(arr):
    
    if len(arr) <= 1:
        
        return arr

    pivot = arr[len(arr) // 2]

    left = [x for x in arr if x < pivot]

    middle = [x for x in arr if x == pivot]

    right = [x for x in arr if x > pivot]

    return RQuickSort(left) + middle + RQuickSort(right)

# 재귀 호출을 쓰지 않는 퀵 정렬 

def SQuickSort(input):
    pivotIndex = 0
    leftIndex = pivotIndex + 1
    rightIndex = len(input) - 1

    s = Stack()
    
    s.push(pivotIndex)
    s.push(rightIndex)

    while len(s.items) > 0:

        rightIndexOfSubSet = s.pop()
        leftIndexOfSubSet = s.pop()

        leftIndex = leftIndexOfSubSet + 1
        pivotIndex = leftIndexOfSubSet
        rightIndex = rightIndexOfSubSet
    
        pivot = input[pivotIndex]

        if leftIndex > rightIndex:
            continue

        while leftIndex < rightIndex:
            while (leftIndex <= rightIndex) and (input[leftIndex] <= pivot):
                leftIndex += 1

            while (leftIndex <= rightIndex) and (input[rightIndex] >= pivot):
                rightIndex -= 1

            if rightIndex >= leftIndex:
                SwapElement(input, leftIndex, rightIndex)


        if pivotIndex <= rightIndex:
            if input[pivotIndex] > input[rightIndex]:
                SwapElement(input, pivotIndex, rightIndex)

        if leftIndexOfSubSet < rightIndex:
            s.push(leftIndexOfSubSet)
            s.push(rightIndex - 1)

        if rightIndexOfSubSet > rightIndex:
            s.push(rightIndex + 1)
            s.push(rightIndexOfSubSet)

def SwapElement(arr, left, right):
    temp = arr[left]
    arr[left] = arr[right]
    arr[right] = temp




stuGroup = []
stuInfo = [0, 0, 0]
stuNum = 50000
interval = 500


for i in range(stuNum):

    ID = '20'
    
    randNum = random.randint(13, 19)

    ID += str(randNum)

    for i in range(5):

        randNum = random.randint(0,9)
    
        ID += str(randNum)

    stuInfo[0] = int(ID)

    name = chr(random.randint(65,90))

    for i in range(9):

        randNum = random.randint(65, 90)
        
        name += chr(randNum)

    stuInfo[1] = name
    
    telNum = '010'

    for i in range(8):

        randNum = random.randint(0, 9)

        telNum += str(randNum)

    stuInfo[2] = telNum
    
    stuGroup.append(copy(stuInfo))


RQstuGroup = copy(stuGroup)

timeB = time.time()

RQstuGroup = RQuickSort(RQstuGroup)

timeA = time.time()

timeForR = timeA - timeB

print('퀵 정렬(재귀 사용)하는데 걸린 시간은:', timeForR, '초 입니다.')

for i in range(0, stuNum, interval):
    print(RQstuGroup[i])
print()



SQstuGroup = copy(stuGroup)

timeB = time.time()

SQuickSort(SQstuGroup)

timeA = time.time()

timeForS = timeA - timeB

print('퀵 정렬(재귀 사용 X)하는데 걸린 시간은:', timeForS, '초 입니다.')

for i in range(0, stuNum, interval):
    print(SQstuGroup[i])
print()

if timeForR < timeForS:
    print('재귀 호출을 사용한 퀵 정렬이', timeForS-timeForR ,'초 더 빠릅니다.')
elif timeForS < timeForR:
    print('재귀 호출을 사용하지 않은 퀵 정렬이', timeForR-timeForS ,'초 더 빠릅니다.')
else:
    print('속도가 같습니다.')
