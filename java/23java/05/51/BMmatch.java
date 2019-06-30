
// Boyer-Moore�@�ɂ�镶����T��

import java.util.Scanner;

class BMmatch {
    // Boyer-Moore�@�ɂ�镶����T��
    static int bmMatch(String txt, String pat) {
        int pt; // txt���Ȃ���J�[�\��
        int pp; // pat���Ȃ���J�[�\��
        int txtLen = txt.length(); // txt�̕�����
        int patLen = pat.length(); // pat�̕�����
        int[] skip = new int[Character.MAX_VALUE + 1]; // �X�L�b�u�e�[�u��

        // �X�L�b�u�e�[�u���̍쐬
        for (pt = 0; pt <= Character.MAX_VALUE; pt++) {
            skip[pt] = patLen;
        }
        for (pt = 0; pt < patLen - 1; pt++) {
            skip[pat.charAt(pt)] = patLen - pt - 1; // pt == patLen - 1�ł���
        }

        // �T��
        while (pt < txtLen) {
            pp = patLen - 1;

            while (txt.charAt(pt) == pat.charAt(pp)) {
                if (pp == 0) {
                    return pt; // �T������
                }
                pp--;
                pt--;
            }
            pt += skip[txt.charAt(pt)];
        }
        return -1; // �T�����s
    }

    public static void main(String[] args) {
        Scanner stdIn = new Scanner(System.in);

        System.out.print("�e�L�X�g: ");
        String s1 = stdIn.next(); // �e�L�X�g�p������

        System.out.print("�p�^�[��: ");
        String s2 = stdIn.next(); // �o�^�[���p������

        int idx = bmMatch(s1, s2); // ������s1���當����s2��BM�@�ŒT��

        if (idx == -1)
            System.out.println("�e�L�X�g���Ƀp�^�[���͑��݂��܂���B");
        else {
            // �}�b�`�����̒��O�܂ł́s���p�t�ł̕����������߂�
            int len = 0;
            for (int i = 0; i < idx; i++)
                len += s1.substring(i, i + 1).getBytes().length;
            len += s2.length();

            System.out.println((idx + 1) + "�����ڂɃ}�b�`���܂��B");
            System.out.println("�e�L�X�g: " + s1);
            System.out.printf(String.format("�p�^�[��: %%%ds\n", len), s2);

        }
    }

}