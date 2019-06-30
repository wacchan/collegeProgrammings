class MyComplexTester {
    public static void main(String[] args) {
        MyComplex a = new MyComplex(2, 3);
        MyComplex b = new MyComplex(4, 5);
        MyComplex c, d, e, f;
        MyComplex g, h, i, j;
        MyComplex k;

        c = MyComplex.add(a, b);
        d = MyComplex.sub(a, b);
        e = MyComplex.mul(a, b);
        f = MyComplex.div(a, b);
        g = a.add(b);
        h = a.sub(b);
        i = a.mul(b);
        j = a.div(b);
        k = a.con();

        System.out.println("a = " + a.toString());
        System.out.println("b = " + b.toString());
        System.out.println();

        System.out.println("c = a + b = " + c.toString());
        System.out.println("d = a - b = " + d.toString());
        System.out.println("e = a * b = " + e.toString());
        System.out.println("f = a / b = " + f.toString());
        System.out.println();

        System.out.println("g = a + b = " + g.toString());
        System.out.println("h = a - b = " + h.toString());
        System.out.println("i = a * b = " + i.toString());
        System.out.println("j = a / b = " + j.toString());
        System.out.println();

        System.out.println("k = a* = " + k.toString());

    }
}