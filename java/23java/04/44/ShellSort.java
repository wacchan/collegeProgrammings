import java.util.*;

class ShellSort {

	static void swap(int[] a, int idx1, int idx2) {
		int t = a[idx1]; a[idx1] = a[idx2]; a[idx2] = t;
	}

	static void shellSort(int[] a, int n) {
		showArray(a);
		for(int h = n/2; h > 0; h/=2){
            for(int i = h; i < n; i++){
                int j;
                int tmp = a[i];
                for(j = i-h; j >= 0 && a[j] > tmp; j -= h){
                    a[j+h] = a[j];
                }
                a[j+h] = tmp;
			}
			System.out.println(h + "ソート");
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

		System.out.println("シェルソート");
		System.out.print("要素数：");
		int nx = stdIn.nextInt();
		int[] x = new int[nx];

		generateRandomValues(x, nx);
		for (int i = 0; i < x.length; i++){
			System.out.println("x[" + i + "]＝" + x[i]);
		}
		System.out.println();
		shellSort(x, nx);
		System.out.println('\n' + "result.");
		for (int i = 0; i < x.length; i++){
			System.out.println("x[" + i + "]＝" + x[i]);
		}
	}
}
