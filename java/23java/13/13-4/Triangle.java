class Triangle extends Figure implements FigureArea{
    int base; // ���
    int height; // ����

    public Triangle(int h,int b){
        super(3,3); // �ǉ�
        base=b;
        height=h;
    }
    /* �ʐ� */
    public int getArea(){
        return base*height/2;
    }
}