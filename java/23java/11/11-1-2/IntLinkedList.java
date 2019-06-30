import java.util.Comparator;

public class IntLinkedList {

    //--- �m�[�h ---//
    class Node{
        private String data;         // �f�[�^
        private Node next;   //�㑱�|�C���^(�㑱�m�[�h�ւ̎Q��)

        //--- �R���X�g���N�^ ---//
        Node(String data, Node next){
            this.data = data;
            this.next = next;
        }
    }

    private Node head;      // �擪�m�[�h
    private Node crnt;      // ���ڃm�[�h

    //--- �R���X�g���N�^ ---//
    public IntLinkedList() {
        head = crnt = null;
    }

    //--- �m�[�h��T�� ---//
    public String search(String sd) {
        Node ptr = head;                     // ���ݑ������̃m�[�h

        while (ptr != null) {
            
            if (ptr.data == sd) {   // �T������
                crnt = ptr;
                return ptr.data;
            }
            ptr = ptr.next;                     // �㑱�m�[�h�ɒ���
        }
        return null;                           // �T�����s
    }

    //--- �擪�Ƀm�[�h��}�� ---//
    public void addFirst(String obj){
        Node ptr = head;                     // �}���O�̐擪�m�[�h
        head = crnt = new Node(obj, ptr);
    }

    //--- �����Ƀm�[�h��}�� ---//
    public void addLast(String obj) {
        if (head == null)            // ���X�g����ł����
            addFirst(obj);            // �擪�ɑ}��
        else {
            Node ptr = head;
            while (ptr.next != null){
                ptr = ptr.next;
            }
            ptr.next=crnt=new Node(obj, null);
        }
    }

    //--- �擪�m�[�h���폜 ---//
    public void removeFirst() {
        if (head != null) {               // ���X�g����łȂ����
            head = crnt = head.next;
        }
    }

    public String getFirstNode(){
        Node get = head;
        removeFirst();
        return get.data;
    }

    //--- �����m�[�h���폜 ---//
    public void removeLast() {
        if (head != null) {
            if (head.next == null){         // �m�[�h��������ł����
                removeFirst();               // �擪�m�[�h���폜
            }
            else {
                Node ptr = head;         // �������̃m�[�h
                Node pre = head;         // �������̃m�[�h�̐�s�m�[�h

                while (ptr.next != null) {
                    pre = ptr;
                    ptr = ptr.next;
                }
                pre.next = null;            // pre�͍폜��̖����m�[�h
                crnt = pre;
            }
        }
    }

    public String getLastNode() {
        Node get;
        if (head != null) {
            if (head.next == null){         // �m�[�h��������ł����
                get = head;
                removeFirst();               // �擪�m�[�h���폜
                return get.data;
            }
            else {
                Node ptr = head;         // �������̃m�[�h
                Node pre = head;         // �������̃m�[�h�̐�s�m�[�h

                while (ptr.next != null) {
                    pre = ptr;
                    ptr = ptr.next;
                }
                get = pre.next;
                pre.next = null;            // pre�͍폜��̖����m�[�h
                crnt = pre;
                return get.data;
            }
        }
        return null;
    }

    //--- �m�[�hp���폜 ---//
    public void remove(Node p) {
        if (head != null) {
            if (p == head)            // p���擪�m�[�h�ł����
                removeFirst();         // �擪�m�[�h���폜
            else {
                Node ptr = head;

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
            System.out.println(crnt.data);
    }

    //--- �S�m�[�h��\�� ---//
    public void dump() {
        Node ptr = head;

        while (ptr != null) {
            if (ptr==crnt){
                System.out.println(ptr.data + " <-- crnt");
            }else{
                System.out.println(ptr.data);
            }
            ptr = ptr.next;
        }
        System.out.println();
    }

    public int size(){
        Node ptr = head;
        int i=0;
        while (ptr != null) {
            i++;
            ptr = ptr.next;
        }
        return i;
    }

}