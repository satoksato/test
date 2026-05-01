public class Sample1_07_01{
    public static void main(String[] argv){
        int numX = 8;
        int numY = 4;
        int numZ = 5;

        // 足し算
        System.out.println("numX + numY = " + (numX+numY));
        // 引き算
        System.out.println("numX - numY = " + (numX-numY));
        // 掛け算
        System.out.println("numX * numY = " + (numX*numY));
        // 割り算
        System.out.println("numX / numY = " + (numX/numY));
        // 余り算
        System.out.println("numX % numY = " + (numX%numY));
        // 符号反転
        System.out.println("-numX = " + (-numX));
        // 前置インクリメント
        int answer = ++numX;
        System.out.println("answer = " + answer);
        System.out.println("++numX = " + numX);
        // 後置インクリメント
        answer = numX++;
        System.out.println("answer = " + answer);
        System.out.println("numX++ = " + numX);

        // インクリメントは 対象変数の値を変えてしまう演算子なので注意
        // int result = numX + 1;
        // int result = ++numX;　　は違う。

        // デクリメント
        answer = --numX;
        System.out.println("--numX = " + answer);
    }
}