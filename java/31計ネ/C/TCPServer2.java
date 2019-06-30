import java.net.*;
import java.io.*;

public class TCPServer2 {
    
    public static void main(String[] argv) throws Exception {
        System.setProperty("java.net.preferIPv4Stack", "true");    	//IPv4で起動する

	InetAddress myAddr = InetAddress.getLocalHost();       //自分のIPアドレスを取得
	//InetAddress myAddr = InetAddress.getByName("127.0.0.1");  

	//ServerSocket servsock = new ServerSocket();
	ServerSocket servsock = new ServerSocket(60600);
	//ServerSocket servsock = new ServerSocket(60600,1,myAddr);
	//servsock.bind(new InetSocketAddress("localhost", 60600));
	//servsock.bind(new InetSocketAddress(myAddr, 60600));

	System.out.println("IP=" + servsock.getInetAddress().getHostAddress() +
			   ",PORT="+servsock.getLocalPort() +
			   "でソケット生成（LISTEN状態）");
	
	while (true) {	    
	    // 接続受付
	    Socket sock = servsock.accept(); 

	    //(1)入力用ストリームの準備
	    //   ソケットの入力ストリームを得る（バイトレベルデータ）
	    InputStream instr = sock.getInputStream();
	    //   読み取り用文字レベルデータに変換（コード変換）
	    InputStreamReader isr = new InputStreamReader(instr);
	    //   テキストを簡単に処理できるclassを利用する
	    BufferedReader reader = new BufferedReader(isr);

	    //(2)出力用ストリームの準備
	    //   ソケットの出力用ストリームを得る（バイトレベルデータ）
	    OutputStream outstr = sock.getOutputStream();
	    //   書き込み用文字レベルデータに変換（コード変換）
	    OutputStreamWriter osw = new OutputStreamWriter(outstr);
	    //   テキストを簡単に処理できるclasssを利用する
	    PrintWriter writer = new PrintWriter(osw);
	    
	    //(3)クライアントのIPアドレスを取得
	    InetAddress cAddr = sock.getInetAddress();
	    
	    //(4)クライアントのポート番号を取得
	    int cPort = sock.getPort();
	    
	    //(5)受信したクライアント情報
	    String clientInfo = " - Received (IP=" + cAddr.getHostAddress() + 
		", Port=" + cPort +
		") " + cAddr.getHostName() ;

	    //(6) (5)を標準出力に出す
	    System.out.println("　　（クライアントのソケット情報）");
	    System.out.println(clientInfo);

	    //(7) 受信メッセージを保存し、標準出力に出す
	    System.out.println("　　（クライアント側からのメッセージです）");

	    String message=null; // 受信メッセージが格納される
	    while (true) {
		String aLine = reader.readLine(); //ストリームからテキストを１行取得する
		if (aLine.equals("END_CLIENT")) {   //文字列が[END_CLIENT]の場合ループを出る
		    System.out.println("GET KEYWORD [END_CLIENT]");
		    break;
		}
		else {   //文字列が[END_CLIENT]以外の時は、入力された文字列を保存し、出力する
		    aLine = " - " + aLine + System.getProperty("line.separator");
		    if (message == null) message = aLine;
		    else message += aLine;
		    System.out.printf(aLine);  //ディスプレイに出力
		}
	    }

	    //(8) クライアントにメッセージを送信する
	    writer.println(clientInfo);  // (5)の情報
	    writer.println(message);   //(7)の情報
	    writer.println("END_SERVER");  //キーワードの送信
	    writer.flush();   //ストリームを書き出す

	    //終了処理
	    writer.close();	    osw.close();	    outstr.close();
	    
	    reader.close();	    isr.close();	    instr.close();
	    
	    sock.close();     

	}
	
    }
}
