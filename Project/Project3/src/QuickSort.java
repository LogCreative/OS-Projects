import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveAction;

public class QuickSort extends RecursiveAction{

    static final int THRESHOLD = 100;
    static final int SIZE = 1000;

    private int low;
    private int high;
    private Comparable[] array;

    public QuickSort(Comparable[] array, int low, int high){
        this.array = array;
        this.low = low;
        this.high = high;
    }

    protected void compute(){
        if(high - low < THRESHOLD){
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
            int mid = divide(array, low, high);

            QuickSort leftAction = new QuickSort(array, low, mid-1);
            QuickSort rightAction = new QuickSort(array, mid+1, high);

            leftAction.fork();
            rightAction.fork();

            rightAction.join();
            leftAction.join();
        }
    }

    public static int divide(Comparable[] a, int low, int high){
        Comparable k = a[low];
        do{
            while(low<high && less(k, a[high])) --high;
            if(low<high){a[low]=a[high]; ++low;}
            while(low<high && less(a[low], k)) ++low;
            if(low<high){a[high]=a[low]; --high;}
        } while (low!=high);
        a[low] = k;
        return low;
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

        QuickSort action = new QuickSort(array, 0, array.length - 1);

        pool.invoke(action);

        assert isSorted(array);
        show(array);
    }
}