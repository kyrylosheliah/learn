/*
6. Zigzag Conversion

The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R

And then read line by line: "PAHNAPLSIIGYIR". Write the code that will take a
string and make this conversion given a number of rows:

string convert(string s, int numRows);

Example 1:
Input: s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"

Example 2:
Input: s = "PAYPALISHIRING", numRows = 4
Output: "PINALSIGYAHRPI"
Explanation:
P     I    N
A   L S  I G
Y A   H R
P     I

Example 3:
Input: s = "A", numRows = 1
Output: "A"

Constraints:
    1 <= s.length <= 1000
    s consists of English letters (lower-case and upper-case), ',' and '.'.
    1 <= numRows <= 1000
*/

trait Solution {
    fn zigzag_convert(&self, s: String, num: usize) -> String;
}

struct Imperative;

impl Solution for Imperative {
    fn zigzag_convert(&self, s: String, num_rows: usize) -> String {
        let num_rows = num_rows as usize;
        if num_rows < 2 {
            return s;
        }/* else if num_rows == 2 {
            // just split odd from even characters
            let odd_chars: String = s
                .chars()
                .enumerate()
                .filter(|(i, _)| i % 2 != 1)
                .map(|(_, c)| c)
                .collect();
            let even_chars: String = s
                .chars()
                .enumerate()
                .filter(|(i, _)| i % 2 != 0)
                .map(|(_, c)| c)
                .collect();
            return odd_chars + &even_chars;
        }*/
        let len = s.len();
        let characters: Vec<char> = s.chars().collect();
        let mut answer = Vec::with_capacity(len);
        // resolve by counting cycles in zigzags
        let hop: usize = num_rows + num_rows - 2;
        // cycle for the first row
        let column_start_pos: usize = 0;
        let mut column_pos: usize = column_start_pos;
        while column_pos < len {
            answer.push(characters[column_pos]);
            column_pos += hop;
        }
        // cycle for the middle part with alternation of columns and diagonals
        if num_rows > 2 {
            let mut column_start_pos: usize = 1;
            let mut diagonal_start_pos = hop - 1;
            let middle_part_limit: usize = num_rows - 1;
            while column_start_pos < middle_part_limit
            /* && diagonal_start_pos >= 0 */ // already restricted by middle_part_limit
            {
                let mut column_pos: usize = column_start_pos;
                let mut diagonal_pos: usize = diagonal_start_pos;
                while column_pos < len {
                    // extract column character
                    answer.push(characters[column_pos]);
                    if diagonal_pos >= len {
                        break;
                    }
                    answer.push(characters[diagonal_pos]);
                    column_pos += hop;
                    diagonal_pos += hop;
                }
                column_start_pos += 1;
                diagonal_start_pos -= 1;
            }
        }
        // cycle for the last row
        let column_start_pos: usize = num_rows - 1;
        let mut column_pos: usize = column_start_pos;
        while column_pos < len {
            answer.push(characters[column_pos]);
            column_pos += hop;
        }
        answer.iter().collect()
        //String::from_iter(answer.iter())
    }
}

struct Chaining;

impl Solution for Chaining {
    fn zigzag_convert(&self, s: String, n: usize) -> String {
        let mut zigzags: Vec<_> = (0..n)
            .chain((1..n - 1).rev())
            .cycle()
            .zip(s.chars())
            .collect();
        zigzags.sort_by_key(|&(row, _)| row);
        zigzags.into_iter().map(|(_, c)| c).collect()
    }
}

fn main() {
    let test_cases = vec![
        ("PAYPALISHIRING", 3, "PAHNAPLSIIGYIR"),
        ("PAYPALISHIRING", 4, "PINALSIGYAHRPI"),
        ("A", 1, "A"),
        ("AaAaAaAa", 2, "AAAAaaaa"),
    ];
    let solutions: Vec<Box<dyn Solution>> = vec![
        Box::new(Imperative),
        Box::new(Chaining),
    ];
    for (i, solution) in solutions.iter().enumerate() {
        for (j, (s, n, expected)) in test_cases.iter().enumerate() {
            let got = solution.zigzag_convert(s.to_string(), *n);
            if got == *expected {
                print!(" v  pass");
                let times = 100;
                use std::time::Instant;
                let now = Instant::now();
                for _ in 0..times {
                    let _ = solution.zigzag_convert(s.to_string(), *n);
                }
                let elapsed = now.elapsed();
                println!(" s:{} c:{} {} times ({:.2?})", i, j, times, elapsed);
            } else {
                println!("[x] failed case {} on solution {}", j, i);
                dbg!(got);
            }
        }
        println!("---");
    }
}
