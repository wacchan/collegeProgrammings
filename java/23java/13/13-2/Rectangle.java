class Rectangle{
    int nvertex; // ���_�̐�
    int nside; // �ӂ̐�
    int width; // ����
    int height; // ����

    public Rectangle(int h,int b){
        width = b;
        height = h;
        nvertex = 4;
        nside = 4;
    }
    /* �ʐ� */ 
    public int getArea(){
        return width*height; 
    }
    /* ���_�̐� */
    public int getNvertex(){
        return nvertex;
    }
    /* �ӂ̐� */
    public int getNSide(){
        return nside;
    }
}