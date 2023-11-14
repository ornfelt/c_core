// FROM: https://www.youtube.com/watch?v=P3YID7liBug
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class bs {

	public static boolean binarySearchIterative(int[] array, int x){
		int left = 0;
		int right = array.length -1;

		while (left <= right){
			int mid = left + ((right - left) / 2);

			if (array[mid] == x){
				return true;
			}else if (x < array[mid]){
				right = mid - 1;
			}else {
				left = mid + 1;
			}
		}
		return false;
	}

	// Recursive binary search
	public static boolean binarySearchRecursive(int[] array, int x, int left, int right){
		// Guard statement (something has gone wrong)
		if (left > right){
			return false;
		}

		int mid = (left + right) / 2;
		// Use below to avoid integer overflow
		int mid = left + ((rigth - left) / 2);
		if (array[mid] == x){
			return true;

		}else if (x < array[mid]){
			return binarySearchRecursive(array, x, left, mid - 1);
		}else {
			return binarySearchRecursive(array, x, mid + 1, right);
		}
	}

	public static boolean binarySearchRecursive(int[] array, int x){
		return binarySearchRecursive(array, x, 0, array.length - 1);
	}

	public static void main(String[] args){


	}
}
