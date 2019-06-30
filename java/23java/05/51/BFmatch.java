import java.util.Scanner;

class BFmatch {

   //--- �͂܂����@�ɂ�镶����T�� ---//
   static int bfMatch(String txt, String pat) {
      int pt = 0;      // txt���Ȃ���J�[�\��
      int pp = 0;      // pat���Ȃ���J�[�\��

      while (pt != txt.length() && pp != pat.length()) {
         if (txt.charAt(pt) == pat.charAt(pp)) {
            pt++;
            pp++;
         } else {
            pt = pt - pp + 1;
            pp = 0;
         }
      }
      if (pp == pat.length())      // �T������
         return pt - pp;
      return -1;               // �T�����s
   }

   public static void main(String[] args) {
      Scanner stdIn = new Scanner(System.in);

      System.out.print("�e�L�X�g�F");
      String s1 = stdIn.next();                // �e�L�X�g�p������

      System.out.print("�p�^�[���F");
      String s2 = stdIn.next();               // �p�^�[���p������

      int idx = bfMatch(s1, s2);   // ������s1���當����s2��͂܂����@�ŒT��

      if (idx == -1)
         System.out.println("�e�L�X�g���Ƀp�^�[���͑��݂��܂���B");
      else {
         // �}�b�`�����̒��O�܂ł́s���p�t�ł̕����������߂�
         int len = 0;
         for (int i = 0; i < idx; i++)
            len += s1.substring(i, i + 1).getBytes().length;
         len += s2.length();

         System.out.println((idx + 1) + "�����ڂɃ}�b�`���܂��B");
         System.out.println("�e�L�X�g�F" + s1);
         System.out.printf(String.format("�p�^�[���F%%%ds\n", len), s2);
      }
   }
}

