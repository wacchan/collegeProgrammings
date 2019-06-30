import java.util.*;

class InsertionSort {

	static void swap(int[] a, int idx1, int idx2) {
		int t = a[idx1]; a[idx1] = a[idx2]; a[idx2] = t;
	}

	static void insertionSort(int[] a, int n) {
		showArray(a);
		// int pass = 1;
		for(int i = 1; i < n; i++){
            int j;
            int tmp = a[i];
            for(j = i; j > 0 && a[j-1] > tmp; j--){
                a[j] = a[j-1];
            }
			a[j] = tmp;
			System.out.println("パス" + i);
			// pass++;	
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

		System.out.println("単純挿入ソート");
		System.out.print("要素数：");
		int nx = stdIn.nextInt();
		int[] x = new int[nx];

		generateRandomValues(x, nx);
		for (int i = 0; i < x.length; i++){
			System.out.println("x[" + i + "]＝" + x[i]);
		}
		System.out.println();
		insertionSort(x, nx);
		System.out.println('\n' + "result.");
		for (int i = 0; i < x.length; i++){
			System.out.println("x[" + i + "]＝" + x[i]);
		}
	}
}