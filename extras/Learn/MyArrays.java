public class MyArrays {

    private int[] arr;
    private int size;

    private int length;

    public static void main(String[] args) {
        System.out.println("sss");
    }

    public MyArrays(int length) {
        this.length = length;
        arr = new int[length];
        size = 0;
    }

    public MyArrays() {
        this.length = 16;
        arr = new int[length];
        size = 0;
    }

    public int size() {
        return size;
    }

    public int capacity() {
        return length;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public int at(int index) {
        if (index < 0 || index >= size) {
            throw new IndexOutOfBoundsException("Index out of bounds");
        }
        return arr[index];
    }

    public void push(int item) {
        arr[size++] = item;
    }

    // 在指定索引中插入元素，并把后面的元素依次后移
    public void insert(int index, int item) {

        if (index < 0 || index > size) {
            throw new IndexOutOfBoundsException("Index out of bounds");
        }
        resize();
        // 从后往前移动元素
        for (int i = size; i > index; --i) {
            arr[i] = arr[i - 1];
        }
        arr[index] = item;
        size++;
    }

    public void resize() {

        if (length == size) {
            int[] newArr = new int[length * 2];
            for (int i = 0; i < length; i++) {
                newArr[i] = arr[i];
            }
            arr = newArr;
            length *= 2;
        }

        if (length >= 4 * size) {
            int[] newArr = new int[length / 2];
            for (int i = 0; i < size; i++) {
                newArr[i] = arr[i];
            }
            arr = newArr;
            length /= 2;

        }
    }

}
