import java.util.Scanner;

class Change {
    public static void main(String[] args) {
        Scanner stdIn = new Scanner(System.in);
        int cou = 0;
        int s2Len;

        System.out.print("�e�L�X�g: ");
        StringBuilder s1 = new StringBuilder(stdIn.next()); // �e�L�X�g�p������

        System.out.print("�����p�^�[��: ");
        String s2 = stdIn.next(); // �o�^�[���p������
        s2Len = s2.length();

        System.out.print("�u����̃p�^�[��: ");
        String s3 = stdIn.next();

        System.out.println(s1);

        int idx = BMmatch.bmMatch(s1.toString(), s2); // ������s1���當����s2��BM�@�ŒT��
        while (idx != -1) {
            cou++;

            s1.replace(idx, idx + s2.length(), s3);

            idx = BMmatch.bmMatch(s1.toString(), s2); // ������s1���當����s2��BM�@�ŒT��
        }

        System.out.println(s1);
        System.out.println("�u���� : " + cou);
    }
}