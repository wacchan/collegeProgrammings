import java.util.Comparator;

public class LinkedList<E> {

    //--- �m�[�h ---//
    class Node<E>{
        private E data;         // �f�[�^
        private Node<E> next;   //�㑱�|�C���^(�㑱�m�[�h�ւ̎Q��)

        //--- �R���X�g���N�^ ---//
        Node(E data, Node<E> next){
            this.data = data;
            this.next = next;
        }
    }

    private Node<E> head;      // �擪�m�[�h
    private Node<E> crnt;      // ���ڃm�[�h

    //--- �R���X�g���N�^ ---//
    public LinkedList() {
        head = crnt = null;
    }

    //--- �m�[�h��T�� ---//
    public E search(E obj, Comparator<? super E> c) {
        Node<E> ptr = head;                     // ���ݑ������̃m�[�h

        while (ptr != null) {
            if (c.compare(obj, ptr.data) == 0) {   // �T������
                crnt = ptr;
                return ptr.data;
            }
            ptr = ptr.next;                     // �㑱�m�[�h�ɒ���
        }
        return null;                           // �T�����s
    }

    //--- �擪�Ƀm�[�h��}�� ---//
    public void addFirst(E obj){
        Node<E> ptr = head;                     // �}���O�̐擪�m�[�h
        head = crnt = new Node<E>(obj, ptr);
    }

    //--- �����Ƀm�[�h��}�� ---//
    public void addLast(E obj) {
        if (head == null)            // ���X�g����ł����
            addFirst(obj);            // �擪�ɑ}��
        else {
            Node<E> ptr = head;
            while (ptr.next != null){
                ptr = ptr.next;
            }
            ptr.next=crnt=new Node<E>(obj, null);
        }
    }

    //--- �擪�m�[�h���폜 ---//
    public void removeFirst() {
        if (head != null) {               // ���X�g����łȂ����
            head = crnt = head.next;
        }
    }

    //--- �����m�[�h���폜 ---//
    public void removeLast() {
        if (head != null) {
            if (head.next == null)         // �m�[�h��������ł����
                removeFirst();               // �擪�m�[�h���폜
            else {
                Node<E> ptr = head;         // �������̃m�[�h
                Node<E> pre = head;         // �������̃m�[�h�̐�s�m�[�h

                while (ptr.next != null) {
                    pre = ptr;
                    ptr = ptr.next;
                }
                pre.next = null;            // pre�͍폜��̖����m�[�h
                crnt = pre;
            }
        }
    }

    //--- �m�[�hp���폜 ---//
    public void remove(Node p) {
        if (head != null) {
            if (p == head)            // p���擪�m�[�h�ł����
                removeFirst();         // �擪�m�[�h���폜
            else {
                Node<E> ptr = head;

                while (ptr.next != p) {
                    ptr = ptr.next;
                    if (ptr == null) return;   // p�̓��X�g��ɑ��݂��Ȃ�
                }
                ptr.next = p.next;
                crnt = ptr;
            }
        }
    }  

    //--- ���ڃm�[�h���폜 ---//
    public void removeCurrentNode() {
        remove(crnt);
    }

    //--- �S�m�[�h���폜 ---//
    public void clear() {
        while (head != null)         // ��ɂȂ�܂�
            removeFirst();            // �擪�m�[�h���폜
        crnt = null;
    }

    //--- ���ڃm�[�h�������ɐi�߂� ---//
    public boolean next() {
        if (crnt == null || crnt.next == null)
            return false;                  // �i�߂邱�Ƃ͂ł��Ȃ�����
        crnt = crnt.next;
        return true;
    }

    //--- ���ڃm�[�h��\�� ---//
    public void printCurrentNode() {
        if (crnt == null)
            System.out.println("���ڃm�[�h�͂���܂���B");
        else
            System.out.println(crnt.data.toString());
    }

    //--- �S�m�[�h��\�� ---//
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