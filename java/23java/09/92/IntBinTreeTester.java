import java.util.Comparator;

public class IntBinTreeTester{
    public static void main(String[] args){
	// リストを生成
	IntBinTree tree = new IntBinTree();

	int[] numArray = {3, 4, 1, 6, 5, 2};

	// 配列要素をツリーに追加
	for(int i=0; i<numArray.length; i++){
	    tree.add(numArray[i]);
	}

	System.out.println("print()");
	tree.print();
	System.out.println("printReverse()");
	tree.printReverse();

	tree.add(10);
	System.out.println("print()");
	tree.print();

	tree.remove(3);
	System.out.println("print()");
	tree.print();

	int a = 4;
	if(tree.search(a) == -1)
	    System.out.println(a + "はありません");
	else
	    System.out.println(a + "はあります");

	a = 11;
	if(tree.search(a) == -1)
	    System.out.println(a + "はありません");
	else
	    System.out.println(a + "はあります");

	System.out.println("最小キー: " + tree.getMinKey());
	System.out.println("最大キー: " + tree.getMaxKey());
    }
}
