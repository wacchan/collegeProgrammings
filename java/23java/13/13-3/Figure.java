abstract class Figure{
    int nvertex; // ���_�̐�
    int nside; // �ӂ̐�
    
    public Figure(int v,int s){
        nvertex=v;
        nside=s; 
    }

    /* ���ۃ��\�b�h */
    abstract int getArea();
    /* ���_�̐� */
    public int getNvertex(){
        return nvertex;
    }
    /* �ӂ̐� */
    public int getNSide(){
        return nside;
    }
}