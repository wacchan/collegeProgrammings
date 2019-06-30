// String型キュー

public class StringQueue {
	private int max;			// キューの容量
	private int front;		// 先頭要素カーソル
	private int rear;			// 末尾要素カーソル
	private int num;			// 現在のデータ数
	private String[] que;		// キューの本体

	//--- 実行時例外：キューが空 ---//
	public class EmptyStringQueueException extends RuntimeException {
		public EmptyStringQueueException() { }
	}

	//--- 実行時例外：キューが満杯 ---//
	public class OverflowStringQueueException extends RuntimeException {
		public OverflowStringQueueException() { }
	}

	//--- コンストラクタ ---//
	public StringQueue(int capacity) {
		num = front = rear = 0;
		max = capacity;
		try {
			que = new String[max];				// キュー本体用の配列を生成
		} catch (OutOfMemoryError e) {	// 生成できなかった
			max = 0;
		}
	}

	//--- キューにデータをエンキュー ---//
	public String enque(String x) throws OverflowStringQueueException {
		if (num >= max)
			throw new OverflowStringQueueException();			// キューは満杯
		que[rear++] = x;
		num++;
		if (rear == max)
			rear = 0;
		return x;
	}

	//--- キューからデータをデキュー ---//
	public String deque() throws EmptyStringQueueException {
		if (num <= 0)
			throw new EmptyStringQueueException();			// キューは空
		String x = que[front++];
		num--;
		if (front == max)
			front = 0;
		return x;
	}

	//--- キューからデータをピーク（先頭データを覗く） ---//
	public String peek() throws EmptyStringQueueException {
		if (num <= 0)
			throw new EmptyStringQueueException();			// キューは空
		return que[front];
	}

	//--- キューの容量を返す ---//
	public int capacity() {
		return max;
	}

	//--- キューに蓄えられているデータ数を返す ---//
	public int size() {
		return num;
	}

	//--- キュー内の全データを先頭→末尾の順に表示 ---//
	public void dump() {
		if (num <= 0)
			System.out.println("キューは空です。");
		else {
			for (int i = 0; i < max; i++){
				System.out.print("["+ i +"] "+ que[i] + " ");
				if (i == front){
					System.out.println("(front)");
				}	else if (i == rear){
					System.out.println("(rear)");
				}	else {
					System.out.println();
				}
			}
		}
		System.out.println();
	}
}
