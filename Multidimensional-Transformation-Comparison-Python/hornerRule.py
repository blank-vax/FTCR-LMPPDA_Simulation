import random
import gmpy2
from line_profiler import LineProfiler


# 生成评估过程所用参数
def paramsGeneration():
    smNumber = 20
    dimensionAccount = 10
    dataUpperBound = 7
    return (smNumber, dimensionAccount, dataUpperBound)

# 生成评估所用随机原始数据
def dataGeneration(dimensionAccount):
    originDataInSmartMeter = []
    for i in range(dimensionAccount):
        originDataInSmartMeter.append(random.getrandbits(7))
    # 打印输出智能电表收集的原始数据
    for i in range(dimensionAccount):
        print(originDataInSmartMeter[i], end = " ")
    return originDataInSmartMeter


# 霍纳法则初始化算法
def HornerRuleInit(smNumber, dataUpperBound, dimensionAccount):
    # 简化编写,确定R为不大于nD的第一个素数
    nD = smNumber*pow(2,dataUpperBound) - 1
    while True:
        # 素性检测
        if gmpy2.is_prime(nD):
            break
        nD -= 1
    R = nD
    RVector = []
    # 生成RVector = (R, R^2, R^3, ..., R^k)
    for i in range(dimensionAccount):
        RVector.append(R)
        R = R*nD
    return RVector

# 霍纳法则数据转换算法
def HornerRuleDP(RVector, originDataInSmartMeter, dimensionAccount):
    transformedResult = 0
    for j in range(dimensionAccount):
        transformedResult += RVector[j]*originDataInSmartMeter[j]
    return transformedResult
    
# 霍纳法则数据恢复算法
def HornerRuleDR(RVector, aggregatedOneDimensionData, dimensionAccount):
    multidimensionResultList = []
    X_0 = aggregatedOneDimensionData // RVector[0]
    for j in range(dimensionAccount):
        multidimensionResultList.append(X_0 % RVector[0])
        X_0 = X_0 // RVector[0]
    return multidimensionResultList
    

def main():
    # 生成算法相关参数
    smNumber, dimensionAccount, dataUpperBound = paramsGeneration()
    # 数值中国剩余定理初始化
    RVector = HornerRuleInit(smNumber=smNumber, dataUpperBound=dataUpperBound, dimensionAccount=dimensionAccount)
     # 生成smNumber对原始数据并执行数据转换算法
    aggregatedResult = 0
    for i in range(smNumber):
        # 生成原始数据
        print("Smart Meter " + str(i+1))
        originDataInSmartMeter = dataGeneration(dimensionAccount=dimensionAccount)
        print("\n")
        # 执行数据维度转换
        transformedResult = HornerRuleDP(RVector=RVector, originDataInSmartMeter=originDataInSmartMeter, dimensionAccount=dimensionAccount)
        # 执行单维数据加法
        aggregatedResult += transformedResult
    # 数据维度分离
    aggregatedMultidimensinDataList = HornerRuleDR(RVector=RVector, aggregatedOneDimensionData=aggregatedResult, dimensionAccount=dimensionAccount)
    # 打印聚合后的数据结果 
    for i in range(dimensionAccount):
        print(aggregatedMultidimensinDataList[i])


if __name__ == "__main__":
    
    lp = LineProfiler()
    
    lp.add_function(HornerRuleInit)
    lp.add_function(HornerRuleDP)
    lp.add_function(HornerRuleDR)
    
    test_func = lp(main)
    test_func()
    lp.print_stats()