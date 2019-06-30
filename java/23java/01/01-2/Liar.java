class Liar extends Person {

    public Liar(String n, int a) {
        super(n, a);
        name = n;
        age = a;
    }

    int getAge() {
        if (age < 20)
            return age;
        else if (age < 30)
            return age - 1;
        else if (age < 40)
            return age - 2;
        else if (age < 50)
            return age - 3;
        else
            return age - 4;

    }
}
