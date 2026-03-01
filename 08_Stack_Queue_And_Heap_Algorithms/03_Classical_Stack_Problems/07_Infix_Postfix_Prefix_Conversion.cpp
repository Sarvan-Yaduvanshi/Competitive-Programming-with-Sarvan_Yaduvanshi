/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           07 — INFIX / POSTFIX / PREFIX CONVERSION                           ║
║           From Zero to Grandmaster — Classical Stack Problems               ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Expression Types
 2. Operator Precedence
 3. Infix → Postfix (Shunting Yard)
 4. Infix → Prefix
 5. Postfix → Infix
 6. Prefix → Infix
 7. Complete Dry Runs

EXPRESSION TYPES:
────────────────
  INFIX:    A + B * C        (operator BETWEEN operands) — Human readable
  POSTFIX:  A B C * +        (operator AFTER operands)   — No precedence needed
  PREFIX:   + A * B C        (operator BEFORE operands)  — No precedence needed

  Why Postfix/Prefix?
    • No parentheses needed
    • No precedence rules needed during evaluation
    • Easy to evaluate with stack
    • Used by compilers internally

OPERATOR PRECEDENCE:
───────────────────
  ┌────────────┬────────────┐
  │ Operator   │ Precedence │
  ├────────────┼────────────┤
  │ ^          │ 3 (highest)│
  │ * /        │ 2          │
  │ + -        │ 1 (lowest) │
  │ (          │ 0 (in stack)│
  └────────────┴────────────┘

  Associativity:
    ^  → Right to Left (2^3^2 = 2^(3^2) = 512, not 8^2=64)
    Others → Left to Right

INFIX → POSTFIX (SHUNTING YARD ALGORITHM):
──────────────────────────────────────────
  Rules:
  1. Operand → output directly
  2. '(' → push to stack
  3. ')' → pop and output until '(' found
  4. Operator → pop and output all operators with HIGHER or EQUAL precedence
     (for right-associative ^, only pop if strictly higher)
     then push current operator

  DRY RUN: "A + B * C - D"

  ┌─────┬────────┬──────────────┬─────────────────┐
  │ Char│ Action │ Stack        │ Output           │
  ├─────┼────────┼──────────────┼─────────────────┤
  │  A  │ output │ []           │ A                │
  │  +  │ push   │ [+]          │ A                │
  │  B  │ output │ [+]          │ A B              │
  │  *  │ push   │ [+, *]       │ A B              │
  │  C  │ output │ [+, *]       │ A B C            │
  │  -  │ pop *  │ [+]→pop +    │ A B C * +        │
  │     │ push - │ [-]          │ A B C * +        │
  │  D  │ output │ [-]          │ A B C * + D      │
  │ END │ pop all│ []           │ A B C * + D -    │
  └─────┴────────┴──────────────┴─────────────────┘

  Result: A B C * + D - ✅

  DRY RUN WITH PARENTHESES: "(A + B) * C"

  ┌─────┬────────┬──────────────┬─────────────────┐
  │ Char│ Action │ Stack        │ Output           │
  ├─────┼────────┼──────────────┼─────────────────┤
  │  (  │ push   │ [(]          │                  │
  │  A  │ output │ [(]          │ A                │
  │  +  │ push   │ [(, +]       │ A                │
  │  B  │ output │ [(, +]       │ A B              │
  │  )  │ pop→(  │ []           │ A B +            │
  │  *  │ push   │ [*]          │ A B +            │
  │  C  │ output │ [*]          │ A B + C          │
  │ END │ pop all│ []           │ A B + C *        │
  └─────┴────────┴──────────────┴─────────────────┘

  Result: A B + C * ✅
*/

#include <iostream>
#include <stack>
#include <string>
#include <algorithm>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// HELPER FUNCTIONS
// ═══════════════════════════════════════════════════════════════

int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

bool isOperand(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9');
}

// ═══════════════════════════════════════════════════════════════
// SECTION 1: INFIX → POSTFIX
// ═══════════════════════════════════════════════════════════════

string infixToPostfix(string infix) {
    stack<char> st;
    string postfix;

    for (char c : infix) {
        if (c == ' ') continue;

        if (isOperand(c)) {
            postfix += c;
        } else if (c == '(') {
            st.push(c);
        } else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                postfix += st.top();
                st.pop();
            }
            if (!st.empty()) st.pop();  // Remove '('
        } else if (isOperator(c)) {
            // For ^, only pop if strictly higher (right-associative)
            while (!st.empty() && st.top() != '(' &&
                   ((c != '^' && precedence(st.top()) >= precedence(c)) ||
                    (c == '^' && precedence(st.top()) > precedence(c)))) {
                postfix += st.top();
                st.pop();
            }
            st.push(c);
        }
    }

    while (!st.empty()) {
        postfix += st.top();
        st.pop();
    }
    return postfix;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: INFIX → PREFIX
// ═══════════════════════════════════════════════════════════════
/*
  Algorithm:
  1. Reverse the infix expression
  2. Replace '(' with ')' and vice versa
  3. Get postfix of the modified expression
  4. Reverse the result → this is the prefix!
*/

string infixToPrefix(string infix) {
    // Step 1 & 2: Reverse and swap brackets
    reverse(infix.begin(), infix.end());
    for (char& c : infix) {
        if (c == '(') c = ')';
        else if (c == ')') c = '(';
    }

    // Step 3: Get postfix
    string postfix = infixToPostfix(infix);

    // Step 4: Reverse to get prefix
    reverse(postfix.begin(), postfix.end());
    return postfix;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: POSTFIX → INFIX
// ═══════════════════════════════════════════════════════════════
/*
  Use stack of strings.
  Operand → push as string
  Operator → pop two, combine as "(B op A)", push result
*/

string postfixToInfix(string postfix) {
    stack<string> st;

    for (char c : postfix) {
        if (isOperand(c)) {
            st.push(string(1, c));
        } else if (isOperator(c)) {
            string b = st.top(); st.pop();
            string a = st.top(); st.pop();
            st.push("(" + a + c + b + ")");
        }
    }
    return st.top();
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: PREFIX → INFIX
// ═══════════════════════════════════════════════════════════════
/*
  Process RIGHT to LEFT.
  Operand → push
  Operator → pop two, combine as "(A op B)", push
*/

string prefixToInfix(string prefix) {
    stack<string> st;

    for (int i = prefix.length() - 1; i >= 0; i--) {
        char c = prefix[i];
        if (isOperand(c)) {
            st.push(string(1, c));
        } else if (isOperator(c)) {
            string a = st.top(); st.pop();
            string b = st.top(); st.pop();
            st.push("(" + a + c + b + ")");
        }
    }
    return st.top();
}

// ═══════════════════════════════════════════════════════════════

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  INFIX / POSTFIX / PREFIX CONVERSION                     ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Infix → Postfix
    cout << "═══ INFIX → POSTFIX ═══\n";
    string tests[] = {"A+B*C", "(A+B)*C", "A+B*C-D", "A*(B+C)/D", "A^B^C"};
    for (auto& s : tests) {
        cout << "  " << s << " → " << infixToPostfix(s) << "\n";
    }

    // Infix → Prefix
    cout << "\n═══ INFIX → PREFIX ═══\n";
    for (auto& s : tests) {
        cout << "  " << s << " → " << infixToPrefix(s) << "\n";
    }

    // Postfix → Infix
    cout << "\n═══ POSTFIX → INFIX ═══\n";
    string pf[] = {"ABC*+", "AB+C*", "ABC*+D-"};
    for (auto& s : pf) {
        cout << "  " << s << " → " << postfixToInfix(s) << "\n";
    }

    // Prefix → Infix
    cout << "\n═══ PREFIX → INFIX ═══\n";
    string pr[] = {"+A*BC", "*+ABC", "-+A*BCD"};
    for (auto& s : pr) {
        cout << "  " << s << " → " << prefixToInfix(s) << "\n";
    }

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "CONVERSION CHEAT SHEET:\n";
    cout << "───────────────────────\n";
    cout << "  Infix→Postfix: Shunting-yard (stack of operators)\n";
    cout << "  Infix→Prefix:  Reverse, swap brackets, get postfix, reverse\n";
    cout << "  Postfix→Infix: Stack of strings, combine with brackets\n";
    cout << "  Prefix→Infix:  R→L, stack of strings\n";
    cout << "  Postfix→Prefix: Convert to infix first, then to prefix\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

