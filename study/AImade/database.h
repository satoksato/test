#include <stdbool.h>

#define MAX_ITEMS 100

typedef struct {
    int id;            // 商品ID（整数）
    char name[50];     // 商品名
    int stock;         // 在庫数
} Item;

extern Item items[MAX_ITEMS];  // 商品配列
extern int itemCount;          // 現在の商品数

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