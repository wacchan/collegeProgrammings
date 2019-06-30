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
  
  System.out.println("“ñ‚Â‚Ì®”‚ÌÅ‘åŒö–ñ”‚ğ‹‚ß‚éB");

  System.out.print("®”‚ğ“ü—Í‚¹‚æ:"); int x=stdIn.nextInt();
  System.out.print("®”‚ğ“ü—Í‚¹‚æ:"); int y=stdIn.nextInt();

  System.out.println("Å‘åŒö–ñ”‚Í"+gcd(x,y)+"‚Å‚·B");
 }
}
