
// KMP法による文字列探索
import java.util.Scanner;

class KmpMatch {
    static int kmpMatch(String txt, String pat) {
        int pt = 1;
        int pp = 0;
        int[] skip = new int[pat.length() + 1];

        // スキップテーブルの作成
        skip[pt] = 0;
        while (pt != pat.length()) {
            if (pat.charAt(pt) == pat.charAt(pp)) {
                skip[++pt] = ++pp;
            } else if (pp == 0) {
                skip[++pt] = pp;
            } else {
                pp = skip[pp];
            }
        }

        // 探索
        pt = pp = 0;
        while (pt != txt.length() && pp != pat.length()) {
            if (txt.charAt(pt) == pat.charAt(pp)) {
                pt++;
                pp++;
            } else if (pp == 0) {
                pt++;
            } else {
                pp = skip[pp];
            }
        }

        if (pp == pat.length()) {
            return pt - pp; // パターンの全文字を照合
        } else {
            return -1; // 探索失敗
        }
    }

    public static void main(String[] args) {
        Scanner stdIn = new Scanner(System.in);
        int[] idx = new int[10];

        System.out.print("テキスト: ");
        String s1 = stdIn.next(); // テキスト用文字列

        System.out.print("パターン: ");
        String s2 = stdIn.next(); // バターン用文字列

        // 文字列s1からs2を探索(先頭側)
        idx[0] = 0;
        for(int i = 1; i < 11; i++){
            idx[i] = kmpMatch(s1.substring(idx[i-1]), s2);//前回までを切り取って再探索

            if(idx[1] == -1){                 //初回でパターンが見つからなかった時
                System.out.println("テキスト中にパターンは存在しません。");
            }else if(idx[i] == -1){           //初回以外でパターンが見つからなかった時
                break;
            }else {                           //パターンが見つかった時
                int len1 = 0;
                idx[i] += idx[i-1];           //今回見つけたパターン+切り取った文字数
                for (int j = 0; j < idx[i]; j++){
                    len1 += s1.substring(j, j + 1).getBytes().length;  //見つけたパターンまでの文字数（半角）
                }
                len1 += s2.length();

                System.out.println((idx[i] + 1) + "文字目にマッチします。");
                System.out.println("テキスト:  " + s1);
                /*System.out.print("パターン: ");
                for(int j = 0; j < len1; j++){
                    System.out.print(" ");
                }
                System.out.println(s2);*/
                System.out.printf(String.format("パターン: %%%ds\n", len1+1), s2);//%len1d（len1だけスペース表示）＋s2表示
                
                idx[i] = idx[i] + s2.length();  //今回見つけたパターンまでの文字数


            }
        }

        
    }

}