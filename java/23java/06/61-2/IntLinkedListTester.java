public class IntLinkedListTester{
    public static void main(String[] args){
		// ���X�g�𐶐�
		IntLinkedList list = new IntLinkedList();

		// ���X�g�̕\��
		list.dump();
		// �擪�Ƀm�[�h��}��
		list.addFirst("a");
		list.addFirst("b");
		list.addFirst("c");
		list.addFirst("d");
		// �����Ƀm�[�h��}��
		list.addLast("e");
		list.addLast("f");
		list.addLast("g");
		list.addLast("h");
		list.dump();

		// ���X�g�̃m�[�h��
		System.out.println("�m�[�h���F" + list.size());

		// �擪�m�[�h�̍폜
		System.out.println("removeFirst");
		list.removeFirst();
		list.dump();

		// ���X�g�̃m�[�h��
		System.out.println("�m�[�h���F" + list.size());

		// �����m�[�h�̍폜
		System.out.println("removeLast");
		list.removeLast();
		list.dump();

		// ���X�g�̃m�[�h��
		System.out.println("�m�[�h���F" + list.size());

		// ���ڃm�[�h�̕\��
		System.out.print("���ڃm�[�h�F");
		list.printCurrentNode();

		// ���ڃm�[�h�̍폜
		System.out.println("removeCurrentNode");
		list.removeCurrentNode();
		list.dump();

		// ���X�g�̃m�[�h��
		System.out.println("�m�[�h���F" + list.size());

		// �擪�m�[�h�̍폜
		System.out.println("removeFirst");
		list.removeFirst();
		list.dump();

		// ���X�g�̃m�[�h��
		System.out.println("�m�[�h���F" + list.size());

		// ���ڃm�[�h�������ɐi�߂�
		System.out.println("next");
		list.next();
		list.dump();

		System.out.println("getFirstNode");
		String get = list.getFirstNode();
		list.dump();
		System.out.println("get :  "+get);

		// 10�̒T��
		String searchData = "c";
		if(list.search(searchData) != null)
	  		System.out.println("�T�������F" + searchData);
		else
	   		System.out.println("�T�����s�F" + searchData);

		// 80�̒T��
		searchData = "f";
		if(list.search(searchData) != null)
	    	System.out.println("�T�������F" + searchData);
		else
	    	System.out.println("�T�����s�F" + searchData);

		// ���X�g�̃m�[�h��
		System.out.println("�m�[�h���F" + list.size());

		// �S�m�[�h�̍폜
		System.out.println("clear");
		list.clear();
		list.dump();

		// ���X�g�̃m�[�h��
		System.out.println("�m�[�h���F" + list.size());
    }
}
