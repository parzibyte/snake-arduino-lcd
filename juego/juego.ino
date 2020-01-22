/*

    Programado por Luis Cabrera Benito
   ____          _____               _ _           _
  |  _ \        |  __ \             (_) |         | |
  | |_) |_   _  | |__) |_ _ _ __ _____| |__  _   _| |_ ___
  |  _ <| | | | |  ___/ _` | '__|_  / | '_ \| | | | __/ _ \
  | |_) | |_| | | |  | (_| | |   / /| | |_) | |_| | ||  __/
  |____/ \__, | |_|   \__,_|_|  /___|_|_.__/ \__, |\__\___|
         __/ |                               __/ |
        |___/                               |___/


    Blog:       https://parzibyte.me/blog
    Ayuda:      https://parzibyte.me/blog/contrataciones-ayuda/
    Contacto:   https://parzibyte.me/blog/contacto/
*/
#include <LiquidCrystal_I2C.h>

#define ANCHURA_LCD 16
#define ALTURA_LCD 2
#define DIRECCION_LCD 0x3F // Si no sabes la dirección, visita https://parzibyte.me/blog/2018/02/02/obtener-direccion-modulo-i2c-lcd-arduino/
LiquidCrystal_I2C pantalla(DIRECCION_LCD, ANCHURA_LCD, ALTURA_LCD);
int prueba[16][20] = {
  {0, 0, 0, 0, 0,/*  */0, 0, 0, 0, 0, /*  */0, 0, 0, 0, 0,/*  */0, 0, 0, 0, 0,},
  {0, 0, 0, 0, 0,/*  */0, 0, 0, 0, 0, /*  */0, 0, 0, 0, 0,/*  */0, 0, 0, 0, 0,},
  {0, 0, 0, 0, 0,/*  */0, 0, 0, 0, 0, /*  */0, 0, 0, 0, 0,/*  */0, 0, 0, 0, 0,},
  {0, 0, 0, 0, 0,/*  */0, 0, 0, 0, 0, /*  */0, 0, 0, 0, 0,/*  */0, 0, 0, 0, 0,},
  {0, 0, 0, 0, 0,/*  */0, 0, 0, 0, 0, /*  */0, 0, 0, 0, 0,/*  */0, 0, 0, 0, 0,},
  {0, 0, 0, 0, 0,/*  */0, 0, 0, 0, 0, /*  */0, 0, 0, 0, 0,/*  */0, 0, 0, 0, 0,},
  {0, 0, 0, 0, 0,/*  */0, 0, 0, 0, 0, /*  */0, 0, 0, 0, 0,/*  */0, 0, 0, 0, 0,},
  {0, 0, 0, 0, 0,/*  */0, 0, 0, 0, 0, /*  */0, 0, 0, 0, 0,/*  */0, 0, 0, 0, 0,},

  /***************************************************************************/
  {0, 0, 0, 0, 0,/*  */0, 0, 0, 0, 0, /*  */0, 0, 0, 0, 0,/*  */0, 0, 0, 0, 0,},
  {0, 0, 0, 0, 0,/*  */0, 0, 0, 0, 0, /*  */0, 0, 0, 0, 0,/*  */0, 0, 0, 0, 0,},
  {0, 0, 0, 0, 0,/*  */0, 0, 0, 0, 0, /*  */0, 0, 0, 0, 0,/*  */0, 0, 0, 0, 0,},
  {0, 0, 0, 0, 0,/*  */0, 0, 0, 0, 0, /*  */0, 0, 0, 0, 0,/*  */0, 0, 0, 0, 0,},
  {0, 0, 0, 0, 0,/*  */0, 0, 0, 0, 0, /*  */0, 0, 0, 0, 0,/*  */0, 0, 0, 0, 0,},
  {0, 0, 0, 0, 0,/*  */0, 0, 0, 0, 0, /*  */0, 0, 0, 0, 0,/*  */0, 0, 0, 0, 0,},
  {0, 0, 0, 0, 0,/*  */0, 0, 0, 0, 0, /*  */0, 0, 0, 0, 0,/*  */0, 0, 0, 0, 0,},
  {0, 0, 0, 0, 0,/*  */0, 0, 0, 0, 0, /*  */0, 0, 0, 0, 0,/*  */0, 0, 0, 0, 0,},
};

class PedazoSerpiente {
  public:
    int x, y;

    PedazoSerpiente(int a, int b) {
      x = a; y = b;
    }

    PedazoSerpiente() {
    }
};
const int MAXIMA_LONGITUD_SERPIENTE = 16 * 20;

PedazoSerpiente serpiente[MAXIMA_LONGITUD_SERPIENTE];
int longitudSerpiente = 0;


void agregarPedazo(int x, int y) {
  if (longitudSerpiente >= MAXIMA_LONGITUD_SERPIENTE) return;
  serpiente[longitudSerpiente] = PedazoSerpiente(x, y);
  longitudSerpiente++;
}

void colocarSerpienteEnMatriz() {
  for (int i = 0; i < longitudSerpiente; i++) {
    int x = serpiente[i].x,
        y = serpiente[i].y;
    prueba[x][y] = 1;
  }
}

void setup() {
  pantalla.init();
  pantalla.backlight();

  for (int i = 0; i < 20; i++) {
    agregarPedazo(5, i);
    colocarSerpienteEnMatriz();
    dibujarMatriz();
    dibujarPuntaje();
    delay(100);
  }


}

void dibujarPuntaje() {
  pantalla.setCursor(6, 0);
  pantalla.print("SCORE");
  pantalla.setCursor(6, 1);
  pantalla.print("666");
}

void dibujarMatriz() {
  pantalla.clear();
  byte figura[8];
  int numeroFigura = 0;
  for (int cuadritoX = 0; cuadritoX < 4; cuadritoX++) {
    for (int cuadritoY = 0; cuadritoY < 2; cuadritoY++) {
      for (int x = 0; x < 8; x++) {
        int numero = 0;
        int indice = cuadritoY == 0 ? x : (x + 8);
        int inicio = cuadritoX * 5;
        // Quién te conoce math.pow
        if (prueba[indice][inicio + 0] == 1)numero += 16;
        if (prueba[indice][inicio + 1] == 1)numero += 8;
        if (prueba[indice][inicio + 2] == 1)numero += 4;
        if (prueba[indice][inicio + 3] == 1)numero += 2;
        if (prueba[indice][inicio + 4] == 1)numero += 1;

        ///
        figura[x] = numero;
      }


      pantalla.createChar(numeroFigura, figura);
      pantalla.setCursor(cuadritoX, cuadritoY); // X, Y
      pantalla.write(byte(numeroFigura));
      numeroFigura++;
    }
  }


}

void loop() {



}
