
//	�z�E�d�A�����X�g�N���X

import java.util.Comparator;

public class DblLinkedList<E> {

	// --- �m�[�h ---//
	class Node<E> {
		private E data; // �f�[�^
		private Node<E> prev; // ��s�|�C���^�i��s�m�[�h�ւ̎Q�Ɓj
		private Node<E> next; // �㑱�|�C���^�i�㑱�m�[�h�ւ̎Q�Ɓj

		// --- �R���X�g���N�^ ---//
		Node() {
			data = null;
			prev = next = this;
		}

		// --- �R���X�g���N�^ ---//
		Node(E obj, Node<E> prev, Node<E> next) {
			data = obj;
			this.prev = prev;
			this.next = next;
		}
	}

	private Node<E> head; // �擪�m�[�h�i�_�~�[�m�[�h�j
	private Node<E> crnt; // ���ڃm�[�h

	// --- �R���X�g���N�^ ---//
	public DblLinkedList() {
		head = crnt = new Node<E>(); // �_�~�[�m�[�h�𐶐�
	}

	// --- ���X�g�͋� ---//
	public boolean isEmpty() {
		return head.next == head;
	}

	// --- �m�[�h��T�� ---//
	public E search(E obj, Comparator<? super E> c) {
		Node<E> ptr = head.next; // ���ݑ������̃m�[�h

		while (ptr != head) {
			if (c.compare(obj, ptr.data) == 0) {
				crnt = ptr;
				return ptr.data; // �T������
			}
			ptr = ptr.next; // �㑱�m�[�h�ɒ���
		}
		return null; // �T�����s
	}

	// --- ���ڃm�[�h��\�� ---//
	public void printCurrentNode() {
		if (isEmpty())
			System.out.println("���ڃm�[�h�͂���܂���B");
		else
			System.out.println(crnt.data);
	}

	// --- �S�m�[�h��\�� ---//
	public void dump() {
		Node<E> ptr = head.next; // �_�~�[�m�[�h�̌㑱�m�[�h

		while (ptr != head) {
			if (ptr == crnt) {
				System.out.println(ptr.data + " <-- crnt");
			} else {
				System.out.println(ptr.data);
			}
			ptr = ptr.next;
		}
	}

	// --- �S�m�[�h���t���ɕ\�� ---//
	public void dumpReverse() {
		Node<E> ptr = head.prev; // �_�~�[�m�[�h�̐�s�m�[�h

		while (ptr != head) {
			if (ptr == crnt) {
				System.out.println(ptr.data + " <-- crnt");
			} else {
				System.out.println(ptr.data);
			}
			ptr = ptr.prev;
		}
	}

	// --- ���ڃm�[�h�������ɐi�߂� ---//
	public boolean next() {
		if (isEmpty() || crnt.next == head)
			return false; // �i�߂邱�Ƃ͂ł��Ȃ�����
		crnt = crnt.next;
		return true;
	}

	// --- ���ڃm�[�h����O���ɐi�߂� ---//
	public boolean prev() {
		if (isEmpty() || crnt.prev == head)
			return false; // �i�߂邱�Ƃ͂ł��Ȃ�����
		crnt = crnt.prev;
		return true;
	}

	// --- ���ڃm�[�h�̒���Ƀm�[�h��}�� ---//
	public void add(E obj) {
		Node<E> node = new Node<E>(obj, crnt, crnt.next);
		crnt.next = crnt.next.prev = node;
		crnt = node;
	}

	// --- �擪�Ƀm�[�h��}�� ---//
	public void addFirst(E obj) {
		crnt = head; // �_�~�[�m�[�hhead�̒���ɑ}��
		add(obj);
	}

	// --- �����Ƀm�[�h��}�� ---//
	public void addLast(E obj) {
		crnt = head.prev; // �����m�[�hhead.prev�̒���ɑ}��
		add(obj);
	}

	// --- ���ڃm�[�h���폜 ---//
	public void removeCurrentNode() {
		if (!isEmpty()) {
			crnt.prev.next = crnt.next;
			crnt.next.prev = crnt.prev;
			crnt = crnt.prev;
			if (crnt == head)
				crnt = head.next;
		}
	}

	// --- �m�[�hp���폜 ---//
	public void remove(Node p) {
		Node<E> ptr = head.next;

		while (ptr != head) {
			if (ptr == p) { // p��������
				crnt = p;
				removeCurrentNode();
				break;
			}
			ptr = ptr.next;
		}
	}

	// --- �擪�m�[�h���폜 ---//
	public void removeFirst() {
		crnt = head.next; // �擪�m�[�hhead.next���폜
		removeCurrentNode();
	}

	// --- �����m�[�h���폜 ---//
	public void removeLast() {
		crnt = head.prev; // �����m�[�hhead.prev���폜
		removeCurrentNode();
	}

	// --- �S�m�[�h���폜 ---//
	public void clear() {
		while (!isEmpty()) // ��ɂȂ�܂�
			removeFirst(); // �擪�m�[�h���폜
	}

	public int size() {
		Node<E> ptr = head.next;
		int counter = 0;
		while (ptr != head) {
			ptr = ptr.next;
			counter++;
		}
		return counter;
	}

	public void swapCurrentNode() {
		Node<E> ptr = crnt.next;

		crnt.prev.next = ptr;
		crnt.next.prev = crnt.prev;

		crnt.next = crnt.next.next;
		ptr.next.prev = crnt;

		ptr.next = crnt;
		crnt.prev = ptr;
	}

}