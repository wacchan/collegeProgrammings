// String�^�L���[

public class StringQueue {
	private int max;			// �L���[�̗e��
	private int front;		// �擪�v�f�J�[�\��
	private int rear;			// �����v�f�J�[�\��
	private int num;			// ���݂̃f�[�^��
	private String[] que;		// �L���[�̖{��

	//--- ���s����O�F�L���[���� ---//
	public class EmptyStringQueueException extends RuntimeException {
		public EmptyStringQueueException() { }
	}

	//--- ���s����O�F�L���[�����t ---//
	public class OverflowStringQueueException extends RuntimeException {
		public OverflowStringQueueException() { }
	}

	//--- �R���X�g���N�^ ---//
	public StringQueue(int capacity) {
		num = front = rear = 0;
		max = capacity;
		try {
			que = new String[max];				// �L���[�{�̗p�̔z��𐶐�
		} catch (OutOfMemoryError e) {	// �����ł��Ȃ�����
			max = 0;
		}
	}

	//--- �L���[�Ƀf�[�^���G���L���[ ---//
	public String enque(String x) throws OverflowStringQueueException {
		if (num >= max)
			throw new OverflowStringQueueException();			// �L���[�͖��t
		que[rear++] = x;
		num++;
		if (rear == max)
			rear = 0;
		return x;
	}

	//--- �L���[����f�[�^���f�L���[ ---//
	public String deque() throws EmptyStringQueueException {
		if (num <= 0)
			throw new EmptyStringQueueException();			// �L���[�͋�
		String x = que[front++];
		num--;
		if (front == max)
			front = 0;
		return x;
	}

	//--- �L���[����f�[�^���s�[�N�i�擪�f�[�^��`���j ---//
	public String peek() throws EmptyStringQueueException {
		if (num <= 0)
			throw new EmptyStringQueueException();			// �L���[�͋�
		return que[front];
	}

	//--- �L���[�̗e�ʂ�Ԃ� ---//
	public int capacity() {
		return max;
	}

	//--- �L���[�ɒ~�����Ă���f�[�^����Ԃ� ---//
	public int size() {
		return num;
	}

	//--- �L���[���̑S�f�[�^��擪�������̏��ɕ\�� ---//
	public void dump() {
		if (num <= 0)
			System.out.println("�L���[�͋�ł��B");
		else {
			for (int i = 0; i < max; i++){
				System.out.print("["+ i +"] "+ que[i] + " ");
				if (i == front){
					System.out.println("(front)");
				}	else if (i == rear){
					System.out.println("(rear)");
				}	else {
					System.out.println();
				}
			}
		}
		System.out.println();
	}
}
