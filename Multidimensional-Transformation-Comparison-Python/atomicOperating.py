'''
Author: Blank-vax 15554467517@163.com
Date: 2023-01-30 01:18:07
LastEditors: Blank-vax 15554467517@163.com
LastEditTime: 2023-01-30 11:24:19
FilePath: /FTCR-LMPPDA_Simulation/Multidimensional-Transformation-Comparison-Python/atomicOperating.py
Description: Efficiency evaluation of atomic operations, utilizing the 100 bits operand as an example
'''
import random
from line_profiler import LineProfiler

# Numerical heterogeneity judgment
def gcd(a, b) :
    while a != 0:
        a, b = b%a, a
    return b

# Generate two 100-bit numbers that are coprime
def generateCoprimeNumber():
    k = 100
    while True:
        operationNumber1 = random.getrandbits(100)
        operationNumber2 = random.getrandbits(100)
        if gcd(operationNumber1, operationNumber2) == 1:
            break
    # Ensure operationNumber1 >= operationNumber2
    if operationNumber1 < operationNumber2:
        operationNumber1, operationNumber2 = operationNumber2, operationNumber1
    return operationNumber1, operationNumber2

# Addition and subtraction
def addOperation(operationNumber1, operationNumber2):
    addResult = operationNumber1 + operationNumber2

# Multiplication
def multOperation(operationNumber1, operationNumber2):
    multiplyResult = operationNumber1*operationNumber2
    return multiplyResult

# Division
def divOperation(operationNumber1, operationNumber2):
    divisionResult = operationNumber1/operationNumber2
    return divisionResult
    
# Modulo
def modOperation(operationNumber1, operationNumber2):
    moduleResult = operationNumber1 % operationNumber2
    return moduleResult

# Rollover division method for modulo inverse
def modInverseOperation(operationNumber2, operationNumber1):
    assert gcd(operationNumber2, operationNumber1) == 1
    u1, u2, u3 = 1, 0, operationNumber2
    v1, v2, v3 = 0, 1, operationNumber1
    while v3 != 0:
        q = u3 // v3
        v1, v2, v3, u1, u2, u3 = (u1-q*v1), (u2-q*v2), (u3-q*v3), v1, v2, v3
    return u1%operationNumber1

def main():
    operationNumber1, operationNumber2 = generateCoprimeNumber()
    addOperation(operationNumber1=operationNumber1, operationNumber2=operationNumber2)
    multOperation(operationNumber1=operationNumber1, operationNumber2=operationNumber2)
    divOperation(operationNumber1=operationNumber1, operationNumber2=operationNumber2)
    modOperation(operationNumber1=operationNumber1, operationNumber2=operationNumber2)
    modInverseOperation(operationNumber2=operationNumber2, operationNumber1=operationNumber1)

if __name__ == "__main__":
    lp = LineProfiler()
    
    lp.add_function(addOperation)
    lp.add_function(multOperation)
    lp.add_function(divOperation)
    lp.add_function(modOperation)
    lp.add_function(modInverseOperation)
    
    test_func = lp(main)
    test_func()
    lp.print_stats()
    
    
