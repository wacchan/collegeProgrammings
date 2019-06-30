import java.util.Base64;
import java.io.*;

public class SubjectBase64Demo {

    static String SubjectBASE64Handling(String a, int b) throws IOException {
	String returnString=null;
	
	switch (b) {
	case 0:  //エンコード
	    // エンコードは、Base64.getEncoder() で得られるオブジェクトを利用する
	    // Base64 エンコード結果を String としたい場合は、Encoder#encodeToString() を呼び出す
	    String encoded = Base64.getEncoder().encodeToString(a.getBytes("ISO2022JP")); //JISコードに変換して符号化
	    
	    returnString = "=?iso-2022-jp?B?" + encoded + "?=";
	    break;
	case 1: //デコード
	    String head = a.substring(0,16);
	    String tail = a.substring(a.length()-2, a.length());
	    if (!(head.equals("=?iso-2022-jp?B?") && tail.equals("?=")) && !(head.equals("=?ISO-2022-JP?B?") && tail.equals("?="))) {
		System.out.println("エンコーディング方法が違います [" + head + "]  + [" + tail + "]");
		//returnString =null;
	    }
	    else {
		String body = a.substring(16,a.length()-2);
		//System.out.println(body);
	    
		// デコードは Base64.getDecoder() で得られるオブジェクトを利用する
		returnString = new String(Base64.getDecoder().decode(body), "ISO2022JP"); //JISコードとして復号化
	    }
	    break;
	default:
	    System.out.println(" 0 or 1を指定してください。");
	    //return null;
	    break;
	}
	return returnString;
    }
    
    public static void main(String[] args)  throws IOException {
	String text = "漢字の件名です";

	System.out.println("オリジナルテキスト：" + text);
	
	String encoded = SubjectBASE64Handling(text, 0);
	
        System.out.println("MIME対応Subject：  " + encoded);
	
	String decoded = SubjectBASE64Handling(encoded, 1);
	
        System.out.println("デコードテキスト： " + decoded);
	
    }
}
