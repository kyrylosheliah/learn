/*
3. Longest Substring Without Repeating Characters

Given a string s, find the length of the longest substring without repeating
characters.

Example 1:
Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.

Example 2:
Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.

Example 3:
Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a
substring.

Constraints:
    0 <= s.length <= 5 * 10^4
    s consists of English letters, digits, symbols and spaces.
*/

use std::collections::HashMap;

trait Solution {
    fn length_of_longest_substring(&self, s: String) -> i32;
}

struct SlidingWindow;

impl Solution for SlidingWindow {
    fn length_of_longest_substring(&self, s: String) -> i32 {
        // first 128 character ASCII codes
        let mut char_table: [usize; 128] = [0; 128];
        let mut max_len: usize = 0;
        let mut left_pos: usize = 0;
        for (right_pos, character) in s.chars().enumerate() {
            let left_pos_per_character = char_table[character as usize];
            left_pos = left_pos.max(left_pos_per_character);
            max_len = max_len.max(right_pos - left_pos + 1);
            char_table[character as usize] = right_pos + 1;
        }
        max_len as i32
    }
}

struct HashMapSolution;

impl Solution for HashMapSolution {
    fn length_of_longest_substring(&self, string: String) -> i32 {
        let mut map: HashMap<char, i32> = HashMap::new();
        let mut left_pos = -1;
        let mut max_len = 0;
        for (right_pos, character) in string.chars().enumerate() {
            let right_pos = right_pos as i32;
            if let Some(left_pos_per_character) = map.insert(character, right_pos) {
                left_pos = std::cmp::max(left_pos, left_pos_per_character);
            }
            max_len = std::cmp::max(max_len, right_pos - left_pos);
        }
        max_len
    }
}

fn main() {
    let test_cases = vec![
        ("abcabcbb", 3),
        ("bbbbb", 1),
        ("pwwkew", 3),
    ];
    let solutions: Vec<Box<dyn Solution>> = vec![
        Box::new(SlidingWindow),
        Box::new(HashMapSolution),
    ];
    for (i, solution) in solutions.iter().enumerate() {
        for (j, (str, expected)) in test_cases.iter().enumerate() {
            let got = solution.length_of_longest_substring(str.to_string());
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
