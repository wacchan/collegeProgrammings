
// �Q���T����

import java.util.Comparator;

public class IntBinTree {

	private int level = 0; // ���x������p
	// --- �m�[�h ---//

	static class Node {

		private int key; // �L�[�l

		private Node left; // ���q�m�[�h

		private Node right; // �E�q�m�[�h

		// --- �R���X�g���N�^ ---//

		Node(int key, Node left, Node right) {

			this.key = key;

			this.left = left;

			this.right = right;

		}

		// --- �L�[�l��Ԃ� ---//

		int getKey() {

			return key;

		}

		// --- �f�[�^�̕\�� ---//

		void print() {

			System.out.println(key);

		}

	}

	private Node root; // ��

	private Comparator comparator = null; // �R���p���[�^

	// --- �R���X�g���N�^ ---//

	public IntBinTree() {

		root = null;

	}

	// --- �R���X�g���N�^ ---//

	public IntBinTree(Comparator c) {

		this();

		comparator = c;

	}

	// --- ��̃L�[�l���r ---//

	private int comp(int key1, int key2) {

		if (key1 == key2){
			return 0;
		}else if (key1>key2){
			return 1;
		}else {
			return -1;
		}
	}

	// --- �L�[�ɂ��T�� ---//

	public int search(int key) {

		Node p = root; // ���ɒ���

		while (true) {

			if (p == null) // ����ȏ�i�߂Ȃ����

				return -1; // �c�T�����s

			int cond = comp(key, p.getKey()); // key�ƃm�[�hp�̃L�[���r

			if (cond == 0) // ���������

				return p.getKey(); // �c�T������

			else if (cond < 0) // key�̂ق������������

				p = p.left; // �c�������؂���T��

			else // key�̂ق����傫�����

				p = p.right; // �c�E�����؂���T��

		}

	}

	// --- node�����Ƃ��镔���؂Ƀm�[�h<K,V>��}�� ---//

	private void addNode(Node node, int key, int data) {

		int cond = comp(key, node.getKey());

		if (cond == 0)

			return; // key�͂Q���T���؏�Ɋ��ɑ���

		else if (cond < 0) {

			if (node.left == null)

				node.left = new Node(key, null, null);

			else

				addNode(node.left, key, data); // �������؂ɒ���

		} else {

			if (node.right == null)

				node.right = new Node(key, null, null);

			else

				addNode(node.right, key, data); // �E�����؂ɒ���

		}

	}

	// --- �m�[�h��}�� ---//

	public void add(int key) {

		if (root == null)

			root = new Node(key, null, null);

		else

			addNode(root, key, key);

	}

	// --- �L�[�l��key�ł���m�[�h���폜 --//

	public boolean remove(int key) {

		Node p = root; // �������̃m�[�h

		Node parent = null; // �������̃m�[�h�̐e�m�[�h

		boolean isLeftChild = true; // p��parent�̍��q�m�[�h���H

		while (true) {

			if (p == null) // ����ȏ�i�߂Ȃ����

				return false; // �c���̃L�[�l�͑��݂��Ȃ�

			int cond = comp(key, p.getKey()); // key�ƃm�[�hp�̃L�[�l���r

			if (cond == 0) // ���������

				break; // �c�T������

			else {

				parent = p; // �}��������O�ɐe��ݒ�

				if (cond < 0) { // key�̂ق������������

					isLeftChild = true; // �c���ꂩ�炭����͍̂��̎q

					p = p.left; // �c�������؂���T��

				} else { // key�̂ق����傫�����

					isLeftChild = false; // �c���ꂩ�炭����͉̂E�̎q

					p = p.right; // �c�E�����؂���T��

				}

			}

		}

		if (p.left == null) { // p�ɂ͍��̎q���Ȃ��c

			if (p == root)

				root = p.right;

			else if (isLeftChild)

				parent.left = p.right; // �e�̍��|�C���^���E�̎q���w��

			else

				parent.right = p.right; // �e�̉E�|�C���^���E�̎q���w��

		} else if (p.right == null) { // p�ɂ͉E�̎q���Ȃ��c

			if (p == root)

				root = p.left;

			else if (isLeftChild)

				parent.left = p.left; // �e�̍��|�C���^�����̎q���w��

			else

				parent.right = p.left; // �e�̉E�|�C���^�����̎q���w��

		} else {

			parent = p;

			Node left = p.left; // �����؂̒��̍ő�m�[�h

			isLeftChild = true;

			while (left.right != null) { // �ő�m�[�hleft��T��

				parent = left;

				left = left.right;

				isLeftChild = false;

			}

			p.key = left.key; // left�̃L�[�l��p�Ɉړ�

			

			if (isLeftChild)

				parent.left = left.left; // left���폜

			else

				parent.right = left.left; // left���폜

		}

		return true;

	}

	// --- node�����Ƃ��镔���؂̃m�[�h���L�[�l�̏����ɕ\�� ---//

	private void printSubTree(Node node, int level) {

		if (node != null) {
			level++;
			printSubTree(node.left, level); // �������؂��L�[�l�̏����ɕ\��

			System.out.print(node.key + " (level=" + level + ")"); // node��\��
			if (node.left == null && node.right == null) {
				System.out.println(" leaf");
			} else {
				System.out.println();
			}

			printSubTree(node.right, level); // �E�����؂��L�[�l�̏����ɕ\��

		}

	}

	// --- node�����Ƃ��镔���؂̃m�[�h���L�[�l�̍~���ɕ\�� ---//

	private void printRevTree(Node node, int level) {

		if (node != null) {
			level++;
			printRevTree(node.right, level); // �E�����؂��L�[�l�̍~���ɕ\��

			System.out.print(node.key + " (level=" + level + ")"); // node��\��
			if (node.left == null && node.right == null) {
				System.out.println(" leaf");
			} else {
				System.out.println();
			}

			printRevTree(node.left, level); // �������؂��L�[�l�̍~���ɕ\��

		}

	}

	// --- �S�m�[�h���L�[�l�̏����ɕ\�� ---//

	public void print() {

		printSubTree(root, level);

	}

	// --- �S�m�[�h���L�[�l�̏����ɕ\�� ---//

	public void printReverse(){

		printRevTree(root, level);

	}

	// --- �ŏ��L�[�l��Ԃ� --- //
	public int getMinKey(){
		return serchMin(root);

	}

	public int serchMin(Node node){
		if (node.left == null){
			return node.getKey();
		}else{
			return serchMin(node.left);
		}
	}

	// --- �ő�L�[�l��Ԃ� --- //
	public int getMaxKey(){
		return serchMax(root);

	}

	public int serchMax(Node node){
		if (node.right == null){
			return node.getKey();
		}else{
			return serchMax(node.right);
		}
	}

}
