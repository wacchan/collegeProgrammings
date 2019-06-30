/*
 *　濃淡画像を二値化し、膨張、収縮を行う
 * 入力画像：8ビット濃淡画像
 * 出力画像：8ビット濃淡画像
 * 実行方法　% java Nichika_Atosyori X Y s (a,b,c,dを指定する）

X: 入力画像ファイル名（8bit/pixelの濃淡画像）
Y: 出力画像ファイル名(png形式で出力する）
　　　出力画像は二値画像であるが，濃淡画像フォーマットで出力
　　　前景画素：０（黒）
　　　背景画素：２５５（白）

s: 二値化のしきい値（固定しきい値法）

第四引数からは処理を指示する（もし何も指示がない場合は二値化のみ）

　　　８近傍収縮処理：a
　　　８近傍膨張処理：b
　　　４近傍収縮処理：c
　　　４近傍膨張処理：d

例）８近傍収縮処理を２回繰り返し，８近傍膨張処理を２回繰り返す

java Nichika_Atosyori X Y 150 a a b b

例）４近傍膨張処理を３回繰り返し，４近傍収縮処理を３回繰り返す

java Nichika_Atosyori X Y 150 d d d c c c

例）二値化のみを行う

java Nichika_Atosyori X Y 150


以上です．
/* 備考
このプログラムは，
前景画素を0（黒）
背景画素を255（白）
として処理している．
*/

import java.awt.image.BufferedImage;
import java.awt.image.ColorModel;
import java.awt.image.WritableRaster;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;

public class Nichika_Atosyori {
    /*  デバッグメッセージ用フラグ
     *  true の場合，いくつかのメッセージがコンソールに出力される
     */
    static final boolean        DEBUG = true;

    private static BufferedImage img = null;

    private static int M=-1; // 横サイズ
    
    private static int N=-1; // 縦サイズ
    
    private static int ImgSize=-1; // 総画素数
    
    private static int[] f=null; // 原画像の画素値
    
    private static int[] g=null; // 処理後の画素値
    
    private static String usage="java Nichika_Atosyori 入力画像（8bit/pixel濃淡画像) 出力画像 二値化しきい値(0～255) または，java Nichika_Atosyori 入力画像（8bit/pixel濃淡画像) 出力画像 二値化しきい値(0～255) 動作指示（a,b,c,dを指定する）";

    public static void main(String[] args) {
	String[] dousa=null;

	//コマンドライン引数のチェック
	if (args.length < 3) {
	    System.out.println(usage);
	    System.exit(1);
	}
	//第三引数の値をチェック
	int shikiichi = Integer.parseInt(args[2]);
	if (shikiichi < 0 || shikiichi > 255) {
	    System.out.println("しきい値は （0～255） の中から指定してください。");
	    System.exit(1);
	}

	//処理系列を取得する
	int num = args.length - 3;  //処理回数
	if (num == 0) { //二値化しか行わない
	    dousa = new String[1];
	    dousa[0] = "z";
	}
	else {
	    dousa = new String[num];
	    for (int i=0; i<num; i++) {
		if (!args[3+i].equals("a") && !args[3+i].equals("b") && !args[3+i].equals("c") && !args[3+i].equals("d")) {
		    System.out.println("処理は （a, b, c, d） の中から指定してください。[ " + args[3+i] + " ]");
		    System.exit(1);
		}
		dousa[i] = args[3+i];
	    }
	}
	
	ReadImage(args[0]); // 画像データを読み込む
	
	Nichika(shikiichi);
	Atosyori(dousa);
	
	WriteImage(args[1]); // 画像データを書き出す
	
	System.out.println("Done.");
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
	    System.out.println("入力画像には8bit/pixelの濃淡画像を指定してください。");
	    System.exit(1);
	}
	//System.out.println("GetProperty = " + img.getProperty(rfname));
	//System.out.println(img.toString());
	
	// 画素データを配列fに読み込む
	WritableRaster ras = img.getRaster();
	f = new int[ImgSize];
	g = new int[ImgSize];
	for (int i = 0; i < ImgSize; i++) {
	    f[i] = ras.getDataBuffer().getElem(i);
	}
    }

    private static void Nichika(int shikiichi) { //shikiichiの値に基づき二値化を行う
	System.out.println("（しきい値 = " + shikiichi + "）で2値化します");
	for (int i = 0; i < ImgSize; i++) {
	    g[i] = (f[i]>shikiichi) ? 255 : 0;
	    //前景画素を:0（黒）
	    //背景画素を:255（白）
	}
    }

    private static void Atosyori(String[] dousa) { //dousaの値に基づき収縮膨張を行う

	for (int i=0; i<dousa.length; i++) {
	    if (dousa[i].equals("a")) {
		System.out.println("８近傍収縮処理を行います");
		syu_syuku8();
	    }
	    else if (dousa[i].equals("b")) {
		System.out.println("８近傍膨張処理を行います");
		bo_chou8();
	    }
	    else if (dousa[i].equals("c")) {
		System.out.println("４近傍収縮処理を行います");	    
		syu_syuku4();
	    }
	    else if (dousa[i].equals("d")) {
		System.out.println("４近傍膨張処理を行います");	    
		bo_chou4();
	    }
	    else {
		System.out.println("何も処理しません");
	    }
	}
    }

    private static void bo_chou8() { //gに対して８近傍膨張処理を行う
	int[] temp = new int[ImgSize];

	for (int i=0; i<ImgSize; i++) {
	    temp[i] = g[i];
	}

	for (int i=1; i<N-1; i++) {
	    for (int j=1; j<M-1; j++) {
		if (g[i*M+j] == 255) {
		    //8近傍をチェック
		    int flg = 0;
		    for (int ii=i-1; ii<=i+1; ii++) {
			for (int jj=j-1; jj<=j+1; jj++) {
			    flg += g[ii*M+jj];
			}
		    }
		    //前景画素が見つかった場合の処理
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

    private static void bo_chou4() { //gに対して4近傍膨張処理を行う
	int[] temp = new int[ImgSize];
	int[] x4 = {0,-1,1,0};
	int[] y4 = {-1, 0, 0, 1};

	for (int i=0; i<ImgSize; i++) {
	    temp[i] = g[i];
	}

	for (int i=1; i<N-1; i++) {
	    for (int j=1; j<M-1; j++) {
		if (g[i*M+j] == 255) {
		    //4近傍をチェック
		    int flg = 0;
		    for (int k=0; k<4; k++) {
			flg += g[(i+y4[k])*M+(j+x4[k])];
		    }
		    //前景画素が見つかった場合の処理
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


    private static void syu_syuku8() { //gに対して8近傍収縮処理を行う
	int[] temp = new int[ImgSize];

	for (int i=0; i<ImgSize; i++) {
	    temp[i] = g[i];
	}

	for (int i=1; i<N-1; i++) {
	    for (int j=1; j<M-1; j++) {
		if (g[i*M+j] == 0) {
		    //8近傍をチェック
		    int flg = 0;
		    for (int ii=i-1; ii<=i+1; ii++) {
			for (int jj=j-1; jj<j+1; jj++) {
			    flg += g[ii*M+jj];
			}
		    }
		    //背景画素が見つかった場合の処理
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

    private static void syu_syuku4() { //gに対して4近傍収縮処理を行う
	int[] temp = new int[ImgSize];
	int[] x4 = {0,-1,1,0};
	int[] y4 = {-1, 0, 0, 1};

	for (int i=0; i<ImgSize; i++) {
	    temp[i] = g[i];
	}

	for (int i=1; i<N-1; i++) {
	    for (int j=1; j<M-1; j++) {
		if (g[i*M+j] == 0) {
		    //4近傍をチェック
		    int flg = 0;
		    for (int k=0; k<4; k++) {
			flg += g[(i+y4[k])*M+(j+x4[k])];
		    }
		    //背景画素が見つかった場合の処理
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
