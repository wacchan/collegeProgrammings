class Dog extends Pet{
    public Dog(int n){
        super(n);
    }
    
    public void walk(){
        System.out.println("Œ¢("+age+"Î)‚ª•à‚­");
    }
    public void bite(){
        System.out.println("Œ¢("+age+"Î)‚ªŠš‚Ş");
    }
    public void scratch(){
        System.out.println("Œ¢("+age+"Î)‚ª‚Ğ‚Á‚©‚­");
    }
}