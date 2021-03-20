import java.util.*;

public class QuickSort {

    public static void sort(Comparable[] a){
        sort(a, 0, a.length - 1);
    }

    public static void sort(Comparable[] a, int low, int high){
        int mid;
        if (low>=high) return;
        mid = divide(a, low, high);
        sort(a, low, mid-1);
        sort(a, mid+1, high);
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
        Scanner scanner = new Scanner(System.in);
        String str = scanner.nextLine();
        scanner.close();
        String array[] = str.split(" ");
        sort(array);
        assert isSorted(array);
        show(array);
    }
}