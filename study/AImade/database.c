#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// グローバル変数定義
Item items[MAX_ITEMS];
int itemCount = 0;

// DB読み込み
bool LoadDB(void)
{
    FILE *rfp = fopen("items.txt", "r");
    if (rfp == NULL)
    {
        // 読み込めなかった場合は空のデータとして開始
        itemCount = 0;
        return true;
    }
    
    char line[256];
    int id, stock;
    char name[50];
    
    itemCount = 0;
    while (fgets(line, sizeof(line), rfp) != NULL && itemCount < MAX_ITEMS)
    {
        if (sscanf(line, "%d %s %d", &id, name, &stock) == 3)
        {
            items[itemCount].id = id;
            strcpy(items[itemCount].name, name);
            items[itemCount].stock = stock;
            itemCount++;
        }
    }
    
    fclose(rfp);
    return true;
}

// 機能1：商品一覧を表示
void dispList(void)
{
    printf("===== 商品一覧 =====\n");
    for (int i = 0; i < itemCount; i++)
    {
        printf("ID: %d  Name: %-10s  Stock: %d\n", items[i].id, items[i].name, items[i].stock);
    }
}

// 機能2：在庫数を変更
void changeStock(void)
{
    int id, newStock;
    printf("商品IDを入力してください：");
    scanf("%d", &id);
    
    for (int i = 0; i < itemCount; i++)
    {
        if (items[i].id == id)
        {
            printf("新しい在庫数を入力してください：");
            scanf("%d", &newStock);
            items[i].stock = newStock;
            printf("ID: %d の在庫数を %d に変更しました\n", id, newStock);
            return;
        }
    }
    printf("該当商品が存在しません\n");
}

// 機能3：商品を追加
void addItem(void)
{
    if (itemCount >= MAX_ITEMS)
    {
        printf("商品数が上限に達しています\n");
        return;
    }
    
    int id, stock;
    char name[50];
    
    printf("新しいIDを入力してください：");
    scanf("%d", &id);
    
    // ID重複チェック
    for (int i = 0; i < itemCount; i++)
    {
        if (items[i].id == id)
        {
            printf("ID: %d は既に存在します\n", id);
            return;
        }
    }
    
    printf("商品名を入力してください：");
    scanf("%s", name);
    printf("在庫数を入力してください：");
    scanf("%d", &stock);
    
    items[itemCount].id = id;
    strcpy(items[itemCount].name, name);
    items[itemCount].stock = stock;
    itemCount++;
    printf("商品 %s を追加しました\n", name);
}

// 機能4：ファイルを出力して終了
bool exitItemDB(void)
{
    FILE *wfp = fopen("items_out.txt", "w");
    if (wfp == NULL)
    {
        printf("ファイルの書き込みに失敗しました\n");
        return false;
    }
    
    for (int i = 0; i < itemCount; i++)
    {
        fprintf(wfp, "%d %s %d\n", items[i].id, items[i].name, items[i].stock);
    }
    
    fclose(wfp);
    return true;
}
