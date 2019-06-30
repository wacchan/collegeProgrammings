import java.io.*;

class CalcRPN {

    public static StringStack temoto;

    public static boolean isDigit(String str) {
        int a,b;
        switch (str.charAt(0)){
            case '+':
                b = Integer.parseInt(temoto.pop());
                a = Integer.parseInt(temoto.pop());
                temoto.push(String.valueOf(a+b));
                return false;
            case '-':
                b = Integer.parseInt(temoto.pop());
                a = Integer.parseInt(temoto.pop());
                temoto.push(String.valueOf(a-b));
                return false;
            case '*':
                b = Integer.parseInt(temoto.pop());
                a = Integer.parseInt(temoto.pop());
                temoto.push(String.valueOf(a*b));
                return false;
            case '/':
                b = Integer.parseInt(temoto.pop());
                a = Integer.parseInt(temoto.pop());
                temoto.push(String.valueOf(a/b));
                return false;
            default:
                temoto.push(str);
                return true;

        }
    
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        System.out.print("逆ホ?ーラント?記法の数式:");
        String targetRPN = br.readLine();
        System.out.println("targetRPN = " + targetRPN);

        String[] tokens = targetRPN.split(" ");
        System.out.println("tokenNum = " + tokens.length);

        temoto = new StringStack(tokens.length);

        for (int i = 0; i < tokens.length; i++) {
            if (isDigit(tokens[i])) {
                System.out.println(i + ": " + tokens[i] + " (digit)");
            } else {
                System.out.println(i + ": " + tokens[i] + " (operator)");
            }
            System.out.print("手元 ");
            temoto.show();
        }

        System.out.println("targetRPN = " + targetRPN);
        System.out.println("ans = " + temoto.pop());

    }
}