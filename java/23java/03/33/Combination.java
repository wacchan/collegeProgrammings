import java.io.*;

class Combination {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int n,r;
        do{
            System.out.print("n = ");
            n = Integer.parseInt(br.readLine());
            System.out.print("r = ");
            r = Integer.parseInt(br.readLine());
            if(n<r||n<0||r<0)System.out.println("n‚©r‚ª•‰‚Ü‚½‚Í n<r ‚Å‚·B");
        }while(n<r||n<0||r<0);
        System.out.println(n + "C" + r + " = " + Combinate(n, r));

    }

    public static int Combinate(int n, int r) {
        if (n == 0 || r == 0 || n == r) {
            return 1;
        } else {
            return Combinate(n - 1, r) + Combinate(n - 1, r - 1);
        }

    }

}