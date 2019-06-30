import java.util.*;

class QuickSort {

	static void swap(int[] a, int idx1, int idx2) {
		int t = a[idx1]; a[idx1] = a[idx2]; a[idx2] = t;
	}

	static void quickSort(int[] a, int left, int right) {
		showArray(a);
        int pl = left;
        int pr = right;
        int x = a[(pl + pr)/2];

        do{
            while(a[pl] < x){
                pl++;
            }
            while(a[pr] > x){
                pr--;
            }
            if(pl <= pr){
                swap(a, pl++, pr--);
            }
        }while(pl <= pr);

        if(left < pr){
            quickSort(a, left, pr);
        }
        if(pl < right){
            quickSort(a, pl, right);
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

		System.out.println("クイックソート");
		System.out.print("要素数：");
		int nx = stdIn.nextInt();
		int[] x = new int[nx];

		generateRandomValues(x, nx);
		for (int i = 0; i < x.length; i++){
			System.out.println("x[" + i + "]＝" + x[i]);
		}
		System.out.println();
		quickSort(x, 0, nx-1);
		System.out.println('\n' + "result.");
		for (int i = 0; i < x.length; i++){
			System.out.println("x[" + i + "]＝" + x[i]);
		}
	}
}
