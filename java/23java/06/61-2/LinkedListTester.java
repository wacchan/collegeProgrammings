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
	// ���X�g�𐶐�
	LinkedList<Data> list = new LinkedList<Data>();

	// ��B�̌������i�[����z��
	String[] nameArray = {"fukuoka", "saga", "nagasaki", "kumamoto", "oita", "miyazaki", "kagoshim"};

	Data data;
	Data searchData = new Data();
	Data ptr;

	// ���X�g�̕\��
	list.dump();

	// �z��v�f�����X�g�ɒǉ�
	for(int i=0; i<nameArray.length; i++){
	    data = new Data();
	    data.setData(i+1, nameArray[i]);
	    list.addFirst(data);
	}
	// ���X�g�̕\��
	list.dump();
	System.out.println();

	// �擪�m�[�h�̍폜
	System.out.println("removeFirst");
	list.removeFirst();
	list.dump();
	System.out.println();

	// �����m�[�h�̍폜
	System.out.println("removeLast");
	list.removeLast();
	list.dump();
	System.out.println();

	// ���ڃm�[�h�̕\��
	System.out.print("���ڃm�[�h�F");
	list.printCurrentNode();
	System.out.println();

	// ���ڃm�[�h�̍폜
	System.out.println("removeCurrentNode");
	list.removeCurrentNode();
	list.dump();
	System.out.println();

	// �擪�m�[�h�̍폜
	System.out.println("removeFirst");
	list.removeFirst();
	list.dump();
	System.out.println();

	// ���ڃm�[�h�������ɐi�߂�
	System.out.println("next");
	list.next();
	list.dump();
	System.out.println();

	// "oita"�̒T��
	searchData.setData(-1, "oita");
	if(list.search(searchData, Data.NAME_ORDER) != null)
	    System.out.println("�T�������F" + searchData);
	else
	    System.out.println("�T�����s�F" + searchData);

	// "fukuoka"�̒T��
	searchData.setData(-1, "fukuoka");
	if(list.search(searchData, Data.NAME_ORDER) != null)
	    System.out.println("�T�������F" + searchData);
	else
	    System.out.println("�T�����s�F" + searchData);

	// �S�m�[�h�̍폜
	System.out.println("clear");
	list.clear();
	list.dump();
    }
}
