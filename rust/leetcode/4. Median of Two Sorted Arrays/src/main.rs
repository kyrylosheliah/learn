/*
4. Median of Two Sorted Arrays

Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.
The overall run time complexity should be O(log (m+n)).

Example 1:
Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2.

Example 2:
Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.

Constraints:
    nums1.length == m
    nums2.length == n
    0 <= m <= 1000
    0 <= n <= 1000
    1 <= m + n <= 2000
    -10^6 <= nums1[i], nums2[i] <= 10^6
*/

trait Solution {
    fn find_median_sorted_arrays(&self, nums1: &Vec<i32>, nums2: &Vec<i32>) -> f64;
}

struct TwoPointerNoMerge;

impl Solution for TwoPointerNoMerge {
    fn find_median_sorted_arrays(&self, nums1: &Vec<i32>, nums2: &Vec<i32>) -> f64 {
        let merged_length = nums1.len() + nums2.len();
        let midpoint: usize = merged_length / 2;
        // Track most recently processed elements
        let mut x_pos: usize = 0;
        let mut y_pos: usize = 0;
        let mut z_pos: usize = 0; // virtual merged array
        let mut head: i32 = 0; // of the virtual array
        let mut tail: i32 = 0; // Element directly behind head in the virtual array
        while z_pos <= midpoint {
            // until the midpoint of the virtual array
            tail = head; // move tail
            if x_pos == nums1.len() {
                // if read everything in nums1
                head = nums2[y_pos];
                y_pos += 1;
            } else if y_pos == nums2.len() {
                // if read everything in nums2
                head = nums1[x_pos];
                x_pos += 1;
            } else if nums1[x_pos] > nums2[y_pos] {
                // didn't read nums2 and picking lesser value
                head = nums2[y_pos];
                y_pos += 1;
            } else {
                // if nums1[x_pos] < nums2[y_pos] {
                // didn't read nums1 and picking lesser value
                head = nums1[x_pos];
                x_pos += 1;
            } /* else {
                  // then elements are equal
                  head = nums1[x_pos];
                  x_pos += 1;
              }*/
            z_pos += 1; // increment the pointer in virtual merged array
        }
        if merged_length % 2 == 1 {
            // odd-length array median is the midpoint element
            return head as f64;
        } else {
            // evel-length array median is the average of two midpoint elements
            return ((head + tail) as f64) / 2.0;
        }
    }
}

struct BinarySearchNoMerge;

impl Solution for BinarySearchNoMerge {
    fn find_median_sorted_arrays(&self, nums1: &Vec<i32>, nums2: &Vec<i32>) -> f64 {
        // swap to always perform binary search on the smaller vector
        let (nums1, nums2) = if nums2.len() > nums1.len() {
            (nums1, nums2)
        } else {
            (nums2, nums1)
        };
        let (m, n) = (nums1.len(), nums2.len());
        let (mut low, mut high) = (0, m); // binary search range on nums1
        while low <= high {
            // the current partition position in nums1
            let partition_x = (low + high) / 2;
            // the position in nums2 in context of (m+n+1)/2 is the half of the virtual vector
            let partition_y = (m + n + 1) / 2 - partition_x;
            // the largest element on the left side
            let max_x = if partition_x == 0 {
                i32::MIN
            } else {
                nums1[partition_x - 1]
            };
            // the smallest element on the right side
            let min_x = if partition_x == m {
                i32::MAX
            } else {
                nums1[partition_x]
            };
            // the largest element on the left side
            let max_y = if partition_y == 0 {
                i32::MIN
            } else {
                nums2[partition_y - 1]
            };
            // the smallest element on the right side
            let min_y = if partition_y == n {
                i32::MAX
            } else {
                nums2[partition_y]
            };
            if max_x <= min_y && max_y <= min_x {
            // reached the virtual middle
                if (m + n) % 2 == 0 {
                    return (max_x.max(max_y) + min_x.min(min_y)) as f64 / 2.0;
                } else {
                    return max_x.max(max_y) as f64;
                }
            } else if max_x > min_y {
                // the partition_x is too far right
                high = partition_x - 1;
            } else {
                // the partition_x is too far left
                low = partition_x + 1;
            }
        }
        0.0 // theoretically not possible unless the inputs are invalid
    }
}

fn main() {
    let test_cases: Vec<((Vec<i32>, Vec<i32>), f64)> = vec![
        ((vec![1, 3], vec![2]), 2.0),
        ((vec![1, 2], vec![3, 4]), 2.5),
        (
            (
                vec![-50, -49, -48, -47, -46, -45],
                vec![45, 46, 47, 48, 49, 50],
            ),
            0.0,
        ),
        (
            (
                vec![-50, -49, -48, -47, -46, -45],
                vec![-50, -49, -48, -47, -46, -45],
            ),
            -47.5,
        ),
        (
            (
                vec![-50, -49, -48, -47, -46, -45],
                vec![-150, -149, -148, -147, -146, -145],
            ),
            -97.5,
        ),
        (
            (vec![-50], vec![-150, -149, -148, -147, -146, -145]),
            -147.0,
        ),
        (
            (
                vec![-146, -145, -48],
                vec![-150, -149, -148, -147, -50, -49],
            ),
            -146.0,
        ),
    ];
    let solutions: Vec<Box<dyn Solution>> =
        vec![Box::new(TwoPointerNoMerge), Box::new(BinarySearchNoMerge)];
    for (i, solution) in solutions.iter().enumerate() {
        for (j, ((nums1, nums2), expected)) in test_cases.iter().enumerate() {
            let got = solution.find_median_sorted_arrays(nums1, nums2);
            let solution_no = i + 1;
            let case_no = j + 1;
            let expected = *expected;
            if got == expected {
                println!(" v  pass");
            } else {
                println!("[x] failed case {} on solution {}", case_no, solution_no);
            }
        }
    }
}
