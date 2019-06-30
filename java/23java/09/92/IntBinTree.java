
// ２分探索木

import java.util.Comparator;

public class IntBinTree {

	private int level = 0; // レベル測定用
	// --- ノード ---//

	static class Node {

		private int key; // キー値

		private Node left; // 左子ノード

		private Node right; // 右子ノード

		// --- コンストラクタ ---//

		Node(int key, Node left, Node right) {

			this.key = key;

			this.left = left;

			this.right = right;

		}

		// --- キー値を返す ---//

		int getKey() {

			return key;

		}

		// --- データの表示 ---//

		void print() {

			System.out.println(key);

		}

	}

	private Node root; // 根

	private Comparator comparator = null; // コンパレータ

	// --- コンストラクタ ---//

	public IntBinTree() {

		root = null;

	}

	// --- コンストラクタ ---//

	public IntBinTree(Comparator c) {

		this();

		comparator = c;

	}

	// --- 二つのキー値を比較 ---//

	private int comp(int key1, int key2) {

		if (key1 == key2){
			return 0;
		}else if (key1>key2){
			return 1;
		}else {
			return -1;
		}
	}

	// --- キーによる探索 ---//

	public int search(int key) {

		Node p = root; // 根に着目

		while (true) {

			if (p == null) // これ以上進めなければ

				return -1; // …探索失敗

			int cond = comp(key, p.getKey()); // keyとノードpのキーを比較

			if (cond == 0) // 等しければ

				return p.getKey(); // …探索成功

			else if (cond < 0) // keyのほうが小さければ

				p = p.left; // …左部分木から探索

			else // keyのほうが大きければ

				p = p.right; // …右部分木から探索

		}

	}

	// --- nodeを根とする部分木にノード<K,V>を挿入 ---//

	private void addNode(Node node, int key, int data) {

		int cond = comp(key, node.getKey());

		if (cond == 0)

			return; // keyは２分探索木上に既に存在

		else if (cond < 0) {

			if (node.left == null)

				node.left = new Node(key, null, null);

			else

				addNode(node.left, key, data); // 左部分木に着目

		} else {

			if (node.right == null)

				node.right = new Node(key, null, null);

			else

				addNode(node.right, key, data); // 右部分木に着目

		}

	}

	// --- ノードを挿入 ---//

	public void add(int key) {

		if (root == null)

			root = new Node(key, null, null);

		else

			addNode(root, key, key);

	}

	// --- キー値がkeyであるノードを削除 --//

	public boolean remove(int key) {

		Node p = root; // 走査中のノード

		Node parent = null; // 走査中のノードの親ノード

		boolean isLeftChild = true; // pはparentの左子ノードか？

		while (true) {

			if (p == null) // これ以上進めなければ

				return false; // …そのキー値は存在しない

			int cond = comp(key, p.getKey()); // keyとノードpのキー値を比較

			if (cond == 0) // 等しければ

				break; // …探索成功

			else {

				parent = p; // 枝をくだる前に親を設定

				if (cond < 0) { // keyのほうが小さければ

					isLeftChild = true; // …これからくだるのは左の子

					p = p.left; // …左部分木から探索

				} else { // keyのほうが大きければ

					isLeftChild = false; // …これからくだるのは右の子

					p = p.right; // …右部分木から探索

				}

			}

		}

		if (p.left == null) { // pには左の子がない…

			if (p == root)

				root = p.right;

			else if (isLeftChild)

				parent.left = p.right; // 親の左ポインタが右の子を指す

			else

				parent.right = p.right; // 親の右ポインタが右の子を指す

		} else if (p.right == null) { // pには右の子がない…

			if (p == root)

				root = p.left;

			else if (isLeftChild)

				parent.left = p.left; // 親の左ポインタが左の子を指す

			else

				parent.right = p.left; // 親の右ポインタが左の子を指す

		} else {

			parent = p;

			Node left = p.left; // 部分木の中の最大ノード

			isLeftChild = true;

			while (left.right != null) { // 最大ノードleftを探索

				parent = left;

				left = left.right;

				isLeftChild = false;

			}

			p.key = left.key; // leftのキー値をpに移動

			

			if (isLeftChild)

				parent.left = left.left; // leftを削除

			else

				parent.right = left.left; // leftを削除

		}

		return true;

	}

	// --- nodeを根とする部分木のノードをキー値の昇順に表示 ---//

	private void printSubTree(Node node, int level) {

		if (node != null) {
			level++;
			printSubTree(node.left, level); // 左部分木をキー値の昇順に表示

			System.out.print(node.key + " (level=" + level + ")"); // nodeを表示
			if (node.left == null && node.right == null) {
				System.out.println(" leaf");
			} else {
				System.out.println();
			}

			printSubTree(node.right, level); // 右部分木をキー値の昇順に表示

		}

	}

	// --- nodeを根とする部分木のノードをキー値の降順に表示 ---//

	private void printRevTree(Node node, int level) {

		if (node != null) {
			level++;
			printRevTree(node.right, level); // 右部分木をキー値の降順に表示

			System.out.print(node.key + " (level=" + level + ")"); // nodeを表示
			if (node.left == null && node.right == null) {
				System.out.println(" leaf");
			} else {
				System.out.println();
			}

			printRevTree(node.left, level); // 左部分木をキー値の降順に表示

		}

	}

	// --- 全ノードをキー値の昇順に表示 ---//

	public void print() {

		printSubTree(root, level);

	}

	// --- 全ノードをキー値の昇順に表示 ---//

	public void printReverse(){

		printRevTree(root, level);

	}

	// --- 最小キー値を返す --- //
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

	// --- 最大キー値を返す --- //
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
