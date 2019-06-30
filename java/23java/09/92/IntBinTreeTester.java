import java.util.Comparator;

public class IntBinTreeTester{
    public static void main(String[] args){
	// ���X�g�𐶐�
	IntBinTree tree = new IntBinTree();

	int[] numArray = {3, 4, 1, 6, 5, 2};

	// �z��v�f���c���[�ɒǉ�
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
	    System.out.println(a + "�͂���܂���");
	else
	    System.out.println(a + "�͂���܂�");

	a = 11;
	if(tree.search(a) == -1)
	    System.out.println(a + "�͂���܂���");
	else
	    System.out.println(a + "�͂���܂�");

	System.out.println("�ŏ��L�[: " + tree.getMinKey());
	System.out.println("�ő�L�[: " + tree.getMaxKey());
    }
}
