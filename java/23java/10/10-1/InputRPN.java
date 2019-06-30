import java.io.*;

class InputRPN {

    public static boolean isDigit(String str) {
        if (str.charAt(0) == '+' || str.charAt(0) == '-' || str.charAt(0) == '*' || str.charAt(0) == '/') {
            return false;
        } else {
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

        for (int i = 0; i < tokens.length; i++) {
            if (isDigit(tokens[i])) {
                System.out.println(i + ": " + tokens[i] + " (digit)");
            } else {
                System.out.println(i + ": " + tokens[i] + " (operator)");
            }
        }

    }
}