import java.util.Scanner;

 class Hanoi{
  static void move(int no,String from,String work,String dest){

   if(no>1)
    move(no-1,from,dest,work);
   
   System.out.println("�~��["+no+"]��"+from+"������"+dest+"���ֈړ�");
   
   if(no>1)
     move(no-1,work,from,dest);
  }

  public static void main(String[] args){
   Scanner stdIn =new Scanner(System.in);
   
   System.out.println("�n�m�C�̓�");
   System.out.print("�~�Ղ̖���");
   int n=stdIn.nextInt();

   move(n,"A","B","C");
  }
}
