#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "database.h"

int main(void) { 
    // DB読み込み
    if (!LoadDB())
    {
        printf("items.txtの読み込みに失敗しました。アプリを終了します。");
        if (list != NULL)
        {
            freeNode(list);
        }
        return 1;
    }

    // MENU選択
    while(1)
    {
        // MENU表示
        printf("===== 商品在庫管理システム =====\n");
        printf("1. 商品一覧を表示\n");
        printf("2. 在庫数を変更\n");
        printf("3. 商品を追加\n");
        printf("4. 終了（ファイルへ保存）\n");
        printf("番号を入力してください：");

        char key[2];
        scanf("%s", key);
        if (judgeKey(key)) 
        {
            if (strcmp(key, "1") == 0)
            {
                system("cls");  //コンソール表示を消す
                printf("商品一覧を表示します\n");
                dispList();
                printf("\n");
            }
            else if (strcmp(key, "2") == 0)
            {
                system("cls");  //コンソール表示を消す
                printf("在庫数を変更します\n");
                changeStock();
                printf("\n");
            }
            else if (strcmp(key, "3") == 0)
            {
                system("cls");  //コンソール表示を消す
                printf("商品を追加します\n");
                addItem();
                printf("\n");
            }
            else if (strcmp(key, "4") == 0)
            {
                system("cls");  //コンソール表示を消す
                if (exitItemDB())
                {
                    printf("保存しました。\nアプリを終了します。");
                }
                else {
                    printf("保存できませんでした。\nアプリを強制終了します。");
                }
                if (list != NULL)
                {
                    freeNode(list);
                }
                return 0;
            }
            continue;
        }
        else
        {
            printf("1~4の数字を入力してください。\n");
            continue;
        }
    }
    if (list != NULL)
    {
        freeNode(list);
    }
    return 0;
}