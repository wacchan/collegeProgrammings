class Triangle{
    int nvertex; // ’¸“_‚Ì”
    int nside; // •Ó‚Ì”
    int base; // ’ê•Ó
    int height; // ‚‚³

    public Triangle(int h, int b){
        base = b;
        height = h;
        nvertex = 3;
        nside = 3;
    }

    /* –ÊÏ */
    public int getArea(){
        return base*height/2;
    }
    /* ’¸“_‚Ì” */
    public int getNvertex(){
        return nvertex;
    }
    /* •Ó‚Ì” */
    public int getNSide(){
        return nside;
    }
}