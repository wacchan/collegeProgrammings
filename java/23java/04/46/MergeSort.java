import java.util.*;

class MergeSort {

    static int[] buff;

	static void __mergeSort(int[] a, int left, int right) {
        if(left < right){
            int i;
            int center = (left + right)/2;
            int p = 0;
            int j = 0;
            int k = left;
            __mergeSort(a, left, center);
            __mergeSort(a, center + 1, right);
            showArray(a);
            for(i = left; i <= center; i++){
                buff[p++] = a[i];
            }
            while(i <= right && j < p){
                a[k++] = (buff[j] <= a[i]) ? buff[j++] : a[i++];
            }
            while(j < p){
                a[k++] = buff[j++];
            }
        }
    }
    
    static void mergeSort(int[] a, int n){
        buff = new int[n];
        __mergeSort(a, 0, n-1);
        buff = null;
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

		System.out.println("マージソート");
		System.out.print("要素数：");
		int nx = stdIn.nextInt();
		int[] x = new int[nx];

		generateRandomValues(x, nx);
		for (int i = 0; i < x.length; i++){
			System.out.println("x[" + i + "]＝" + x[i]);
		}
		System.out.println();
        mergeSort(x, nx);
        showArray(x);
		System.out.println('\n' + "result.");
		for (int i = 0; i < x.length; i++){
			System.out.println("x[" + i + "]＝" + x[i]);
		}
	}
}
