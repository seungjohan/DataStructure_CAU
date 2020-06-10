import random
from copy import copy
import time

# 선택 정렬
def SearchMin(arr):

    num = len(arr)

    minIndex = 0

    for i in range(1, num):
        if arr[i] < arr[minIndex]:
            minIndex = i

    return minIndex

def SortMin(arr):

    a = []

    while arr:
        minIndex = SearchMin(arr)
        value = arr.pop(minIndex)
        a.append(value)
    return a

# 퀵 소트
def QuickSort(arr):
    if len(arr) <= 1:
        return arr

    pivot = arr[len(arr) // 2]

    left = [x for x in arr if x < pivot]

    middle = [x for x in arr if x == pivot]

    right = [x for x in arr if x > pivot]

    return QuickSort(left) + middle + QuickSort(right)

# 힙 정렬
def HeapSort(arr):
    size = len(arr)
    for i in range(size, -1, -1): Heapify(arr, size, i)
    for i in range(size-1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]
        Heapify(arr, i, 0)

def Heapify(arr, size, i):
    largest = i
    L = 2*i + 1
    R = 2*i + 2
    if L<size and arr[i]<arr[L]: largest = L
    if R<size and arr[largest]<arr[R]: largest = R
    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]
        Heapify(arr, size, largest)



'''
다음의 구성을 가진 데이터 5만 명분을 랜덤하게 생성한다.
1. 학번(13-19년도에 입학한 학생의 9자리 숫자),  2. 이름(10자 크기의 영문자 임의의 문자), 3. 전화번호(010 으로 시작하는 11자리 숫자)
'''

'''
아스키 코드
'A': 65
'Z': 90
'''

# 학번 정렬을 위한 리스트.
stuGroup = []
stuInfo = [0, 0, 0]

# 이름 정렬을 위한 리스트.
stuGroup2 = []
stuInfo2 = [0, 0, 0]

# 만들 데이터 갯수.
stuNum = 50000
# 표시할 간격.
interval = 500


# stuInfo 에선 학번을 기준으로 데이터가 저장되고, stuInfo2 에선 이름을 기준으로 데이터가 저장된다.
for i in range(stuNum):

    # 학번 랜덤 생성. 앞은 2013~2019의 패턴을 지키며.    
    ID = '20'

    randNum = random.randint(13, 19)

    ID += str(randNum)

    for i in range(5):

        randNum = random.randint(0,9)

        ID += str(randNum)

    stuInfo[0] = int(ID)
    stuInfo2[1] = int(ID)

    # 이름 랜덤 생성. 'A' - 'Z'의 아스키 코드가 65 - 90 임을 이용해 생성.
    name = chr(random.randint(65,90))

    for i in range(9):

        randNum = random.randint(65, 90)

        name += chr(randNum)

    stuInfo[1] = name
    stuInfo2[0] = name

    # 전화번호 랜덤 생성.
    telNum = '010'

    for i in range(8):

        randNum = random.randint(0, 9)

        telNum += str(randNum)

    stuInfo[2] = telNum
    stuInfo2[2] = telNum

    # stuGroup에는 학번 기준으로 넣어진 데이터들 저장.
    stuGroup.append(copy(stuInfo))
    
    # stuGroup2에는 이름 기준으로 넣어진 데이터를 저장.
    stuGroup2.append(copy(stuInfo2))


print('***학번으로 정렬***\n')

SstuGroup = copy(stuGroup)

timeB = time.time()

SstuGroup = SortMin(SstuGroup)

timeA = time.time()

print('선택 정렬하는데 걸린 시간은:', timeA - timeB, '초 입니다.')

InstuGroup = sorted(SstuGroup, key = lambda student: SstuGroup[i], reverse = True)

timeC = time.time()

print('선택 정렬하는데 내장된 정렬방법과의 시간차:', timeC - (timeA - timeB), '초 입니다.')

for i in range(0, stuNum, interval):
    print(SstuGroup[i])

print()





QstuGroup = copy(stuGroup)

timeB = time.time()

QstuGroup = QuickSort(QstuGroup)

timeA = time.time()

print('퀵 정렬하는데 걸린 시간은:', timeA - timeB, '초 입니다.')

InstuGroup = sorted(QstuGroup, key = lambda student: QstuGroup[i], reverse = True)

timeC = time.time()

print('퀵 정렬하는데 내장된 정렬방법과의 시간차:', timeC - (timeA - timeB), '초 입니다.')

for i in range(0, stuNum, interval):
    print(QstuGroup[i])

print()





HstuGroup = copy(stuGroup)

timeB = time.time()

HeapSort(HstuGroup)

timeA = time.time()

print('힙 정렬하는데 걸린 시간은:', timeA - timeB, '초 입니다.')

InstuGroup = sorted(SstuGroup, key = lambda student: SstuGroup[i], reverse = True)

timeC = time.time()

print('힙 정렬하는데 내장된 정렬방법과의 시간차:', timeC - (timeA - timeB), '초 입니다.')

for i in range(0, stuNum, interval):
    print(HstuGroup[i])

print()





print('***이름으로 정렬***\n')

SstuGroup2 = copy(stuGroup2)

timeB = time.time()

SstuGroup2 = SortMin(SstuGroup2)

timeA = time.time()

print('선택 정렬하는데 걸린 시간은:', timeA - timeB, '초 입니다.')


InstuGroup = sorted(SstuGroup, key = lambda student: SstuGroup[i], reverse = True)

timeC = time.time()

print('선택 정렬하는데 내장된 정렬방법과의 시간차:', timeC - (timeA - timeB), '초 입니다.')

for i in range(0, stuNum, interval):
    print(SstuGroup2[i])

print()





QstuGroup2 = copy(stuGroup2)

timeB = time.time()

QstuGroup2 = QuickSort(QstuGroup2)

timeA = time.time()

print('퀵 정렬하는데 걸린 시간은:', timeA - timeB, '초 입니다.')

InstuGroup = sorted(SstuGroup, key = lambda student: SstuGroup[i], reverse = True)

timeC = time.time()

print('퀵 정렬하는데 내장된 정렬방법과의 시간차:', timeC - (timeA - timeB), '초 입니다.')

for i in range(0, stuNum, interval):
    print(QstuGroup2[i])

print()





HstuGroup2 = copy(stuGroup2)

timeB = time.time()

HeapSort(HstuGroup2)

timeA = time.time()

print('힙 정렬하는데 걸린 시간은:', timeA - timeB, '초 입니다.')


InstuGroup = sorted(SstuGroup, key = lambda student: SstuGroup[i], reverse = True)

timeC = time.time()

print('힙 정렬하는데 내장된 정렬방법과의 시간차:', timeC - (timeA - timeB), '초 입니다.')

for i in range(0, stuNum, interval):
    print(HstuGroup2[i])



print('20160499 한승조')
