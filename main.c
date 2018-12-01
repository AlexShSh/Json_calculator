#include <stdio.h>
#include "json.h"
#include "calculator_json.h"

int main()
{
    pJsonElement elem = parseJson("task.txt");

    printf("res = %f\n", CalculateJSON(elem));

    DeleteJson(&elem);

    return 0;
}
