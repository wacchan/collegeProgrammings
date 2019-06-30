import java.util.Scanner;

class BFmatch {

   //--- 力まかせ法による文字列探索 ---//
   static int bfMatch(String txt, String pat) {
      int pt = 0;      // txtをなぞるカーソル
      int pp = 0;      // patをなぞるカーソル

      while (pt != txt.length() && pp != pat.length()) {
         if (txt.charAt(pt) == pat.charAt(pp)) {
            pt++;
            pp++;
         } else {
            pt = pt - pp + 1;
            pp = 0;
         }
      }
      if (pp == pat.length())      // 探索成功
         return pt - pp;
      return -1;               // 探索失敗
   }

   public static void main(String[] args) {
      Scanner stdIn = new Scanner(System.in);

      System.out.print("テキスト：");
      String s1 = stdIn.next();                // テキスト用文字列

      System.out.print("パターン：");
      String s2 = stdIn.next();               // パターン用文字列

      int idx = bfMatch(s1, s2);   // 文字列s1から文字列s2を力まかせ法で探索

      if (idx == -1)
         System.out.println("テキスト中にパターンは存在しません。");
      else {
         // マッチ文字の直前までの《半角》での文字数を求める
         int len = 0;
         for (int i = 0; i < idx; i++)
            len += s1.substring(i, i + 1).getBytes().length;
         len += s2.length();

         System.out.println((idx + 1) + "文字目にマッチします。");
         System.out.println("テキスト：" + s1);
         System.out.printf(String.format("パターン：%%%ds\n", len), s2);
      }
   }
}

