class FigureTester{
    public static void main(String[] args) { 
        Triangle t = new Triangle(3, 2); 
        Rectangle r = new Rectangle(3, 2); 

        System.out.println("三角形の頂点は" + t.getNvertex() 
                            + "個、辺は" + t.getNSide() 
                            + "個、面積は" + t.getArea());
        System.out.println("四角形の頂点は" + r.getNvertex() 
                            + "個、辺は" + r.getNSide() 
                            + "個、面積は" + r.getArea()); 
    }
}