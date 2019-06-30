import java.util.Scanner;

class Replace2 {
    public static void main(String[] args) {
        Scanner stdIn = new Scanner(System.in);
        int cou = 0;
        int s2Len;

        System.out.print("テキスト: ");
        //StringBuilder s1 = new StringBuilder(stdIn.next()); // テキスト用文字列
        String s1 = stdIn.next(); 

        System.out.print("パターン: ");
        String s2 = stdIn.next(); // バターン用文字列
        s2Len = s2.length();

        System.out.println(s1);

        int idx = BMmatch.bmMatch(s1.toString(), s2); // 文字列s1から文字列s2をBM法で探索
        while (idx != -1) {
            cou++;
            for (int i = idx; i < idx + s2Len; i++) {
                s1 = s1.replaceFirst(s2, "@");
            }
            idx = BMmatch.bmMatch(s1.toString(), s2); // 文字列s1から文字列s2をBM法で探索
        }

        System.out.println(s1);
        System.out.println("出現回数 : " + cou);
        System.out.println("置換文字数 : " + cou * s2Len);
    }
}