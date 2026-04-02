#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>

#define MAX_ITEMS 100

typedef struct {
    int id;            // 商品ID（整数）
    char name[50];     // 商品名
    int stock;         // 在庫数
} Item;

// 関数プロトタイプ
bool loadItems(Item items[], int *count);
void displayItems(const Item items[], int count);
void changeStock(Item items[], int count);
void addItem(Item items[], int *count);
bool saveItems(const Item items[], int count);

#endif