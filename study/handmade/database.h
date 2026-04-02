#include <stdbool.h>

typedef struct Item{
    int id;                   // 商品ID（整数）
    char name[50];            // 商品名
    int stock;                // 在庫数
    struct Item* next;        // 次の商品へのポインタ
} Item;

extern Item* list;            // DB実体

// DB読み込み
bool LoadDB(void);

// 機能1：商品一覧を表示
void dispList(void);

// 機能2：在庫数を変更
void changeStock(void);

// 機能3：商品を追加
void addItem(void);

// 機能4：ファイルを出力して終了
bool exitItemDB(void);

// DBにID、名前、在庫数を追加する
void pushBack(Item** head, int id, char* name, int stock);

// DB解放
void freeNode(Item* head);