import java.util.Comparator;

// moodleそのまま
public class BinTreeTester {
	// データ
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
		// リストを生成
		BinTree<Integer, Data> tree = new BinTree<Integer, Data>();

		Data data;

		// 九州の県名を格納する配列
		String[] nameArray = { "A", "B", "C", "D", "E", "F" };
		int[] numArray = { 30, 40, 10, 60, 50, 20 };

		// 配列要素を２分探索木に追加
		for (int i = 0; i < nameArray.length; i++) {
			data = new Data();
			data.setData(numArray[i], nameArray[i]);
			tree.add(data.keyCode(), data);
		}

		// ツリーの表示
		System.out.println("print");
		tree.print();

		// ノードの追加
		System.out.println("add");
		data = new Data();
		data.setData(80, "G");
		tree.add(data.keyCode(), data);

		data = new Data();
		data.setData(15, "H");
		tree.add(data.keyCode(), data);

		// ツリーの表示
		System.out.println("print");
		tree.print();

		// ノードの削除
		System.out.println("remove");
		tree.remove(data.keyCode());

		// ツリーの表示
		System.out.println("print");
		tree.print();

		// 探索
		System.out.println("search");
		data.setData(1, "C");
		Data ptr = tree.search(data.keyCode());
		if (ptr != null)
			System.out.println(data + "は見つかりません");
		else
			System.out.println(data + "は見つかりました");
	}
}