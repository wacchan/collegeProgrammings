
// string�^�X�^�b�N�̗��p��

import java.io.*;

class StringStackTester {

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringStack s = new StringStack(20); // �ő�20�v�b�V���ł���X�^�b�N

		while (true) {
			System.out.println("���݂̃f�[�^���F" + s.size() + " / " + s.capacity());
			System.out.print("(1)�v�b�V���@(2)�|�b�v�@(3)�s�[�N�@" + "(4)�_���v�@(0)�I���F");

			int menu = Integer.parseInt(br.readLine());
			if (menu == 0)
				break;

			String x;
			switch (menu) {
			case 1: // �v�b�V��
				System.out.print("�f�[�^�F");
				x = br.readLine();
				try {
					s.push(x);
				} catch (StringStack.OverflowStringStackException e) {
					System.out.println("�X�^�b�N�����t�ł��B");
				}
				break;

			case 2: // �|�b�v
				try {
					x = s.pop();
					System.out.println("�|�b�v�����f�[�^��" + x + "�ł��B");
				} catch (StringStack.EmptyStringStackException e) {
					System.out.println("�X�^�b�N����ł��B");
				}
				break;

			case 3: // �s�[�N
				try {
					x = s.peek();
					System.out.println("�s�[�N�����f�[�^��" + x + "�ł��B");
				} catch (StringStack.EmptyStringStackException e) {
					System.out.println("�X�^�b�N����ł��B");
				}
				break;

			case 4: // �_���v
				s.dump();
				break;
			}
		}
	}
}
