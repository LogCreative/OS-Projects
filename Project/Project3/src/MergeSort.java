import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveAction;

public class MergeSort extends RecursiveAction{

    static final int THRESHOLD = 100;
    static final int SIZE = 1000;

    private int left;
    private int right;
    private Comparable[] array;

    public MergeSort(Comparable[] array, int left, int right){
        this.array = array;
        this.left = left;
        this.right = right;
    }

    protected void compute(){
        if(right - left < THRESHOLD){
            // Apply Selection Sort
            int i,j,min;
            for(i = 0; i < array.length; i++){
                min = i;
                for(j = i+1; j < array.length; j++)
                    if(less(array[j],array[min]))
                        min = j;
                exch(array, i, min);
            }
        } else {
            int mid = (left + right) / 2;

            MergeSort leftAction = new MergeSort(array, left, mid);
            MergeSort rightAction = new MergeSort(array, mid+1, right);

            leftAction.fork();
            rightAction.fork();

            rightAction.join();
            leftAction.join();

            merge(array, left, mid+1, right);
        }
    }

    public static void merge(Comparable[] a, int left, int mid, int right){
        Comparable aux[] = new Comparable[right-left+1];
        int i = left;
        int j = mid;
        int k = 0;
        while(i<mid && j<=right){
            if(less(a[i],a[j])) aux[k++] = a[i++];
            else aux[k++] = a[j++];
        }
        while(i<mid) aux[k++] = a[i++];
        while(j<=right) aux[k++] = a[j++];
        for(i = 0, k = left; k<=right;) a[k++] = aux[i++];
    }

    public static boolean less(Comparable v, Comparable w){
        return v.compareTo(w) < 0;
    }

    public static void exch(Comparable[] a, int i, int j){
        Comparable t = a[i];
        a[i] = a[j];
        a[j] = t;
    }

    private static void show(Comparable[] a){
        for (int i = 0; i < a.length; i++)
            System.out.print(a[i] + " ");
        System.out.println();
    }

    public static boolean isSorted(Comparable[] a){
        for(int i = 1; i < a.length; i++)
            if(less(a[i],a[i-1])) return false;
        return true;
    }

    public static void main(String[] args) {
        // Scanner scanner = new Scanner(System.in);
        // String str = scanner.nextLine();
        // scanner.close();
        // String array[] = str.split(" ");

        Comparable[] array = new Comparable[SIZE];

		// create SIZE random integers between 0 and 9
		java.util.Random rand = new java.util.Random();

		for (int i = 0; i < SIZE; i++) {
			array[i] = rand.nextInt(10);
		}		

        ForkJoinPool pool = new ForkJoinPool();

        MergeSort action = new MergeSort(array, 0, array.length - 1);

        pool.invoke(action);

        assert isSorted(array);
        show(array);
    }
}