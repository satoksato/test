public class Sample1_10_01{
    public static void main(String[] argv){
        String data1 = "data";
        String data2 = new String("data");
        
        System.out.println(data1 == "data");
        System.out.println(data1 == data2);
        System.out.println(data1.equals(data2));
    }
}