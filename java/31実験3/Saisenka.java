/*
 *　Hilditchの細線化を行う
 *
 * 入力画像：8ビット濃淡画像（０と２５５の値だけ）
 * 出力画像：8ビット濃淡画像（０と２５５の値だけ）
 */

import javax.imageio.ImageIO;
import java.awt.image.*;
import java.io.*;

public class Saisenka {
    /*
     * デバッグメッセージ用フラグ true の場合，いくつかのメッセージがコンソールに出力される
     */
    private static final boolean DEBUG = true;
    private static BufferedImage img = null;
    private static int M=-1; // 横サイズ
    private static int N=-1; // 縦サイズ
    private static int ImgSize=-1; // 総画素数
    private static int[] f=null; // 原画像の画素値
    private static int[] g=null; // 処理後の画素値
    private static String usage="java Saisenka 入力画像（8bit/pixel濃淡画像、０と２５５の値だけ) 出力画像";

    //mainメソッド
    public static void main(String args[]) {
	
	//コマンドライン引数のチェック
	if (args.length != 2) {
	    System.out.println(usage);
	    System.exit(1);
	}

	ReadImage(args[0]); // 画像データを読み込む
	
	Thinning(); // 細線化を実行
	
	WriteImage(args[1]); // 画像データを書き出す
	
	System.out.println("Done.");
    }
    
    private static boolean delPoint(int ptr[]) {
	int[] Ns = {4, 5, 2, 1, 0, 3, 6, 7, 8, 5};
	int[] N8 = {1, 2, 3, 4, 5, 6, 7, 8, 1};
	int[] Nodd = {1,3,5,7};
	
	// 条件2 - 境界画素である条件
	{
	    int sum = 0;
	    for (int i=0; i<4; i++) 
		sum += (1-Math.abs(ptr[Ns[Nodd[i]]]));
			
	    if( !( sum >= 1 ) ) {
		return false;
	    }
	}
	
	// 条件3 - 端点を削除しない条件
	{
	    int sum = 0;
	    for (int i=0; i<8; i++) {
		sum += Math.abs(ptr[Ns[N8[i]]]);
	    }
	    if( !( sum >= 2 ) ) {
		return false;	
	    }
	}
	
	// 条件4 - 孤立点を保存する条件
	{
	    int sum = 0;
	    for (int i=0; i<8; i++) {
		sum += ((ptr[Ns[N8[i]]] == 1) ? 1 : 0);
	    }
	    
	    if( !( sum >= 1 ) ) {
		return false;
	    }
	}
	
	
	// 条件5 - 連結性を保存する条件
	{
	    int sum = GetConnectNum(ptr); 
	    if( !( sum == 1 ) ){
		return false;	
	    }
	}
	
	// 条件6 - 線幅が2の線分に対して、その片側のみを削除する条件
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
    
    // 連結数を求める 
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
	    //sum += (csk-(csk*csk1*csk2));  //間違い
	}
	
	return sum;
    }
    
    private static void Thinning() {
	int del=0;  //削除可能画素数を示す
	int[] ptr= new int[9];
	
	for (int i=0; i<ImgSize; i++) {
	    g[i] = f[i];
	}
	
	do {
	    del=0;
	    for (int i=1; i<N-1; i++) {
		for (int j=1; j<M-1; j++) {
		    
		    
		    if(g[i*M+j] == 1) {	//前景画素なので削除可能性を判定
			
			// 8近傍データ抽出
			int k=0;
			for (int ii=i-1; ii<=i+1; ii++){
			    for (int jj=j-1; jj<=j+1; jj++) {
				ptr[k++] = g[ii*M+jj];
			    }
			}
			
			// 削除可能か否かの判定
			if (delPoint(ptr)) {
			    g[i*M+j] = -1;
			    del++;
			}
		    }
		}
	    }
	    
	    //「-1」を「0」（背景画素）に変更する
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
    
    private static void ReadImage(String rfname) { // 画像データを読み込む
	if (DEBUG) {
	    System.out.println("Input Image = " + rfname);
	}
	
	try {
	    img = ImageIO.read(new File(rfname));
	} catch (Exception e) {
	    e.printStackTrace();
	}
	
	if (img != null) {
	    M = img.getWidth(); // 幅を設定
	    N = img.getHeight(); // 高さを設定
	    ImgSize = M * N; // 総画素数を設定
	} else {
	    System.out.println("img = null !!!, something is wrong.");
	    System.exit(1);
	}
	
	// 8ビット濃淡画像か否かをチェックする
	ColorModel cm = img.getColorModel();
	if (cm.getPixelSize() != 8 || cm.getNumColorComponents() != 1) {
	    System.out.println("GetProperty = " + img.getProperty(rfname));
	    System.out.println(img.toString());
	    System.out.println(" Type = " +img.getType());
	    System.exit(1);
	}
	
	// 画素データを配列fに読み込む
	WritableRaster ras = img.getRaster();
	f = new int[ImgSize];
	g = new int[ImgSize];
	for (int i = 0; i < ImgSize; i++) {
	    f[i] = ras.getDataBuffer().getElem(i);
	}
	
	// 2値画像か否かをチェックする
	for (int i=0; i<ImgSize; i++) {
	    if (f[i] != 0 && f[i] != 255) {
		System.out.println("An input image must be a bi-level image.");
		System.exit(1);				
	    }
	    // 黒い画素を前景画素「１」、白い画素を背景画素「０」に設定する
	    f[i] = (f[i] == 0) ? 1 : 0;
	}
	
	
    }
    
    private static void WriteImage(String wfname) {
	WritableRaster ras = img.getRaster();
	
	for (int i=0; i<ImgSize; i++) {
	    // 前景画素「１」を黒い画素、背景画素「０」を白画素に設定する
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