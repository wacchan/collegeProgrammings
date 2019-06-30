import java.util.*;

class SelectionSort {

	static void swap(int[] a, int idx1, int idx2) {
		int t = a[idx1]; a[idx1] = a[idx2]; a[idx2] = t;
	}

	static void selectionSort(int[] a, int n) {
		showArray(a);
		// int pass = 1;
		for(int i = 0; i < n-1; i++){
            int min = i;
            for(int j = i+1; j < n; j++){
                if(a[j] < a[min])
                    min = j;
            }
			swap(a, i, min);
			System.out.println("パス" + (i+1));
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

		System.out.println("単純選択ソート");
		System.out.print("要素数：");
		int nx = stdIn.nextInt();
		int[] x = new int[nx];

		generateRandomValues(x, nx);
		for (int i = 0; i < x.length; i++){
			System.out.println("x[" + i + "]＝" + x[i]);
		}
		System.out.println();
		selectionSort(x, nx);
		System.out.println('\n' + "result.");
		for (int i = 0; i < x.length; i++){
			System.out.println("x[" + i + "]＝" + x[i]);
		}
	}
}