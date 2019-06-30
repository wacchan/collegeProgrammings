import java.net.*;
import java.io.*;
import java.util.*;
import java.text.*;

public class SmtpClient_kadai3 {
	static final int SMTP_PORT = 25; // ポート番号
	static final String SMTP_Server = "orange.mip.ces.kyutech.ac.jp"; // SMTPサーバ名
	static final String fromAddress = "b17236082@orange.mip.ces.kyutech.ac.jp"; // FROMアドレス
	static final String toAddress = "cnw@orange.mip.ces.kyutech.ac.jp"; // TOアドレス
	static final String subjectText = "漢字【課題3】"; // 件名（Subject）課題3で変更
	static String smtpCommand = null; // SMTPのコマンド
	static String line = null; // サーバからの返答を格納
	static String firstString = null; // 返答の最初の文字列
	static String dataString = null; // DATAコマンド送信する情報
	static String[] strs = null; // 返答を空白で分割した結果を格納する

	static OutputStream outstr = null;
	static OutputStreamWriter osw = null;
	static PrintWriter writer = null;
	static Socket socket = null;
	static InputStream instr = null;
	static InputStreamReader isr = null;
	static BufferedReader reader = null;

	// 入力用ストリームに文字列dataを書き込む
	public static void writeSomething(String data) throws IOException {
		writer.println(data);
		writer.flush();
	}

	// コマンドcommを発して、返答コードがcodeか否かチェックする
	// codeが正しい場合：処理を続行、 codeが間違っている場合：プログラムを中断
	static void smtpCommandCheck(String comm, String code) throws IOException {
		System.out.print("コマンド:[" + comm + "]\t");
		writeSomething(comm);

		line = reader.readLine();
		strs = line.split(" ");
		firstString = strs[0];

		if (firstString.equals(code)) {
			System.out.println("返答コード:[" + firstString + "]\t" + "PASSED\t");
		} else {
			System.err.println("返答コード:[" + firstString + "]\t" + "FAILED" + "( neq " + code + " )");
			System.exit(1); // プログラムを止める
		}
	}

	// ヘッダー情報の送信
	public static void sendHeader() throws IOException {
		// ヘッダーDate
		Date date1 = new Date();
		DateFormat df1 = new SimpleDateFormat("EEE, d MMM yyyy HH:mm:ss Z (z)", Locale.US);
		String dateMoji = df1.format(date1).toString();
		dataString = "Date: " + dateMoji;
		writeSomething(dataString);
		System.out.println("　　　　　  - " + dataString); //

		// ヘッダーFrom
		dataString = "From: " + fromAddress;
		writeSomething(dataString);
		System.out.println("　　　　　  - " + dataString);

		// ヘッダーTo
		dataString = "To: " + toAddress;
		writeSomething(dataString);
		System.out.println("　　　　　  - " + dataString);

		// ヘッダーSubject 2
		dataString = subjectText;
		writeSomething(dataString);
		System.out.println("　　　　　  - " + dataString);


	}

	// メッセージの送信
	public static void sendBody() throws IOException {
		//dataString = "This is a test mail in English (Computer Network) from " + fromAddress + "."; // メッセージ本体

		dataString = "漢字の本文です。"; // 課題3で変更
		writeSomething(dataString);
		System.out.println("　　　　　  - " + dataString);
	}

	public static void sendMailContents() throws IOException {
		// DATAコマンドの送信
		sendHeader();

		// ヘッダーとメッセージを分割するために改行を送信
		dataString = "";
		writeSomething(dataString);
		System.out.println("　　　　　  - " + dataString);

		sendBody();

		// メッセージの終了を表す行頭のピリオドを送信
		smtpCommand = ".";
		smtpCommandCheck(smtpCommand, "250");
	}

	public static void main(String[] argv) throws IOException {
		// IPv4で起動する
		System.setProperty("java.net.preferIPv4Stack", "true");

		// 送信先IPアドレスとポート番号を指定し，ソケットを生成
		System.out.println("サーバ " + SMTP_Server + " にSMTPで接続します");
		Socket socket = new Socket(SMTP_Server, SMTP_PORT);

		// ソケットの出力用ストリームを得る
		outstr = socket.getOutputStream();
		osw = new OutputStreamWriter(outstr, "ISO-2022-JP");
		writer = new PrintWriter(osw);

		// ソケットの入力用ストリームを得る
		instr = socket.getInputStream();
		isr = new InputStreamReader(instr);
		reader = new BufferedReader(isr);

		// 入力用ストリームから一行取り出す
		line = reader.readLine();
		// 空白を区切り文字として、文字列を分割する
		strs = line.split(" ");

		// 最初の文字列
		firstString = strs[0];
		// 返答コードのチェック
		if (firstString.equals("220")) {
			System.out.println("返答コード:[" + firstString + "]\t" + "PASSED\t");
		} else {
			System.err.println("返答コード:[" + firstString + "]\t" + "FAILED" + "( neq 220 )");
			System.exit(1);
		}

		// 自分のIPアドレスを取得
		InetAddress myAddr = InetAddress.getLocalHost();
		// 自分のFQDNを取得
		String FQDN = myAddr.getCanonicalHostName();
		// ★HELOコマンドの送信
		smtpCommand = "HELO " + FQDN;
		smtpCommandCheck(smtpCommand, "250");

		// ★MAIL FROMコマンドの送信
		smtpCommand = "MAIL FROM: " + fromAddress;
		smtpCommandCheck(smtpCommand, "250");

		//★RCPT TOコマンドの送信
		smtpCommand = "RCPT TO: " + toAddress;
		smtpCommandCheck(smtpCommand, "250");
		
		//★メールの中身を送る
		smtpCommand = "DATA";
		smtpCommandCheck(smtpCommand, "354");
		sendMailContents();
		
		//★QUITコマンドの送信
		smtpCommand = "QUIT";
		smtpCommandCheck(smtpCommand, "221");

		// 終了処理
		reader.close();
		isr.close();
		instr.close();
		writer.close();
		osw.close();
		outstr.close();
		socket.close();
	}
}
