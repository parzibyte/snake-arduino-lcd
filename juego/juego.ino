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
#define ALTURA_TABLERO 16
#define ANCHURA_TABLERO 20
#define MAXIMA_LONGITUD_SERPIENTE (ALTURA_TABLERO * ANCHURA_TABLERO)


#define DIRECCION_DERECHA 0
#define DIRECCION_IZQUIERDA 1
#define DIRECCION_ARRIBA 2
#define DIRECCION_ABAJO 3

const int pinX = 0,
          pinY = 1;


LiquidCrystal_I2C pantalla(DIRECCION_LCD, ANCHURA_LCD, ALTURA_LCD);
int prueba[ALTURA_TABLERO][ANCHURA_TABLERO] = {
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


PedazoSerpiente serpiente[MAXIMA_LONGITUD_SERPIENTE];
int longitudSerpiente = 0;
int direccion = DIRECCION_DERECHA;

int comidaX, comidaY;
int puntaje = 0;

int obtenerDireccion() {

  int valorX = analogRead(pinX),
      valorY = analogRead(pinY);
  if (valorX > 900) {
    return DIRECCION_IZQUIERDA;
  } else if (valorX < 400) {
    return DIRECCION_DERECHA;
  }

  if (valorY > 900) {
    return DIRECCION_ARRIBA;
  } else if (valorY < 400) {
    return DIRECCION_ABAJO;
  }
  return -1;
}

void cambiarDireccion(int nuevaDireccion) {
  if (
    nuevaDireccion != DIRECCION_DERECHA
    && nuevaDireccion != DIRECCION_IZQUIERDA
    && nuevaDireccion != DIRECCION_ARRIBA
    && nuevaDireccion != DIRECCION_ABAJO
  ) {
    return;
  }
  if (
    (nuevaDireccion == DIRECCION_DERECHA || nuevaDireccion == DIRECCION_IZQUIERDA)
    && (direccion == DIRECCION_DERECHA || direccion == DIRECCION_IZQUIERDA)
  ) return;

  if (
    (nuevaDireccion == DIRECCION_ARRIBA || nuevaDireccion == DIRECCION_ABAJO)
    && (direccion == DIRECCION_ARRIBA || direccion == DIRECCION_ABAJO)
  ) return;

  direccion = nuevaDireccion;
}

void agregarPedazo(int x, int y) {
  if (longitudSerpiente >= MAXIMA_LONGITUD_SERPIENTE) return;
  if (x + 1 >= ANCHURA_TABLERO || x < 0)return;
  if (y + 1 >= ALTURA_TABLERO || y < 0)return;
  serpiente[longitudSerpiente] = PedazoSerpiente(x, y);
  longitudSerpiente++;
}

void moverSerpiente() {
  for (int i = longitudSerpiente - 1; i >= 1; i--) {
    serpiente[i].x = serpiente[i - 1].x;
    serpiente[i].y = serpiente[i - 1].y;
  }
  switch (direccion) {
    case DIRECCION_DERECHA:
      if (serpiente[0].x + 1 >= ANCHURA_TABLERO)serpiente[0].x = 0;
      else serpiente[0].x++;
      break;
    case DIRECCION_IZQUIERDA:
      if (serpiente[0].x <= 0)serpiente[0].x = ANCHURA_TABLERO - 1;
      else serpiente[0].x--;
      break;
    case DIRECCION_ARRIBA:
      if (serpiente[0].y <= 0)serpiente[0].y = ALTURA_TABLERO - 1;
      else serpiente[0].y--;
      break;
    case DIRECCION_ABAJO:
      if (serpiente[0].y + 1 >= ALTURA_TABLERO)serpiente[0].y = 0;
      else serpiente[0].y++;
      break;
  }
}

void colocarSerpienteEnMatriz() {
  for (int i = 0; i < longitudSerpiente; i++) {
    int x = serpiente[i].y,
        y = serpiente[i].x;
    prueba[x][y] = 1;
  }
}

void randomizarComida() {

  comidaX = random(0, ANCHURA_TABLERO);
  comidaY = random(0, ALTURA_TABLERO);
}

void acomodarComida() {
  prueba[comidaY][comidaX] = 1;
}



void setup() {
  randomSeed(analogRead(0));
  Serial.begin(9600);
  pantalla.init();
  pantalla.backlight();
  for (int i = 0; i < 3; i++) {
    agregarPedazo(5, i);
  }

  randomizarComida();

}

void dibujarPuntaje() {
  pantalla.setCursor(6, 0);
  pantalla.print("SCORE");
  pantalla.setCursor(6, 1);
  pantalla.print(puntaje);
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

void limpiarMatriz() {

  for (int y = 0; y < 16; y++) {
    for (int x = 0; x < 20; x++) {
      prueba[y][x] = 0;
    }
  }
}

bool colisionaConComida() {
  return serpiente[0].x == comidaX && serpiente[0].y == comidaY;
}

void loop() {
  limpiarMatriz();
  cambiarDireccion(obtenerDireccion());
  moverSerpiente();
  colocarSerpienteEnMatriz();
  acomodarComida();
  dibujarMatriz();
  if (colisionaConComida()) {
    puntaje++;
    randomizarComida();
    agregarPedazo(0, 0);
  }

  dibujarPuntaje();
  delay(100);

}
