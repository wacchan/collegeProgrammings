
// KMP�@�ɂ�镶����T��
import java.util.Scanner;

class KmpMatch {
    static int kmpMatch(String txt, String pat) {
        int pt = 1;
        int pp = 0;
        int[] skip = new int[pat.length() + 1];

        // �X�L�b�v�e�[�u���̍쐬
        skip[pt] = 0;
        while (pt != pat.length()) {
            if (pat.charAt(pt) == pat.charAt(pp)) {
                skip[++pt] = ++pp;
            } else if (pp == 0) {
                skip[++pt] = pp;
            } else {
                pp = skip[pp];
            }
        }

        // �T��
        pt = pp = 0;
        while (pt != txt.length() && pp != pat.length()) {
            if (txt.charAt(pt) == pat.charAt(pp)) {
                pt++;
                pp++;
            } else if (pp == 0) {
                pt++;
            } else {
                pp = skip[pp];
            }
        }

        if (pp == pat.length()) {
            return pt - pp; // �p�^�[���̑S�������ƍ�
        } else {
            return -1; // �T�����s
        }
    }

    public static void main(String[] args) {
        Scanner stdIn = new Scanner(System.in);
        int[] idx = new int[10];

        System.out.print("�e�L�X�g: ");
        String s1 = stdIn.next(); // �e�L�X�g�p������

        System.out.print("�p�^�[��: ");
        String s2 = stdIn.next(); // �o�^�[���p������

        // ������s1����s2��T��(�擪��)
        idx[0] = 0;
        for(int i = 1; i < 11; i++){
            idx[i] = kmpMatch(s1.substring(idx[i-1]), s2);//�O��܂ł�؂����čĒT��

            if(idx[1] == -1){                 //����Ńp�^�[����������Ȃ�������
                System.out.println("�e�L�X�g���Ƀp�^�[���͑��݂��܂���B");
            }else if(idx[i] == -1){           //����ȊO�Ńp�^�[����������Ȃ�������
                break;
            }else {                           //�p�^�[��������������
                int len1 = 0;
                idx[i] += idx[i-1];           //���񌩂����p�^�[��+�؂�����������
                for (int j = 0; j < idx[i]; j++){
                    len1 += s1.substring(j, j + 1).getBytes().length;  //�������p�^�[���܂ł̕������i���p�j
                }
                len1 += s2.length();

                System.out.println((idx[i] + 1) + "�����ڂɃ}�b�`���܂��B");
                System.out.println("�e�L�X�g:  " + s1);
                /*System.out.print("�p�^�[��: ");
                for(int j = 0; j < len1; j++){
                    System.out.print(" ");
                }
                System.out.println(s2);*/
                System.out.printf(String.format("�p�^�[��: %%%ds\n", len1+1), s2);//%len1d�ilen1�����X�y�[�X�\���j�{s2�\��
                
                idx[i] = idx[i] + s2.length();  //���񌩂����p�^�[���܂ł̕�����


            }
        }

        
    }

}