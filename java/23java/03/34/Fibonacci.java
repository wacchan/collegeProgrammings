//フィボナッチ数列　再帰

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
	
	int n=0;  //第n項
	
	do{
	    System.out.println("第何項まで求めますか?");
	    System.out.println("2以上の整数を入力してください");
		n = Integer.parseInt(br.readLine());
	}while(n<2); //2以上でないともう一度入力させる
	
	for(int i=0; i<n+1; i++){
	    System.out.print(fibonacci(i));
	    System.out.print(", ");
	}
	System.out.println();
    }
}
