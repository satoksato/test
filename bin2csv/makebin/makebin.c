#include <stdio.h>
#include <stdlib.h>

// プロトタイプ宣言
void make_bin(int* bin_data);

int main(int argc, char *argv[]) {
    int bin_data[100]; // 100個の整数を格納する配列
    FILE *binfile;     // バイナリファイルのポインタ
    
    make_bin(bin_data);

    if (argv[1] == NULL) 
    {
        // コマンドラインに入力がない場合は、デフォルトファイルで生成する。
        binfile = fopen("./maked.bin", "wb");
    }
    else 
    {
        // コマンドラインに入力がある場合は、そのファイルを使用する。
        binfile = fopen(argv[1], "wb");
    }

    if (binfile == NULL) 
    {
        perror("Error binary file");
        return 1;
    }

    make_bin(bin_data); // ランダムに100件の整数を生成する。
    fwrite(bin_data, sizeof(bin_data), 1, binfile); // 配列全体をバイナリファイルに書き込む

    fclose(binfile);

    return 0;
}

void make_bin(int* bin_data) 
{
    
    for (int i = 0; i < 100; i++) 
    {
        bin_data[i] = rand() % 100; // 0～99までの整数を生成し格納
    }

    return;
}