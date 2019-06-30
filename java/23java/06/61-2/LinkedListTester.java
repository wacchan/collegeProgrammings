import java.util.Comparator;

public class LinkedListTester{
    static class Data{
	private Integer no;
	private String name;

	public String toString(){
	    return "(" + no + ")" + name;
	}

	public void setData(int no, String name){
	    this.no = no;
	    this.name = name;
	}

	public static final Comparator<Data> NO_ORDER = new NoOrderComparator();

	public static class NoOrderComparator implements Comparator<Data>{
	    public int compare(Data d1, Data d2){
		return (d1.no > d2.no) ? 1 : (d1.no < d2.no) ? -1 : 0;
	    }
	}

	public static final Comparator<Data> NAME_ORDER = new NameOrderComparator();

	public static class NameOrderComparator implements Comparator<Data>{
	    public int compare(Data d1, Data d2){
		return d1.name.compareTo(d2.name);
	    }
	}
    }

    public static void main(String[] args){
	// リストを生成
	LinkedList<Data> list = new LinkedList<Data>();

	// 九州の県名を格納する配列
	String[] nameArray = {"fukuoka", "saga", "nagasaki", "kumamoto", "oita", "miyazaki", "kagoshim"};

	Data data;
	Data searchData = new Data();
	Data ptr;

	// リストの表示
	list.dump();

	// 配列要素をリストに追加
	for(int i=0; i<nameArray.length; i++){
	    data = new Data();
	    data.setData(i+1, nameArray[i]);
	    list.addFirst(data);
	}
	// リストの表示
	list.dump();
	System.out.println();

	// 先頭ノードの削除
	System.out.println("removeFirst");
	list.removeFirst();
	list.dump();
	System.out.println();

	// 末尾ノードの削除
	System.out.println("removeLast");
	list.removeLast();
	list.dump();
	System.out.println();

	// 着目ノードの表示
	System.out.print("着目ノード：");
	list.printCurrentNode();
	System.out.println();

	// 着目ノードの削除
	System.out.println("removeCurrentNode");
	list.removeCurrentNode();
	list.dump();
	System.out.println();

	// 先頭ノードの削除
	System.out.println("removeFirst");
	list.removeFirst();
	list.dump();
	System.out.println();

	// 着目ノードを一つ後方に進める
	System.out.println("next");
	list.next();
	list.dump();
	System.out.println();

	// "oita"の探索
	searchData.setData(-1, "oita");
	if(list.search(searchData, Data.NAME_ORDER) != null)
	    System.out.println("探索成功：" + searchData);
	else
	    System.out.println("探索失敗：" + searchData);

	// "fukuoka"の探索
	searchData.setData(-1, "fukuoka");
	if(list.search(searchData, Data.NAME_ORDER) != null)
	    System.out.println("探索成功：" + searchData);
	else
	    System.out.println("探索失敗：" + searchData);

	// 全ノードの削除
	System.out.println("clear");
	list.clear();
	list.dump();
    }
}
