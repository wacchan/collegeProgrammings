class Rectangle extends Figure implements FigureArea{
    int width; // ����
    int height; // ����

    public Rectangle(int h,int b){
        super(4,4);
        width=b;
        height=h;
    }
    /* �ʐ� */
    public int getArea(){
    return width*height;
    }
}
