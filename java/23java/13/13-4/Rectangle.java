class Rectangle extends Figure implements FigureArea{
    int width; // ‰¡•
    int height; // ‚‚³

    public Rectangle(int h,int b){
        super(4,4);
        width=b;
        height=h;
    }
    /* –ÊÏ */
    public int getArea(){
    return width*height;
    }
}
