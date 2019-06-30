/*
 *�@Hilditch�̍א������s��
 *
 * ���͉摜�F8�r�b�g�Z�W�摜�i�O�ƂQ�T�T�̒l�����j
 * �o�͉摜�F8�r�b�g�Z�W�摜�i�O�ƂQ�T�T�̒l�����j
 */

import javax.imageio.ImageIO;
import java.awt.image.*;
import java.io.*;

public class Saisenka {
    /*
     * �f�o�b�O���b�Z�[�W�p�t���O true �̏ꍇ�C�������̃��b�Z�[�W���R���\�[���ɏo�͂����
     */
    private static final boolean DEBUG = true;
    private static BufferedImage img = null;
    private static int M=-1; // ���T�C�Y
    private static int N=-1; // �c�T�C�Y
    private static int ImgSize=-1; // ����f��
    private static int[] f=null; // ���摜�̉�f�l
    private static int[] g=null; // ������̉�f�l
    private static String usage="java Saisenka ���͉摜�i8bit/pixel�Z�W�摜�A�O�ƂQ�T�T�̒l����) �o�͉摜";

    //main���\�b�h
    public static void main(String args[]) {
	
	//�R�}���h���C�������̃`�F�b�N
	if (args.length != 2) {
	    System.out.println(usage);
	    System.exit(1);
	}

	ReadImage(args[0]); // �摜�f�[�^��ǂݍ���
	
	Thinning(); // �א��������s
	
	WriteImage(args[1]); // �摜�f�[�^�������o��
	
	System.out.println("Done.");
    }
    
    private static boolean delPoint(int ptr[]) {
	int[] Ns = {4, 5, 2, 1, 0, 3, 6, 7, 8, 5};
	int[] N8 = {1, 2, 3, 4, 5, 6, 7, 8, 1};
	int[] Nodd = {1,3,5,7};
	
	// ����2 - ���E��f�ł������
	{
	    int sum = 0;
	    for (int i=0; i<4; i++) 
		sum += (1-Math.abs(ptr[Ns[Nodd[i]]]));
			
	    if( !( sum >= 1 ) ) {
		return false;
	    }
	}
	
	// ����3 - �[�_���폜���Ȃ�����
	{
	    int sum = 0;
	    for (int i=0; i<8; i++) {
		sum += Math.abs(ptr[Ns[N8[i]]]);
	    }
	    if( !( sum >= 2 ) ) {
		return false;	
	    }
	}
	
	// ����4 - �Ǘ��_��ۑ��������
	{
	    int sum = 0;
	    for (int i=0; i<8; i++) {
		sum += ((ptr[Ns[N8[i]]] == 1) ? 1 : 0);
	    }
	    
	    if( !( sum >= 1 ) ) {
		return false;
	    }
	}
	
	
	// ����5 - �A������ۑ��������
	{
	    int sum = GetConnectNum(ptr); 
	    if( !( sum == 1 ) ){
		return false;	
	    }
	}
	
	// ����6 - ������2�̐����ɑ΂��āA���̕Б��݂̂��폜�������
	{
	    int sum=0;
	    for(int i=0 ; i<8 ; i++){
		if (ptr[Ns[N8[i]]] != -1) {
		    sum++;
		}
		else {
		    ptr[Ns[N8[i]]] = 0;
		    if (GetConnectNum(ptr) == 1) sum++;
		    ptr[Ns[N8[i]]] = -1;
		}
	    }
	    if( !( sum == 8 ) ){
		return false ;
	    }
	}
		
	return true;
    }
    
    // �A���������߂� 
    private static int GetConnectNum(int ptr[]) {
	int[] Ns = {4, 5, 2, 1, 0, 3, 6, 7, 8, 5};
	int[] N8 = {1, 2, 3, 4, 5, 6, 7, 8, 1};
	int[] Nodd = {1,3,5,7};
	
	int sum = 0;
	for (int i=0; i<4; i++) {
	    int csk = (Math.abs(ptr[Ns[Nodd[i]]]) == 1) ? 1 : 0;
	    int csk1 = (Math.abs(ptr[Ns[Nodd[i]+1]]) == 1) ? 1 : 0;
	    int csk2 = (Math.abs(ptr[Ns[Nodd[i]+2]]) == 1) ? 1 : 0;
	    
	    sum += ((1-csk)-(1-csk)*(1-csk1)*(1-csk2));
	    //sum += (csk-(csk*csk1*csk2));  //�ԈႢ
	}
	
	return sum;
    }
    
    private static void Thinning() {
	int del=0;  //�폜�\��f��������
	int[] ptr= new int[9];
	
	for (int i=0; i<ImgSize; i++) {
	    g[i] = f[i];
	}
	
	do {
	    del=0;
	    for (int i=1; i<N-1; i++) {
		for (int j=1; j<M-1; j++) {
		    
		    
		    if(g[i*M+j] == 1) {	//�O�i��f�Ȃ̂ō폜�\���𔻒�
			
			// 8�ߖT�f�[�^���o
			int k=0;
			for (int ii=i-1; ii<=i+1; ii++){
			    for (int jj=j-1; jj<=j+1; jj++) {
				ptr[k++] = g[ii*M+jj];
			    }
			}
			
			// �폜�\���ۂ��̔���
			if (delPoint(ptr)) {
			    g[i*M+j] = -1;
			    del++;
			}
		    }
		}
	    }
	    
	    //�u-1�v���u0�v�i�w�i��f�j�ɕύX����
	    for (int i=1; i<N-1; i++) {
		for (int j=1; j<M-1; j++) { 
		    if (g[i*M+j] == -1) {
			g[i*M+j] = 0;
		    }
		}
	    }
	    
	    System.out.println("Del = " +del);
	} while(del != 0);
		
	
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
	    System.exit(1);
	}
	
	// ��f�f�[�^��z��f�ɓǂݍ���
	WritableRaster ras = img.getRaster();
	f = new int[ImgSize];
	g = new int[ImgSize];
	for (int i = 0; i < ImgSize; i++) {
	    f[i] = ras.getDataBuffer().getElem(i);
	}
	
	// 2�l�摜���ۂ����`�F�b�N����
	for (int i=0; i<ImgSize; i++) {
	    if (f[i] != 0 && f[i] != 255) {
		System.out.println("An input image must be a bi-level image.");
		System.exit(1);				
	    }
	    // ������f��O�i��f�u�P�v�A������f��w�i��f�u�O�v�ɐݒ肷��
	    f[i] = (f[i] == 0) ? 1 : 0;
	}
	
	
    }
    
    private static void WriteImage(String wfname) {
	WritableRaster ras = img.getRaster();
	
	for (int i=0; i<ImgSize; i++) {
	    // �O�i��f�u�P�v��������f�A�w�i��f�u�O�v�𔒉�f�ɐݒ肷��
	    g[i] = (g[i] == 1) ? 0 : 255;
	}
	
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