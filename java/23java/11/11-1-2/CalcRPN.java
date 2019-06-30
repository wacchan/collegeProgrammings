import java.io.*;

class CalcRPN {

    public static IntLinkedList temoto;

    public static boolean isDigit(String str) {
        int a,b;
        switch (str.charAt(0)){
            case '+':
                b = Integer.parseInt(temoto.getLastNode());
                a = Integer.parseInt(temoto.getLastNode());
                temoto.addLast(String.valueOf(a+b));
                return false;
            case '-':
                b = Integer.parseInt(temoto.getLastNode());
                a = Integer.parseInt(temoto.getLastNode());
                temoto.addLast(String.valueOf(a-b));
                return false;
            case '*':
                b = Integer.parseInt(temoto.getLastNode());
                a = Integer.parseInt(temoto.getLastNode());
                temoto.addLast(String.valueOf(a*b));
                return false;
            case '/':
                b = Integer.parseInt(temoto.getLastNode());
                a = Integer.parseInt(temoto.getLastNode());
                temoto.addLast(String.valueOf(a/b));
                return false;
            default:
                temoto.addLast(str);
                return true;

        }
    
    }

    public static void main(String[] args) throws IOException {
        /*
        System.out.print("逆ポーランド記法の数式："); 
        InputStreamReader input = new InputStreamReader(System.in); 
        BufferedReader br = new BufferedReader(input);
        String targetRPN = br.readLine(); 
        String[] tokens = targetRPN.split(" "); 
        System.out.println("targetRPN = " + targetRPN); 
        IntLinkedList RPN = new IntLinkedList(); 
        for(int i=0; i<tokens.length; i++){     
            RPN.addLast(tokens[i]); 
        } 
        RPN.dump(); 
        System.out.println("ans = " + calcRPN(RPN));*/


        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        System.out.print("逆ポーランド記法の数式:");
        String targetRPN = br.readLine();
        System.out.println("targetRPN = " + targetRPN);

        String[] tokens = targetRPN.split(" ");
        System.out.println("tokenNum = " + tokens.length);

        temoto = new IntLinkedList();

        for (int i = 0; i < tokens.length; i++) {
            if (isDigit(tokens[i])) {
                System.out.println(i + ": " + tokens[i] + " (digit)");
            } else {
                System.out.println(i + ": " + tokens[i] + " (operator)");
            }
            System.out.print("手元 ");
            temoto.dump();
        }

        System.out.println("targetRPN = " + targetRPN);
        System.out.println("ans = " + temoto.getFirstNode());

    }
}