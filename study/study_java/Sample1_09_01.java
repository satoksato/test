public class Sample1_09_01{
    public static void main(String[] argv){
        // 配列宣言
        String sign[] = new String[3];
        // 要素代入
        sign[0] = "Blue";
        sign[1] = "Yellow";
        sign[2] = "Red";
        System.out.println(sign[0] + " " + sign[1] + " "  + sign[2]);

        System.out.println(sign.length);

        // 配列初期化
        String[] name_list = {"SATO","ITO","KATO","SAITO","GOTO"};
        for (String index : name_list)
        {
            System.out.println(index);
        }
    }
}