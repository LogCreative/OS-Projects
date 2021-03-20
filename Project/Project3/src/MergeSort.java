import java.util.*;

public class MergeSort {
    public static void sort(Comparable[] a){
        sort(a, 0, a.length - 1);
    }

    public static void sort(Comparable[] a, int left, int right){
        int mid = (left + right) / 2;
        if(left == right) return ;
        sort(a, left, mid);
        sort(a, mid+1, right);
        merge(a, left, mid+1, right);
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
        Scanner scanner = new Scanner(System.in);
        String str = scanner.nextLine();
        scanner.close();
        String array[] = str.split(" ");
        sort(array);
        assert isSorted(array);
        show(array);
    }
}
