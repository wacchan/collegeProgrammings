import java.util.Scanner;

class Replace2 {
    public static void main(String[] args) {
        Scanner stdIn = new Scanner(System.in);
        int cou = 0;
        int s2Len;

        System.out.print("�e�L�X�g: ");
        //StringBuilder s1 = new StringBuilder(stdIn.next()); // �e�L�X�g�p������
        String s1 = stdIn.next(); 

        System.out.print("�p�^�[��: ");
        String s2 = stdIn.next(); // �o�^�[���p������
        s2Len = s2.length();

        System.out.println(s1);

        int idx = BMmatch.bmMatch(s1.toString(), s2); // ������s1���當����s2��BM�@�ŒT��
        while (idx != -1) {
            cou++;
            for (int i = idx; i < idx + s2Len; i++) {
                s1 = s1.replaceFirst(s2, "@");
            }
            idx = BMmatch.bmMatch(s1.toString(), s2); // ������s1���當����s2��BM�@�ŒT��
        }

        System.out.println(s1);
        System.out.println("�o���� : " + cou);
        System.out.println("�u�������� : " + cou * s2Len);
    }
}