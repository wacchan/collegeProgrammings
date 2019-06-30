import java.net.*;
import java.io.*;

public class ReportTCPClient2 {
    
    public static void main(String[] args) throws Exception {

	
	String usage = "usage : java ReoirtTCPClient1 host port";

        if (args.length != 2) {
            System.out.println("�ڑ���z�X�g�A�|�[�g�ԍ����w�肵�Ă������� " + args.length);
	    System.out.println(usage);
            System.exit(1);
        }
	String SERVERNAME=args[0];  //�������͐ڑ���FQDN ( or IP�A�h���X�j
        int SPORT = Integer.parseInt(args[1]);  //�������̓|�[�g�ԍ�

	//IPv4�ŋN������
        System.setProperty("java.net.preferIPv4Stack", "true");

	// ����IP�A�h���X�ƃ|�[�g�ԍ����w�肵�C�\�P�b�g�𐶐�
	Socket socket = new Socket(InetAddress.getByName(SERVERNAME), SPORT);

	//socket���g���ăT�[�o��IP�A�h���X���擾
	InetAddress sAddr = socket.getInetAddress();
            
	//socket���g���ăT�[�o�̃|�[�g�ԍ����擾
	int sPort = socket.getPort();

	//�T�[�o�̃\�P�b�g���
	String serverInfo = "�@�@�T�[�o�\�P�b�g (IP=" + sAddr.getHostAddress() + 
                ", Port=" + sPort +
                ") " + sAddr.getHostName() ;

	//�T�[�o�̃\�P�b�g����W���o�͂ɏo��
	System.out.println(serverInfo);

	//(1)���͗p�X�g���[���̏���
	InputStream instr = socket.getInputStream();
	InputStreamReader isr = new InputStreamReader(instr); 
	BufferedReader reader = new BufferedReader(isr);

	//(2)�o�͗p�X�g���[���̏���
	OutputStream outstr = socket.getOutputStream();
	OutputStreamWriter osw = new OutputStreamWriter(outstr); 
	PrintWriter writer = new PrintWriter(osw);
	
	//(3)�L�[���[�hend�����͂����܂ŁA�L�[�{�[�h������͂��ꂽ��������X�g���[���ɏ�������
	InputStreamReader isr2 = new InputStreamReader(System.in); 
	BufferedReader br = new BufferedReader(isr2);

	System.out.println("���͂��Ă�������");

	//   ���o�̓X�g���[���ɏ������ޖ���flush���邱��
	while (true) {
		String aLine = br.readLine(); //�L�[�{�[�h������͂��ꂽ�e�L�X�g���P�s�擾����
		if (aLine.equals("END")) {   //������[END]�̏ꍇ���[�v���o��
		    System.out.println("GET KEYWORD [END]");
		    break;
		}
		else {   //������[END]�ȊO�̎��́A���͂��ꂽ�������ۑ����A�o�͂���
		    
		    System.out.println("-"+aLine);  //�f�B�X�v���C�ɏo��
		}
		writer.println(aLine);  //�T�[�o�[�ɑ���
		writer.flush();
	}

	//(4)�o�̓X�g���[���ɃL�[���[�hEND_CLIENT����������
	writer.println("END_CLIENT");

	//(5)�o�̓X�g���[����flush����
	writer.flush();

	System.out.println("�@�@�T�[�o������̃��b�Z�[�W�ł�");

	//(6)�L�[���[�hEND_SERVER����M����܂ŁA�T�[�o������̃��b�Z�[�W���e�L�X�g�łP�s�Âǂ݁A�W���o�͂ɏo���B
	String message = null;

	while (true) {
		String aLine = reader.readLine(); //�X�g���[������e�L�X�g���P�s�擾����
		if (aLine.equals("END_SERVER")) {   //������[END_CLIENT]�̏ꍇ���[�v���o��
		    System.out.println("GET KEYWORD [END_SERVER]");
		    break;
		}
		else {   //������[END_CLIENT]�ȊO�̎��́A���͂��ꂽ�������ۑ����A�o�͂���
		    aLine = " - " + aLine + System.getProperty("line.separator");
		    if (message == null) message = aLine;
		    else message += aLine;
		    System.out.printf(aLine);  //�f�B�X�v���C�ɏo��
		}
	}

	//(7)�I������
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

