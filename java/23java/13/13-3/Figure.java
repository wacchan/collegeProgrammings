abstract class Figure{
    int nvertex; // 頂点の数
    int nside; // 辺の数
    
    public Figure(int v,int s){
        nvertex=v;
        nside=s; 
    }

    /* 抽象メソッド */
    abstract int getArea();
    /* 頂点の数 */
    public int getNvertex(){
        return nvertex;
    }
    /* 辺の数 */
    public int getNSide(){
        return nside;
    }
}