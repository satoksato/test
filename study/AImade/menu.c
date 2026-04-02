#include "menu.h"
#include <string.h>

// MENU選択時の入力キー判断
bool judgeKey(const char *key)
{
    if (   (strcmp(key, "1") == 0)
        || (strcmp(key, "2") == 0)
        || (strcmp(key, "3") == 0)
        || (strcmp(key, "4") == 0)
    )
    {   return true;    }
    return false;
}