class HonestPerson extends Person {

    public HonestPerson(String n, int a) {
        super(n, a);
        name = n;
        age = a;
    }

    int getAge() {
        return age;
    }
}
