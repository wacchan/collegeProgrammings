import java.net.*;
import java.io.*;

public class TCPServer1 {
    //サーバポート番号
    static final int SPORT=60600;
    
    public static void main(String[] argv) throws Exception {
	//IPv4で起動する
        System.setProperty("java.net.preferIPv4Stack", "true");

	InetAddress myAddr = InetAddress.getLocalHost();       //自分のIPアドレスを取得

	// PORTを監視するサーバソケットを生成
	//(1) ServerSocket servsock = new ServerSocket(SPORT);
	//(2) ServerSocket servsock = new ServerSocket(0);
	//(3) ServerSocket servsock = new ServerSocket();
	//    servsock.bind(new InetSocketAddress("localhost", SPORT));
	//(4) ServerSocket servsock = new ServerSocket();
	//    servsock.bind(new InetSocketAddress("localhost", 0));
	//(5) ServerSocket servsock = new ServerSocket();
	//    servsock.bind(new InetSocketAddress(myAddr, SPORT));
	//(6) ServerSocket servsock = new ServerSocket();
	//    servsock.bind(new InetSocketAddress(myAddr, 0));

	System.out.println("IP=" + servsock.getInetAddress().getHostAddress() +
			   ",PORT="+servsock.getLocalPort() +
			   "でソケット生成（LISTEN状態）");
	
	while (true) {	    
	    // 接続受付
	    Socket sock = servsock.accept(); 
	    
	    // ソケットの入力ストリームを得る（バイトレベルデータ）
	    InputStream instr = sock.getInputStream();

	    // 読み取り用文字レベルデータに変換（コード変換）
	    InputStreamReader isr = new InputStreamReader(instr);
	    //InputStreamReader isr = new InputStreamReader(instr, "EUC-JP");   //日本語EUCコード
	    //InputStreamReader isr = new InputStreamReader(instr, "ISO2022JP");   //JISコード

	    // テキストを簡単に処理できるclassを利用する
	    BufferedReader reader = new BufferedReader(isr);
	    
	    // クライアントのIPアドレスを取得
	    InetAddress cAddr = sock.getInetAddress();
	    
	    // クライアントのポート番号を取得
	    int cPort = sock.getPort();
	    
	    // 受信したクライアント情報
	    System.out.println("Received (IP=" + cAddr.getHostAddress() + 
			       ", Port=" + cPort +
			       ") " + cAddr.getHostName());

	    System.out.printf("Received message : ");
	    String aLine=null;
	    while ((aLine = reader.readLine()) != null) {  //ストリームからテキストを１行取得する
		System.out.println(aLine);  //ディスプレイに出力
	    }
	    
	    //終了処理
	    reader.close();
	    isr.close();
	    instr.close();
	    sock.close();
	}
	
    }
}
