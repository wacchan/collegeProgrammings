import java.net.*;
import java.io.*;

public class TCPClient1 {
    //宛先マシンのFQDN／宛先マシンのIPアドレス（文字列で指定）
    static final String SERVERNAME="localhost";
    
    //ポート番号
    static final int SPORT=60600;

    public static void main(String[] argv) throws Exception{
	//IPv4で起動する
        System.setProperty("java.net.preferIPv4Stack", "true");

	// 送信するデータ（文字列）
	String message = "TCPのサンプルプログラム TCPClient1";
	    
	// 送信先IPアドレスとポート番号を指定し，ソケットを生成
	Socket socket = new Socket(InetAddress.getByName(SERVERNAME), SPORT);

	// ソケットの出力用ストリームを得る（バイトレベルデータ）
	OutputStream outstr = socket.getOutputStream();

	// 書き込み用文字レベルデータに変換（コード変換）
	OutputStreamWriter osw = new OutputStreamWriter(outstr);
	//OutputStreamWriter osw = new OutputStreamWriter(outstr, "EUC-JP"); //日本語EUCコード
	//OutputStreamWriter osw = new OutputStreamWriter(outstr, "ISO2022JP"); //JISコード
	
	// テキストを簡単に処理できるclasssを利用する
	PrintWriter writer = new PrintWriter(osw);
	
	//ストリームにデータを書き込む（データ送信）
	writer.println(message);
	writer.flush();

	System.out.println("Send done ("+ message +").");

	//終了処理
	writer.close();
	osw.close();
	outstr.close();
	socket.close();
    }
}
