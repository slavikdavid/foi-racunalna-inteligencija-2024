# Vježba 1 iz kolegija Računalna inteligencija

<strong>Autor</strong>: David Slavik - 0016148382

<strong>Zadatak</strong>: 1a

## Opis zadatka

Napisati program koji standardnim PSO-om minimizira funkciju `funkcijaA()` za raspon ulazne varijable x ∈ [2, 6]. Definicija funkcije `funkcijaA()` navedena je ispod zadatka. Kao predložak dozvoljeno je koristiti program koji smo radili na seminarima i koji je u dorađenom obliku dostupan na stranicama predmeta. Algoritam treba imati upravljanje granicama tehnikom vraćanje na rub.

```c++
double funkcijaA(double x)
{
      double fx = 0.2 * (x - 2.0) * sin(7.0 * x - 15.0) + 1;
      if (fx >= 1.0)
        fx = cos(2.0 / (pow(x - 6.0, 2.0) + 1.0)) + 0.7;
      return fx;

}
```

Autor je program realizirao koristeći programski jezik C++ te datoteku zaglavlja `matplotlibcpp.h` za grafički prikaz.

Repozitorij biblioteke: <a target="_blank" href="https://github.com/lava/matplotlib-cpp">https://github.com/lava/matplotlib-cpp</a>

## Vizualizacija

Za vizualizaciju korišteno je `matplotlib` sučelje za programski jezik C++ (`matplotlibcpp.h` datoteka zaglavlja). Ova datoteka zaglavlja ovisna je o `Python.h` zaglavlju koje se dobiva instalacijom paketa `python2-dev` odnosno `python3-dev`.

## Kompajliranje i pokretanje programa

Pri prevođenju programa potrebno je specificirati direktorij u kojemu je instalirana željena Python verzija.

U slučaju verzije Python 3.10, program se prevodi na sljedeći način:

`g++ -o vj1.out vj1.cpp -I/usr/include/python3.10 -lpython3.10`

Za pokretanje programa dovoljno je u konzolu napisati:

`./vj1.out`

## Prekidanje programa

Program hvata signale i moguće ga je prijevremeno ugasiti kombinacijom tipki

`CTRL` + `C`,

`CTRL` + `Ž` ili

`CTRL` + `Z`.

Gašenjem programa gasi se i instanca matplotliba.
