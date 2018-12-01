#include <stdio.h>
#include <stdlib.h>
#include "hashMap.h"
#include "calculator_json.h"

double CalculateExpr(pJsonElement expr);
double CalculateSum(pJsonElement func);
double CalculateSub(pJsonElement func);
double CalculateMul(pJsonElement func);
double CalculateDiv(pJsonElement func);


double CalculateJSON(pJsonElement elem)
{
    if (elem->type != JSON_MAP)
    {
        printf("Calculator error: wrong JSON Element\n");
        return 0;
    }

    pMap map = elem->value;
    pJsonElement expression = GetFromMap(map, "calculate");
    if (!expression)
    {
        printf("Calculator error: expected key \"calculate\"\n");
        return 0;
    }
    return CalculateExpr(expression);
}

double CalculateExpr(pJsonElement expr)
{
    double res = 0;
    switch (expr->type)
    {
        case JSON_VALUE:
        {
            res = atof(expr->value);
            break;
        }
        case JSON_MAP:
        {
            pMap exprMap = expr->value;
            pJsonElement func = GetFromMap(exprMap, "sum");
            if (func)
                res = CalculateSum(func);
            else
            {
                func = GetFromMap(exprMap, "sub");
                if (func)
                    res = CalculateSub(func);
                else
                {
                    func = GetFromMap(exprMap, "mul");
                    if (func)
                        res = CalculateMul(func);
                    else
                    {
                        func = GetFromMap(exprMap, "div");
                        if (func)
                            res = CalculateDiv(func);
                        else
                            printf("Calculator error: expected key \"sum\", \"sub\", \"mul\" or \"div\"\n");
                    }
                }
            }
            break;
        }
        default:
            printf("Calculator error: wrong expression\n");
    }
    return res;
}

double CalculateSum(pJsonElement func)
{
    if (func->type != JSON_MAP)
    {
        printf("Calculator error: wrong JSON sum\n");
        return 0;
    }
    pMap funcMap = func->value;

    pJsonElement arg1 = GetFromMap(funcMap, "arg1");
    if (!arg1)
    {
        printf("Calculator error: expected key \"arg1\"\n");
        return 0;
    }
    pJsonElement arg2 = GetFromMap(funcMap, "arg2");
    if (!arg2)
    {
        printf("Calculator error: expected key \"arg2\"\n");
        return 0;
    }

    return CalculateExpr(arg1) + CalculateExpr(arg2);
}

double CalculateSub(pJsonElement func)
{
    if (func->type != JSON_MAP)
    {
        printf("Calculator error: wrong JSON sum\n");
        return 0;
    }
    pMap funcMap = func->value;

    pJsonElement arg1 = GetFromMap(funcMap, "arg1");
    if (!arg1)
    {
        printf("Calculator error: expected key \"arg1\"\n");
        return 0;
    }
    pJsonElement arg2 = GetFromMap(funcMap, "arg2");
    if (!arg2)
    {
        printf("Calculator error: expected key \"arg2\"\n");
        return 0;
    }

    return CalculateExpr(arg1) - CalculateExpr(arg2);
}

double CalculateMul(pJsonElement func)
{
    if (func->type != JSON_MAP)
    {
        printf("Calculator error: wrong JSON sum\n");
        return 0;
    }
    pMap funcMap = func->value;

    pJsonElement arg1 = GetFromMap(funcMap, "arg1");
    if (!arg1)
    {
        printf("Calculator error: expected key \"arg1\"\n");
        return 0;
    }
    pJsonElement arg2 = GetFromMap(funcMap, "arg2");
    if (!arg2)
    {
        printf("Calculator error: expected key \"arg2\"\n");
        return 0;
    }

    return CalculateExpr(arg1) * CalculateExpr(arg2);
}

double CalculateDiv(pJsonElement func)
{
    if (func->type != JSON_MAP)
    {
        printf("Calculator error: wrong JSON sum\n");
        return 0;
    }
    pMap funcMap = func->value;

    pJsonElement arg1 = GetFromMap(funcMap, "arg1");
    if (!arg1)
    {
        printf("Calculator error: expected key \"arg1\"\n");
        return 0;
    }
    pJsonElement arg2 = GetFromMap(funcMap, "arg2");
    if (!arg2)
    {
        printf("Calculator error: expected key \"arg2\"\n");
        return 0;
    }

    return CalculateExpr(arg1) / CalculateExpr(arg2);
}
