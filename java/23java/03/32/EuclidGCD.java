import java.util.Scanner;

class EuclidGCD{
  
  static int gcd(int x,int y){
   if(y==0)
    return x;
   else
    return gcd(y,x%y);
  }

 public static void main(String[] args){
  Scanner stdIn=new Scanner(System.in);
  
  System.out.println("��̐����̍ő���񐔂����߂�B");

  System.out.print("��������͂���:"); int x=stdIn.nextInt();
  System.out.print("��������͂���:"); int y=stdIn.nextInt();

  System.out.println("�ő���񐔂�"+gcd(x,y)+"�ł��B");
 }
}
