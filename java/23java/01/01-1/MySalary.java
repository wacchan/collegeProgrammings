class MySalary
{
  public static void main(String[] args)
  {
    Staff yamada = new Staff("山田");
    Arbeit murata = new Arbeit("村田");
    printSalary(yamada, 8, 17, 30);
    printSalary(murata, 8, 17, 30);
  }
  private static void printSalary(Employee person, int fromTime, int toTime, int days)
  {
    System.out.println(person.getName() + " さんの給料は " + person.getSalary(fromTime, toTime, days) + " 円です。");
  }
}

class Employee
{
  private String name;
  public Employee(String n){
    this.name = n;
  }
  public String getName(){
    return name;
  }
  public int getSalary(int fromTime, int toTime, int days) {
    return 0;
  }
}

class Staff extends Employee
{
  public Staff(String n) {
    super(n);
  }
  public int getSalary(int fromTime, int toTime, int days) {
    return 10000 * days;
  }
}

class Arbeit extends Employee
{
  public Arbeit(String n) {
    super(n);
  }
  public int getSalary(int fromTime, int toTime, int days) {
    return ((toTime - fromTime) * 800 ) * days;
  }
}
