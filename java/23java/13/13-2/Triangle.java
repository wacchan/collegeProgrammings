class Triangle{
    int nvertex; // ���_�̐�
    int nside; // �ӂ̐�
    int base; // ���
    int height; // ����

    public Triangle(int h, int b){
        base = b;
        height = h;
        nvertex = 3;
        nside = 3;
    }

    /* �ʐ� */
    public int getArea(){
        return base*height/2;
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