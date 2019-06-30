import java.util.Comparator;
import java.util.Scanner;

public class DblLinkedListTester2{
  static Scanner stdIn = new Scanner(System.in);

  static class Data{

    static final int NO = 1;
    static final int NAME = 2;

    private Integer no;
    private String name;

	  public String toString(){
	    return "(" + no + ")" + name;
	  }

    void scanData(String guide, int sw){
      System.out.println(guide + "����f�[�^����͂��Ă�������");

      if((sw & NO) == NO){
        System.out.print("�ԍ�:");
        no = stdIn.nextInt();
      }
      if((sw & NAME) == NAME){
        System.out.print("���O:");
        name = stdIn.next();
      }
    }

    public static final Comparator<Data> NO_ORDER = new NoOrderComparator();
    private static class NoOrderComparator implements Comparator<Data>{
      public int compare(Data d1, Data d2){
        return (d1.no > d2.no) ? 1 : (d1.no < d2.no) ? -1 : 0;
      }
    }

    public static final Comparator<Data> NAME_ORDER = new NameOrderComparator();

    private static class NameOrderComparator implements Comparator<Data>{
      public int compare(Data d1, Data d2){
        return d1.name.compareTo(d2.name);
      }
    }
  }






  public static void main(String[] args){
    Data data;
    Data ptr;
    Data temp = new Data();

	  DblLinkedList<Data> list = new DblLinkedList<Data>();

    data = new Data();
    data.scanData("�擪�ɑ}��",Data.NO | Data.NAME);
    list.addFirst(data);
    list.dump();

    data = new Data();
    data.scanData("�擪�ɑ}��",Data.NO | Data.NAME);
    list.addFirst(data);
    list.dump();

    data = new Data();
    data.scanData("�擪�ɑ}��",Data.NO | Data.NAME);
    list.addFirst(data);
    list.dump();

    data = new Data();
    data.scanData("�擪�ɑ}��",Data.NO | Data.NAME);
    list.addFirst(data);
    list.dump();


    data = new Data();
    data.scanData("�����ɑ}��",Data.NO | Data.NAME);
    list.addLast(data);
    list.dump();

    data = new Data();
    data.scanData("���ڃm�[�h�̒���ɑ}��",Data.NO | Data.NAME);
    list.add(data);
    list.dump();

    System.out.println("�擪�m�[�h������");
    list.removeFirst();
    list.dump();

    System.out.println("�����m�[�h������");
    list.removeLast();
    list.dump();

    System.out.println("���ڃm�[�h������");
    list.removeCurrentNode();
    list.dump();

    temp.scanData("�ԍ��ŒT��",Data.NO);
    ptr = list.search(temp, Data.NO_ORDER);
    if(ptr == null)
      System.out.println("���̔ԍ��̃f�[�^�͂���܂���");
    else
      System.out.println("�T������" + ptr);
    list.dump();


    temp.scanData("���O�ŒT��",Data.NAME);
    ptr = list.search(temp, Data.NAME_ORDER);
    if(ptr == null)
      System.out.println("���̖��O�̃f�[�^�͂���܂���");
    else
      System.out.println("�T������" + ptr);
    list.dump();


    System.out.println("���ڃm�[�h��O���ɐi�߂�");
    list.prev();
    list.dump();

    System.out.println("���ڃm�[�h������ɐi�߂�");
    list.next();
    list.dump();


    System.out.println("���ڃm�[�h�̃f�[�^��\��");
    list.printCurrentNode();

    System.out.println("�S�m�[�h������");
    list.clear();
    list.dump();

  }
}
