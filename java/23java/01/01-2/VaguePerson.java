class VaguePerson extends Person {

    public VaguePerson(String n, int a) {
        super(n, a);
        name = n;
        age = a;
    }

    int getAge() {
        return ((age + 5) / 10) * 10;
    }
}
