// String型キューのテストプログラム

class StringQueueTester {

	public static void main(String[] args) {
		StringQueue q = new StringQueue(20);

		System.out.println("現在のデータ数："	+ q.size() + "/" + q.capacity());

		q.enque("fukuoka");
		q.enque("saga");
		q.enque("nagasaki");
		q.enque("kumamoto");
		q.enque("oita");
		q.enque("miyazaki");
		q.enque("kagoshima");

		System.out.println("現在のデータ数："	+ q.size() + "/" + q.capacity());
		q.dump();

		q.deque();

		System.out.println("現在のデータ数："	+ q.size() + "/" + q.capacity());
		q.dump();

		q.peek();
		System.out.println("現在のデータ数："	+ q.size() + "/" + q.capacity());
		q.dump();
	}
}
