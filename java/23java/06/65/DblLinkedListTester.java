import java.util.Comparator;

class DblLinkedListTester {
    static class Data {
        private Integer no;
        private String name;

        public String toString() {
            return "(" + no + ")" + name;
        }

        public void setData(int no, String name) {
            this.no = no;
            this.name = name;
        }

        public static final Comparator<Data> NO_ORDER = new NoOrderComparator();

        public static class NoOrderComparator implements Comparator<Data> {
            public int compare(Data d1, Data d2) {
                return (d1.no > d2.no) ? 1 : (d1.no < d2.no) ? -1 : 0;
            }
        }

        public static final Comparator<Data> NAME_ORDER = new NameOrderComparator();

        public static class NameOrderComparator implements Comparator<Data> {
            public int compare(Data d1, Data d2) {
                return d1.name.compareTo(d2.name);
            }
        }
    }

    public static void main(String[] args) {
        // リストを生成
        DblLinkedList<Data> list = new DblLinkedList<Data>();

        String[] nameArray = { "A", "B", "C", "D", "E", "F" };

        Data data;
        Data searchData = new Data();
        Data ptr;

        list.dump();

        for (int i = 0; i < nameArray.length; i++) {
            data = new Data();
            data.setData(i + 1, nameArray[i]);
            list.addLast(data);
        }

        System.out.println("ノード数：" + list.size());

        list.prev();
        list.prev();

        System.out.println("交換前(dump)");
        list.dump();
        System.out.println("交換前(dumpReverse)");
        list.dumpReverse();

        list.swapCurrentNode();

        System.out.println("交換後(dump)");
        list.dump();
        System.out.println("交換後(dumpReverse)");
        list.dumpReverse();

    }
}