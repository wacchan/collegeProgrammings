abstract class Figure{
    int nvertex; // ���_�̐�
    int nside; // �ӂ̐�
    
    public Figure(int v,int s){
        nvertex=v;
        nside=s; 
    }

    // �폜
    /* ���_�̐� */
    public int getNvertex(){
        return nvertex;
    }
    /* �ӂ̐� */
    public int getNSide(){
        return nside;
    }
}