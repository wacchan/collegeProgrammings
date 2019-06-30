import java.util.Scanner;

 class Hanoi{
  static void move(int no,String from,String work,String dest){

   if(no>1)
    move(no-1,from,dest,work);
   
   System.out.println("‰~”Õ["+no+"]‚ğ"+from+"²‚©‚ç"+dest+"²‚ÖˆÚ“®");
   
   if(no>1)
     move(no-1,work,from,dest);
  }

  public static void main(String[] args){
   Scanner stdIn =new Scanner(System.in);
   
   System.out.println("ƒnƒmƒC‚Ì“ƒ");
   System.out.print("‰~”Õ‚Ì–‡”");
   int n=stdIn.nextInt();

   move(n,"A","B","C");
  }
}
