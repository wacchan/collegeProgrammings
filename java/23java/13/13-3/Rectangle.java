class Rectangle extends Figure{
    // nvertex・nsideをFigureへ
    int width; // 横幅
    int height; // 高さ

    public Rectangle(int h,int b){
        super(4,4); // 追加
        width=b;
        height=h;
        // nvertex・nsideをFigureへ
    }
    /* 面積 */
    public int getArea(){
    return width*height;
    }
    // 頂点の数・辺の数をFigureへ
}
