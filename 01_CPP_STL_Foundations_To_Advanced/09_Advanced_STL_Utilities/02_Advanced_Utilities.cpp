/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           02 — ADVANCED UTILITIES: optional, variant, any, string_view     ║
║           From Zero to Grandmaster                                         ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ═══ std::optional (C++17) ═══
    cout << "═══ std::optional ═══\n\n";
    /*
     optional<T> may or may not hold a value.
     Like a "nullable" type — safer than using sentinel values (-1, INT_MAX).
    */
    auto safeDivide = [](int a, int b) -> optional<double> {
        if (b == 0) return nullopt;
        return (double)a / b;
    };

    auto r1 = safeDivide(10, 3);
    auto r2 = safeDivide(10, 0);
    cout << "10/3 = " << (r1.has_value() ? to_string(r1.value()) : "nullopt") << "\n";
    cout << "10/0 = " << (r2.has_value() ? to_string(r2.value()) : "nullopt") << "\n";

    // value_or for default
    cout << "10/0 or -1: " << r2.value_or(-1) << "\n\n";

    // CP USE: Binary search returning optional position
    auto binarySearch = [](vector<int>& v, int target) -> optional<int> {
        auto it = lower_bound(v.begin(), v.end(), target);
        if (it != v.end() && *it == target)
            return (int)(it - v.begin());
        return nullopt;
    };

    vector<int> v = {1, 3, 5, 7, 9};
    auto pos = binarySearch(v, 5);
    cout << "Search 5: " << (pos ? "found at " + to_string(*pos) : "not found") << "\n";
    pos = binarySearch(v, 4);
    cout << "Search 4: " << (pos ? "found at " + to_string(*pos) : "not found") << "\n\n";

    // ═══ std::variant (C++17) ═══
    cout << "═══ std::variant ═══\n\n";
    /*
     variant<Types...> = type-safe union. Holds ONE of the listed types.
     Safer than raw unions.
    */
    variant<int, double, string> val;
    val = 42;
    cout << "int: " << get<int>(val) << "\n";
    val = 3.14;
    cout << "double: " << get<double>(val) << "\n";
    val = string("hello");
    cout << "string: " << get<string>(val) << "\n";

    // Check which type
    cout << "Index: " << val.index() << " (0=int, 1=double, 2=string)\n";
    cout << "Holds string? " << holds_alternative<string>(val) << "\n\n";

    // Visit pattern
    val = 42;
    visit([](auto&& arg) {
        cout << "Visit: " << arg << "\n";
    }, val);
    cout << "\n";

    // ═══ std::any (C++17) ═══
    cout << "═══ std::any ═══\n\n";
    /*
     any can hold ANY type. Like a type-erased container.
     Less type-safe than variant but more flexible.
    */
    any a = 42;
    cout << "int: " << any_cast<int>(a) << "\n";
    a = string("CP");
    cout << "string: " << any_cast<string>(a) << "\n";
    a = 3.14;
    cout << "double: " << any_cast<double>(a) << "\n";
    cout << "Has value: " << a.has_value() << "\n";
    cout << "Type: " << a.type().name() << "\n\n";

    // ═══ std::string_view (C++17) ═══
    cout << "═══ std::string_view ═══\n\n";
    /*
     string_view = non-owning reference to a string.
     No allocation, no copy — just a pointer + length.
     PERFECT for function parameters that don't modify the string.
    */
    string str = "Hello, Competitive Programming!";
    string_view sv = str;
    string_view sub = sv.substr(7, 11);  // No allocation!

    cout << "Full: " << sv << "\n";
    cout << "Sub:  " << sub << "\n";
    cout << "Size: " << sv.size() << "\n";

    // Remove prefix/suffix (modifies VIEW, not string)
    sv.remove_prefix(7);
    sv.remove_suffix(1);
    cout << "Trimmed: " << sv << "\n\n";

    // Performance: string_view vs string for function params
    auto countVowels = [](string_view s) -> int {
        int cnt = 0;
        for (char c : s)
            if (string("aeiouAEIOU").find(c) != string::npos) cnt++;
        return cnt;
    };
    cout << "Vowels in \"Hello\": " << countVowels("Hello") << "\n\n";

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. optional: nullable values, safer than sentinel (-1)\n";
    cout << "2. variant: type-safe union, holds one of listed types\n";
    cout << "3. any: holds anything, less safe but more flexible\n";
    cout << "4. string_view: non-owning, zero-copy string reference\n";
    cout << "5. In CP: optional/string_view most useful of these\n";

    return 0;
}

