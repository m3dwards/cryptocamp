#include <iostream>
#include <format>
#include <vector>

// ============================================================
// ElGamal Encryption
// A public-key encryption scheme based on the difficulty of
// computing discrete logarithms in Z*_p.
//
// Overview:
//   1. Bob generates a key pair (private + public)
//   2. Alice encrypts a message using Bob's public key
//   3. Bob decrypts the message using his private key
// ============================================================

// Fast modular exponentiation: computes base^exp mod m
// (same square-and-multiply approach as in modinverse.cpp)
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

// Modular inverse using Fermat's little theorem: a^(p-2) mod p
// Only valid when p is prime.
long long modInverse(long long a, long long p) {
    return modExp(a, p - 2, p);
}

// Returns the prime factors of n.
// e.g. primeFactors(22) = {2, 11}
std::vector<long long> primeFactors(long long n) {
    std::vector<long long> factors;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            factors.push_back(i);
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) factors.push_back(n);
    return factors;
}

// Returns true if g is a generator of Z*_p.
// g is a generator if g^((p-1)/q) mod p != 1 for every prime factor q of p-1.
bool isGenerator(long long g, long long p, const std::vector<long long>& factors) {
    for (long long q : factors)
        if (modExp(g, (p - 1) / q, p) == 1)
            return false;
    return true;
}

int main() {

    // --------------------------------------------------------
    // Public parameters (known to everyone)
    // p: a large prime that defines the group Z*_p
    // g: a generator of Z*_p (a base that can produce all
    //    elements of the group by repeated exponentiation)
    // --------------------------------------------------------
    long long p, g;
    std::cout << "=== Public Parameters ===\n";
    std::cout << "Enter prime p: ";
    std::cin >> p;

    // Compute and display all valid generators so the user knows what to pick
    auto factors = primeFactors(p - 1);
    std::cout << "Valid generators for p=" << p << ": ";
    for (long long g_candidate = 2; g_candidate < p; g_candidate++)
        if (isGenerator(g_candidate, p, factors))
            std::cout << g_candidate << " ";
    std::cout << "\n";

    std::cout << "Enter generator g: ";
    std::cin >> g;

    // --------------------------------------------------------
    // Bob's key generation
    // Bob picks a secret private key x, then computes his
    // public key y = g^x mod p, which he shares with everyone.
    // --------------------------------------------------------
    long long x;
    std::cout << "\n=== Bob: Key Generation ===\n";
    std::cout << std::format("Enter Bob's private key x (between 2 and {}): ", p - 2);
    std::cin >> x;

    long long y = modExp(g, x, p);
    std::cout << std::format("Bob's public key y = g^x mod p = {}\n", y);

    // --------------------------------------------------------
    // Alice encrypts a message for Bob
    // Alice needs: the public parameters (p, g) and Bob's
    // public key (y). She also picks a random k.
    //
    // Encryption:
    //   c1 = g^k mod p       (a "hint" about k)
    //   c2 = m * y^k mod p   (message blinded by shared secret)
    // --------------------------------------------------------
    long long m, k;
    std::cout << "\n=== Alice: Encryption ===\n";
    std::cout << "Enter message m (a number less than p): ";
    std::cin >> m;
    std::cout << "Enter random k: ";
    std::cin >> k;

    long long c1 = modExp(g, k, p);
    long long c2 = (m * modExp(y, k, p)) % p;
    std::cout << std::format("Alice sends ciphertext: (c1={}, c2={})\n", c1, c2);

    // --------------------------------------------------------
    // Bob decrypts the message
    // Bob uses his private key x to recover the shared secret,
    // then removes it from c2 to get back the original message.
    //
    // Decryption:
    //   s  = c1^x mod p      (recover shared secret: same as y^k)
    //   m  = c2 * s^-1 mod p (unblind the message)
    // --------------------------------------------------------
    std::cout << "\n=== Bob: Decryption ===\n";

    long long s = modExp(c1, x, p);
    long long decrypted = (c2 * modInverse(s, p)) % p;
    std::cout << std::format("Decrypted message: {}\n", decrypted);
    std::cout << std::format("Success: {}\n", decrypted == m ? "yes" : "no");
}
