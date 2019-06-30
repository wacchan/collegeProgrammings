// string�^�X�^�b�N

public class StringStack {
	private int max; // �X�^�b�N�̗e��
	private int ptr; // �X�^�b�N�|�C���^
	private String[] stk; // �X�^�b�N�̖{��

	// --- ���s����O�F�X�^�b�N���� ---//
	public class EmptyStringStackException extends RuntimeException {
		public EmptyStringStackException() {
		}
	}

	// --- ���s����O�F�X�^�b�N�����t ---//
	public class OverflowStringStackException extends RuntimeException {
		public OverflowStringStackException() {
		}
	}

	// --- �R���X�g���N�^ ---//
	public StringStack(int capacity) {
		ptr = 0;
		max = capacity;
		try {
			stk = new String[max]; // �X�^�b�N�{�̗p�̔z��𐶐�
		} catch (OutOfMemoryError e) { // �����ł��Ȃ�����
			max = 0;
		}
	}

	// --- �X�^�b�N��x���v�b�V�� ---//
	public String push(String x) throws OverflowStringStackException {
		if (ptr >= max) // �X�^�b�N�͖��t
			throw new OverflowStringStackException();
		return stk[ptr++] = x;
	}

	// --- �X�^�b�N����f�[�^���|�b�v�i����̃f�[�^�����o���j ---//
	public String pop() throws EmptyStringStackException {
		if (ptr <= 0) // �X�^�b�N�͋�
			throw new EmptyStringStackException();
		return stk[--ptr];
	}

	// --- �X�^�b�N����f�[�^���s�[�N�i����̃f�[�^��`�����j ---//
	public String peek() throws EmptyStringStackException {
		if (ptr <= 0) // �X�^�b�N�͋�
			throw new EmptyStringStackException();
		return stk[ptr - 1];
	}

	// --- �X�^�b�N����x��T���ăC���f�b�N�X�i������Ȃ����-1�j��Ԃ� ---//
	public int indexOf(String x) {
		for (int i = ptr - 1; i >= 0; i--) // ���㑤������`�T��
			if (stk[i] == x)
				return i; // �T������
		return -1; // �T�����s
	}

	// --- �X�^�b�N����ɂ��� ---//
	public void clear() {
		ptr = 0;
	}

	// --- �X�^�b�N�̗e�ʂ�Ԃ� ---//
	public int capacity() {
		return max;
	}

	// --- �X�^�b�N�ɐς܂�Ă���f�[�^����Ԃ� ---//
	public int size() {
		return ptr;
	}

	// --- �X�^�b�N�͋�ł��邩 ---//
	public boolean isEmpty() {
		return ptr <= 0;
	}

	// --- �X�^�b�N�͖��t�ł��邩 ---//
	public boolean isFull() {
		return ptr >= max;
	}

	// --- �X�^�b�N���̑S�f�[�^��ꁨ����̏��ɕ\�� ---//
	public void dump() {
		if (ptr <= 0) {
			System.out.println("�X�^�b�N�͋�ł��B");
		} else {
			for (int i = 0; i < max; i++) {
				System.out.print("[" + i + "] " + stk[i] + " ");
				if (i == ptr) {
					System.out.print("<-- ptr");
				}
				System.out.println();
			}

		}
	}
}
