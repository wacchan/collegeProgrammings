
// String.indexOf���\�b�h��String.lastIndexOf���\�b�h�ɂ�镶����T��

import java.util.Scanner;

class IndexOfTester {
    public static void main(String[] args) {
        Scanner stdIn = new Scanner(System.in);

        System.out.print("�e�L�X�g: ");
        String s1 = stdIn.next(); // �e�L�X�g�p������

        System.out.print("�p�^�[��: ");
        String s2 = stdIn.next(); // �o�^�[���p������

        int idx1 = s1.indexOf(s2); // ������s1����s2��T��(�擪��)
        int idx2 = s1.lastIndexOf(s2); // ������s1����s2��T��(������)

        if (idx1 == -1)
            System.out.println("�e�L�X�g���Ƀp�^�[���͑��݂��܂���B");
        else {
            // �}�b�`�����̒��O�܂ł́s���p�t�ł̕����������߂�
            int len1 = 0;
            for (int i = 0; i < idx1; i++)
                len1 += s1.substring(i, i + 1).getBytes().length;
            len1 += s2.length();

            int len2 = 0;
            for (int i = 0; i < idx2; i++)
                len2 += s1.substring(i, i + 1).getBytes().length;
            len2 += s2.length();

            System.out.println("�e�L�X�g: " + s1);
            System.out.printf(String.format("�p�^�[��: %%%ds\n", len1), s2);
            System.out.println("�e�L�X�g: " + s1);
            System.out.printf(String.format("�p�^�[��: %%%ds\n", len2), s2);
        }
    }
}
