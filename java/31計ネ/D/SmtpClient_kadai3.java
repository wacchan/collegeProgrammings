import java.net.*;
import java.io.*;
import java.util.*;
import java.text.*;

public class SmtpClient_kadai3 {
	static final int SMTP_PORT = 25; // �|�[�g�ԍ�
	static final String SMTP_Server = "orange.mip.ces.kyutech.ac.jp"; // SMTP�T�[�o��
	static final String fromAddress = "b17236082@orange.mip.ces.kyutech.ac.jp"; // FROM�A�h���X
	static final String toAddress = "cnw@orange.mip.ces.kyutech.ac.jp"; // TO�A�h���X
	static final String subjectText = "�����y�ۑ�3�z"; // �����iSubject�j�ۑ�3�ŕύX
	static String smtpCommand = null; // SMTP�̃R�}���h
	static String line = null; // �T�[�o����̕ԓ����i�[
	static String firstString = null; // �ԓ��̍ŏ��̕�����
	static String dataString = null; // DATA�R�}���h���M������
	static String[] strs = null; // �ԓ����󔒂ŕ����������ʂ��i�[����

	static OutputStream outstr = null;
	static OutputStreamWriter osw = null;
	static PrintWriter writer = null;
	static Socket socket = null;
	static InputStream instr = null;
	static InputStreamReader isr = null;
	static BufferedReader reader = null;

	// ���͗p�X�g���[���ɕ�����data����������
	public static void writeSomething(String data) throws IOException {
		writer.println(data);
		writer.flush();
	}

	// �R�}���hcomm�𔭂��āA�ԓ��R�[�h��code���ۂ��`�F�b�N����
	// code���������ꍇ�F�����𑱍s�A code���Ԉ���Ă���ꍇ�F�v���O�����𒆒f
	static void smtpCommandCheck(String comm, String code) throws IOException {
		System.out.print("�R�}���h:[" + comm + "]\t");
		writeSomething(comm);

		line = reader.readLine();
		strs = line.split(" ");
		firstString = strs[0];

		if (firstString.equals(code)) {
			System.out.println("�ԓ��R�[�h:[" + firstString + "]\t" + "PASSED\t");
		} else {
			System.err.println("�ԓ��R�[�h:[" + firstString + "]\t" + "FAILED" + "( neq " + code + " )");
			System.exit(1); // �v���O�������~�߂�
		}
	}

	// �w�b�_�[���̑��M
	public static void sendHeader() throws IOException {
		// �w�b�_�[Date
		Date date1 = new Date();
		DateFormat df1 = new SimpleDateFormat("EEE, d MMM yyyy HH:mm:ss Z (z)", Locale.US);
		String dateMoji = df1.format(date1).toString();
		dataString = "Date: " + dateMoji;
		writeSomething(dataString);
		System.out.println("�@�@�@�@�@  - " + dataString); //

		// �w�b�_�[From
		dataString = "From: " + fromAddress;
		writeSomething(dataString);
		System.out.println("�@�@�@�@�@  - " + dataString);

		// �w�b�_�[To
		dataString = "To: " + toAddress;
		writeSomething(dataString);
		System.out.println("�@�@�@�@�@  - " + dataString);

		// �w�b�_�[Subject 2
		dataString = subjectText;
		writeSomething(dataString);
		System.out.println("�@�@�@�@�@  - " + dataString);


	}

	// ���b�Z�[�W�̑��M
	public static void sendBody() throws IOException {
		//dataString = "This is a test mail in English (Computer Network) from " + fromAddress + "."; // ���b�Z�[�W�{��

		dataString = "�����̖{���ł��B"; // �ۑ�3�ŕύX
		writeSomething(dataString);
		System.out.println("�@�@�@�@�@  - " + dataString);
	}

	public static void sendMailContents() throws IOException {
		// DATA�R�}���h�̑��M
		sendHeader();

		// �w�b�_�[�ƃ��b�Z�[�W�𕪊����邽�߂ɉ��s�𑗐M
		dataString = "";
		writeSomething(dataString);
		System.out.println("�@�@�@�@�@  - " + dataString);

		sendBody();

		// ���b�Z�[�W�̏I����\���s���̃s���I�h�𑗐M
		smtpCommand = ".";
		smtpCommandCheck(smtpCommand, "250");
	}

	public static void main(String[] argv) throws IOException {
		// IPv4�ŋN������
		System.setProperty("java.net.preferIPv4Stack", "true");

		// ���M��IP�A�h���X�ƃ|�[�g�ԍ����w�肵�C�\�P�b�g�𐶐�
		System.out.println("�T�[�o " + SMTP_Server + " ��SMTP�Őڑ����܂�");
		Socket socket = new Socket(SMTP_Server, SMTP_PORT);

		// �\�P�b�g�̏o�͗p�X�g���[���𓾂�
		outstr = socket.getOutputStream();
		osw = new OutputStreamWriter(outstr, "ISO-2022-JP");
		writer = new PrintWriter(osw);

		// �\�P�b�g�̓��͗p�X�g���[���𓾂�
		instr = socket.getInputStream();
		isr = new InputStreamReader(instr);
		reader = new BufferedReader(isr);

		// ���͗p�X�g���[�������s���o��
		line = reader.readLine();
		// �󔒂���؂蕶���Ƃ��āA������𕪊�����
		strs = line.split(" ");

		// �ŏ��̕�����
		firstString = strs[0];
		// �ԓ��R�[�h�̃`�F�b�N
		if (firstString.equals("220")) {
			System.out.println("�ԓ��R�[�h:[" + firstString + "]\t" + "PASSED\t");
		} else {
			System.err.println("�ԓ��R�[�h:[" + firstString + "]\t" + "FAILED" + "( neq 220 )");
			System.exit(1);
		}

		// ������IP�A�h���X���擾
		InetAddress myAddr = InetAddress.getLocalHost();
		// ������FQDN���擾
		String FQDN = myAddr.getCanonicalHostName();
		// ��HELO�R�}���h�̑��M
		smtpCommand = "HELO " + FQDN;
		smtpCommandCheck(smtpCommand, "250");

		// ��MAIL FROM�R�}���h�̑��M
		smtpCommand = "MAIL FROM: " + fromAddress;
		smtpCommandCheck(smtpCommand, "250");

		//��RCPT TO�R�}���h�̑��M
		smtpCommand = "RCPT TO: " + toAddress;
		smtpCommandCheck(smtpCommand, "250");
		
		//�����[���̒��g�𑗂�
		smtpCommand = "DATA";
		smtpCommandCheck(smtpCommand, "354");
		sendMailContents();
		
		//��QUIT�R�}���h�̑��M
		smtpCommand = "QUIT";
		smtpCommandCheck(smtpCommand, "221");

		// �I������
		reader.close();
		isr.close();
		instr.close();
		writer.close();
		osw.close();
		outstr.close();
		socket.close();
	}
}
