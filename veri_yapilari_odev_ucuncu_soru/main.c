#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ALFABE 26

// Trie düğümü tanımı
typedef struct TrieDugumu {
    struct TrieDugumu *harfler[ALFABE];
    bool kelimeSonuMu; // Bu düğüm bir kelimenin sonunu mu temsil ediyor?
} TrieDugumu;

// Yeni düğüm oluşturma
TrieDugumu* yeniTrieDugumu() {
    TrieDugumu *dugum = (TrieDugumu*)malloc(sizeof(TrieDugumu));
    if (dugum) {
        dugum->kelimeSonuMu = false;
        for (int i = 0; i < ALFABE; i++)
            dugum->harfler[i] = NULL;
    }
    return dugum;
}

// Trie'ye kelime ekleme
void trieKelimeEkle(TrieDugumu *kok, const char *kelime) {
    TrieDugumu *gezici = kok;
    while (*kelime) {
        int index = *kelime - 'a';
        if (!gezici->harfler[index])
            gezici->harfler[index] = yeniTrieDugumu();
        gezici = gezici->harfler[index];
        kelime++;
    }
    gezici->kelimeSonuMu = true;
}

// Trie'de kelime arama
bool trieKelimeAra(TrieDugumu *kok, const char *kelime) {
    TrieDugumu *gezici = kok;
    while (*kelime) {
        int index = *kelime - 'a';
        if (!gezici->harfler[index])
            return false;
        gezici = gezici->harfler[index];
        kelime++;
    }
    return gezici != NULL && gezici->kelimeSonuMu;
}

// Örnek kullanım
int main() {
    TrieDugumu *kok = yeniTrieDugumu();

    trieKelimeEkle(kok, "cat");
    trieKelimeEkle(kok, "car");
    trieKelimeEkle(kok, "dog");

    printf("Arama sonucu (cat): %s\n", trieKelimeAra(kok, "cat") ? "Bulundu" : "Bulunamadı");
    printf("Arama sonucu (emre): %s\n", trieKelimeAra(kok, "emre") ? "Bulundu" : "Bulunamadi");
    printf("Arama sonucu (dog): %s\n", trieKelimeAra(kok, "dog") ? "Bulundu" : "Bulunamadi");

    return 0;
}
