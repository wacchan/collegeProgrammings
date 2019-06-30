
//	循環・重連結リストクラス

import java.util.Comparator;

public class DblLinkedList<E> {

	// --- ノード ---//
	class Node<E> {
		private E data; // データ
		private Node<E> prev; // 先行ポインタ（先行ノードへの参照）
		private Node<E> next; // 後続ポインタ（後続ノードへの参照）

		// --- コンストラクタ ---//
		Node() {
			data = null;
			prev = next = this;
		}

		// --- コンストラクタ ---//
		Node(E obj, Node<E> prev, Node<E> next) {
			data = obj;
			this.prev = prev;
			this.next = next;
		}
	}

	private Node<E> head; // 先頭ノード（ダミーノード）
	private Node<E> crnt; // 着目ノード

	// --- コンストラクタ ---//
	public DblLinkedList() {
		head = crnt = new Node<E>(); // ダミーノードを生成
	}

	// --- リストは空か ---//
	public boolean isEmpty() {
		return head.next == head;
	}

	// --- ノードを探索 ---//
	public E search(E obj, Comparator<? super E> c) {
		Node<E> ptr = head.next; // 現在走査中のノード

		while (ptr != head) {
			if (c.compare(obj, ptr.data) == 0) {
				crnt = ptr;
				return ptr.data; // 探索成功
			}
			ptr = ptr.next; // 後続ノードに着目
		}
		return null; // 探索失敗
	}

	// --- 着目ノードを表示 ---//
	public void printCurrentNode() {
		if (isEmpty())
			System.out.println("着目ノードはありません。");
		else
			System.out.println(crnt.data);
	}

	// --- 全ノードを表示 ---//
	public void dump() {
		Node<E> ptr = head.next; // ダミーノードの後続ノード

		while (ptr != head) {
			if (ptr == crnt) {
				System.out.println(ptr.data + " <-- crnt");
			} else {
				System.out.println(ptr.data);
			}
			ptr = ptr.next;
		}
	}

	// --- 全ノードを逆順に表示 ---//
	public void dumpReverse() {
		Node<E> ptr = head.prev; // ダミーノードの先行ノード

		while (ptr != head) {
			if (ptr == crnt) {
				System.out.println(ptr.data + " <-- crnt");
			} else {
				System.out.println(ptr.data);
			}
			ptr = ptr.prev;
		}
	}

	// --- 着目ノードを一つ後方に進める ---//
	public boolean next() {
		if (isEmpty() || crnt.next == head)
			return false; // 進めることはできなかった
		crnt = crnt.next;
		return true;
	}

	// --- 着目ノードを一つ前方に進める ---//
	public boolean prev() {
		if (isEmpty() || crnt.prev == head)
			return false; // 進めることはできなかった
		crnt = crnt.prev;
		return true;
	}

	// --- 着目ノードの直後にノードを挿入 ---//
	public void add(E obj) {
		Node<E> node = new Node<E>(obj, crnt, crnt.next);
		crnt.next = crnt.next.prev = node;
		crnt = node;
	}

	// --- 先頭にノードを挿入 ---//
	public void addFirst(E obj) {
		crnt = head; // ダミーノードheadの直後に挿入
		add(obj);
	}

	// --- 末尾にノードを挿入 ---//
	public void addLast(E obj) {
		crnt = head.prev; // 末尾ノードhead.prevの直後に挿入
		add(obj);
	}

	// --- 着目ノードを削除 ---//
	public void removeCurrentNode() {
		if (!isEmpty()) {
			crnt.prev.next = crnt.next;
			crnt.next.prev = crnt.prev;
			crnt = crnt.prev;
			if (crnt == head)
				crnt = head.next;
		}
	}

	// --- ノードpを削除 ---//
	public void remove(Node p) {
		Node<E> ptr = head.next;

		while (ptr != head) {
			if (ptr == p) { // pを見つけた
				crnt = p;
				removeCurrentNode();
				break;
			}
			ptr = ptr.next;
		}
	}

	// --- 先頭ノードを削除 ---//
	public void removeFirst() {
		crnt = head.next; // 先頭ノードhead.nextを削除
		removeCurrentNode();
	}

	// --- 末尾ノードを削除 ---//
	public void removeLast() {
		crnt = head.prev; // 末尾ノードhead.prevを削除
		removeCurrentNode();
	}

	// --- 全ノードを削除 ---//
	public void clear() {
		while (!isEmpty()) // 空になるまで
			removeFirst(); // 先頭ノードを削除
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