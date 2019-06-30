import java.applet.Applet;
import java.awt.*;
import java.util.*;
import java.awt.event.*;

/**
 * テトリスクラス
 * @author Takeshi SAITOH
 * @version 2013.12.19
 */
public class Tetris extends java.applet.Applet implements Runnable, KeyListener, MouseListener{
    /**
     * ブロックの初期位置
     */
    int blockX;
    int blockY;

    /**
     * 水平方向ブロック数
     */
    int nw = 12;

    /**
     * 垂直方向ブロック数
     */
    int nh = 21;

    /**
     * ブロックサイズ
     */
    int blockSize = 16;
    
    /**
     * スコア
     */
    int score = 0;

    /**
     * 消した行数
     */    
    int cntLine = 0;

    /**
     * 表示領域
     */
    Dimension d;

    /**
     * オフスクリーン
     */
    Image offBuf;
    Graphics offG;

    /**
     * アニメーションのためのスレッド変数
     */
    Thread kicker = null;

    /**
     * スピード
     * 値が小さいほど速度が早くなる
     */
    int speed = 200;

    /**
     * 繰り返すための変数
     */
    boolean loop = true;

    /**
     * ブロックなし
     */
    final int NO_BLOCK = 0;
    /**
     * 壁ブロック
     */
    final int WALL_BLOCK = 9;

    /**
     * 現在落下中のブロック用
     */
    int block[][] = new int[4][4];

    /**
     * 壁と固定済みブロック用
     */
    int stage[][] = new int[nh][nw];

    /**
     * 描画ブロック用（stage に block を重ねたもの）
     */
    int field[][] = new int[nh][nw];
    
    /**
     * ７種類のブロックのデータ
     */
    int[][][] blockList =
    {
    {
        {0,1,0,0},
        {0,1,0,0},
        {0,1,0,0},
        {0,1,0,0},
    },
    {
        {0,0,0,0},
        {0,2,2,0},
        {0,2,0,0},
        {0,2,0,0},
    },
	{
	    // |　　■　|
	    // |　■■　|
	    // |　■　　|
	    // |　　　　|
	    {0,0,3,0},
	    {0,3,3,0},
	    {0,3,0,0},
	    {0,0,0,0}
	},
	{
	    // |　■　　|
	    // |　■■　|
	    // |　　■　|
	    // |　　　　|
	    {0,4,0,0},
	    {0,4,4,0},
	    {0,0,4,0},
	    {0,0,0,0}
	},
	{
	    // |　　　　|
	    // |　■　　|
	    // |■■■　|
	    // |　　　　|
	    {0,0,0,0},
	    {0,5,0,0},
	    {5,5,5,0},
	    {0,0,0,0}
    },
    {
        {0,0,0,0},
        {0,6,6,0},
        {0,6,6,0},
        {0,0,0,0},
    },
    {
        {0,0,0,0},
        {0,7,7,0},
        {0,0,7,0},
        {0,0,7,0},
    },
    };

    /**
     * アプレットが読み込まれた時に1回だけ呼び出されるメソッド
     */
    public void init(){
        // ブロックなしに設定
        for(int i=0; i<nh; i++){
            for(int j=0; j<nw; j++){
                field[i][j] = NO_BLOCK;
                stage[i][j] = NO_BLOCK;

		if(j == 0 || j == nw-1 || i == nh-1){
		    // 最左端（j=0） or 最右端（j=nw） or 最下端（i=nh）を壁ブロックにする
		    field[i][j] = WALL_BLOCK;
		    stage[i][j] = WALL_BLOCK;
		}
            }
        }
	
        // オフスクリーンの設定
	// 表示領域の取得
        d = getSize();
        offBuf = createImage(d.width, d.height);
        offG   = offBuf.getGraphics();

        // キーリスナとして自分自身を登録
        addKeyListener(this);
	// キー入力フォーカス
        requestFocus();

        // マウスリスナとして自分自身を登録
        addMouseListener(this);

        // ブロックの設定
        createBlock();

        score = 0;
	cntLine = 0;
	
        loop = true;
        start();
    }

    /**
     * アプレットの開始時にinitメソッドの後に呼び出されるメソッド
     */
    public void start(){
        if(kicker == null){
            // スレッドの実行
            kicker = new Thread(this);
            kicker.start();
        }
    }

    /**
     * アプレットの終了時に呼び出されるメソッド
     */
    public void stop(){
        /* スレッドを止める */
        kicker = null;
    }

    /**
     * アプレットが表示される際に呼び出されメソッド
     */
    public void paint(Graphics g){
        update(g);
    }

    /**
     * paintメソッドが呼ばれる前に呼び出されるメソッド
     */
    public void update(Graphics g){
        // 背景の描画
	offG.setColor(Color.black);
	offG.fillRect(0, 0, d.width, d.height);
	
        // ブロックの描画
        for(int i=0; i<nh; i++){
            for(int j=0; j<nw; j++){
                switch (field[i][j]){
		case NO_BLOCK:
		    // ブロックなし
		    break;

		case WALL_BLOCK:
		    // 壁ブロック
		    offG.setColor(Color.darkGray);
                    offG.fillRect(j*blockSize, i*blockSize, blockSize, blockSize);
		    break;
        
        case 1:
            // １ブロック
		    offG.setColor(Color.red);
                    offG.fillRect(j*blockSize, i*blockSize, blockSize, blockSize);
		    break;
        case 2:
		    // ２ブロック
		    offG.setColor(Color.blue);
                    offG.fillRect(j*blockSize, i*blockSize, blockSize, blockSize);
		    break;        
        case 3:
		    // ３ブロック
		    offG.setColor(Color.green);
                    offG.fillRect(j*blockSize, i*blockSize, blockSize, blockSize);
            break; 
        case 4:
		    // ４ブロック
		    offG.setColor(Color.yellow);
                    offG.fillRect(j*blockSize, i*blockSize, blockSize, blockSize);
            break;
        case 5:
		    // ５ブロック
		    offG.setColor(Color.cyan);
                    offG.fillRect(j*blockSize, i*blockSize, blockSize, blockSize);
		    break; 
        case 6:
		    // ６ブロック
		    offG.setColor(Color.magenta);
                    offG.fillRect(j*blockSize, i*blockSize, blockSize, blockSize);
            break; 
        case 7:
		    // ７ブロック
		    offG.setColor(Color.orange);
                    offG.fillRect(j*blockSize, i*blockSize, blockSize, blockSize);
		    break;  
        }
            }
        }

	// スコアの表示
	int x = 20;
	int y = (nh + 1) * blockSize;

	offG.setColor(Color.black);
	offG.fillRect(0, y-20, d.width, y+20);

	String str = "Score : " + score;
        offG.setColor(Color.white);
        offG.drawString(str, x, y);

        if(!loop){
	    // ゲームオーバーの場合
	    offG.setColor(Color.black);
	    offG.fillRect(0, y-20, d.width, y+20);

            offG.setColor(Color.white);
	    str = "Game Over, Score : " + score;
            offG.drawString(str, x, y);

            // RESTARTボタンの描画
            offG.setColor(Color.red);
            offG.fillRect(48, 120, 65, 25);
            offG.setColor(Color.white);
	        offG.drawString("RESTART", 55, 138);
            offG.setColor(Color.white);
            offG.drawLine(48, 120, 113, 120);
            offG.drawLine(48, 120, 48, 145);
            offG.setColor(Color.black);
            offG.drawLine(48, 145, 113, 145);
            offG.drawLine(113, 145, 113, 120);
        }

        // オフスクリーンのイメージを一挙に実際の表示領域に描く
        g.drawImage(offBuf, 0, 0, this);	
    }

    /**
     * 実行
     */
    public void run(){
	// 消した行数

        // 実行中のスレッドをチェック
        Thread thisThread = Thread.currentThread();

        // 繰り返し
        while(loop && kicker == thisThread){
	    // ブロックを落とす
	    dropBlock();

	    checkLines();
            // 消した行数から点数を計算
            cntLine = cntLine * cntLine;
            score = score + cntLine * 10;
            cntLine = 0;
            repaint();

	    try{
                Thread.sleep(speed);
            } catch (InterruptedException e){}
        }
    }

    /**
     * キーが押された時に呼ばれるメソッド
     */
    public void keyPressed(KeyEvent e){
	// 押されたキーのコードを取得
        int key = e.getKeyCode();

	switch (key){
	case KeyEvent.VK_LEFT:
	    // 左ボタン
            if(checkOverlap(blockX-1, blockY))
		moveBlock(blockX-1, blockY);
	    break;

	case KeyEvent.VK_RIGHT:
	    // 右ボタン
            if(checkOverlap(blockX+1, blockY))
		moveBlock(blockX+1, blockY);
	    break;

	case KeyEvent.VK_DOWN:
	    // 下ボタン
            if(checkOverlap(blockX, blockY+1))
		moveBlock(blockX, blockY+1);
	    break;

	case KeyEvent.VK_UP:
	    // 上ボタン
	    // 回転
	    turnBlock();
	    break;
	}
    }

    /**
     * キーが押されてから離された時に呼ばれるメソッド
     */
    public void keyTyped(KeyEvent e){
    }

    /**
     * キーが離された時に呼ばれるメソッド
     */
    public void keyReleased(KeyEvent e){
    }

    /**
     * マウスボタンが押された時に呼ばれるメソッド
     */
    public void mousePressed(MouseEvent e){
        // マウスが押された座標を得る
        int ix = e.getX();
        int iy = e.getY();

        if(ix > 48 && ix < 113 && iy > 120 && iy < 145){
            // マウスの座標(ix,iy)がRESTARTボタン内の場合ゲーム再スタート
            if(!loop){
                stop();
                init();
                repaint();
            }
        }
    }

    /**
     * マウスボタンが離された時に呼ばれるメソッド
     */
    public void mouseReleased(MouseEvent e){
    }

    /**
     * マウスボタンがクリックされた時に呼ばれるメソッド
     */
    public void mouseClicked(MouseEvent e){
    }
      
    /**
     * マウスカーソルが入ってきた時に呼ばれるメソッド
     */
    public void mouseEntered(MouseEvent e){
    }

    /**
     * マウスカーソルが出た時に呼ばれるメソッド
     */
    public void mouseExited(MouseEvent e){
    }

    /**
     * ブロックの作成
     */
    public boolean createBlock(){
	// 次ブロックの位置
        blockY = 0;
        blockX = 4;

	// 次ブロックのパターンを乱数で決める
        int blockType = (int)(Math.random() * (float)7);

	// ブロックデータの中からblockTypeに応じた種類のブロックを読み込む
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                block[i][j] = blockList[blockType][i][j];
            }
        }

	// 壁＋ブロックをフィールドへ
	for(int i=0; i<4; i++){
	    for(int j=0; j<4; j++){
		field[i][j+4] = stage[i][j+4] + block[i][j];
		
		// 初期位置に置いたブロックが既に固定ブロックに重なっていればゲームオーバー
		if(field[i][j+4] > 8)
		    return false;
	    }
	}

	return true;
    }

    /**
     * ブロックの重なり検査
     */
    public boolean checkOverlap(int xx, int yy){
	// ブロックが向かう位置に、固定ブロックもしくは壁があるかどうかを検査
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
		if(block[i][j] != 0)
		    if(stage[yy+i][xx+j] != 0)
			return false;
            }
        }

        return true;
    }

    /**
     * ブロックの移動
     */
    public void moveBlock(int xx, int yy){
	// 今までのブロックを消す
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
		if(blockX+j > nw-1 || blockY+i > nh-1)
		    continue;
		field[blockY+i][blockX+j] -= block[i][j];
            }
        }

	// ブロックの座標を更新
	blockX = xx;
	blockY = yy;

	// 新しい座標にブロックを入れなおす
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
		if(blockX+j > nw-1 || blockY+i > nh-1)
		    continue;
		field[blockY+i][blockX+j] += block[i][j];
            }
        }
    }

    /**
     * ブロックの回転
     */
    public boolean turnBlock(){
	// ブロックを一時保存するための配列
	int[][] temp = new int[4][4];

	// ブロックを回転する前にtempにセーブ
	for(int i=0; i<4; i++){
	    for(int j=0; j<4; j++){
		temp[i][j] = block[i][j];
	    }
	}

	// ブロックを回転
	for(int i=0; i<4; i++){
	    for(int j=0; j<4; j++){
		block[i][j] = temp[3-j][i];
	    }
	}

	// 重なってるブロックが出てしまったらブロックを回転前に戻して中止
	if(!checkOverlap(blockX, blockY)){
	    for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
		    block[i][j] = temp[i][j];
		}
	    }

	    return false;
	}

	// 一旦フィールドからブロック消して回転後のブロックを再表示
	for(int i=0; i<4; i++){
	    for(int j=0; j<4; j++){
		field[blockY+i][blockX+j] -= temp[i][j];
		field[blockY+i][blockX+j] += block[i][j];
	    }
	}

	return true;
    }

    /**
     * ブロックを落とす
     */
    public void dropBlock(){
	if(checkOverlap(blockX, blockY+1))
	    // 重なりがなければ移動
	    moveBlock(blockX, blockY+1);
	else{
	    // 重なりがあれば壁にする
	    lockBlock();
	    boolean ret = createBlock();

	    if(!ret)
		loop = false;
	}
    }

    /**
     * 着地後のブロックを固定し、横一列がそろってるかの判定を呼び出す
     */
    public void lockBlock(){
	// ブロックを壁に加える
	for(int i=0; i<nh; i++){
	    for(int j=0; j<nw; j++){
		stage[i][j] = field[i][j];
	    }
	}

	// 横一列がそろってるか判定して処理する関数を呼ぶ
	checkLines();

	// 列完成判定後の壁をフィールドへ
	for(int i=0; i<nh; i++){
	    for(int j=0; j<nw; j++){
		field[i][j] = stage[i][j];
	    }
	}
    }

    /**
     * 横一列が完成しているか検査。そろっていればそこを消して上のブロック群を下ろす
     */
    public void checkLines(){
	// 横一列がそろっていれば１、一つでも隙間があると０になる
	int comp = 0;

	while(true){
	    int i;
	    for(i=0; i<nh-1; i++){
		comp = 1;
		
		for(int j=1; j<nw; j++){
		    if(stage[i][j] == 0)
			comp = 0;
		}

		if(comp == 1)
		    break;
	    }

	    if(comp == 0)
		break;

	    cntLine++;

	    // 列を消去
	    for(int j=1; j<nw; j++){
		stage[i][j] = 0;
	    }

	    // 消えた列より上にあった固定ブロックを列の消えたところへ下ろす
	    for(int k=i; k>0; k--){
		for(int j=1; j<nw; j++){
		    stage[k][j] = stage[k-1][j];
		}
	    }
	}
    }
}
