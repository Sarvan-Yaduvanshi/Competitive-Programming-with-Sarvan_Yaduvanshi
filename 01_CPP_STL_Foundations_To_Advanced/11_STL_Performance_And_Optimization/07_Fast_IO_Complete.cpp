/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           07 — FAST I/O — THE COMPLETE GUIDE                               ║
║           From Zero to Grandmaster — The #1 Optimization in CP             ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Why I/O is the Bottleneck (Not Your Algorithm!)
 2. ios::sync_with_stdio(false) — What It Does Internally
 3. cin.tie(nullptr) — Why Untying Matters
 4. endl vs '\n' — The Silent Killer
 5. scanf/printf vs cin/cout
 6. Custom Fast Reader (for N > 10^7)
 7. Output Tricks: printf formatting, cout optimization

═══════════════════════════════════════════════════════════════════════════════
 WHY I/O IS THE BOTTLENECK
═══════════════════════════════════════════════════════════════════════════════

 Many CP problems have N = 10^5 to 10^6 integers as input.
 Reading 10^6 integers:
   • cin (default):           ~500ms  ← TLE!
   • cin (sync off, untied):  ~50ms   ← AC!
   • scanf:                   ~50ms   ← AC!
   • Custom fast reader:      ~20ms   ← Overkill usually

 The ALGORITHM is fine. The I/O is killing you.
 Fix I/O first, then worry about complexity.
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: ios::sync_with_stdio(false)
// ═══════════════════════════════════════════════════════════════
/*
 WHAT IT DOES:
 ─────────────
 By default, C++ streams (cin/cout) are SYNCHRONIZED with C streams
 (stdin/stdout/scanf/printf). This means:
   • Every cin/cout operation checks C buffers too → OVERHEAD
   • Thread-safe interleaving with C I/O → OVERHEAD

 sync_with_stdio(false):
   • Breaks the sync → cin/cout use their OWN independent buffers
   • MUCH faster because no cross-checking
   • BUT: Can't mix cin/cout with scanf/printf after this!

 RULES:
   1. Call ONCE at the start of main()
   2. NEVER use scanf/printf after calling this
   3. NEVER use puts/getchar after calling this
*/

// ═══════════════════════════════════════════════════════════════
// SECTION 2: cin.tie(nullptr)
// ═══════════════════════════════════════════════════════════════
/*
 WHAT IT DOES:
 ─────────────
 By default, cin is TIED to cout. This means:
   Before every cin >> operation, cout is FLUSHED.

   WHY? So that prompts appear before input:
     cout << "Enter number: ";  // Flushed automatically
     cin >> n;                   // User sees prompt first

 In CP, we DON'T need this! We just read input and write output.
 Untying saves a flush operation per cin call.

 cin.tie(nullptr):
   • Unties cin from cout → no auto-flush before reads
   • Saves ~20-30% I/O time
*/

// ═══════════════════════════════════════════════════════════════
// SECTION 3: endl vs '\n'
// ═══════════════════════════════════════════════════════════════
/*
 endl DOES TWO THINGS:
   1. Outputs '\n'
   2. FLUSHES the buffer  ← THIS IS THE KILLER

 What is flushing?
   The output buffer accumulates data before sending to stdout.
   Flushing forces the buffer to write immediately.
   For 10^5 lines of output, that's 10^5 unnecessary flushes!

 DRY RUN:
   cout << "hello" << endl;
   → Buffer: "hello\n" → FLUSH → write to stdout → buffer empty

   cout << "hello" << '\n';
   → Buffer: "hello\n" → (still in buffer, write when full or program ends)

   For N=10^5 outputs:
     endl: 10^5 writes to stdout → SLOW
     '\n': ~1-2 writes to stdout (buffer flushes when full) → FAST
*/

void benchmarkEndl() {
    cout << "═══ endl vs '\\n' BENCHMARK ═══\n\n";

    const int N = 100000;

    // Using '\n'
    {
        stringstream ss;
        auto start = chrono::steady_clock::now();
        for (int i = 0; i < N; i++) ss << i << '\n';
        auto t = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "  '\\n' (" << N << " lines): " << t << " ms\n";
    }

    // Using endl
    {
        stringstream ss;
        auto start = chrono::steady_clock::now();
        for (int i = 0; i < N; i++) ss << i << endl;
        auto t = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "  endl (" << N << " lines): " << t << " ms\n\n";
    }
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: COMPLETE FAST I/O TEMPLATE
// ═══════════════════════════════════════════════════════════════

void printTemplate() {
    cout << "═══ FAST I/O TEMPLATE ═══\n\n";

    cout << "// BASIC (sufficient for 99%% of problems):\n";
    cout << "#include <bits/stdc++.h>\n";
    cout << "using namespace std;\n";
    cout << "int main() {\n";
    cout << "    ios::sync_with_stdio(false);\n";
    cout << "    cin.tie(nullptr);\n";
    cout << "    // Use '\\n' not endl\n";
    cout << "    return 0;\n";
    cout << "}\n\n";

    cout << "// ADVANCED (for extreme I/O > 10^7 values):\n";
    cout << "// Add pragma + custom reader (see below)\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: CUSTOM FAST READER (for 10^7+ input)
// ═══════════════════════════════════════════════════════════════
/*
 When even cin with sync off isn't fast enough:
   • Read entire input at once with fread
   • Parse integers manually from buffer
   • ~2-3x faster than cin

 Only needed when N > 5×10^6 and you're borderline TLE.
*/

namespace FastIO {
    const int BUFFER_SIZE = 1 << 22;  // 4MB buffer
    char buffer[BUFFER_SIZE];
    int bufPos = 0, bufLen = 0;

    inline char getChar() {
        if (bufPos == bufLen) {
            bufLen = fread(buffer, 1, BUFFER_SIZE, stdin);
            bufPos = 0;
        }
        return buffer[bufPos++];
    }

    inline int readInt() {
        int x = 0;
        bool neg = false;
        char c = getChar();
        while (c < '0' || c > '9') {
            if (c == '-') neg = true;
            c = getChar();
        }
        while (c >= '0' && c <= '9') {
            x = x * 10 + (c - '0');
            c = getChar();
        }
        return neg ? -x : x;
    }

    // Fast output
    char outBuffer[BUFFER_SIZE];
    int outPos = 0;

    inline void writeChar(char c) {
        if (outPos == BUFFER_SIZE) {
            fwrite(outBuffer, 1, outPos, stdout);
            outPos = 0;
        }
        outBuffer[outPos++] = c;
    }

    inline void writeInt(int x) {
        if (x < 0) { writeChar('-'); x = -x; }
        if (x == 0) { writeChar('0'); return; }
        char tmp[12];
        int len = 0;
        while (x > 0) { tmp[len++] = '0' + x % 10; x /= 10; }
        for (int i = len - 1; i >= 0; i--) writeChar(tmp[i]);
    }

    inline void flush() {
        fwrite(outBuffer, 1, outPos, stdout);
        outPos = 0;
    }
}

void demonstrateCustomReader() {
    cout << "═══ CUSTOM FAST READER ═══\n\n";
    cout << "FastIO::readInt() reads integers ~2-3x faster than cin\n";
    cout << "FastIO::writeInt() writes ~2x faster than cout\n\n";
    cout << "WHEN TO USE:\n";
    cout << "  • N > 5×10^6 and you're getting TLE\n";
    cout << "  • Stress testing with massive inputs\n";
    cout << "  • Interactive problems (need flush control)\n\n";
    cout << "WHEN NOT TO USE:\n";
    cout << "  • N ≤ 10^6 → cin with sync off is fine\n";
    cout << "  • Most contest problems → overkill\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 6: OUTPUT TRICKS
// ═══════════════════════════════════════════════════════════════

void outputTricks() {
    cout << "═══ OUTPUT TRICKS ═══\n\n";

    // Trick 1: Build output in string, print once
    cout << "TRICK 1: Build output string, print once\n";
    {
        string output;
        output.reserve(1000000);
        for (int i = 0; i < 10; i++) {
            output += to_string(i);
            output += ' ';
        }
        cout << "  " << output << "\n\n";
    }

    // Trick 2: Fixed precision for floating point
    cout << "TRICK 2: Fixed precision\n";
    double pi = 3.14159265358979;
    cout << "  default:       " << pi << "\n";
    cout << "  fixed(6):      " << fixed << setprecision(6) << pi << "\n";
    cout << "  fixed(10):     " << fixed << setprecision(10) << pi << "\n\n";

    // Trick 3: cout.write for known-length strings (faster than <<)
    cout << "TRICK 3: Bulk output\n";
    cout << "  For massive output, use puts() or printf() with single call\n\n";

    // Trick 4: '\n' at the end of output
    cout << "TRICK 4: Don't forget trailing newline!\n";
    cout << "  Some judges require it, some don't.\n";
    cout << "  Safe: always end output with '\\n'\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 7: COMMON MISTAKES
// ═══════════════════════════════════════════════════════════════

void commonMistakes() {
    cout << "═══ COMMON I/O MISTAKES ═══\n\n";

    cout << "MISTAKE 1: Forgetting sync_with_stdio\n";
    cout << "  → 10x slower I/O → TLE on N=10^5\n\n";

    cout << "MISTAKE 2: Using endl in loops\n";
    cout << "  → Flushes 10^5 times → TLE\n\n";

    cout << "MISTAKE 3: Mixing cin/cout with scanf/printf after sync off\n";
    cout << "  → Undefined behavior! Choose one or the other.\n\n";

    cout << "MISTAKE 4: cout << fixed << setprecision(k) affects ALL later output!\n";
    cout << "  → Reset with cout << defaultfloat if needed.\n\n";

    cout << "MISTAKE 5: Reading string with spaces using cin >>\n";
    cout << "  → cin >> reads until whitespace. Use getline() for full lines.\n";
    cout << "  → After cin >> n, call cin.ignore() before getline()!\n\n";

    cout << "MISTAKE 6: Not handling multiple test cases output efficiently\n";
    cout << "  → Print all output at end, or use '\\n' not endl.\n\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    benchmarkEndl();
    printTemplate();
    demonstrateCustomReader();
    outputTricks();
    commonMistakes();

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. ALWAYS: ios::sync_with_stdio(false); cin.tie(nullptr);\n";
    cout << "2. ALWAYS: '\\n' not endl\n";
    cout << "3. These two rules prevent 90%% of I/O TLEs\n";
    cout << "4. Custom fast reader: only for N > 5×10^6\n";
    cout << "5. Don't mix C and C++ I/O after sync off\n";
    cout << "6. For floating point: cout << fixed << setprecision(k)\n";

    return 0;
}

