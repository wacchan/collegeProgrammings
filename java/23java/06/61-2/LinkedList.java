import java.util.Comparator;

public class LinkedList<E> {

    //--- ノード ---//
    class Node<E>{
        private E data;         // データ
        private Node<E> next;   //後続ポインタ(後続ノードへの参照)

        //--- コンストラクタ ---//
        Node(E data, Node<E> next){
            this.data = data;
            this.next = next;
        }
    }

    private Node<E> head;      // 先頭ノード
    private Node<E> crnt;      // 着目ノード

    //--- コンストラクタ ---//
    public LinkedList() {
        head = crnt = null;
    }

    //--- ノードを探索 ---//
    public E search(E obj, Comparator<? super E> c) {
        Node<E> ptr = head;                     // 現在走査中のノード

        while (ptr != null) {
            if (c.compare(obj, ptr.data) == 0) {   // 探索成功
                crnt = ptr;
                return ptr.data;
            }
            ptr = ptr.next;                     // 後続ノードに着目
        }
        return null;                           // 探索失敗
    }

    //--- 先頭にノードを挿入 ---//
    public void addFirst(E obj){
        Node<E> ptr = head;                     // 挿入前の先頭ノード
        head = crnt = new Node<E>(obj, ptr);
    }

    //--- 末尾にノードを挿入 ---//
    public void addLast(E obj) {
        if (head == null)            // リストが空であれば
            addFirst(obj);            // 先頭に挿入
        else {
            Node<E> ptr = head;
            while (ptr.next != null){
                ptr = ptr.next;
            }
            ptr.next=crnt=new Node<E>(obj, null);
        }
    }

    //--- 先頭ノードを削除 ---//
    public void removeFirst() {
        if (head != null) {               // リストが空でなければ
            head = crnt = head.next;
        }
    }

    //--- 末尾ノードを削除 ---//
    public void removeLast() {
        if (head != null) {
            if (head.next == null)         // ノードが一つだけであれば
                removeFirst();               // 先頭ノードを削除
            else {
                Node<E> ptr = head;         // 走査中のノード
                Node<E> pre = head;         // 走査中のノードの先行ノード

                while (ptr.next != null) {
                    pre = ptr;
                    ptr = ptr.next;
                }
                pre.next = null;            // preは削除後の末尾ノード
                crnt = pre;
            }
        }
    }

    //--- ノードpを削除 ---//
    public void remove(Node p) {
        if (head != null) {
            if (p == head)            // pが先頭ノードであれば
                removeFirst();         // 先頭ノードを削除
            else {
                Node<E> ptr = head;

                while (ptr.next != p) {
                    ptr = ptr.next;
                    if (ptr == null) return;   // pはリスト上に存在しない
                }
                ptr.next = p.next;
                crnt = ptr;
            }
        }
    }  

    //--- 着目ノードを削除 ---//
    public void removeCurrentNode() {
        remove(crnt);
    }

    //--- 全ノードを削除 ---//
    public void clear() {
        while (head != null)         // 空になるまで
            removeFirst();            // 先頭ノードを削除
        crnt = null;
    }

    //--- 着目ノードを一つ後方に進める ---//
    public boolean next() {
        if (crnt == null || crnt.next == null)
            return false;                  // 進めることはできなかった
        crnt = crnt.next;
        return true;
    }

    //--- 着目ノードを表示 ---//
    public void printCurrentNode() {
        if (crnt == null)
            System.out.println("着目ノードはありません。");
        else
            System.out.println(crnt.data.toString());
    }

    //--- 全ノードを表示 ---//
    public void dump() {
        Node<E> ptr = head;

        while (ptr != null) {
            if (ptr==crnt){
                System.out.println(ptr.data.toString() + " <-- crnt");
            }else{
                System.out.println(ptr.data.toString());
            }
            ptr = ptr.next;
        }
    }

}