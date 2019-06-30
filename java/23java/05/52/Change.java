import java.util.Scanner;

class Change {
    public static void main(String[] args) {
        Scanner stdIn = new Scanner(System.in);
        int cou = 0;
        int s2Len;

        System.out.print("テキスト: ");
        StringBuilder s1 = new StringBuilder(stdIn.next()); // テキスト用文字列

        System.out.print("検索パターン: ");
        String s2 = stdIn.next(); // バターン用文字列
        s2Len = s2.length();

        System.out.print("置換後のパターン: ");
        String s3 = stdIn.next();

        System.out.println(s1);

        int idx = BMmatch.bmMatch(s1.toString(), s2); // 文字列s1から文字列s2をBM法で探索
        while (idx != -1) {
            cou++;

            s1.replace(idx, idx + s2.length(), s3);

            idx = BMmatch.bmMatch(s1.toString(), s2); // 文字列s1から文字列s2をBM法で探索
        }

        System.out.println(s1);
        System.out.println("置換回数 : " + cou);
    }
}