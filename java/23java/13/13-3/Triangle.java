class Triangle extends Figure{
    // nvertex�Enside��Figure��
    int base; // ���
    int height; // ����

    public Triangle(int h,int b){
        super(3,3); // �ǉ�
        base=b;
        height=h;
        // nvertex�Enside��Figure��
    }
    /* �ʐ� */
    public int getArea(){
        return base*height/2;
    }
    // ���_�̐��E�ӂ̐���Figure��
}