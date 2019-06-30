class Rectangle{
    int nvertex; // ’¸“_‚Ì”
    int nside; // •Ó‚Ì”
    int width; // ‰¡•
    int height; // ‚‚³

    public Rectangle(int h,int b){
        width = b;
        height = h;
        nvertex = 4;
        nside = 4;
    }
    /* –ÊÏ */ 
    public int getArea(){
        return width*height; 
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