public class IntLinkedListTester{
    public static void main(String[] args){
		// リストを生成
		IntLinkedList list = new IntLinkedList();

		// リストの表示
		list.dump();
		// 先頭にノードを挿入
		list.addFirst("a");
		list.addFirst("b");
		list.addFirst("c");
		list.addFirst("d");
		// 末尾にノードを挿入
		list.addLast("e");
		list.addLast("f");
		list.addLast("g");
		list.addLast("h");
		list.dump();

		// リストのノード数
		System.out.println("ノード数：" + list.size());

		// 先頭ノードの削除
		System.out.println("removeFirst");
		list.removeFirst();
		list.dump();

		// リストのノード数
		System.out.println("ノード数：" + list.size());

		// 末尾ノードの削除
		System.out.println("removeLast");
		list.removeLast();
		list.dump();

		// リストのノード数
		System.out.println("ノード数：" + list.size());

		// 着目ノードの表示
		System.out.print("着目ノード：");
		list.printCurrentNode();

		// 着目ノードの削除
		System.out.println("removeCurrentNode");
		list.removeCurrentNode();
		list.dump();

		// リストのノード数
		System.out.println("ノード数：" + list.size());

		// 先頭ノードの削除
		System.out.println("removeFirst");
		list.removeFirst();
		list.dump();

		// リストのノード数
		System.out.println("ノード数：" + list.size());

		// 着目ノードを一つ後方に進める
		System.out.println("next");
		list.next();
		list.dump();

		System.out.println("getFirstNode");
		String get = list.getFirstNode();
		list.dump();
		System.out.println("get :  "+get);

		// 10の探索
		String searchData = "c";
		if(list.search(searchData) != null)
	  		System.out.println("探索成功：" + searchData);
		else
	   		System.out.println("探索失敗：" + searchData);

		// 80の探索
		searchData = "f";
		if(list.search(searchData) != null)
	    	System.out.println("探索成功：" + searchData);
		else
	    	System.out.println("探索失敗：" + searchData);

		// リストのノード数
		System.out.println("ノード数：" + list.size());

		// 全ノードの削除
		System.out.println("clear");
		list.clear();
		list.dump();

		// リストのノード数
		System.out.println("ノード数：" + list.size());
    }
}
