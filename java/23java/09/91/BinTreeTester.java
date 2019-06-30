import java.util.Comparator;

// moodle���̂܂�
public class BinTreeTester {
	// �f�[�^
	static class Data {
		private Integer no;
		private String name;

		Integer keyCode() {
			return no;
		}

		public String toString() {
			return name;
		}

		public void setData(int no, String name) {
			this.no = no;
			this.name = name;
		}
	}

	public static void main(String[] args) {
		// ���X�g�𐶐�
		BinTree<Integer, Data> tree = new BinTree<Integer, Data>();

		Data data;

		// ��B�̌������i�[����z��
		String[] nameArray = { "A", "B", "C", "D", "E", "F" };
		int[] numArray = { 30, 40, 10, 60, 50, 20 };

		// �z��v�f���Q���T���؂ɒǉ�
		for (int i = 0; i < nameArray.length; i++) {
			data = new Data();
			data.setData(numArray[i], nameArray[i]);
			tree.add(data.keyCode(), data);
		}

		// �c���[�̕\��
		System.out.println("print");
		tree.print();

		// �m�[�h�̒ǉ�
		System.out.println("add");
		data = new Data();
		data.setData(80, "G");
		tree.add(data.keyCode(), data);

		data = new Data();
		data.setData(15, "H");
		tree.add(data.keyCode(), data);

		// �c���[�̕\��
		System.out.println("print");
		tree.print();

		// �m�[�h�̍폜
		System.out.println("remove");
		tree.remove(data.keyCode());

		// �c���[�̕\��
		System.out.println("print");
		tree.print();

		// �T��
		System.out.println("search");
		data.setData(1, "C");
		Data ptr = tree.search(data.keyCode());
		if (ptr != null)
			System.out.println(data + "�͌�����܂���");
		else
			System.out.println(data + "�͌�����܂���");
	}
}