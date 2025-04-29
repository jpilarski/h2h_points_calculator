# H2H Points Calculator

Ten projekt odpowiada na pytanie:  
**„Co, gdyby punkty w Ekstraklasie przyznawać na podstawie wyników dwumeczy między zainteresowanymi drużynami?”**

## Przykładowe porównanie

Poniższa tabela ilustruje, jak zmieniłaby się liczba punktów:

| 1. mecz | 2. mecz | Punkty A | Punkty B | Dwumecz | Nowe punkty A | Nowe punkty B |
|:-------:|:-------:|:--------:|:--------:|:-------:|:-------------:|:-------------:|
|  3–0    |   0–2   |    3     |    3     |   3–2   |       3       |       0       |
|  1–0    |   0–1   |    3     |    3     |   1–1   |       1       |       1       |
|  1–1    |   0–2   |    1     |    4     |   1–3   |       0       |       3       |
|  3–1    |   2–0   |    6     |    0     |   5–1   |       3       |       0       |
|  0–0    |   2–2   |    2     |    2     |   2–2   |       1       |       1       |

## Wymagane pliki wejściowe

### `teams.csv`

Zawiera dane drużyn w formacie:

```
id_drużyny,nazwa_drużyny
```

Przykład:

```
12,Poznaniak Poznań
21,Warszawiak Warszawa
97,Gdańszczanin Gdańsk
```

### `results.csv`

Zawiera dane o rozegranych meczach w formacie:

```
id_gospodarzy,id_gości,bramki_gospodarzy,bramki_gości
```

Przykład:

```
12,21,2,0
21,97,0,0
97,12,1,3
21,12,3,1
97,21,1,0
12,97,1,1
```

## Wynik

W wyniku powstaje plik `table.csv`, który zawiera następujące dane:

```
nazwa_drużyny,liczba_punktów,bramki_zdobyte,bramki_stracone,różnica_bramek
```

Tabela jest posortowane według punktów, różnicy bramek i bramek strzelonych:

```
Poznaniak Poznań,4,7,5,2
Gdańszczanin Gdańsk,3,3,4,-1
Warszawiak Warszawa,1,3,4,-1
```

##  Technologie
- C++

Projekt będzie rozwijany.