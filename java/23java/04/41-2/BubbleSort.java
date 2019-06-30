import java.util.*;

class BubbleSort {

	static void swap(int[] a, int idx1, int idx2) {
		int t = a[idx1]; a[idx1] = a[idx2]; a[idx2] = t;
	}

	static void bubbleSort(int[] a, int n) {
		showArray(a);
		int k = 0;
		int pass = 1;
		while (k < n - 1) {
			int last = n - 1;
			for (int j = n - 1; j > k; j--){
				if (a[j - 1] > a[j]) {
					swap(a, j - 1, j);
					last = j;
				}
			}
			k = last;
			System.out.println("パス" + pass);
			pass++;
			showArray(a);
		}
	}

	static void generateRandomValues(int[] array, int maxValue){
		for(int i = 0; i < maxValue; i++){
			array[i] = (int)(Math.random()*100);
		}
	}

	static void showArray(int[] array){
		for (int i = 0; i < array.length; i++){
			System.out.print(array[i] + " ");
		}
		System.out.println();
	}
	public static void main(String[] args) {
		Scanner stdIn = new Scanner(System.in);

		System.out.println("単純交換ソート（バブルソート）");
		System.out.print("要素数：");
		int nx = stdIn.nextInt();
		int[] x = new int[nx];

		generateRandomValues(x, nx);
		for (int i = 0; i < x.length; i++){
			System.out.println("x[" + i + "]＝" + x[i]);
		}
		System.out.println();
		bubbleSort(x, nx);
		System.out.println('\n' + "result.");
		for (int i = 0; i < x.length; i++){
			System.out.println("x[" + i + "]＝" + x[i]);
		}
	}
}