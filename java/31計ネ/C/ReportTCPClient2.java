import java.net.*;
import java.io.*;

public class ReportTCPClient2 {
    
    public static void main(String[] args) throws Exception {

	
	String usage = "usage : java ReoirtTCPClient1 host port";

        if (args.length != 2) {
            System.out.println("接続先ホスト、ポート番号を指定してください " + args.length);
	    System.out.println(usage);
            System.exit(1);
        }
	String SERVERNAME=args[0];  //第一引数は接続先FQDN ( or IPアドレス）
        int SPORT = Integer.parseInt(args[1]);  //第二引数はポート番号

	//IPv4で起動する
        System.setProperty("java.net.preferIPv4Stack", "true");

	// 宛先IPアドレスとポート番号を指定し，ソケットを生成
	Socket socket = new Socket(InetAddress.getByName(SERVERNAME), SPORT);

	//socketを使ってサーバのIPアドレスを取得
	InetAddress sAddr = socket.getInetAddress();
            
	//socketを使ってサーバのポート番号を取得
	int sPort = socket.getPort();

	//サーバのソケット情報
	String serverInfo = "　　サーバソケット (IP=" + sAddr.getHostAddress() + 
                ", Port=" + sPort +
                ") " + sAddr.getHostName() ;

	//サーバのソケット情報を標準出力に出す
	System.out.println(serverInfo);

	//(1)入力用ストリームの準備
	InputStream instr = socket.getInputStream();
	InputStreamReader isr = new InputStreamReader(instr); 
	BufferedReader reader = new BufferedReader(isr);

	//(2)出力用ストリームの準備
	OutputStream outstr = socket.getOutputStream();
	OutputStreamWriter osw = new OutputStreamWriter(outstr); 
	PrintWriter writer = new PrintWriter(osw);
	
	//(3)キーワードendが入力されるまで、キーボードから入力された文字列をストリームに書き込む
	InputStreamReader isr2 = new InputStreamReader(System.in); 
	BufferedReader br = new BufferedReader(isr2);

	System.out.println("入力してください");

	//   ※出力ストリームに書き込む毎にflushすること
	while (true) {
		String aLine = br.readLine(); //キーボードから入力されたテキストを１行取得する
		if (aLine.equals("END")) {   //文字列が[END]の場合ループを出る
		    System.out.println("GET KEYWORD [END]");
		    break;
		}
		else {   //文字列が[END]以外の時は、入力された文字列を保存し、出力する
		    
		    System.out.println("-"+aLine);  //ディスプレイに出力
		}
		writer.println(aLine);  //サーバーに送る
		writer.flush();
	}

	//(4)出力ストリームにキーワードEND_CLIENTを書き込む
	writer.println("END_CLIENT");

	//(5)出力ストリームをflushする
	writer.flush();

	System.out.println("　　サーバ側からのメッセージです");

	//(6)キーワードEND_SERVERを受信するまで、サーバ側からのメッセージをテキストで１行づつ読み、標準出力に出す。
	String message = null;

	while (true) {
		String aLine = reader.readLine(); //ストリームからテキストを１行取得する
		if (aLine.equals("END_SERVER")) {   //文字列が[END_CLIENT]の場合ループを出る
		    System.out.println("GET KEYWORD [END_SERVER]");
		    break;
		}
		else {   //文字列が[END_CLIENT]以外の時は、入力された文字列を保存し、出力する
		    aLine = " - " + aLine + System.getProperty("line.separator");
		    if (message == null) message = aLine;
		    else message += aLine;
		    System.out.printf(aLine);  //ディスプレイに出力
		}
	}

	//(7)終了処理
	writer.close();
	osw.close();
	outstr.close();
	reader.close();
	isr.close();
	instr.close();
	socket.close();	
	br.close();
    }
}

