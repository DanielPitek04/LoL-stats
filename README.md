# Projekt: League of Legends Štatistiky

Program napísaný v jazyku C, ktorý umožňuje vypočítať štatistiky z LoL a zobraziť 
ich v podobe štyroch tabuliek a jedného SVG grafu.

## Štruktúra projektu

Projekt sa skladá z troch C súborov, dvoch hlavičkových súborov a jedného makefile

- `lolstatsproj.c` – súbor obsahujúci hlavnú logiku programu

- `nacitat.h` – hlavičkový súbor, v ktorom sú definované štruktúry, globálne premenné a metódy pre nacitat.c
- `nacitat.c` – súbor zodpovedný za načítanie a spracovanie vstupných dát

- `html.h` - hlavičkový súbor, ktorý obsahuje cestu k výpočtu štatistík v rámci metódy
- `html.c` – súbor na generovanie výstupnej HTML stránky.

- `makefile` – súbor na zlinkovanie súborov a vytvorenia spustiteľného súboru

## Požiadavky

Pred spustením projektu sa uistite, že máte nainštalované nasledujúce nástroje:

- **GCC**: Pre kompiláciu C súborov
- **Make**: Pre kompilovanie projektu

## Inštalácia a spustenie

1. Otvorte terminál (bash)
2. Uistite sa, že máte všetky súbory projektu v rovnakom adresári
3. Spustite nasledujúci príkaz na skompilovanie projektu:
    
    - make
    
   Tento príkaz vytvorí spustiteľný súbor s názvom `lolstats`
   
4. Na spustenie programu použite príkaz:
    
    - ./lolstats zaznamy.txt hraci.txt stats.html
    
   - `zaznamy.txt` – vstupný súbor obsahujúci zápisy zo zápasov
   - `hraci.txt` – vstupný súbor obsahujúci zoznam hráčov
   - `stats.html` – výstupný súbor, kde bude generovaný HTML report s štatistikami



