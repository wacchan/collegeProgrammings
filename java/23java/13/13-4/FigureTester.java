class FigureTester{
    public static void main(String[] args) { 
        Triangle t = new Triangle(3, 2); 
        Rectangle r = new Rectangle(3, 2); 

        System.out.println("�O�p�`�̒��_��" + t.getNvertex() 
                            + "�A�ӂ�" + t.getNSide() 
                            + "�A�ʐς�" + t.getArea());
        System.out.println("�l�p�`�̒��_��" + r.getNvertex() 
                            + "�A�ӂ�" + r.getNSide() 
                            + "�A�ʐς�" + r.getArea()); 
    }
}