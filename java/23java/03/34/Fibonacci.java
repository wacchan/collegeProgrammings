//�t�B�{�i�b�`����@�ċA

import java.io.*;

class Fibonacci{

    public static int fibonacci(int n){
		if(n==1 || n==0)
		return n;
	  else
		return fibonacci(n-2) + fibonacci(n-1);
	}

    public static void main(String[] args)throws IOException{
	BufferedReader br =
	    new BufferedReader(new InputStreamReader(System.in));
	
	int n=0;  //��n��
	
	do{
	    System.out.println("�扽���܂ŋ��߂܂���?");
	    System.out.println("2�ȏ�̐�������͂��Ă�������");
		n = Integer.parseInt(br.readLine());
	}while(n<2); //2�ȏ�łȂ��Ƃ�����x���͂�����
	
	for(int i=0; i<n+1; i++){
	    System.out.print(fibonacci(i));
	    System.out.print(", ");
	}
	System.out.println();
    }
}
