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
      System.out.println(guide + "するデータを入力してください");

      if((sw & NO) == NO){
        System.out.print("番号:");
        no = stdIn.nextInt();
      }
      if((sw & NAME) == NAME){
        System.out.print("名前:");
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
    data.scanData("先頭に挿入",Data.NO | Data.NAME);
    list.addFirst(data);
    list.dump();

    data = new Data();
    data.scanData("先頭に挿入",Data.NO | Data.NAME);
    list.addFirst(data);
    list.dump();

    data = new Data();
    data.scanData("先頭に挿入",Data.NO | Data.NAME);
    list.addFirst(data);
    list.dump();

    data = new Data();
    data.scanData("先頭に挿入",Data.NO | Data.NAME);
    list.addFirst(data);
    list.dump();


    data = new Data();
    data.scanData("末尾に挿入",Data.NO | Data.NAME);
    list.addLast(data);
    list.dump();

    data = new Data();
    data.scanData("着目ノードの直後に挿入",Data.NO | Data.NAME);
    list.add(data);
    list.dump();

    System.out.println("先頭ノードを消去");
    list.removeFirst();
    list.dump();

    System.out.println("末尾ノードを消去");
    list.removeLast();
    list.dump();

    System.out.println("着目ノードを消去");
    list.removeCurrentNode();
    list.dump();

    temp.scanData("番号で探索",Data.NO);
    ptr = list.search(temp, Data.NO_ORDER);
    if(ptr == null)
      System.out.println("その番号のデータはありません");
    else
      System.out.println("探索成功" + ptr);
    list.dump();


    temp.scanData("名前で探索",Data.NAME);
    ptr = list.search(temp, Data.NAME_ORDER);
    if(ptr == null)
      System.out.println("その名前のデータはありません");
    else
      System.out.println("探索成功" + ptr);
    list.dump();


    System.out.println("着目ノードを前方に進める");
    list.prev();
    list.dump();

    System.out.println("着目ノードを後方に進める");
    list.next();
    list.dump();


    System.out.println("着目ノードのデータを表示");
    list.printCurrentNode();

    System.out.println("全ノードを消去");
    list.clear();
    list.dump();

  }
}
