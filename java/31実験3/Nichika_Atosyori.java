/*
 *�@�Z�W�摜���l�����A�c���A���k���s��
 * ���͉摜�F8�r�b�g�Z�W�摜
 * �o�͉摜�F8�r�b�g�Z�W�摜
 * ���s���@�@% java Nichika_Atosyori X Y s (a,b,c,d���w�肷��j

X: ���͉摜�t�@�C�����i8bit/pixel�̔Z�W�摜�j
Y: �o�͉摜�t�@�C����(png�`���ŏo�͂���j
�@�@�@�o�͉摜�͓�l�摜�ł��邪�C�Z�W�摜�t�H�[�}�b�g�ŏo��
�@�@�@�O�i��f�F�O�i���j
�@�@�@�w�i��f�F�Q�T�T�i���j

s: ��l���̂������l�i�Œ肵�����l�@�j

��l��������͏������w������i���������w�����Ȃ��ꍇ�͓�l���̂݁j

�@�@�@�W�ߖT���k�����Fa
�@�@�@�W�ߖT�c�������Fb
�@�@�@�S�ߖT���k�����Fc
�@�@�@�S�ߖT�c�������Fd

��j�W�ߖT���k�������Q��J��Ԃ��C�W�ߖT�c���������Q��J��Ԃ�

java Nichika_Atosyori X Y 150 a a b b

��j�S�ߖT�c���������R��J��Ԃ��C�S�ߖT���k�������R��J��Ԃ�

java Nichika_Atosyori X Y 150 d d d c c c

��j��l���݂̂��s��

java Nichika_Atosyori X Y 150


�ȏ�ł��D
/* ���l
���̃v���O�����́C
�O�i��f��0�i���j
�w�i��f��255�i���j
�Ƃ��ď������Ă���D
*/

import java.awt.image.BufferedImage;
import java.awt.image.ColorModel;
import java.awt.image.WritableRaster;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;

public class Nichika_Atosyori {
    /*  �f�o�b�O���b�Z�[�W�p�t���O
     *  true �̏ꍇ�C�������̃��b�Z�[�W���R���\�[���ɏo�͂����
     */
    static final boolean        DEBUG = true;

    private static BufferedImage img = null;

    private static int M=-1; // ���T�C�Y
    
    private static int N=-1; // �c�T�C�Y
    
    private static int ImgSize=-1; // ����f��
    
    private static int[] f=null; // ���摜�̉�f�l
    
    private static int[] g=null; // ������̉�f�l
    
    private static String usage="java Nichika_Atosyori ���͉摜�i8bit/pixel�Z�W�摜) �o�͉摜 ��l���������l(0�`255) �܂��́Cjava Nichika_Atosyori ���͉摜�i8bit/pixel�Z�W�摜) �o�͉摜 ��l���������l(0�`255) ����w���ia,b,c,d���w�肷��j";

    public static void main(String[] args) {
	String[] dousa=null;

	//�R�}���h���C�������̃`�F�b�N
	if (args.length < 3) {
	    System.out.println(usage);
	    System.exit(1);
	}
	//��O�����̒l���`�F�b�N
	int shikiichi = Integer.parseInt(args[2]);
	if (shikiichi < 0 || shikiichi > 255) {
	    System.out.println("�������l�� �i0�`255�j �̒�����w�肵�Ă��������B");
	    System.exit(1);
	}

	//�����n����擾����
	int num = args.length - 3;  //������
	if (num == 0) { //��l�������s��Ȃ�
	    dousa = new String[1];
	    dousa[0] = "z";
	}
	else {
	    dousa = new String[num];
	    for (int i=0; i<num; i++) {
		if (!args[3+i].equals("a") && !args[3+i].equals("b") && !args[3+i].equals("c") && !args[3+i].equals("d")) {
		    System.out.println("������ �ia, b, c, d�j �̒�����w�肵�Ă��������B[ " + args[3+i] + " ]");
		    System.exit(1);
		}
		dousa[i] = args[3+i];
	    }
	}
	
	ReadImage(args[0]); // �摜�f�[�^��ǂݍ���
	
	Nichika(shikiichi);
	Atosyori(dousa);
	
	WriteImage(args[1]); // �摜�f�[�^�������o��
	
	System.out.println("Done.");
    }
    
    private static void ReadImage(String rfname) { // �摜�f�[�^��ǂݍ���
	if (DEBUG) {
	    System.out.println("Input Image = " + rfname);
	}
	
	try {
	    img = ImageIO.read(new File(rfname));
	} catch (Exception e) {
	    e.printStackTrace();
	}
	
	if (img != null) {
	    M = img.getWidth(); // ����ݒ�
	    N = img.getHeight(); // ������ݒ�
	    ImgSize = M * N; // ����f����ݒ�
	} else {
	    System.out.println("img = null !!!, something is wrong.");
	    System.exit(1);
	}
	
	// 8�r�b�g�Z�W�摜���ۂ����`�F�b�N����
	ColorModel cm = img.getColorModel();
	if (cm.getPixelSize() != 8 || cm.getNumColorComponents() != 1) {
	    System.out.println("GetProperty = " + img.getProperty(rfname));
	    System.out.println(img.toString());
	    System.out.println(" Type = " +img.getType());
	    System.out.println("���͉摜�ɂ�8bit/pixel�̔Z�W�摜���w�肵�Ă��������B");
	    System.exit(1);
	}
	//System.out.println("GetProperty = " + img.getProperty(rfname));
	//System.out.println(img.toString());
	
	// ��f�f�[�^��z��f�ɓǂݍ���
	WritableRaster ras = img.getRaster();
	f = new int[ImgSize];
	g = new int[ImgSize];
	for (int i = 0; i < ImgSize; i++) {
	    f[i] = ras.getDataBuffer().getElem(i);
	}
    }

    private static void Nichika(int shikiichi) { //shikiichi�̒l�Ɋ�Â���l�����s��
	System.out.println("�i�������l = " + shikiichi + "�j��2�l�����܂�");
	for (int i = 0; i < ImgSize; i++) {
	    g[i] = (f[i]>shikiichi) ? 255 : 0;
	    //�O�i��f��:0�i���j
	    //�w�i��f��:255�i���j
	}
    }

    private static void Atosyori(String[] dousa) { //dousa�̒l�Ɋ�Â����k�c�����s��

	for (int i=0; i<dousa.length; i++) {
	    if (dousa[i].equals("a")) {
		System.out.println("�W�ߖT���k�������s���܂�");
		syu_syuku8();
	    }
	    else if (dousa[i].equals("b")) {
		System.out.println("�W�ߖT�c���������s���܂�");
		bo_chou8();
	    }
	    else if (dousa[i].equals("c")) {
		System.out.println("�S�ߖT���k�������s���܂�");	    
		syu_syuku4();
	    }
	    else if (dousa[i].equals("d")) {
		System.out.println("�S�ߖT�c���������s���܂�");	    
		bo_chou4();
	    }
	    else {
		System.out.println("�����������܂���");
	    }
	}
    }

    private static void bo_chou8() { //g�ɑ΂��ĂW�ߖT�c���������s��
	int[] temp = new int[ImgSize];

	for (int i=0; i<ImgSize; i++) {
	    temp[i] = g[i];
	}

	for (int i=1; i<N-1; i++) {
	    for (int j=1; j<M-1; j++) {
		if (g[i*M+j] == 255) {
		    //8�ߖT���`�F�b�N
		    int flg = 0;
		    for (int ii=i-1; ii<=i+1; ii++) {
			for (int jj=j-1; jj<=j+1; jj++) {
			    flg += g[ii*M+jj];
			}
		    }
		    //�O�i��f�����������ꍇ�̏���
		    if (flg != (255*9)) {
			temp[i*M+j] = 0;
		    }
		}
	    }
	}

	for (int i=0; i<ImgSize; i++) {
	    g[i] = temp[i];
	}
    }

    private static void bo_chou4() { //g�ɑ΂���4�ߖT�c���������s��
	int[] temp = new int[ImgSize];
	int[] x4 = {0,-1,1,0};
	int[] y4 = {-1, 0, 0, 1};

	for (int i=0; i<ImgSize; i++) {
	    temp[i] = g[i];
	}

	for (int i=1; i<N-1; i++) {
	    for (int j=1; j<M-1; j++) {
		if (g[i*M+j] == 255) {
		    //4�ߖT���`�F�b�N
		    int flg = 0;
		    for (int k=0; k<4; k++) {
			flg += g[(i+y4[k])*M+(j+x4[k])];
		    }
		    //�O�i��f�����������ꍇ�̏���
		    if (flg != (255*4)) {
			temp[i*M+j] = 0;
		    }
		}
	    }
	}

	for (int i=0; i<ImgSize; i++) {
	    g[i] = temp[i];
	}
    }


    private static void syu_syuku8() { //g�ɑ΂���8�ߖT���k�������s��
	int[] temp = new int[ImgSize];

	for (int i=0; i<ImgSize; i++) {
	    temp[i] = g[i];
	}

	for (int i=1; i<N-1; i++) {
	    for (int j=1; j<M-1; j++) {
		if (g[i*M+j] == 0) {
		    //8�ߖT���`�F�b�N
		    int flg = 0;
		    for (int ii=i-1; ii<=i+1; ii++) {
			for (int jj=j-1; jj<j+1; jj++) {
			    flg += g[ii*M+jj];
			}
		    }
		    //�w�i��f�����������ꍇ�̏���
		    if (flg != 0) {
			temp[i*M+j] = 255;
		    }
		}
	    }
	}

	for (int i=0; i<ImgSize; i++) {
	    g[i] = temp[i];
	}
    }

    private static void syu_syuku4() { //g�ɑ΂���4�ߖT���k�������s��
	int[] temp = new int[ImgSize];
	int[] x4 = {0,-1,1,0};
	int[] y4 = {-1, 0, 0, 1};

	for (int i=0; i<ImgSize; i++) {
	    temp[i] = g[i];
	}

	for (int i=1; i<N-1; i++) {
	    for (int j=1; j<M-1; j++) {
		if (g[i*M+j] == 0) {
		    //4�ߖT���`�F�b�N
		    int flg = 0;
		    for (int k=0; k<4; k++) {
			flg += g[(i+y4[k])*M+(j+x4[k])];
		    }
		    //�w�i��f�����������ꍇ�̏���
		    if (flg != 0) {
			temp[i*M+j] = 255;
		    }
		}
	    }
	}

	for (int i=0; i<ImgSize; i++) {
	    g[i] = temp[i];
	}
    }

    private static void WriteImage(String wfname) {
	WritableRaster ras = img.getRaster();
	
	ras.setPixels(0, 0, M, N, g);
	
	try {
	    ImageIO.write(img, "png", new File(wfname));
	} catch (Exception e) {
	    e.printStackTrace();
	}
	if (DEBUG) {
	    System.out.println("Output Image = " + wfname);
	}
    }
}
