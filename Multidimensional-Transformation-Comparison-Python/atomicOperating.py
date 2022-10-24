# 首先评估原子操作效率开销,以100bits操作数为例
import random
from line_profiler import LineProfiler

# 数字互素判断
def gcd(a, b) :
    while a != 0:
        a, b = b%a, a
    return b

# 生成互素的两个100比特数字
def generateCoprimeNumber():
    k = 100
    while True:
        operationNumber1 = random.getrandbits(100)
        operationNumber2 = random.getrandbits(100)
        if gcd(operationNumber1, operationNumber2) == 1:
            break
    # 保证operationNumber1 >= operationNumber2
    if operationNumber1 < operationNumber2:
        operationNumber1, operationNumber2 = operationNumber2, operationNumber1
    return operationNumber1, operationNumber2

# 加法/减法运算
def addOperation(operationNumber1, operationNumber2):
    addResult = operationNumber1 + operationNumber2

# 乘法运算
def multOperation(operationNumber1, operationNumber2):
    multiplyResult = operationNumber1*operationNumber2
    return multiplyResult

# 除法运算
def divOperation(operationNumber1, operationNumber2):
    divisionResult = operationNumber1/operationNumber2
    return divisionResult
    
# 模运算
def modOperation(operationNumber1, operationNumber2):
    moduleResult = operationNumber1 % operationNumber2
    return moduleResult

# 辗转相除法求模逆
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
    
    
