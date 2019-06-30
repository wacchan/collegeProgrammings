class MyComplex {
    double real, imag;

    public MyComplex(double x, double y) {
        real = x;
        imag = y;
    }

    public MyComplex(double x) {
        real = x;
        imag = 0;
    }

    public String toString() {
        StringBuffer sb = new StringBuffer().append(real);
        if (imag >= 0.0)
            sb.append('+');
        return sb.append(imag).append('i').toString();
    }

    public double real() {
        return real;
    }

    public double imag() {
        return imag;
    }

    public static MyComplex add(MyComplex a, MyComplex b) {
        MyComplex alt = new MyComplex(a.real() + b.real(), a.imag() + b.imag());
        return alt;
    }

    public static MyComplex sub(MyComplex a, MyComplex b) {
        MyComplex alt = new MyComplex(a.real() - b.real(), a.imag() - b.imag());
        return alt;
    }

    public static MyComplex mul(MyComplex a, MyComplex b) {
        MyComplex alt = new MyComplex(a.real() * b.real() - a.imag() * b.imag(),
                a.real() * b.imag() + b.real() * a.imag());
        return alt;
    }

    public static MyComplex div(MyComplex a, MyComplex b) {
        MyComplex alt = new MyComplex(
                (a.real() * b.real() + a.imag() * b.imag()) / (Math.pow(b.real(), 2) + (Math.pow(b.imag(), 2))),
                (a.imag() * b.real() - a.real() * b.imag()) / (Math.pow(b.real(), 2) + (Math.pow(b.imag(), 2))));
        return alt;
    }

    public MyComplex add(MyComplex a) {
        MyComplex alt = new MyComplex(real + a.real(), imag + a.imag());
        return alt;
    }

    public MyComplex sub(MyComplex a) {
        MyComplex alt = new MyComplex(real - a.real(), imag - a.imag());
        return alt;
    }

    public MyComplex mul(MyComplex a) {
        // ここを入力
        MyComplex alt = new MyComplex(real * a.real() - imag * a.imag(), real * a.imag() + imag * a.real());
        return alt;
    }

    public MyComplex div(MyComplex a) {
        // ここを入力
        MyComplex alt = new MyComplex(
                (real * a.real() + imag * a.imag()) / (Math.pow(a.real(), 2) + (Math.pow(a.imag(), 2))),
                (imag * a.real() - real * a.imag()) / (Math.pow(a.real(), 2) + (Math.pow(a.imag(), 2))));
        return alt;
    }

    public MyComplex con() {
        // ここを入力
        MyComplex alt = new MyComplex(real, -imag);
        return alt;
    }
}