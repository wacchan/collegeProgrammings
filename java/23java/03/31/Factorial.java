import java.util.Scanner;

class Factorial{
 
 static int factorial(int n){
  if(n>0)
    return n*factorial(n-1);
  else 
   return 1;
  }

 public static void main(String[] args){
  Scanner stdIn=new Scanner(System.in);
   
  System.out.println("®”‚ğ“ü—Í‚¹‚æ:");
  int x=stdIn.nextInt();

  System.out.println(x+"‚ÌŠKæ‚Í"+factorial(x)+"‚Å‚·B");
 }
}
