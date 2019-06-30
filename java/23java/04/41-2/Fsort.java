import java.io.*;

class Fsort {

   //--- 度数ソート（配列要素の値は0以上max以下） ---//
    static void fSort(int[] a, int n, int max) {
        int[] f = new int[max + 1];   // 累積度数
        int[] b = new int[n];         // 作業用目的配列

        //度数分布
        System.out.println("度数分布"); 
        for (int i = 0; i < n; i++) {
            f[a[i]]++;
        }
        
        //度数分布表示
        for(int i = 0; i <= max; i++){
            System.out.printf(" %3d： %3d ", i,f[i]);
            for(int k = 0; k < f[i]; k++){
                System.out.print("*");
            }
            System.out.println();
        }
        System.out.println();

        //度数分布を累積度数化
        System.out.println("累積度数分布"); 
        for (int i = 1; i <= max; i++) {
            f[i] += f[i - 1];
        }

        //累積度数表示
        for(int i = 0; i <= max; i++){
            System.out.printf(" %3d： %3d ", i,f[i]);
            for(int k = 0; k < f[i]; k++){
                System.out.print("*");
            }
            System.out.println();
        }

        //累積度数を元に、ソート
        for (int i = n - 1; i >= 0; i--) {
            b[--f[a[i]]] = a[i];
        }
      
        //bをaに代入
        for (int i = 0;   i < n;i++) a[i] = b[i];              
    }

    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        System.out.print("要素数：");
        int nx = Integer.parseInt(br.readLine());
        int[] x = new int[nx];

        for (int i = 0; i < nx; i++) {
            do {
                System.out.print("x[" + i + "]：");
                x[i] = Integer.parseInt(br.readLine());
            } while (x[i] < 0);
        }

        int max = x[0];
        for (int i = 1; i < nx; i++)
            if (x[i] > max) max = x[i];
      
        fSort(x, nx, max);            // 配列xを度数ソート
      
        System.out.println("result");
        for (int i = 0; i < nx; i++)
            System.out.println(" x[" + i + "]＝" + x[i]);
    }
}