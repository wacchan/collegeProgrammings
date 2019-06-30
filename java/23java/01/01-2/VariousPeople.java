class VariousPeople {
    public static void main(String[] args) {
        HonestPerson asahina = new HonestPerson("Asahina", 24);
        VaguePerson aiki = new VaguePerson("Aiki", 32);
        Liar saitoh = new Liar("Saitoh", 45);
        introduce(asahina);
        introduce(aiki);
        introduce(saitoh);
    }

    private static void introduce(Person p) {
        System.out.println("My name is " + p.getName() + ".");
        System.out.println("I am " + p.getAge() + " years old.");
        System.out.println();
    }
}
