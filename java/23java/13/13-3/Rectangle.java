class Rectangle extends Figure{
    // nvertex�Enside��Figure��
    int width; // ����
    int height; // ����

    public Rectangle(int h,int b){
        super(4,4); // �ǉ�
        width=b;
        height=h;
        // nvertex�Enside��Figure��
    }
    /* �ʐ� */
    public int getArea(){
    return width*height;
    }
    // ���_�̐��E�ӂ̐���Figure��
}
