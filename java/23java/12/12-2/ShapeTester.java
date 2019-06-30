abstract class Shape {
    protected int x;

    public Shape(int x) {
        this.x = x;
    }

    abstract void draw();
}

class Square extends Shape {
    public Square(int x) {
        super(x);
    }

    void draw() {
        for (int i = 0; i < x; i++) {
            System.out.print("¡ ");
        }
        System.out.println();
    }
}

class Circle extends Shape {
    public Circle(int x) {
        super(x);
    }

    void draw() {
        for (int i = 0; i < x; i++) {
            System.out.print("œ ");
        }
        System.out.println();
    }
}

class Triangle extends Shape {
    public Triangle(int x) {
        super(x);
    }

    void draw() {
        for (int i = 0; i < x; i++) {
            System.out.print("£ ");
        }
        System.out.println();
    }
}

class ShapeTester {
    public static void main(String[] args) {
        Shape s = new Square(3);
        Shape c = new Circle(5);
        Shape t = new Triangle(2);

        s.draw();
        c.draw();
        t.draw();
    }
}