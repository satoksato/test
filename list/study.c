#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// プロトタイプ宣言
static void menu(void);
static bool func1(char** mem);
static void func2(char** mem);
static int  func3(char** mem);
static void func4(char** mem);
static bool func5(char** mem);

// グローバル変数
int words_cnt;  // リストに載せた言葉の数

int main(void)
{
    int menu_key = 0;   // menu時に入力した画面
    char** words = calloc(100 * 50, sizeof(char));   // 100文字、50件までを許容
    if (words == NULL)
    {
        printf("Error");
        return 1;
    }

    while(1)
    {
        menu();
        if (scanf("%d",&menu_key) != -1)
        {
            switch (menu_key)
            {
            case 1:
                // MENU1. 文字列を追加
                if (func1(words))
                {
                    words_cnt++;
                }
                break;
            case 2:
                // MENU2. 登録済み文字列一覧を表示
                func2(words);
                break;
            case 3:
                // MENU3. 文字列を検索
                int index = func3(words);
                if (index == 0)
                {
                    // 見つからず
                    printf("Not found input keywords\n");
                }
                else {
                    // 見つかった
                    printf("Success. index : %d\n", index);
                }
                break;
            case 4:
                // MENU4. 文字列を削除
                func4(words);
                break;
            case 5:
                // MENU5. 全データを解放して終了
                if (func5(words))
                {
                    printf("Success Exit Application");
                    return 0;
                }
                else {
                    printf("Error Exit Application");
                    return 1;
                }
                break;
            default:
                // 1~5以外が入力された
                printf("Invalid Number\n");
                break;
            }
        }
    }
    
    return 0;
}

// MENU表示
static void menu(void)
{
    printf(" === MENU ===\n");
    printf("1 : Add a new string\n");
    printf("2 : Show all registered strings\n");
    printf("3 : Search for a string\n");
    printf("4 : Delete a string\n");
    printf("5 : Free all data and exit\n");
    printf(" ============\n");
    printf("Please input MENU number : ");
}

// MENU1. 文字列を追加
static bool func1(char** mem)
{
    // 変数宣言
    int length;               // 文字長
    char input[100] = {0};    // 入力文字
    
    // コンソール
    system("cls");
    printf("Please input data\n");
    
    scanf("%s",input);          // キーボード入力
    length = strlen(input) + 1; // 文字長計算

    mem[words_cnt] = (char*)calloc(length, sizeof(char)); // 入力文字分のメモリ作成

    if (mem == NULL)
    {
        printf("Failed input data\n");
        return false;
    }

    memcpy(mem[words_cnt], input, length);    // 入力文字記憶
    printf("Add data %s \n\n", mem[words_cnt]);

    return true;
}

// MENU2. 登録済み文字列一覧を表示
static void func2(char** mem)
{
    system("cls");
    if (words_cnt == 0)
    {
        printf("no data\n");
        return;
    }

    int str_ptr = 0;
    for (int i = 0; i < words_cnt; i++)
    {
        printf("[%d] : %s\n",i, mem[i]);
    }
    
    printf("\n");
}

// MENU3. 文字列を検索
static int func3(char** mem)
{
    // 変数宣言
    char input[100] = {0};    // 入力文字
    
    system("cls");
    if (words_cnt == 0)
    {
        return 0;             // 失敗時は0を返す
    }
    
    printf("Please search words\n");
    scanf("%s",input);        // キーボード入力

    for (int i = 0; i < words_cnt; i++)
    {
        if (strcmp(mem[i], input) == 0 )
        {
            // 該当文字があった
            return i;          // 成功時はindexを返す
        }
    }
    
    return 0;                  // 失敗時は0を返す
}

// MENU4. 文字列を削除
static void func4(char** mem)
{
    // 変数宣言
    int input;                    // 入力文字
    int target = 0;               // 0:見つからず, 0以外:見つかった
    
    system("cls");
    
    printf("Please Delete index\n");
    scanf("%d", &input);          // キーボード入力

    for (int i = 0; i < words_cnt; i++)
    {
        if (i == input)
        {
            // 該当インデックスがあった
            if (mem[i] != NULL)
            {
                free(mem[i]);
            }
            
            // メモリを前詰めする
            for (int j = i; j < words_cnt - 1; j++) {
                mem[j] = mem[j + 1];
            }
            words_cnt--;

            return;
        }
    }
    
    printf("Not found index number\n");
    return;
}

// MENU5. 全データを解放して終了
static bool func5(char** mem)
{
    system("cls");

    bool result = false;
    // 作成時とは逆順で解放。
    for (int i = words_cnt; i > 0; i--)
    {
        if (mem[i] != NULL)
        {
            free(mem[i]);
            result = true;
        }
    }
    if (mem != NULL)
    {
        free(mem);
        result = true;
    }

    return result;
}