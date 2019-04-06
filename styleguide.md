# Style guide

## Functies
Functies worden benoemd in `snake_case()` indien ze uit meerdere woorden bestaan.
Ze krijgen best een prefix om aan te duiden waartoe ze behoren,
bijvoorbeeld `led_init()`.

### Constructors
Constructors zijn shortcutfuncties om snel een `struct` aan te maken, bv:
```C
typedef struct Led {
  uint8_t intensity;
  uint8_t blue;
  uint8_t green;
  uint8_t red;
} Led;

Led led(uint8_t i, uint8_t b, uint8_t g, uint8_t r);
```
Ze hebben steeds dezelfde naam als de `struct`,
maar dan in kleine letters.

## Structs
Structs worden benoemd in `PascalCase`.
Ze hebben best steeds een constructor,
de `typedef` bevind zich in de header file.

## Commentaar
Wanneer uit de naam van een functie niet duidelijk is wat deze doet,
moet er _in de headerfile_ commentaar bij de functie staan
met een verklaring van argumenten en doel.
Het moet mogelijk zijn om enkel uit de headerfile te bepalen welke Functies
je nodig hebt, wat deze doen, en welke argumenten ze nodig hebben.
Idealiter is commentaar daar niet nodig, maar dat is niet haalbaar.

Commentaar in code enkel bij stukken code die niet onmiddelijk duidelijk zijn.

## Organisatie
Headerfiles gaan in `include/`, C bestanden in `src/`.
Indien een stuk code volledig onafhankelijk is van de rest,
kan het als een _library_ in `lib/` geplaatst worden.
Libraries kan je importeren als `#include <Librarynaam.h>`,
gewone headerfiles als `#include "headerfile.h"`.
