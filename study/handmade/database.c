#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// プロトタイプ宣言
static Item* createNode(int id, char* name, int stock);
static Item* find(Item* head, int target);
static void printDB(Item* head);
static bool writeDB(Item* head, char *file);

// グローバル変数定義
Item* list = NULL;

// DB読み込み
bool LoadDB(void)
{
    // items.txtの読み込み
    FILE *rfp = fopen("./items.txt", "r");
    if (rfp == NULL)
    {
        printf("ファイルの読み込みに失敗しました\n");
        return false;
    }
    
    // 変数宣言
    char line[256]; // 1行分のデータを格納する変数
    int id;
    char name[50];
    int stock;

    while (fgets(line, sizeof(line), rfp) != NULL) // 1行読み込む
    {
        sscanf(line, "%d %s %d", &id, name, &stock);    //ID,名前,在庫数 を分割
        pushBack(&list, id, name, stock);               //リストにID,名前,在庫数を追加  
    }
    
    if (rfp != NULL)
    {
        fclose(rfp);
    }

    return true;
}

// 機能1：商品一覧を表示
void dispList(void)
{
    printDB(list);
}

// 機能2：在庫数を変更
void changeStock(void)
{
    int id;
    int stock;

    printf("IDを入力してください：");
    scanf("%d", &id);
    
    if (find(list, id) == NULL)
    {
        printf("ID：%d は存在しません\n", id);
    }
    else
    {
        printf("在庫数を変更してください：");
        scanf("%d", &stock);
        list->stock = stock;
        printf("ID：%d の在庫数を %d に変更しました\n", list->id, list->stock);
    }

    return;
}

// 機能3：商品を追加
void addItem(void)
{
    int id;
    char name[50];
    int stock;

    printf("IDを入力してください：");
    scanf("%d", &id);
    printf("名前を入力してください：");
    scanf("%s", name);
    printf("在庫数を入力してください：");
    scanf("%d", &stock);
    printf("\n");
    
    if (find(list, id) == NULL)
    {
        pushBack(&list, id, name, stock);
        printf("商品%sを追加しました\n", name);
    }
    else
    {
        printf("ID：%d は既に存在します\n", id);
    }

    return;
}

// 機能4：ファイルを出力して終了
bool exitItemDB(void)
{
    // items.txtの読み込み
    FILE *rfp = fopen("./items.txt", "r");
    if (rfp == NULL)
    {
        printf("ファイルの読み込みに失敗しました\n");
        return false;
    }
    char dbStr[100 * 3 * (5 + 51 + 11)] = {0}; // 3つのデータを格納した100レコード分のデータベース（文字数区切り）
    fread(dbStr, sizeof(char), sizeof(dbStr), rfp);
    
    if (rfp != NULL)
    {
        fclose(rfp);
    }

    // items_out.txtの書き込み
    if (!writeDB(list, "./items_out.txt"))
    {
        return false;
    }

    return true;
}

// リストを作成（構造体メモリ確保）
static Item* createNode(int id, char* name, int stock) {
    Item* node = (Item*)malloc(sizeof(Item));
    if (node == NULL) {
        printf("メモリ確保に失敗しました\n");
        exit(1);
    }
    node->id = id;
    memcpy(node->name,name,sizeof(name));
    node->stock = stock;
    node->next = NULL;
    return node;
}

// IDを検索してリストを返す。見つからない場合はNULLを返す。
static Item* find(Item* head, int target)
{
    // 今のDBを参照
    Item* current = head;
    // 今のDBの末尾までIDを検索
    while (current != NULL) {
        if (current->id == target) {
            return current;
        }
        current = current->next;
    }
    return NULL;  // 見つからない場合
}

// リストを表示
static void printDB(Item* head) {
    Item* current = head;

    printf("===== 商品一覧 =====\n");

    while (current != NULL) {
        printf("ID: %d\t名前: %s\t在庫: %d\n", current->id, current->name, current->stock);
        current = current->next;
    }
}

static bool writeDB(Item* head, char *file) {
    Item* current = head;

    FILE *wfp = fopen(file, "w");
    if (wfp == NULL)
    {
        printf("ファイルの読み込みに失敗しました\n");
        return false;
    }

    while (current != NULL) {
        fprintf(wfp, "%d %s %d\n", current->id, current->name, current->stock);
        current = current->next;
    }
    
    if (wfp != NULL)
    {
        fclose(wfp);
    }

    return true;
}

// 末尾にリストを追加
void pushBack(Item** head, int id, char* name, int stock)
{
    // DB作成
    Item* newNode = createNode(id, name, stock);

    // DBのNULL✓
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    // 今のDBを参照
    Item* current = *head;
    while (current->next != NULL) {
        // 次のDBを参照
        current = current->next;
    }
    current->next = newNode;
}

// DB解放
void freeNode(Item* head)
{
    Item* current = head;
    Item* next;

    // 今のDBの末尾までDBを解放
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}
