# 📡 Minitalk

![Score](https://img.shields.io/badge/Score-125%2F125-brightgreen)
![Language](https://img.shields.io/badge/Language-C-blue)
![42](https://img.shields.io/badge/42-Project-black)

## 📌 Project Goal

**Minitalk** is a small inter-process communication project from the 42 curriculum. The goal is to build a **client-server messaging system** where the only communication channel between two processes is **UNIX signals** — specifically `SIGUSR1` and `SIGUSR2`.

The server starts first and prints its **PID**. The client takes that PID and a string as arguments, encodes the string **bit by bit** into signals, and sends it to the server. The server decodes the signals back into characters and prints the message.

Bonus adds **acknowledgment signals** (the server confirms each character received) and **Unicode support**.

---

## 🧠 Key Concepts

### UNIX Signals
A signal is an asynchronous notification sent to a process. Minitalk uses only two:

| Signal | Meaning (by convention) |
|---|---|
| `SIGUSR1` | Bit `0` |
| `SIGUSR2` | Bit `1` |

Every character is encoded as 8 bits and transmitted one signal at a time — 8 signals per character.

### `sigaction` vs `signal`
Always use **`sigaction`** over the older `signal()`. It gives full control over signal handling behavior and is more portable and reliable.

```c
struct sigaction sa;
sa.sa_sigaction = handler_function;
sa.sa_flags = SA_SIGINFO;           // enables extended info (sender PID)
sigemptyset(&sa.sa_mask);
sigaction(SIGUSR1, &sa, NULL);
sigaction(SIGUSR2, &sa, NULL);
```

`SA_SIGINFO` enables the handler to receive a `siginfo_t` argument containing the **sender's PID** — essential for the bonus acknowledgment.

### Encoding: Characters to Bits
Each character is sent **LSB first** (or MSB first — pick one and be consistent). For each of the 8 bits:
- Bit is `0` → send `SIGUSR1`
- Bit is `1` → send `SIGUSR2`

```c
void send_char(int pid, char c)
{
    int bit;

    bit = 0;
    while (bit < 8)
    {
        if ((c >> bit) & 1)
            kill(pid, SIGUSR2);
        else
            kill(pid, SIGUSR1);
        // wait for acknowledgment (bonus) or just usleep
        bit++;
    }
}
```

### `kill()` — Sending Signals
Despite the name, `kill()` is the syscall for **sending any signal** to a process:

```c
kill(pid, SIGUSR1);   // send SIGUSR1 to process pid
```

Returns `-1` on error (e.g. pid doesn't exist).

### Timing & Synchronization
The client must not send the next signal before the server has processed the current one. Two approaches:

- **Mandatory**: `usleep()` between signals — a fixed pause long enough for the server to handle the signal. Simple but fragile under load.
- **Bonus**: **Acknowledgment signals** — the server sends `SIGUSR1` back to the client after processing each bit (or each character). The client waits in `pause()` or `sigsuspend()` until it receives the ack before sending the next signal.

### `pause()` and `sigsuspend()`
```c
pause();          // sleep until any signal is received
sigsuspend(&mask); // sleep until a signal not in mask is received
```
Used by the client (bonus) to block until the server acknowledges, instead of busy-waiting.

---

## 🚀 Usage

### Compilation
```bash
make        # mandatory
make bonus  # with acknowledgment + unicode
```

### Running
```bash
# Terminal 1 — start the server
./server
# prints: Server PID: 12345

# Terminal 2 — send a message
./client 12345 "Hello, World!"
```

### Bonus — Unicode
Unicode characters (e.g. `é`, `中`, `🚀`) use **multi-byte UTF-8 encoding**. Since each byte is sent independently with 8 signals, sending raw bytes without any special handling already supports UTF-8 transparently — as long as you send the null terminator and the server reconstructs full bytes correctly.

---

## 🏗️ Implementation Logic

### Server Logic
```
sigaction → register SIGUSR1/SIGUSR2 handlers
while (1)
    pause()                   ← sleep until a signal arrives

handler(sig, info):
    shift bit into current_char based on sig (0 or 1)
    bit_count++
    if bit_count == 8:
        if current_char == '\0' → print full message, reset
        else → append current_char to buffer
        bit_count = 0
        current_char = 0
        [Bonus] kill(info->si_pid, SIGUSR1)  ← send ack to client
```

### Client Logic
```
for each char in string (including '\0'):
    for bit 0..7:
        kill(server_pid, SIGUSR1 or SIGUSR2)
        [Mandatory] usleep(some_delay)
        [Bonus] pause() ← wait for ack from server
[Bonus] wait for final ack after '\0'
```

### Bonus — Acknowledgment Flow
```
Client sends bit N
    └── Server receives bit N → processes → kill(client_pid, SIGUSR1)
         └── Client receives ack → sends bit N+1
```
This turns the transmission into a synchronized **stop-and-wait** protocol — reliable at any speed.

---

## ⚠️ Common Mistakes & Tricky Points

- **`signal()` instead of `sigaction()`**: `signal()` resets the handler after each call on some systems and doesn't provide sender info. Always use `sigaction`.
- **Signal loss**: If signals arrive too fast, the OS may drop duplicates (two `SIGUSR1`s in quick succession may only trigger the handler once). The bonus ack system solves this entirely; for mandatory, tune `usleep` to a safe value (typically 200–500µs).
- **`usleep` timing is fragile**: A value that works on your machine may fail on the evaluator's. Acknowledgment is the only truly robust solution.
- **Not sending the null terminator**: The server needs to know when the string ends. Always send `'\0'` as the final character so the server knows to print and reset.
- **Static variables in the handler**: The server's bit accumulator and buffer must be `static` (or global) since the handler is called separately for each signal.
- **`SA_SIGINFO` missing**: Without this flag, `siginfo_t` is not populated — `info->si_pid` will be garbage, breaking the bonus ack.
- **Bonus ack on every bit vs every byte**: Acking every bit is safest and simplest. Acking every byte is faster but requires the client to count bits itself before waiting.

---

## ✅ Evaluation Checklist

- [ ] Server prints its PID on startup
- [ ] Client correctly sends any ASCII string to the server
- [ ] Server prints the message accurately and completely
- [ ] No signal loss for reasonable string lengths
- [ ] Server can receive multiple messages without restarting
- [ ] No memory leaks
- [ ] **Bonus**: server sends acknowledgment after each received bit/character
- [ ] **Bonus**: client waits for ack before sending the next signal
- [ ] **Bonus**: Unicode (multi-byte UTF-8) strings are transmitted correctly

---

## 🛠️ Useful Debug Commands

```bash
# Check server PID
./server &
echo $!

# Send various messages
./client $! "Hello"
./client $! "Unicode: 🚀 中文 é"
./client $! ""          # empty string (just null terminator)

# Long string stress test
python3 -c "print('A' * 1000, end='')" | xargs ./client $!

# Check for leaks
valgrind --leak-check=full ./server &
./client $! "test"
```
