class DogCat
{
    public static void main(String[] args){
        Dog d = new Dog(3);  
        Cat c = new Cat(2); 

        d.walk();
        d.bite(); 

        c.walk(); 
        c.scratch();
    }
}