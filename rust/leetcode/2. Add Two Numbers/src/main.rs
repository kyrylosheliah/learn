/*
2. Add Two Numbers

You are given two non-empty linked lists representing two non-negative integers.
The digints are stored in reverse order, and each of their nodes contains a
single digit. Add the two numbers and return the sum as a linked list.

You may assume the two numbers do not contain any leading zero, except the
number 0 itself.

Example 1:
Input: l1 = [2,4,3], l2 = [5,6,4]
Output: [7,0,8]
Explanation: 342 + 465 = 807.

Example 2:
Input: l1 = [0], l2 = [0]
Output: [0]

Example 3:
Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
Output: [8,9,9,9,0,0,0,1]

Constraints:
    The number of nodes in each linked list is in the range [1, 100].
    0 <= Node.val <= 9
    It is guaranteed that the list represents a number that does not have
      leading zeros.
*/

pub struct ListNode {
    pub val: i32,
    pub next: Option<Box<ListNode>>,
}

impl ListNode {
    fn new(val: i32) -> Self {
        ListNode { next: None, val }
    }
    fn push(&mut self, val: i32) {
        //self.next.insert(Box::new(ListNode::new(val)));
        self.next = Some(Box::new(ListNode::new(val)));
    }
    fn sum(&self) -> i32 {
        let mut sum = self.val.clone();
        let mut node = &self.next;
        while node.is_some() {
            /*sum += l1.as_ref().map_or(0, |node| node.val)
            + l2.as_ref().map_or(0, |node| node.val);*/
            sum += match node {
                Some(n) => {
                    node = &n.next;
                    n.val
                }
                None => 0,
            };
        }
        sum
    }
}

impl Clone for ListNode {
    fn clone(&self) -> Self {
        ListNode {
            val: self.val,
            next: self.next.as_ref().map(|next_node| next_node.clone()),
        }
    }
}

macro_rules! LNs {
    ( $x0:expr, $x1:expr $(, $x:expr )* ) => {
        {
            let mut head: ListNode = ListNode::new($x0);
            let mut current: &mut ListNode = &mut head;
            current.push($x1);
            $(
                current = current.next.as_mut().unwrap();
                current.push($x);
            )*
            Some(Box::new(head))
        }
    };
    ( $x0:expr ) => {
        Some(Box::new(ListNode::new($x0)))
    };
    () => {
        None
    };
}

trait Solution {
    fn add_two_numbers(
        &self,
        l1: &Option<Box<ListNode>>,
        l2: &Option<Box<ListNode>>,
    ) -> Option<Box<ListNode>>;
}

struct IterativeV1;

impl Solution for IterativeV1 {
    fn add_two_numbers(
        &self,
        l1: &Option<Box<ListNode>>,
        l2: &Option<Box<ListNode>>,
    ) -> Option<Box<ListNode>> {
        let mut carry = 0;
        let mut head: Option<Box<ListNode>> = None;
        let mut curr = &mut head;
        let mut l1: Option<Box<ListNode>> = l1.clone();
        let mut l2: Option<Box<ListNode>> = l2.clone();
        while l1.is_some() || l2.is_some() || carry != 0 {
            let sum = l1.as_ref().map_or(0, |x| x.val) + l2.as_ref().map_or(0, |x| x.val) + carry;
            carry = sum / 10;
            let sum_node = curr.insert(Box::new(ListNode::new(sum % 10)));
            curr = &mut sum_node.next;
            l1 = l1.and_then(|node| node.next);
            l2 = l2.and_then(|node| node.next);
        }
        head
    }
}

struct IterativeV2;

impl Solution for IterativeV2 {
    fn add_two_numbers(
        &self,
        mut l1: &Option<Box<ListNode>>,
        mut l2: &Option<Box<ListNode>>,
    ) -> Option<Box<ListNode>> {
        let mut carry = 0;
        let mut head = Box::new(ListNode::new(0));
        let mut tail = &mut head;
        while l1.is_some() || l2.is_some() || carry != 0 {
            let val = match l1 {
                Some(n) => {
                    l1 = &n.next;
                    n.val
                }
                None => 0,
            } + match l2 {
                Some(n) => {
                    l2 = &n.next;
                    n.val
                }
                None => 0,
            } + carry;
            carry = val / 10;
            let rem = val % 10;
            tail.next = Some(Box::new(ListNode::new(rem)));
            tail = tail.next.as_mut().unwrap();
        }
        head.next
    }
}

fn main() {
    let test_cases = vec![
        (LNs![2, 4, 3], LNs![5, 6, 4], LNs![7, 0, 8]),
        (LNs![0], LNs![0], LNs![0]),
        (
            LNs![9, 9, 9, 9, 9, 9, 9],
            LNs![9, 9, 9, 9],
            LNs![8, 9, 9, 9, 0, 0, 0, 1],
        ),
    ];
    let solutions: Vec<Box<dyn Solution>> = vec![Box::new(IterativeV1), Box::new(IterativeV2)];
    for (i, solution) in solutions.iter().enumerate() {
        for (j, (left, right, expected)) in test_cases.iter().enumerate() {
            let result = solution.add_two_numbers(left, right);
            let solution_no = i + 1;
            let case_no = j + 1;
            let got = match result {
                Some(n) => n.sum(),
                None => 0,
            };
            // forced to `expected.clone().unwrap().sum()` otherwise
            let expected = match expected {
                Some(n) => n.sum(),
                None => 0,
            };
            if got == expected {
                println!(" v  pass");
            } else {
                println!("[x] failed case {} on solution {}", case_no, solution_no);
            }
        }
    }
}
