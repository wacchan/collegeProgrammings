
// String.indexOfメソッドとString.lastIndexOfメソッドによる文字列探索

import java.util.Scanner;

class IndexOfTester {
    public static void main(String[] args) {
        Scanner stdIn = new Scanner(System.in);

        System.out.print("テキスト: ");
        String s1 = stdIn.next(); // テキスト用文字列

        System.out.print("パターン: ");
        String s2 = stdIn.next(); // バターン用文字列

        int idx1 = s1.indexOf(s2); // 文字列s1からs2を探索(先頭側)
        int idx2 = s1.lastIndexOf(s2); // 文字列s1からs2を探索(末尾側)

        if (idx1 == -1)
            System.out.println("テキスト中にパターンは存在しません。");
        else {
            // マッチ文字の直前までの《半角》での文字数を求める
            int len1 = 0;
            for (int i = 0; i < idx1; i++)
                len1 += s1.substring(i, i + 1).getBytes().length;
            len1 += s2.length();

            int len2 = 0;
            for (int i = 0; i < idx2; i++)
                len2 += s1.substring(i, i + 1).getBytes().length;
            len2 += s2.length();

            System.out.println("テキスト: " + s1);
            System.out.printf(String.format("パターン: %%%ds\n", len1), s2);
            System.out.println("テキスト: " + s1);
            System.out.printf(String.format("パターン: %%%ds\n", len2), s2);
        }
    }
}
