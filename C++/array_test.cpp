#include <iostream>

char symbols[][8] = {"EUR/USD", "GBP/USD", "USD/JPY", "USD/CHF", "USD/CAD",
                     "AUD/USD", "AUD/JPY", "AUD/NZD", "AUD/CAD", "AUD/CHF",
                     "CAD/CHF", "CAD/JPY", "CHF/JPY", "EUR/AUD", "EUR/CAD",
                     "EUR/CHF", "EUR/GBP", "EUR/JPY", "EUR/NZD", "GBP/JPY",
                     "GBP/AUD", "GBP/CAD", "GBP/CHF", "GBP/NZD", "NZD/CAD",
                     "NZD/CHF", "NZD/USD", "NZD/JPY"};

int main() {
  std::cerr << "sizeof(symbols)" << sizeof(symbols) << "\n";
  std::cerr << "sizeof(symbols[0])" << sizeof(symbols[0]) << "\n";
  for (int i = 0; i < 28; i++) {
    std::cerr << symbols[i] << "\r\n";
  }
  return 0;
}
