class Triangle extends Figure implements FigureArea{
    int base; // ’ê•Ó
    int height; // ‚‚³

    public Triangle(int h,int b){
        super(3,3); // ’Ç‰Á
        base=b;
        height=h;
    }
    /* –ÊÏ */
    public int getArea(){
        return base*height/2;
    }
}