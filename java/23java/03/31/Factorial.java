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
   
  System.out.println("��������͂���:");
  int x=stdIn.nextInt();

  System.out.println(x+"�̊K���"+factorial(x)+"�ł��B");
 }
}
