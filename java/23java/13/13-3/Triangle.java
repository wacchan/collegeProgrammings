class Triangle extends Figure{
    // nvertex・nsideをFigureへ
    int base; // 底辺
    int height; // 高さ

    public Triangle(int h,int b){
        super(3,3); // 追加
        base=b;
        height=h;
        // nvertex・nsideをFigureへ
    }
    /* 面積 */
    public int getArea(){
        return base*height/2;
    }
    // 頂点の数・辺の数をFigureへ
}