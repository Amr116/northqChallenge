def RemovesNthDupicate(array, n):
    hashTable = {}
    i = 0
    while i < len(array):
        if array[i] in hashTable:
            hashTable[array[i]] += 1
            
            if hashTable[array[i]] == n:
                hashTable[array[i]] = 1                
                array.pop(i)
        else:
            hashTable[array[i]] = 1

        i += 1
    return array
