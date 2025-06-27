/*
1. Two Sum

Given an array of integers nums and an integer target, return indices of the two
  numbers such that they add up to target.
You may assume that each input would have exactly one solution, and you may not
  use the same element twice.
You can return the answer in any order.

Constraints:
    2 <= nums.length <= 10^4
    -10^9 <= nums[i] <= 10^9
    -10^9 <= target <= 10^9
    Only one valid answer exists.

Example 1:

Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].

Example 2:

Input: nums = [3,2,4], target = 6
Output: [1,2]

Example 3:

Input: nums = [3,3], target = 6
Output: [0,1]
*/

use std::collections::HashMap;

pub trait Solution {
    fn two_sum(&self, nums: &Vec<i32>, target: &i32) -> Vec<i32>;
}

struct BruteForce;

impl Solution for BruteForce {
    /// Time complexity:
    /// - Worst case and average case are O(n^2).
    ///     - The outer loop runs n times.
    ///     - For each iteration of the outer loop, the inner loop runs n-1
    ///       times in the first iteration, n-2 times in the second iteration
    ///       and so on. This sums up to O(n^2).
    /// - Best case is O(1).
    ///     - If the first two elements we check are the solution, we'll find
    ///       it immediately.
    /// Space complexity:
    /// - Is always O(1).
    ///     - Space doesn't scales with the input size.
    ///     - There are only a couple of integer variables for `for` loop and
    ///       result.
    fn two_sum(&self, nums: &Vec<i32>, target: &i32) -> Vec<i32> {
        let length = nums.len();
        for gap in 1..length {
            for right in gap..length {
                let left = right - gap;
                if nums[left] + nums[right] == *target {
                    return vec![left as i32, right as i32];
                }
            }
        }
        vec![]
    }
}

struct TwoPointer;

impl Solution for TwoPointer {
    /// Time complexity:
    /// - Overall O(n*log(n)).
    ///     - Sorting the array is O(n*log(n)).
    ///     - Two-pointer traversal is O(n) in the worst case.
    /// Space complexity:
    /// - Overall O(n).
    ///     - O(n) to store the sorted array with original indices.
    ///     - O(1) for several variables.
    fn two_sum(&self, nums: &Vec<i32>, target: &i32) -> Vec<i32> {
        let mut nums_with_indices: Vec<(i32, usize)> = nums
            .iter()
            .copied()
            .enumerate()
            .map(|(i, num)| (num, i))
            .collect();
        nums_with_indices.sort_by_key(|&(value, _)| value);
        let mut left = 0;
        let mut right = nums_with_indices.len() - 1;
        while left < right {
            let sum = nums_with_indices[left].0 + nums_with_indices[right].0;
            if sum == *target {
                return vec![
                    nums_with_indices[left].1 as i32,
                    nums_with_indices[right].1 as i32,
                ];
            } else if sum < *target {
                left += 1;
            } else {
                right -= 1;
            }
        }
        vec![]
    }
}

struct TwoPassHashTable;

impl Solution for TwoPassHashTable {
    /// Time complexity:
    /// - Overall O(n).
    ///     - First pass is O(n).
    ///     - Second pass is O(n).
    ///     - Hash map lookup is O(1).
    /// Space complexity:
    ///     - Overall O(n) which is the size of hash map with a record for each
    ///       element.
    fn two_sum(&self, nums: &Vec<i32>, target: &i32) -> Vec<i32> {
        let mut map = HashMap::new();
        for (i, &num) in nums.iter().enumerate() {
            map.insert(num, i);
        }
        for (i, &num) in nums.iter().enumerate() {
            let complement = target - num;
            if let Some(&complement_index) = map.get(&complement) {
                if complement_index != i {
                    return vec![i as i32, complement_index as i32];
                }
            }
        }
        vec![]
    }
}

struct OnePassHashTable;

impl Solution for OnePassHashTable {
    /// Time complexity:
    /// - Overall O(n)
    ///     - There is a single pass through the array
    ///     - Each element is being subjected for constant-time operations
    /// Space complexity:
    /// - Worst case is O(n)
    ///     - Might need to store n-1 elements before the solution will be found
    ///     - Number of elements is proportional to solution position
    fn two_sum(&self, nums: &Vec<i32>, target: &i32) -> Vec<i32> {
        let mut map = HashMap::new();
        for (i, &num) in nums.iter().enumerate() {
            let complement = target - num;
            if let Some(&complement_index) = map.get(&complement) {
                return vec![complement_index as i32, i as i32];
            }
            map.insert(num, i);
        }
        vec![]
    }
}

pub fn main() {
    let test_cases: Vec<(Vec<i32>, i32, Vec<i32>)> = vec![
        (vec![2, 7, 11, 15], 9, vec![1, 1]),
        (vec![3, 2, 4], 6, vec![1, 2]),
        (vec![3, 3], 6, vec![0, 1]),
    ];
    let solutions: Vec<Box<dyn Solution>> = vec![
        Box::new(BruteForce),
        Box::new(TwoPointer),
        Box::new(TwoPassHashTable),
        Box::new(OnePassHashTable),
    ];
    for (i, solution) in solutions.iter().enumerate() {
        for (j, (nums, target, expected)) in test_cases.iter().enumerate() {
            let result = solution.two_sum(&nums, target);
            let solution_no = i + 1;
            let case_no = j + 1;
            if result == *expected {
                println!(" v  pass");
            } else {
                println!("[x] solution {} failed case {}", solution_no, case_no);
            }
        }
    }
}
