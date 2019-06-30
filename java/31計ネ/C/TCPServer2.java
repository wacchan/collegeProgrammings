import java.net.*;
import java.io.*;

public class TCPServer2 {
    
    public static void main(String[] argv) throws Exception {
        System.setProperty("java.net.preferIPv4Stack", "true");    	//IPv4�ŋN������

	InetAddress myAddr = InetAddress.getLocalHost();       //������IP�A�h���X���擾
	//InetAddress myAddr = InetAddress.getByName("127.0.0.1");  

	//ServerSocket servsock = new ServerSocket();
	ServerSocket servsock = new ServerSocket(60600);
	//ServerSocket servsock = new ServerSocket(60600,1,myAddr);
	//servsock.bind(new InetSocketAddress("localhost", 60600));
	//servsock.bind(new InetSocketAddress(myAddr, 60600));

	System.out.println("IP=" + servsock.getInetAddress().getHostAddress() +
			   ",PORT="+servsock.getLocalPort() +
			   "�Ń\�P�b�g�����iLISTEN��ԁj");
	
	while (true) {	    
	    // �ڑ���t
	    Socket sock = servsock.accept(); 

	    //(1)���͗p�X�g���[���̏���
	    //   �\�P�b�g�̓��̓X�g���[���𓾂�i�o�C�g���x���f�[�^�j
	    InputStream instr = sock.getInputStream();
	    //   �ǂݎ��p�������x���f�[�^�ɕϊ��i�R�[�h�ϊ��j
	    InputStreamReader isr = new InputStreamReader(instr);
	    //   �e�L�X�g���ȒP�ɏ����ł���class�𗘗p����
	    BufferedReader reader = new BufferedReader(isr);

	    //(2)�o�͗p�X�g���[���̏���
	    //   �\�P�b�g�̏o�͗p�X�g���[���𓾂�i�o�C�g���x���f�[�^�j
	    OutputStream outstr = sock.getOutputStream();
	    //   �������ݗp�������x���f�[�^�ɕϊ��i�R�[�h�ϊ��j
	    OutputStreamWriter osw = new OutputStreamWriter(outstr);
	    //   �e�L�X�g���ȒP�ɏ����ł���classs�𗘗p����
	    PrintWriter writer = new PrintWriter(osw);
	    
	    //(3)�N���C�A���g��IP�A�h���X���擾
	    InetAddress cAddr = sock.getInetAddress();
	    
	    //(4)�N���C�A���g�̃|�[�g�ԍ����擾
	    int cPort = sock.getPort();
	    
	    //(5)��M�����N���C�A���g���
	    String clientInfo = " - Received (IP=" + cAddr.getHostAddress() + 
		", Port=" + cPort +
		") " + cAddr.getHostName() ;

	    //(6) (5)��W���o�͂ɏo��
	    System.out.println("�@�@�i�N���C�A���g�̃\�P�b�g���j");
	    System.out.println(clientInfo);

	    //(7) ��M���b�Z�[�W��ۑ����A�W���o�͂ɏo��
	    System.out.println("�@�@�i�N���C�A���g������̃��b�Z�[�W�ł��j");

	    String message=null; // ��M���b�Z�[�W���i�[�����
	    while (true) {
		String aLine = reader.readLine(); //�X�g���[������e�L�X�g���P�s�擾����
		if (aLine.equals("END_CLIENT")) {   //������[END_CLIENT]�̏ꍇ���[�v���o��
		    System.out.println("GET KEYWORD [END_CLIENT]");
		    break;
		}
		else {   //������[END_CLIENT]�ȊO�̎��́A���͂��ꂽ�������ۑ����A�o�͂���
		    aLine = " - " + aLine + System.getProperty("line.separator");
		    if (message == null) message = aLine;
		    else message += aLine;
		    System.out.printf(aLine);  //�f�B�X�v���C�ɏo��
		}
	    }

	    //(8) �N���C�A���g�Ƀ��b�Z�[�W�𑗐M����
	    writer.println(clientInfo);  // (5)�̏��
	    writer.println(message);   //(7)�̏��
	    writer.println("END_SERVER");  //�L�[���[�h�̑��M
	    writer.flush();   //�X�g���[���������o��

	    //�I������
	    writer.close();	    osw.close();	    outstr.close();
	    
	    reader.close();	    isr.close();	    instr.close();
	    
	    sock.close();     

	}
	
    }
}
