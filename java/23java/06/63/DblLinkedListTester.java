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
        DblLinkedList<Data> list = new DblLinkedList<Data>();
        String[] nameArray = { "A", "B", "C", "D", "E", "F" };
        Data data = new Data();
        Data searchData = new Data();
        for (int i = 0; i < nameArray.length; i++) {
            data = new Data();
            data.setData(i + 1, nameArray[i]);
            list.addLast(data);
        }

        System.out.println("交換前(dump)");
        list.dump();
        System.out.println();

        System.out.println("isEmpty");
        System.out.println(list.isEmpty());

        searchData.setData(-1, "B");
        if (list.search(searchData, Data.NAME_ORDER) != null)
            System.out.println("探索成功：" + searchData);
        else
            System.out.println("探索失敗：" + searchData);

        System.out.print("着目ノード：");
        list.printCurrentNode();
        System.out.println();

        System.out.println("全ノード");
        list.dump();
        System.out.println();

        System.out.println("全ノードを逆順に表示");
        list.dumpReverse();
        System.out.println();

        System.out.println("着目ノードを一つ後方に進める");
        list.next();
        list.dump();
        System.out.println();

        System.out.println("着目ノードを一つ前方に進める");
        list.prev();
        list.dump();
        System.out.println();

        System.out.println("着目ノードの直後にノードを挿入");
        list.add(data);
        list.dump();
        System.out.println();

        System.out.println("先頭にノードを挿入");
        list.addFirst(data);
        list.dump();
        System.out.println();

        System.out.println("末尾にノードを挿入");
        list.addLast(data);
        list.dump();
        System.out.println();

        System.out.println("着目ノードを削除");
        list.removeCurrentNode();
        list.dump();
        System.out.println();

        /**
         * System.out.println("ノードpを削除"); list.remove(わからん); list.dump();
         * System.out.println();
         */

        System.out.println("先頭ノードを削除");
        list.removeFirst();
        list.dump();
        System.out.println();

        System.out.println("末尾ノードを削除");
        list.removeLast();
        list.dump();
        System.out.println();

        System.out.println("全ノードを削除");
        list.clear();
        list.dump();
        System.out.println();

    }
}