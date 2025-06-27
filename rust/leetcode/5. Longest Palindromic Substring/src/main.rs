/*
5. Longest Palindromic Substring

Given a string s, return the longest palindromic substring in s.

Example 1:
Input: s = "babad"
Output: "bab"
Explanation: "aba" is also a valid answer.

Example 2:
Input: s = "cbbd"
Output: "bb"

Constraints:
    1 <= s.length <= 1000
    s consist of only digits and English letters.
*/

trait Solution {
    fn longest_palindrome(&self, s: String) -> String;
}

struct ManacherExpandAlgorithm;

impl Solution for ManacherExpandAlgorithm {
    // try every possible position to expand the palindrom from there
    fn longest_palindrome(&self, s: String) -> String {
        let bytes = s.as_bytes();
        let n = bytes.len();
        let mut pos = (0, 0);
        for i in 0..n * 2 {
            let (mut left, mut right) = (i / 2, i / 2 + (i % 2 != 0) as usize);
            while left <= right && left < n && right < n {
                if bytes.get(left).unwrap() != bytes.get(right).unwrap() {
                    break;
                }
                if right - left > pos.1 - pos.0 {
                    pos = (left, right);
                }
                if left <= 0 {
                    // should always break after uptating `pos = ...`
                    break;
                }
                left -= 1;
                right += 1;
            }
        }
        s.get(pos.0..=pos.1).unwrap().to_string()
    }
}

struct RustArrayWindows;

impl RustArrayWindows {
    fn is_palindrome(s: &[u8]) -> bool {
        s.iter()
            // Iterate left to right along with iterating from right to left
            .zip(s.iter().rev())
            // Make sure each spot is the same
            .all(|(l, r)| l == r)
        // Returns false once the left is not equal to the right
    }
}

impl Solution for RustArrayWindows {
    fn longest_palindrome(&self, s: String) -> String {
        for size in (1..(s.len() + 1)).rev() {
            match s
                .as_bytes()
                .windows(size)
                .find(|substr| Self::is_palindrome(substr))
            {
                Some(pal) => return String::from_utf8(pal.to_vec()).unwrap(),
                None => continue,
            }
        }
        String::from("")
    }
}

fn main() {
    let test_cases = vec![
        ("babad", vec!["bab", "aba"]),
        ("cbbd", vec!["bb"]),
        ("peeweep", vec!["peeweep"]),
        ("ababaaaaa", vec!["ababa", "aaaaa"]),
    ];
    let solutions: Vec<Box<dyn Solution>> = vec![
        Box::new(ManacherExpandAlgorithm),
        Box::new(RustArrayWindows),
    ];
    for (i, solution) in solutions.iter().enumerate() {
        for (j, (s, expected)) in test_cases.iter().enumerate() {
            let got = solution.longest_palindrome(s.to_string());
            let solution_no = i + 1;
            let case_no = j + 1;
            let found = expected.iter().any(|answer| {
                let expected = answer.to_string();
                got == expected
            });
            if found {
                println!(" v  pass");
            } else {
                println!("[x] failed case {} on solution {}", case_no, solution_no);
                dbg!(got);
            }
        }
    }
}
