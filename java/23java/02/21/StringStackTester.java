
// string型スタックの利用例

import java.io.*;

class StringStackTester {

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringStack s = new StringStack(20); // 最大20個プッシュできるスタック

		while (true) {
			System.out.println("現在のデータ数：" + s.size() + " / " + s.capacity());
			System.out.print("(1)プッシュ　(2)ポップ　(3)ピーク　" + "(4)ダンプ　(0)終了：");

			int menu = Integer.parseInt(br.readLine());
			if (menu == 0)
				break;

			String x;
			switch (menu) {
			case 1: // プッシュ
				System.out.print("データ：");
				x = br.readLine();
				try {
					s.push(x);
				} catch (StringStack.OverflowStringStackException e) {
					System.out.println("スタックが満杯です。");
				}
				break;

			case 2: // ポップ
				try {
					x = s.pop();
					System.out.println("ポップしたデータは" + x + "です。");
				} catch (StringStack.EmptyStringStackException e) {
					System.out.println("スタックが空です。");
				}
				break;

			case 3: // ピーク
				try {
					x = s.peek();
					System.out.println("ピークしたデータは" + x + "です。");
				} catch (StringStack.EmptyStringStackException e) {
					System.out.println("スタックが空です。");
				}
				break;

			case 4: // ダンプ
				s.dump();
				break;
			}
		}
	}
}
