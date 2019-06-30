class MyComplex{
    double real, imag;

    public MyComplex(double x,double y){
        real = x;
        imag = y;
    }
    public MyComplex(double x){
        real = x; imag = 0;
    }

    public String toString(){
        return " "+ String.valueOf(real) +" + "+ String.valueOf(imag) +" i";
    }

    public double real(){
        return real;
    }

    public double imag(){
        return imag;
    }

    public static MyComplex add(MyComplex a, MyComplex b){
        double abreal = a.real() + b.real();
        double abimag = a.imag() + b.imag();
        return new MyComplex(abreal, abimag);
    }

    public static MyComplex sub(MyComplex a, MyComplex b){
        double abreal = a.real() - b.real();
        double abimag = a.imag() - b.imag();
        return new MyComplex(abreal, abimag);
    }

    public static MyComplex mul(MyComplex a, MyComplex b){
        double abreal = a.real * b.real() - a.imag() * b.imag();
        double abimag = a.real * b.imag() + a.imag() * b.real();
        return new MyComplex(abreal, abimag);
    }

    public static MyComplex div(MyComplex a, MyComplex b){
        double abreal = (a.real() * b.real() + a.imag() * b.imag())/(Math.pow(b.real(),2) + Math.pow(b.imag(),2));
        double abimag = (b.real() * a.imag() - a.real() * b.imag())/(Math.pow(b.real(),2) + Math.pow(b.imag(),2));
        return new MyComplex(abreal, abimag);
    }

    public MyComplex add(MyComplex a){
        double abreal = real() + a.real();
        double abimag = imag() + a.imag();
        return new MyComplex(abreal, abimag);
    }

    public MyComplex sub(MyComplex a){
        double abreal = real() - a.real();
        double abimag = imag() - a.imag();
        return new MyComplex(abreal, abimag);
    }

    public MyComplex mul(MyComplex a){
        double abreal = real() * a.real() - imag() * a.imag();
        double abimag = real() * a.imag() + imag() * a.real();
        return new MyComplex(abreal, abimag);
    }

    public MyComplex div(MyComplex a){
        double abreal = (real() * a.real() + imag() * a.imag())/(Math.pow(a.real(),2) + Math.pow(a.imag(),2));
        double abimag = (a.real() * imag() - real() * a.imag())/(Math.pow(a.real(),2) + Math.pow(a.imag(),2));
        return new MyComplex(abreal, abimag);
    }

    public MyComplex con(){
        return new MyComplex(real, -imag);
    } 
}
