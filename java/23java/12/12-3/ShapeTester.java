interface Shape {

    void draw();
}

class Square implements Shape {
    int x;

    public Square(int x) {
        this.x = x;
    }

    public void draw() {
        for (int i = 0; i < x; i++) {
            System.out.print("¡ ");
        }
        System.out.println();
    }
}

class Circle implements Shape {
    int x;

    public Circle(int x) {
        this.x = x;
    }

    public void draw() {
        for (int i = 0; i < x; i++) {
            System.out.print("œ ");
        }
        System.out.println();
    }
}

class Triangle implements Shape {
    int x;

    public Triangle(int x) {
        this.x = x;
    }

    public void draw() {
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