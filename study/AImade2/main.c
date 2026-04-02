#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    Item items[MAX_ITEMS];
    int itemCount = 0;

    // ファイルから読み込み
    if (!loadItems(items, &itemCount)) {
        // 読み込めなかった場合は空で開始
        itemCount = 0;
    }

    int choice;
    while (1) {
        printf("\n===== 商品在庫管理システム =====\n");
        printf("1. 商品一覧を表示\n");
        printf("2. 在庫数を変更\n");
        printf("3. 商品を追加\n");
        printf("4. 終了（ファイルへ保存）\n");
        printf("番号を入力してください：");

        if (scanf("%d", &choice) != 1) {
            // 無効な入力
            while (getchar() != '\n'); // バッファクリア
            printf("無効な入力です。1-4の数字を入力してください。\n");
            continue;
        }

        switch (choice) {
            case 1:
                displayItems(items, itemCount);
                break;
            case 2:
                changeStock(items, itemCount);
                break;
            case 3:
                addItem(items, &itemCount);
                break;
            case 4:
                if (saveItems(items, itemCount)) {
                    printf("データを保存しました。プログラムを終了します。\n");
                } else {
                    printf("データの保存に失敗しました。\n");
                }
                return 0;
            default:
                printf("無効な選択です。1-4の数字を入力してください。\n");
                break;
        }
    }

    return 0;
}

bool loadItems(Item items[], int *count) {
    FILE *fp = fopen("items.txt", "r");
    if (fp == NULL) {
        return false;
    }

    char line[256];
    *count = 0;
    while (fgets(line, sizeof(line), fp) != NULL && *count < MAX_ITEMS) {
        int id, stock;
        char name[50];
        if (sscanf(line, "%d %s %d", &id, name, &stock) == 3) {
            items[*count].id = id;
            strcpy(items[*count].name, name);
            items[*count].stock = stock;
            (*count)++;
        }
    }

    fclose(fp);
    return true;
}

void displayItems(const Item items[], int count) {
    printf("\n===== 商品一覧 =====\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %d  Name: %-10s  Stock: %d\n", items[i].id, items[i].name, items[i].stock);
    }
    if (count == 0) {
        printf("商品がありません。\n");
    }
}

void changeStock(Item items[], int count) {
    int id;
    printf("変更する商品のIDを入力してください：");
    if (scanf("%d", &id) != 1) {
        printf("無効な入力です。\n");
        while (getchar() != '\n');
        return;
    }

    for (int i = 0; i < count; i++) {
        if (items[i].id == id) {
            int newStock;
            printf("新しい在庫数を入力してください：");
            if (scanf("%d", &newStock) != 1) {
                printf("無効な入力です。\n");
                while (getchar() != '\n');
                return;
            }
            items[i].stock = newStock;
            printf("ID %d の在庫数を %d に変更しました。\n", id, newStock);
            return;
        }
    }
    printf("該当する商品が見つかりません。\n");
}

void addItem(Item items[], int *count) {
    if (*count >= MAX_ITEMS) {
        printf("商品数が上限（%d）に達しています。\n", MAX_ITEMS);
        return;
    }

    int id, stock;
    char name[50];

    printf("新しい商品のIDを入力してください：");
    if (scanf("%d", &id) != 1) {
        printf("無効な入力です。\n");
        while (getchar() != '\n');
        return;
    }

    // ID重複チェック
    for (int i = 0; i < *count; i++) {
        if (items[i].id == id) {
            printf("ID %d は既に存在します。\n", id);
            return;
        }
    }

    printf("商品名を入力してください：");
    if (scanf("%s", name) != 1) {
        printf("無効な入力です。\n");
        while (getchar() != '\n');
        return;
    }

    printf("在庫数を入力してください：");
    if (scanf("%d", &stock) != 1) {
        printf("無効な入力です。\n");
        while (getchar() != '\n');
        return;
    }

    items[*count].id = id;
    strcpy(items[*count].name, name);
    items[*count].stock = stock;
    (*count)++;
    printf("商品 %s を追加しました。\n", name);
}

bool saveItems(const Item items[], int count) {
    FILE *fp = fopen("items_out.txt", "w");
    if (fp == NULL) {
        return false;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d %s %d\n", items[i].id, items[i].name, items[i].stock);
    }

    fclose(fp);
    return true;
}