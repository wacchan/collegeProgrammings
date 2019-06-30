import java.applet.Applet;
import java.awt.*;
import java.util.*;
import java.awt.event.*;

/**
 * �e�g���X�N���X
 * @author Takeshi SAITOH
 * @version 2013.12.19
 */
public class Tetris extends java.applet.Applet implements Runnable, KeyListener, MouseListener{
    /**
     * �u���b�N�̏����ʒu
     */
    int blockX;
    int blockY;

    /**
     * ���������u���b�N��
     */
    int nw = 12;

    /**
     * ���������u���b�N��
     */
    int nh = 21;

    /**
     * �u���b�N�T�C�Y
     */
    int blockSize = 16;
    
    /**
     * �X�R�A
     */
    int score = 0;

    /**
     * �������s��
     */    
    int cntLine = 0;

    /**
     * �\���̈�
     */
    Dimension d;

    /**
     * �I�t�X�N���[��
     */
    Image offBuf;
    Graphics offG;

    /**
     * �A�j���[�V�����̂��߂̃X���b�h�ϐ�
     */
    Thread kicker = null;

    /**
     * �X�s�[�h
     * �l���������قǑ��x�������Ȃ�
     */
    int speed = 200;

    /**
     * �J��Ԃ����߂̕ϐ�
     */
    boolean loop = true;

    /**
     * �u���b�N�Ȃ�
     */
    final int NO_BLOCK = 0;
    /**
     * �ǃu���b�N
     */
    final int WALL_BLOCK = 9;

    /**
     * ���ݗ������̃u���b�N�p
     */
    int block[][] = new int[4][4];

    /**
     * �ǂƌŒ�ς݃u���b�N�p
     */
    int stage[][] = new int[nh][nw];

    /**
     * �`��u���b�N�p�istage �� block ���d�˂����́j
     */
    int field[][] = new int[nh][nw];
    
    /**
     * �V��ނ̃u���b�N�̃f�[�^
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
	    // |�@�@���@|
	    // |�@�����@|
	    // |�@���@�@|
	    // |�@�@�@�@|
	    {0,0,3,0},
	    {0,3,3,0},
	    {0,3,0,0},
	    {0,0,0,0}
	},
	{
	    // |�@���@�@|
	    // |�@�����@|
	    // |�@�@���@|
	    // |�@�@�@�@|
	    {0,4,0,0},
	    {0,4,4,0},
	    {0,0,4,0},
	    {0,0,0,0}
	},
	{
	    // |�@�@�@�@|
	    // |�@���@�@|
	    // |�������@|
	    // |�@�@�@�@|
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
     * �A�v���b�g���ǂݍ��܂ꂽ����1�񂾂��Ăяo����郁�\�b�h
     */
    public void init(){
        // �u���b�N�Ȃ��ɐݒ�
        for(int i=0; i<nh; i++){
            for(int j=0; j<nw; j++){
                field[i][j] = NO_BLOCK;
                stage[i][j] = NO_BLOCK;

		if(j == 0 || j == nw-1 || i == nh-1){
		    // �ō��[�ij=0�j or �ŉE�[�ij=nw�j or �ŉ��[�ii=nh�j��ǃu���b�N�ɂ���
		    field[i][j] = WALL_BLOCK;
		    stage[i][j] = WALL_BLOCK;
		}
            }
        }
	
        // �I�t�X�N���[���̐ݒ�
	// �\���̈�̎擾
        d = getSize();
        offBuf = createImage(d.width, d.height);
        offG   = offBuf.getGraphics();

        // �L�[���X�i�Ƃ��Ď������g��o�^
        addKeyListener(this);
	// �L�[���̓t�H�[�J�X
        requestFocus();

        // �}�E�X���X�i�Ƃ��Ď������g��o�^
        addMouseListener(this);

        // �u���b�N�̐ݒ�
        createBlock();

        score = 0;
	cntLine = 0;
	
        loop = true;
        start();
    }

    /**
     * �A�v���b�g�̊J�n����init���\�b�h�̌�ɌĂяo����郁�\�b�h
     */
    public void start(){
        if(kicker == null){
            // �X���b�h�̎��s
            kicker = new Thread(this);
            kicker.start();
        }
    }

    /**
     * �A�v���b�g�̏I�����ɌĂяo����郁�\�b�h
     */
    public void stop(){
        /* �X���b�h���~�߂� */
        kicker = null;
    }

    /**
     * �A�v���b�g���\�������ۂɌĂяo���ꃁ�\�b�h
     */
    public void paint(Graphics g){
        update(g);
    }

    /**
     * paint���\�b�h���Ă΂��O�ɌĂяo����郁�\�b�h
     */
    public void update(Graphics g){
        // �w�i�̕`��
	offG.setColor(Color.black);
	offG.fillRect(0, 0, d.width, d.height);
	
        // �u���b�N�̕`��
        for(int i=0; i<nh; i++){
            for(int j=0; j<nw; j++){
                switch (field[i][j]){
		case NO_BLOCK:
		    // �u���b�N�Ȃ�
		    break;

		case WALL_BLOCK:
		    // �ǃu���b�N
		    offG.setColor(Color.darkGray);
                    offG.fillRect(j*blockSize, i*blockSize, blockSize, blockSize);
		    break;
        
        case 1:
            // �P�u���b�N
		    offG.setColor(Color.red);
                    offG.fillRect(j*blockSize, i*blockSize, blockSize, blockSize);
		    break;
        case 2:
		    // �Q�u���b�N
		    offG.setColor(Color.blue);
                    offG.fillRect(j*blockSize, i*blockSize, blockSize, blockSize);
		    break;        
        case 3:
		    // �R�u���b�N
		    offG.setColor(Color.green);
                    offG.fillRect(j*blockSize, i*blockSize, blockSize, blockSize);
            break; 
        case 4:
		    // �S�u���b�N
		    offG.setColor(Color.yellow);
                    offG.fillRect(j*blockSize, i*blockSize, blockSize, blockSize);
            break;
        case 5:
		    // �T�u���b�N
		    offG.setColor(Color.cyan);
                    offG.fillRect(j*blockSize, i*blockSize, blockSize, blockSize);
		    break; 
        case 6:
		    // �U�u���b�N
		    offG.setColor(Color.magenta);
                    offG.fillRect(j*blockSize, i*blockSize, blockSize, blockSize);
            break; 
        case 7:
		    // �V�u���b�N
		    offG.setColor(Color.orange);
                    offG.fillRect(j*blockSize, i*blockSize, blockSize, blockSize);
		    break;  
        }
            }
        }

	// �X�R�A�̕\��
	int x = 20;
	int y = (nh + 1) * blockSize;

	offG.setColor(Color.black);
	offG.fillRect(0, y-20, d.width, y+20);

	String str = "Score : " + score;
        offG.setColor(Color.white);
        offG.drawString(str, x, y);

        if(!loop){
	    // �Q�[���I�[�o�[�̏ꍇ
	    offG.setColor(Color.black);
	    offG.fillRect(0, y-20, d.width, y+20);

            offG.setColor(Color.white);
	    str = "Game Over, Score : " + score;
            offG.drawString(str, x, y);

            // RESTART�{�^���̕`��
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

        // �I�t�X�N���[���̃C���[�W���ꋓ�Ɏ��ۂ̕\���̈�ɕ`��
        g.drawImage(offBuf, 0, 0, this);	
    }

    /**
     * ���s
     */
    public void run(){
	// �������s��

        // ���s���̃X���b�h���`�F�b�N
        Thread thisThread = Thread.currentThread();

        // �J��Ԃ�
        while(loop && kicker == thisThread){
	    // �u���b�N�𗎂Ƃ�
	    dropBlock();

	    checkLines();
            // �������s������_�����v�Z
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
     * �L�[�������ꂽ���ɌĂ΂�郁�\�b�h
     */
    public void keyPressed(KeyEvent e){
	// �����ꂽ�L�[�̃R�[�h���擾
        int key = e.getKeyCode();

	switch (key){
	case KeyEvent.VK_LEFT:
	    // ���{�^��
            if(checkOverlap(blockX-1, blockY))
		moveBlock(blockX-1, blockY);
	    break;

	case KeyEvent.VK_RIGHT:
	    // �E�{�^��
            if(checkOverlap(blockX+1, blockY))
		moveBlock(blockX+1, blockY);
	    break;

	case KeyEvent.VK_DOWN:
	    // ���{�^��
            if(checkOverlap(blockX, blockY+1))
		moveBlock(blockX, blockY+1);
	    break;

	case KeyEvent.VK_UP:
	    // ��{�^��
	    // ��]
	    turnBlock();
	    break;
	}
    }

    /**
     * �L�[��������Ă��痣���ꂽ���ɌĂ΂�郁�\�b�h
     */
    public void keyTyped(KeyEvent e){
    }

    /**
     * �L�[�������ꂽ���ɌĂ΂�郁�\�b�h
     */
    public void keyReleased(KeyEvent e){
    }

    /**
     * �}�E�X�{�^���������ꂽ���ɌĂ΂�郁�\�b�h
     */
    public void mousePressed(MouseEvent e){
        // �}�E�X�������ꂽ���W�𓾂�
        int ix = e.getX();
        int iy = e.getY();

        if(ix > 48 && ix < 113 && iy > 120 && iy < 145){
            // �}�E�X�̍��W(ix,iy)��RESTART�{�^�����̏ꍇ�Q�[���ăX�^�[�g
            if(!loop){
                stop();
                init();
                repaint();
            }
        }
    }

    /**
     * �}�E�X�{�^���������ꂽ���ɌĂ΂�郁�\�b�h
     */
    public void mouseReleased(MouseEvent e){
    }

    /**
     * �}�E�X�{�^�����N���b�N���ꂽ���ɌĂ΂�郁�\�b�h
     */
    public void mouseClicked(MouseEvent e){
    }
      
    /**
     * �}�E�X�J�[�\���������Ă������ɌĂ΂�郁�\�b�h
     */
    public void mouseEntered(MouseEvent e){
    }

    /**
     * �}�E�X�J�[�\�����o�����ɌĂ΂�郁�\�b�h
     */
    public void mouseExited(MouseEvent e){
    }

    /**
     * �u���b�N�̍쐬
     */
    public boolean createBlock(){
	// ���u���b�N�̈ʒu
        blockY = 0;
        blockX = 4;

	// ���u���b�N�̃p�^�[���𗐐��Ō��߂�
        int blockType = (int)(Math.random() * (float)7);

	// �u���b�N�f�[�^�̒�����blockType�ɉ�������ނ̃u���b�N��ǂݍ���
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                block[i][j] = blockList[blockType][i][j];
            }
        }

	// �ǁ{�u���b�N���t�B�[���h��
	for(int i=0; i<4; i++){
	    for(int j=0; j<4; j++){
		field[i][j+4] = stage[i][j+4] + block[i][j];
		
		// �����ʒu�ɒu�����u���b�N�����ɌŒ�u���b�N�ɏd�Ȃ��Ă���΃Q�[���I�[�o�[
		if(field[i][j+4] > 8)
		    return false;
	    }
	}

	return true;
    }

    /**
     * �u���b�N�̏d�Ȃ茟��
     */
    public boolean checkOverlap(int xx, int yy){
	// �u���b�N���������ʒu�ɁA�Œ�u���b�N�������͕ǂ����邩�ǂ���������
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
     * �u���b�N�̈ړ�
     */
    public void moveBlock(int xx, int yy){
	// ���܂ł̃u���b�N������
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
		if(blockX+j > nw-1 || blockY+i > nh-1)
		    continue;
		field[blockY+i][blockX+j] -= block[i][j];
            }
        }

	// �u���b�N�̍��W���X�V
	blockX = xx;
	blockY = yy;

	// �V�������W�Ƀu���b�N�����Ȃ���
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
		if(blockX+j > nw-1 || blockY+i > nh-1)
		    continue;
		field[blockY+i][blockX+j] += block[i][j];
            }
        }
    }

    /**
     * �u���b�N�̉�]
     */
    public boolean turnBlock(){
	// �u���b�N���ꎞ�ۑ����邽�߂̔z��
	int[][] temp = new int[4][4];

	// �u���b�N����]����O��temp�ɃZ�[�u
	for(int i=0; i<4; i++){
	    for(int j=0; j<4; j++){
		temp[i][j] = block[i][j];
	    }
	}

	// �u���b�N����]
	for(int i=0; i<4; i++){
	    for(int j=0; j<4; j++){
		block[i][j] = temp[3-j][i];
	    }
	}

	// �d�Ȃ��Ă�u���b�N���o�Ă��܂�����u���b�N����]�O�ɖ߂��Ē��~
	if(!checkOverlap(blockX, blockY)){
	    for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
		    block[i][j] = temp[i][j];
		}
	    }

	    return false;
	}

	// ��U�t�B�[���h����u���b�N�����ĉ�]��̃u���b�N���ĕ\��
	for(int i=0; i<4; i++){
	    for(int j=0; j<4; j++){
		field[blockY+i][blockX+j] -= temp[i][j];
		field[blockY+i][blockX+j] += block[i][j];
	    }
	}

	return true;
    }

    /**
     * �u���b�N�𗎂Ƃ�
     */
    public void dropBlock(){
	if(checkOverlap(blockX, blockY+1))
	    // �d�Ȃ肪�Ȃ���Έړ�
	    moveBlock(blockX, blockY+1);
	else{
	    // �d�Ȃ肪����Εǂɂ���
	    lockBlock();
	    boolean ret = createBlock();

	    if(!ret)
		loop = false;
	}
    }

    /**
     * ���n��̃u���b�N���Œ肵�A����񂪂�����Ă邩�̔�����Ăяo��
     */
    public void lockBlock(){
	// �u���b�N��ǂɉ�����
	for(int i=0; i<nh; i++){
	    for(int j=0; j<nw; j++){
		stage[i][j] = field[i][j];
	    }
	}

	// ����񂪂�����Ă邩���肵�ď�������֐����Ă�
	checkLines();

	// �񊮐������̕ǂ��t�B�[���h��
	for(int i=0; i<nh; i++){
	    for(int j=0; j<nw; j++){
		field[i][j] = stage[i][j];
	    }
	}
    }

    /**
     * ����񂪊������Ă��邩�����B������Ă���΂����������ď�̃u���b�N�Q�����낷
     */
    public void checkLines(){
	// ����񂪂�����Ă���΂P�A��ł����Ԃ�����ƂO�ɂȂ�
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

	    // �������
	    for(int j=1; j<nw; j++){
		stage[i][j] = 0;
	    }

	    // �����������ɂ������Œ�u���b�N���̏������Ƃ���։��낷
	    for(int k=i; k>0; k--){
		for(int j=1; j<nw; j++){
		    stage[k][j] = stage[k-1][j];
		}
	    }
	}
    }
}
