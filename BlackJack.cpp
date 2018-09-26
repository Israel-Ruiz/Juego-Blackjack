#include<time.h>
#include<allegro.h>
#include<stdio.h>
#define height 600
#define width 800


typedef struct tcarta
              {
                  int valor;
                  int numero;
                  struct tcarta *siguiente;
              }cartas;
typedef cartas *pNodo;
typedef cartas *Pila;

void Push(Pila *pila, int n);
int Pop(Pila *pila);

int main ()
   {
       //INICIALIZACION
       allegro_init();
       install_keyboard();
       install_mouse();
       set_color_depth(32);
       set_gfx_mode( GFX_AUTODETECT_WINDOWED , width , height , 0 , 0 );
       set_window_title("BLACKJACK");
       install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
       set_display_switch_mode(SWITCH_BACKGROUND);
       srand(time(NULL));
       FONT *font = load_font("font.pcx", NULL, NULL);
       FILE *dolares;
       SAMPLE *blackjack = load_wav("blackjack.wav");

       //BUFFER Y BITMAPS
       BITMAP *buffer = create_bitmap(width, height);
       BITMAP *main = load_bitmap("MAIN.bmp", NULL);
       BITMAP *cursor = load_bitmap("cursor.bmp", NULL);
       BITMAP *jugar = load_bitmap("jugar.bmp", NULL);
       BITMAP *salir = load_bitmap("salir.bmp", NULL);
       BITMAP *logo = load_bitmap("logo.bmp", NULL);
       BITMAP *fondo = load_bitmap("fondo.bmp", NULL);
       BITMAP *otra = load_bitmap("otra.bmp", NULL);
       BITMAP *otra2 = load_bitmap("otra2.bmp", NULL);
       BITMAP *apostar = load_bitmap("apostar.bmp", NULL);
       BITMAP *apostar2 = load_bitmap("apostar2.bmp", NULL);
       //CARTAS TREBOL
       BITMAP *atras = load_bitmap("cartas/trasero.bmp", NULL);
       BITMAP *carta[52];
       carta[0] = load_bitmap("cartas/astrevoles.bmp", NULL);
       carta[1] = load_bitmap("cartas/2trevoles.bmp", NULL);
       carta[2] = load_bitmap("cartas/3trevoles.bmp", NULL);
       carta[3] = load_bitmap("cartas/4trevoles.bmp", NULL);
       carta[4] = load_bitmap("cartas/5trevoles.bmp", NULL);
       carta[5] = load_bitmap("cartas/6trevoles.bmp", NULL);
       carta[6] = load_bitmap("cartas/7trevoles.bmp", NULL);
       carta[7] = load_bitmap("cartas/8trevoles.bmp", NULL);
       carta[8] = load_bitmap("cartas/9trevoles.bmp", NULL);
       carta[9] = load_bitmap("cartas/10trevoles.bmp", NULL);
       carta[10] = load_bitmap("cartas/jtrevoles.bmp", NULL);
       carta[11] = load_bitmap("cartas/qtrevoles.bmp", NULL);
       carta[12] = load_bitmap("cartas/ktrevoles.bmp", NULL);
       //CARTAS DIAMANTE
       carta[13] = load_bitmap("cartas/asdiamantes.bmp", NULL);
       carta[14] = load_bitmap("cartas/2diamantes.bmp", NULL);
       carta[15] = load_bitmap("cartas/3diamantes.bmp", NULL);
       carta[16] = load_bitmap("cartas/4diamantes.bmp", NULL);
       carta[17] = load_bitmap("cartas/5diamantes.bmp", NULL);
       carta[18] = load_bitmap("cartas/6diamantes.bmp", NULL);
       carta[19] = load_bitmap("cartas/7diamantes.bmp", NULL);
       carta[20] = load_bitmap("cartas/8diamantes.bmp", NULL);
       carta[21] = load_bitmap("cartas/9diamantes.bmp", NULL);
       carta[22] = load_bitmap("cartas/10diamantes.bmp", NULL);
       carta[23] = load_bitmap("cartas/jdiamantes.bmp", NULL);
       carta[24] = load_bitmap("cartas/qdiamantes.bmp", NULL);
       carta[25] = load_bitmap("cartas/kdiamantes.bmp", NULL);
       //CARTAS ESPADA
       carta[26] = load_bitmap("cartas/asespadas.bmp", NULL);
       carta[27] = load_bitmap("cartas/2espadas.bmp", NULL);
       carta[28] = load_bitmap("cartas/3espadas.bmp", NULL);
       carta[29] = load_bitmap("cartas/4espadas.bmp", NULL);
       carta[30] = load_bitmap("cartas/5espadas.bmp", NULL);
       carta[31] = load_bitmap("cartas/6espadas.bmp", NULL);
       carta[32] = load_bitmap("cartas/7espadas.bmp", NULL);
       carta[33] = load_bitmap("cartas/8espadas.bmp", NULL);
       carta[34] = load_bitmap("cartas/9espadas.bmp", NULL);
       carta[35] = load_bitmap("cartas/10espadas.bmp", NULL);
       carta[36] = load_bitmap("cartas/jespadas.bmp", NULL);
       carta[37] = load_bitmap("cartas/qespadas.bmp", NULL);
       carta[38] = load_bitmap("cartas/kespadas.bmp", NULL);
       //CARTAS CORAZON
       carta[39] = load_bitmap("cartas/ascorazones.bmp", NULL);
       carta[40] = load_bitmap("cartas/2corazones.bmp", NULL);
       carta[41] = load_bitmap("cartas/3corazones.bmp", NULL);
       carta[42] = load_bitmap("cartas/4corazones.bmp", NULL);
       carta[43] = load_bitmap("cartas/5corazones.bmp", NULL);
       carta[44] = load_bitmap("cartas/6corazones.bmp", NULL);
       carta[45] = load_bitmap("cartas/7corazones.bmp", NULL);
       carta[46] = load_bitmap("cartas/8corazones.bmp", NULL);
       carta[47] = load_bitmap("cartas/9corazones.bmp", NULL);
       carta[48] = load_bitmap("cartas/10corazones.bmp", NULL);
       carta[49] = load_bitmap("cartas/jcorazones.bmp", NULL);
       carta[50] = load_bitmap("cartas/qcorazones.bmp", NULL);
       carta[51] = load_bitmap("cartas/kcorazones.bmp", NULL);
       BITMAP *C = load_bitmap("1.bmp", NULL);
       SAMPLE *C2 = load_wav("1.wav");
       SAMPLE *C3 = load_wav("1a.wav");
       BITMAP *P = load_bitmap("2.bmp", NULL);
       SAMPLE *P2 = load_wav("2.wav");

       //VARIABLES
       int m=1;//PARA CONTROLAR EL MENU Y EL JUEGO, COMIENZA EN 1
       int x=0, y=0;//PARA CONTROLAR LA POSICION DEL LOGO
       int a=1;//PARA CONTROLAR LA ANIMACION DEL LOGO, COMIENZA EN 1
       int b=0, p=0;//CONTADOR PARA BARAJAR CARTAS
       int n;//NUMERO ALEATORIO
       int x2=0, y2=0;//PARA CONTROLAR LA POSICION DE LA BARAJA
       int bj=1, j;//CONTROLA EL JUEGO
       int ac=1, dc=1;//CONTROLA LOS JUGADORES
       int x3=320, y3=100;//POSICION DE LAS CARTAS DE LA CASA
       int n1, n2, n3, n4, n5, n6, n7, n8;//PARA LAS CARTAS VOLTEADAS
       int x4=230, y4=380;
       int puntaje;//PUNTAJE JUGADOR
       int puntaje2;
       int puntaje3;
       int puntajec;//PUNTAJE COMPUTADORA
       int puntajec2;
       int puntajec3;
       int apuesta;//SE LEERA LA CANTIDAD DEL ARCHIVO, DINERO DISPONIBLE
       Pila pila = NULL;
       cartas c[52];
       //VALOR CARTAS TREBOLcargando
       c[0].valor = 1;
       c[1].valor = 2;
       c[2].valor = 3;
       c[3].valor = 4;
       c[4].valor = 5;
       c[5].valor = 6;
       c[6].valor = 7;
       c[7].valor = 8;
       c[8].valor = 9;
       c[9].valor = 10;
       c[10].valor = 10;
       c[11].valor = 10;
       c[12].valor = 10;
       //VALOR CARTAS DIAMANTE
       c[13].valor = 1;
       c[14].valor = 2;
       c[15].valor = 3;
       c[16].valor = 4;
       c[17].valor = 5;
       c[18].valor = 6;
       c[19].valor = 7;
       c[20].valor = 8;
       c[21].valor = 9;
       c[22].valor = 10;
       c[23].valor = 10;
       c[24].valor = 10;
       c[25].valor = 10;
       //VALOR CARTAS ESPADA
       c[26].valor = 1;
       c[27].valor = 2;
       c[28].valor = 3;
       c[29].valor = 4;
       c[30].valor = 5;
       c[31].valor = 6;
       c[32].valor = 7;
       c[33].valor = 8;
       c[34].valor = 9;
       c[35].valor = 10;
       c[36].valor = 10;
       c[37].valor = 10;
       c[38].valor = 10;
       //VALOR CARTAS CORAZON
       c[39].valor = 1;
       c[40].valor = 2;
       c[41].valor = 3;
       c[42].valor = 4;
       c[43].valor = 5;
       c[44].valor = 6;
       c[45].valor = 7;
       c[46].valor = 8;
       c[47].valor = 9;
       c[48].valor = 10;
       c[49].valor = 10;
       c[50].valor = 10;
       c[51].valor = 10;
       dolares = fopen("dolares.txt", "a+");
       fscanf(dolares, "%ld", &apuesta);//SE LEE EL ARCHIVO CON LOS DOLARES
       fclose(dolares);
       play_sample(blackjack, 80, 0, 1000, 1);
       while (m!=0)
            {
                //MENU PRINCIPAL
                while (m==1)
                     {
                         if (mouse_x > 320 && mouse_x < 480 && mouse_y > 240 && mouse_y < 300)
                           {
                               masked_blit(jugar, buffer, 0, 0, 0, 0, width, height);
                               masked_blit(cursor, buffer, 0, 0, mouse_x, mouse_y, 20, 25);
                               blit(buffer, screen, 0, 0, 0, 0, width, height);
                               if (mouse_b & 1)
                                  {
                                      m=2;//BANDERA PARA PASAR AL JUEGO
                                  }
                           }
                          else if (mouse_x > 340 && mouse_x < 460 && mouse_y > 300 && mouse_y < 340)
                           {
                               masked_blit(salir, buffer, 0, 0, 0, 0, width, height);
                               masked_blit(cursor, buffer, 0, 0, mouse_x, mouse_y, 20, 25);
                               blit(buffer, screen, 0, 0, 0, 0, width, height);
                               if (mouse_b & 1)
                                  {
                                      m=0;//BANDERA PARA SALIR DEL JUEGO
                                  }
                           }
                          else
                           {
                               masked_blit(main, buffer, 0, 0, 0, 0, width, height);
                               masked_blit(cursor, buffer, 0, 0, mouse_x, mouse_y, 20, 25);
                               blit(buffer, screen, 0, 0, 0, 0, width, height);
                           }
                     }
                //JUEGO
                while (m==2)
                     {
                         if (a==1)//SOLO SE REPRODUCE LA ANIMACION LA PRIMERA VEZ
                           {
                               for (x=210, y=700; y>=-20; y-=1)
                                  {
                                      masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                      masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                      blit(buffer, screen, 0, 0, 0, 0, width, height);
                                  }

                               for (x2=10, y2=700; y2>=450; y2-=1)
                                  {
                                      masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                      masked_blit(atras, buffer, 0, 0, x2, y2, 150, 201);
                                      masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                      blit(buffer, screen, 0, 0, 0, 0, width, height);
                                  }
                            a=0;//BANDERA PARA QUE NO SE REPITA LA ANIMACION
                           }
                          //GUARDA VALORES ALEATORIOS EN EL VECTOR DE C[]NUMERO
                          for (b=0; b<52;)
                             {
                                 n=rand()%52;
                                 for (p=0; p<52; p++)
                                    {
                                        if (c[p].numero!=n)
                                          {
                                              c[b].numero=n;
                                              b++;
                                              break;
                                          }
                                    }
                             }
                          //GUARDA LOS VALORES EN NUMERO DE LA PILA
                          for (b=0; b<52; b++)
                             {
                                 Push(&pila, c[b].numero);
                             }
                          //ENTREGA DE CARTAS
                          while (bj==1)
                               {
                                   if (ac==1)
                                     {
                                         n1=Pop(&pila);
                                         masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                         masked_blit(atras, buffer, 0, 0, x2, y2, 150, 201);
                                         masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                         masked_blit(carta[n1], buffer, 0, 0, x3, y3, 150, 201);
                                         blit(buffer, screen, 0, 0, 0, 0, width, height);
                                         rest(500);
                                         n2=Pop(&pila);
                                         masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                         masked_blit(atras, buffer, 0, 0, x2, y2, 150, 201);
                                         masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                         masked_blit(atras, buffer, 0, 0, x3+10, y3+10, 150, 201);
                                         masked_blit(carta[n1], buffer, 0, 0, x3, y3, 150, 201);
                                         blit(buffer, screen, 0, 0, 0, 0, width, height);
                                         rest(500);
                                         ac=2;
                                     }
                                   if (dc==1)
                                     {
                                         n3=Pop(&pila);
                                         masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                         masked_blit(atras, buffer, 0, 0, x2, y2, 150, 201);
                                         masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                         masked_blit(atras, buffer, 0, 0, x3+10, y3+10, 150, 201);
                                         masked_blit(carta[n1], buffer, 0, 0, x3, y3, 150, 201);
                                         masked_blit(carta[n3], buffer, 0, 0, x4, y4, 150, 201);
                                         blit(buffer, screen, 0, 0, 0, 0, width, height);
                                         rest(500);
                                         n4=Pop(&pila);
                                         masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                         masked_blit(atras, buffer, 0, 0, x2, y2, 150, 201);
                                         masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                         masked_blit(atras, buffer, 0, 0, x3+10, y3+10, 150, 201);
                                         masked_blit(carta[n1], buffer, 0, 0, x3, y3, 150, 201);
                                         masked_blit(carta[n3], buffer, 0, 0, x4, y4, 150, 201);
                                         masked_blit(carta[n4], buffer, 0, 0, x4+50, y4, 150, 201);
                                         blit(buffer, screen, 0, 0, 0, 0, width, height);
                                         rest(500);
                                         dc=2;
                                     }
                                  //OPERACIONES MATEMATICAS
                                  if (dc==2 && ac==2)
                                    {
                                        puntaje = c[n3].valor + c[n4].valor;
                                        puntajec = c[n1].valor + c[n2].valor;
                                        if (c[n3].valor==1 || c[n4].valor==1)
                                          {
                                              masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                              masked_blit(atras, buffer, 0, 0, x2, y2, 150, 201);
                                              masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                              masked_blit(atras, buffer, 0, 0, x3+10, y3+10, 150, 201);
                                              masked_blit(carta[n1], buffer, 0, 0, x3, y3, 150, 201);
                                              masked_blit(carta[n3], buffer, 0, 0, x4, y4, 150, 201);
                                              masked_blit(carta[n4], buffer, 0, 0, x4+50, y4, 150, 201);
                                               textprintf(buffer, font, 700, 40, palette_color[11], "%d P", puntaje);
                                              textprintf(buffer, font, 700, 80, palette_color[11], "O PUNTAJE: %d", puntaje+10);
                                              textprintf(buffer, font, 0, 10, palette_color[5], "Dolares: %ld", apuesta);
                                              masked_blit(otra, buffer, 0, 0, 610, 450, 170, 30);
                                              masked_blit(apostar, buffer, 0, 0, 630, 490, 135, 25);
                                              masked_blit(cursor, buffer, 0, 0, mouse_x, mouse_y, 20, 25);
                                              blit(buffer, screen, 0, 0, 0, 0, width, height);
                                          }
                                        if (mouse_x > 600 && mouse_x < 780 && mouse_y > 420 && mouse_y < 480)
                                          {
                                              masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                              masked_blit(atras, buffer, 0, 0, x2, y2, 150, 201);
                                              masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                              masked_blit(atras, buffer, 0, 0, x3+10, y3+10, 150, 201);
                                              masked_blit(carta[n1], buffer, 0, 0, x3, y3, 150, 201);
                                              masked_blit(carta[n3], buffer, 0, 0, x4, y4, 150, 201);
                                              masked_blit(carta[n4], buffer, 0, 0, x4+50, y4, 150, 201);
                                               textprintf(buffer, font, 700, 40, palette_color[11], "%d P", puntaje);
                                                textprintf(buffer, font, 0, 10, palette_color[5], "Dolares: %ld", apuesta);
                                              if (c[n3].valor==1 || c[n4].valor==1)
                                                {
                                                    textprintf(buffer, font, 700, 80, palette_color[11], "O %d", puntaje+10);
                                                }
                                              masked_blit(otra2, buffer, 0, 0, 610, 450, 170, 30);
                                              masked_blit(apostar, buffer, 0, 0, 630, 490, 135, 25);
                                              masked_blit(cursor, buffer, 0, 0, mouse_x, mouse_y, 20, 25);
                                              blit(buffer, screen, 0, 0, 0, 0, width, height);
                                              //VALIDACION A'S 11 O 1
                                              if (mouse_b & 1)
                                                {
                                                    bj=2;//LE DA OTRA CARTA
                                                }
                                          }
                                         else if (mouse_x > 620 && mouse_x < 770 && mouse_y > 450 && mouse_y < 520)
                                          {
                                              masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                              masked_blit(atras, buffer, 0, 0, x2, y2, 150, 201);
                                              masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                              masked_blit(atras, buffer, 0, 0, x3+10, y3+10, 150, 201);
                                              masked_blit(carta[n1], buffer, 0, 0, x3, y3, 150, 201);
                                              masked_blit(carta[n3], buffer, 0, 0, x4, y4, 150, 201);
                                              masked_blit(carta[n4], buffer, 0, 0, x4+50, y4, 150, 201);
                                                textprintf(buffer, font, 700, 40, palette_color[11], "%d P", puntaje);
                                              textprintf(buffer, font, 0, 10, palette_color[5], "Dolares: %ld", apuesta);
                                               if (c[n3].valor==1 || c[n4].valor==1)
                                                {
                                                    textprintf(buffer, font, 700, 80, palette_color[11], "O %d", puntaje+10);
                                                }
                                              masked_blit(otra, buffer, 0, 0, 610, 450, 170, 30);
                                              masked_blit(apostar2, buffer, 0, 0, 630, 490, 135, 25);
                                              masked_blit(cursor, buffer, 0, 0, mouse_x, mouse_y, 20, 25);
                                              blit(buffer, screen, 0, 0, 0, 0, width, height);
                                              if (mouse_b & 1)
                                                {
                                                    bj=0;//PASA A LA OPCION DE APOSTAR
                                                    j=1;
                                                }
                                          }
                                         else
                                          {
                                              masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                              masked_blit(atras, buffer, 0, 0, x2, y2, 150, 201);
                                              masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                              masked_blit(atras, buffer, 0, 0, x3+10, y3+10, 150, 201);
                                              masked_blit(carta[n1], buffer, 0, 0, x3, y3, 150, 201);
                                              masked_blit(carta[n3], buffer, 0, 0, x4, y4, 150, 201);
                                              masked_blit(carta[n4], buffer, 0, 0, x4+50, y4, 150, 201);
                                            textprintf(buffer, font, 700, 40, palette_color[11], "%d P", puntaje);
                                                textprintf(buffer, font, 0, 10, palette_color[5], "Dolares: %ld", apuesta);
                                              if (c[n3].valor==1 || c[n4].valor==1)
                                                {
                                                    textprintf(buffer, font, 700, 80, palette_color[11], "O %d", puntaje+10);
                                                }
                                              masked_blit(otra, buffer, 0, 0, 610, 450, 170, 30);
                                              masked_blit(apostar, buffer, 0, 0, 630, 490, 135, 25);
                                              masked_blit(cursor, buffer, 0, 0, mouse_x, mouse_y, 20, 25);
                                              blit(buffer, screen, 0, 0, 0, 0, width, height);
                                          }
                                     //BLACKJACK AUTOMATICO
                                     if (c[n1].valor==1 || c[n2].valor==1 || c[n3].valor==1 || c[n4].valor==1)
                                       {
                                           if (puntaje==11 || puntajec==11)
                                             {
                                                 bj=0;
                                                 j=1;
                                             }
                                       }
                                    }
                               }
                          //OTRA CARTA
                          while (bj==2)
                               {
                                   if (ac==2)
                                     {
                                         n5=Pop(&pila);
                                         masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                         masked_blit(atras, buffer, 0, 0, x2, y2, 150, 201);
                                         masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                         masked_blit(atras, buffer, 0, 0, x3+10, y3+10, 150, 201);
                                         masked_blit(carta[n1], buffer, 0, 0, x3, y3, 150, 201);
                                         masked_blit(carta[n5], buffer, 0, 0, x3+50, y3, 150, 201);
                                         masked_blit(carta[n3], buffer, 0, 0, x4, y4, 150, 201);
                                         masked_blit(carta[n4], buffer, 0, 0, x4+50, y4, 150, 201);
                                         blit(buffer, screen, 0, 0, 0, 0, width, height);
                                         rest(500);
                                         ac=3;
                                     }
                                   if (dc==2)
                                     {
                                         n6=Pop(&pila);
                                         masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                         masked_blit(atras, buffer, 0, 0, x2, y2, 150, 201);
                                         masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                         masked_blit(atras, buffer, 0, 0, x3+10, y3+10, 150, 201);
                                         masked_blit(carta[n1], buffer, 0, 0, x3, y3, 150, 201);
                                         masked_blit(carta[n5], buffer, 0, 0, x3+50, y3, 150, 201);
                                         masked_blit(carta[n3], buffer, 0, 0, x4, y4, 150, 201);
                                         masked_blit(carta[n4], buffer, 0, 0, x4+50, y4, 150, 201);
                                         masked_blit(carta[n6], buffer, 0, 0, x4+100, y4, 150, 201);
                                         blit(buffer, screen, 0, 0, 0, 0, width, height);
                                         rest(500);
                                         dc=3;
                                     }
                                   if (dc==3 && ac==3)
                                    {
                                        puntaje2 = puntaje + c[n6].valor;
                                        puntajec2 = puntajec + c[n5].valor;
                                        if (c[n6].valor==1)
                                          {
                                              masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                              masked_blit(atras, buffer, 0, 0, x2, y2, 150, 201);
                                              masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                              masked_blit(atras, buffer, 0, 0, x3+10, y3+10, 150, 201);
                                              masked_blit(carta[n1], buffer, 0, 0, x3, y3, 150, 201);
                                              masked_blit(carta[n5], buffer, 0, 0, x3+50, y3, 150, 201);
                                              masked_blit(carta[n3], buffer, 0, 0, x4, y4, 150, 201);
                                              masked_blit(carta[n4], buffer, 0, 0, x4+50, y4, 150, 201);
                                              masked_blit(carta[n6], buffer, 0, 0, x4+100, y4, 150, 201);
                                              textprintf(buffer, font, 700, 40, palette_color[11], "%d P", puntaje2);
                                              textprintf(buffer, font, 700, 80, palette_color[11], "O %d", puntaje2+10);
                                                textprintf(buffer, font, 0, 10, palette_color[5], "Dolares: %ld", apuesta);
                                              masked_blit(otra, buffer, 0, 0, 610, 450, 170, 30);
                                              masked_blit(apostar, buffer, 0, 0, 630, 490, 135, 25);
                                              masked_blit(cursor, buffer, 0, 0, mouse_x, mouse_y, 20, 25);
                                              blit(buffer, screen, 0, 0, 0, 0, width, height);
                                          }
                                        if (mouse_x > 600 && mouse_x < 780 && mouse_y > 420 && mouse_y < 480)
                                          {
                                              masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                              masked_blit(atras, buffer, 0, 0, x2, y2, 150, 201);
                                              masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                              masked_blit(atras, buffer, 0, 0, x3+10, y3+10, 150, 201);
                                              masked_blit(carta[n1], buffer, 0, 0, x3, y3, 150, 201);
                                              masked_blit(carta[n5], buffer, 0, 0, x3+50, y3, 150, 201);
                                              masked_blit(carta[n3], buffer, 0, 0, x4, y4, 150, 201);
                                              masked_blit(carta[n4], buffer, 0, 0, x4+50, y4, 150, 201);
                                              masked_blit(carta[n6], buffer, 0, 0, x4+100, y4, 150, 201);
                                              textprintf(buffer, font, 700, 40, palette_color[11], "%d P", puntaje2);
                                                textprintf(buffer, font, 0, 10, palette_color[5], "Dolares: %ld", apuesta);;
                                              if (c[n6].valor==1)
                                                {
                                                    textprintf(buffer, font, 700, 80, palette_color[11], "O %d", puntaje2+10);
                                                }
                                              masked_blit(otra2, buffer, 0, 0, 610, 450, 170, 30);
                                              masked_blit(apostar, buffer, 0, 0, 630, 490, 135, 25);
                                              masked_blit(cursor, buffer, 0, 0, mouse_x, mouse_y, 20, 25);
                                              blit(buffer, screen, 0, 0, 0, 0, width, height);
                                              if (mouse_b & 1)
                                                {
                                                    bj=3;//LE DA OTRA CARTA
                                                }
                                          }
                                         else if (mouse_x > 620 && mouse_x < 770 && mouse_y > 450 && mouse_y < 520)
                                          {
                                              masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                              masked_blit(atras, buffer, 0, 0, x2, y2, 150, 201);
                                              masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                              masked_blit(atras, buffer, 0, 0, x3+10, y3+10, 150, 201);
                                              masked_blit(carta[n1], buffer, 0, 0, x3, y3, 150, 201);
                                              masked_blit(carta[n5], buffer, 0, 0, x3+50, y3, 150, 201);
                                              masked_blit(carta[n3], buffer, 0, 0, x4, y4, 150, 201);
                                              masked_blit(carta[n4], buffer, 0, 0, x4+50, y4, 150, 201);
                                              masked_blit(carta[n6], buffer, 0, 0, x4+100, y4, 150, 201);
                                             textprintf(buffer, font, 700, 40, palette_color[11], "%d P", puntaje2);
                                                textprintf(buffer, font, 0, 10, palette_color[5], "Dolares: %ld", apuesta);;
                                              if (c[n6].valor==1)
                                                {
                                                    textprintf(buffer, font, 700, 80, palette_color[11], "O %d", puntaje2+10);
                                                }
                                              masked_blit(otra, buffer, 0, 0, 610, 450, 170, 30);
                                              masked_blit(apostar2, buffer, 0, 0, 630, 490, 135, 25);
                                              masked_blit(cursor, buffer, 0, 0, mouse_x, mouse_y, 20, 25);
                                              blit(buffer, screen, 0, 0, 0, 0, width, height);
                                              if (mouse_b & 1)
                                                {
                                                    bj=0;//PASA A LA OPCION DE APOSTAR
                                                    j=2;
                                                }
                                          }
                                         else
                                          {
                                              masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                              masked_blit(atras, buffer, 0, 0, x2, y2, 150, 201);
                                              masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                              masked_blit(atras, buffer, 0, 0, x3+10, y3+10, 150, 201);
                                              masked_blit(carta[n1], buffer, 0, 0, x3, y3, 150, 201);
                                              masked_blit(carta[n5], buffer, 0, 0, x3+50, y3, 150, 201);
                                              masked_blit(carta[n3], buffer, 0, 0, x4, y4, 150, 201);
                                              masked_blit(carta[n4], buffer, 0, 0, x4+50, y4, 150, 201);
                                              masked_blit(carta[n6], buffer, 0, 0, x4+100, y4, 150, 201);
                                              textprintf(buffer, font, 700, 40, palette_color[11], "%d P", puntaje2);
                                                textprintf(buffer, font, 0, 10, palette_color[5], "Dolares: %ld", apuesta);
                                              if (c[n6].valor==1)
                                                {
                                                    textprintf(buffer, font, 700, 80, palette_color[11], "O %d", puntaje2+10);
                                                }
                                              masked_blit(otra, buffer, 0, 0, 610, 450, 170, 30);
                                              masked_blit(apostar, buffer, 0, 0, 630, 490, 135, 25);
                                              masked_blit(cursor, buffer, 0, 0, mouse_x, mouse_y, 20, 25);
                                              blit(buffer, screen, 0, 0, 0, 0, width, height);
                                          }
                                    }
                                  if (puntaje2>21)
                                    {
                                         textprintf(screen, font, 150, 400, palette_color[6], "TE PASASTE DE LOS 21, PERDISTE");
                                         apuesta-=100;
                                         textprintf(screen, font, 150, 500, palette_color[12], "-100");
                                         rest(3000);
                                         bj=1;m=1;ac=1;dc=1;
                                    }
                                 //BLACKJACK
                                 if (puntaje2==21)
                                    {
                                         bj=0;
                                         j=2;
                                    }
                               }
                          while (bj==3)
                               {
                                   if (ac==3)
                                     {
                                         n7=Pop(&pila);
                                         masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                         masked_blit(atras, buffer, 0, 0, x2, y2, 150, 201);
                                         masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                         masked_blit(atras, buffer, 0, 0, x3+10, y3+10, 150, 201);
                                         masked_blit(carta[n1], buffer, 0, 0, x3, y3, 150, 201);
                                         masked_blit(carta[n5], buffer, 0, 0, x3+50, y3, 150, 201);
                                         masked_blit(carta[n7], buffer, 0, 0, x3+100, y3, 150, 201);
                                         masked_blit(carta[n3], buffer, 0, 0, x4, y4, 150, 201);
                                         masked_blit(carta[n4], buffer, 0, 0, x4+50, y4, 150, 201);
                                         masked_blit(carta[n6], buffer, 0, 0, x4+100, y4, 150, 201);
                                         blit(buffer, screen, 0, 0, 0, 0, width, height);
                                         rest(500);
                                         ac=4;
                                     }
                                   if (dc==3)
                                     {
                                         n8=Pop(&pila);
                                         masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                         masked_blit(atras, buffer, 0, 0, x2, y2, 150, 201);
                                         masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                         masked_blit(atras, buffer, 0, 0, x3+10, y3+10, 150, 201);
                                         masked_blit(carta[n1], buffer, 0, 0, x3, y3, 150, 201);
                                         masked_blit(carta[n5], buffer, 0, 0, x3+50, y3, 150, 201);
                                         masked_blit(carta[n7], buffer, 0, 0, x3+100, y3, 150, 201);
                                         masked_blit(carta[n3], buffer, 0, 0, x4, y4, 150, 201);
                                         masked_blit(carta[n4], buffer, 0, 0, x4+50, y4, 150, 201);
                                         masked_blit(carta[n6], buffer, 0, 0, x4+100, y4, 150, 201);
                                         masked_blit(carta[n8], buffer, 0, 0, x4+150, y4, 150, 201);
                                         blit(buffer, screen, 0, 0, 0, 0, width, height);
                                         rest(500);
                                         dc=4;
                                     }
                                   if (dc==4 && ac==4)
                                    {
                                        puntaje3 = puntaje2 + c[n8].valor;
                                        puntajec3 = puntaje3 + c[n7].valor;
                                        if (c[n8].valor==1)
                                          {
                                              masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                              masked_blit(atras, buffer, 0, 0, x2, y2, 150, 201);
                                              masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                              masked_blit(atras, buffer, 0, 0, x3+10, y3+10, 150, 201);
                                              masked_blit(carta[n1], buffer, 0, 0, x3, y3, 150, 201);
                                              masked_blit(carta[n5], buffer, 0, 0, x3+50, y3, 150, 201);
                                              masked_blit(carta[n7], buffer, 0, 0, x3+100, y3, 150, 201);
                                              masked_blit(carta[n3], buffer, 0, 0, x4, y4, 150, 201);
                                              masked_blit(carta[n4], buffer, 0, 0, x4+50, y4, 150, 201);
                                              masked_blit(carta[n6], buffer, 0, 0, x4+100, y4, 150, 201);
                                              masked_blit(carta[n8], buffer, 0, 0, x4+150, y4, 150, 201);;
                                              textprintf(buffer, font, 700, 80, palette_color[11], "O %d", puntaje3+10);
                                              textprintf(buffer, font, 700, 40, palette_color[11], "%d P", puntaje3);
                                                textprintf(buffer, font, 0, 10, palette_color[5], "Dolares: %ld", apuesta);
                                              masked_blit(apostar, buffer, 0, 0, 630, 490, 135, 25);
                                              masked_blit(cursor, buffer, 0, 0, mouse_x, mouse_y, 20, 25);
                                              blit(buffer, screen, 0, 0, 0, 0, width, height);
                                          }
                                         else if (mouse_x > 620 && mouse_x < 770 && mouse_y > 450 && mouse_y < 520)
                                          {
                                              masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                              masked_blit(atras, buffer, 0, 0, x2, y2, 150, 201);
                                              masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                              masked_blit(atras, buffer, 0, 0, x3+10, y3+10, 150, 201);
                                              masked_blit(carta[n1], buffer, 0, 0, x3, y3, 150, 201);
                                              masked_blit(carta[n5], buffer, 0, 0, x3+50, y3, 150, 201);
                                              masked_blit(carta[n7], buffer, 0, 0, x3+100, y3, 150, 201);
                                              masked_blit(carta[n3], buffer, 0, 0, x4, y4, 150, 201);
                                              masked_blit(carta[n4], buffer, 0, 0, x4+50, y4, 150, 201);
                                              masked_blit(carta[n6], buffer, 0, 0, x4+100, y4, 150, 201);
                                              masked_blit(carta[n8], buffer, 0, 0, x4+150, y4, 150, 201);
                                              textprintf(buffer, font, 700, 40, palette_color[11], "%d P", puntaje3);
                                                textprintf(buffer, font, 0, 10, palette_color[5], "Dolares: %ld", apuesta);;
                                              if (c[n6].valor==1)
                                                {
                                                    textprintf(buffer, font, 700, 80, palette_color[11], "O %d", puntaje3+10);
                                                }
                                              masked_blit(apostar2, buffer, 0, 0, 630, 490, 135, 25);
                                              masked_blit(cursor, buffer, 0, 0, mouse_x, mouse_y, 20, 25);
                                              blit(buffer, screen, 0, 0, 0, 0, width, height);
                                              if (mouse_b & 1)
                                                {
                                                    bj=0;//PASA A LA OPCION DE APOSTAR
                                                    j=3;
                                                }
                                          }
                                         else
                                          {
                                              masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                              masked_blit(atras, buffer, 0, 0, x2, y2, 150, 201);
                                              masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                              masked_blit(atras, buffer, 0, 0, x3+10, y3+10, 150, 201);
                                              masked_blit(carta[n1], buffer, 0, 0, x3, y3, 150, 201);
                                              masked_blit(carta[n5], buffer, 0, 0, x3+50, y3, 150, 201);
                                              masked_blit(carta[n7], buffer, 0, 0, x3+100, y3, 150, 201);
                                              masked_blit(carta[n3], buffer, 0, 0, x4, y4, 150, 201);
                                              masked_blit(carta[n4], buffer, 0, 0, x4+50, y4, 150, 201);
                                              masked_blit(carta[n6], buffer, 0, 0, x4+100, y4, 150, 201);
                                              masked_blit(carta[n8], buffer, 0, 0, x4+150, y4, 150, 201);
                                           textprintf(buffer, font, 700, 40, palette_color[11], "%d P", puntaje3);
                                                textprintf(buffer, font, 0, 10, palette_color[5], "Dolares: %ld", apuesta);
                                              if (c[n8].valor==1)
                                                {
                                                    textprintf(buffer, font, 700, 80, palette_color[11], "O %d", puntaje3+10);
                                                }
                                              masked_blit(apostar, buffer, 0, 0, 630, 490, 135, 25);
                                              masked_blit(cursor, buffer, 0, 0, mouse_x, mouse_y, 20, 25);
                                              blit(buffer, screen, 0, 0, 0, 0, width, height);
                                          }
                                    }
                                  if (puntaje3>21)
                                    {
                                         textprintf(screen, font, 150, 400, palette_color[6], "TU NUMERO ES MAYOR A 21, PERDISTE");
                                         apuesta-=100;
                                         textprintf(screen, font, 150, 500, palette_color[12], "-100");
                                         rest(3000);
                                         bj=1;m=1;ac=1;dc=1;
                                    }
                                  //BLACKJACK
                                  if (puntaje3==21)
                                    {
                                         bj=0;
                                         j=3;
                                    }
                               }
                          while (bj==0)
                               {
                                   if (j==1)
                                     {
                                         if (puntajec==11 && (c[n1].valor==1 || c[n2].valor==1))
                                           {
                                               masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                               masked_blit(atras, buffer, 0, 0, x2, y2, 150, 201);
                                               masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                               masked_blit(atras, buffer, 0, 0, x3+10, y3+10, 150, 201);
                                               masked_blit(carta[n1], buffer, 0, 0, x3, y3, 150, 201);
                                               masked_blit(carta[n3], buffer, 0, 0, x4, y4, 150, 201);
                                               masked_blit(carta[n4], buffer, 0, 0, x4+50, y4, 150, 201);
                                                textprintf(buffer, font, 700, 40, palette_color[11], "%d P", puntaje);
                                                textprintf(buffer, font, 0, 10, palette_color[5], "Dolares: %ld", apuesta);
                                               blit(buffer, screen, 0, 0, 0, 0, width, height);
                                               textprintf(screen, font, 150, 400, palette_color[6], "BLACkJACK!!, PERDISTE");
                                               apuesta-=200;
                                               textprintf(screen, font, 150, 500, palette_color[12], "-200");
                                               rest(3000);
                                               bj=1;m=1;ac=1;dc=1;
                                               break;
                                           }
                                        else if (puntaje==11 && (c[n3].valor==1 || c[n4].valor==1))
                                           {
                                               masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                               masked_blit(atras, buffer, 0, 0, x2, y2, 150, 201);
                                               masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                               masked_blit(atras, buffer, 0, 0, x3+10, y3+10, 150, 201);
                                               masked_blit(carta[n1], buffer, 0, 0, x3, y3, 150, 201);
                                               masked_blit(carta[n3], buffer, 0, 0, x4, y4, 150, 201);
                                               masked_blit(carta[n4], buffer, 0, 0, x4+50, y4, 150, 201);
                                               textprintf(buffer, font, 700, 40, palette_color[11], "%d P", puntaje);
                                                textprintf(buffer, font, 0, 10, palette_color[255,215,0], "Dolares: %ld", apuesta);
                                               blit(buffer, screen, 0, 0, 0, 0, width, height);
                                               textprintf(screen, font, 150, 400, palette_color[6], "BLACkJACK!!, GANASTE");
                                               apuesta+=200;
                                               textprintf(screen, font, 150, 500, palette_color[10], "+200");
                                               rest(3000);
                                               bj=1;m=1;ac=1;dc=1;
                                               break;
                                           }
                                        else if (c[n1].valor==1 || c[n2].valor==1)
                                           {
                                                puntajec=puntajec+10;
                                                if (puntaje > puntajec)
                                                  {
                                                      masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                                      masked_blit(atras, buffer, 0, 0, x2, y2, 150, 201);
                                                      masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                                      masked_blit(atras, buffer, 0, 0, x3+10, y3+10, 150, 201);
                                                      masked_blit(carta[n1], buffer, 0, 0, x3, y3, 150, 201);
                                                      masked_blit(carta[n3], buffer, 0, 0, x4, y4, 150, 201);
                                                      masked_blit(carta[n4], buffer, 0, 0, x4+50, y4, 150, 201);
                                                     textprintf(buffer, font, 700, 40, palette_color[11], "%d P", puntaje);
                                                textprintf(buffer, font, 0, 10, palette_color[5], "Dolares: %ld", apuesta);;
                                                      blit(buffer, screen, 0, 0, 0, 0, width, height);
                                                      textprintf(screen, font, 150, 400, palette_color[6], "GANASTE");
                                                      apuesta+=100;
                                                      textprintf(screen, font, 150, 500, palette_color[10], "+100");
                                                      rest(3000);
                                                      bj=1;m=1;ac=1;dc=1;
                                                      break;
                                                  }
                                                if (puntaje <= puntajec)
                                                  {
                                                      masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                                      masked_blit(atras, buffer, 0, 0, x2, y2, 150, 201);
                                                      masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                                      masked_blit(atras, buffer, 0, 0, x3+10, y3+10, 150, 201);
                                                      masked_blit(carta[n1], buffer, 0, 0, x3, y3, 150, 201);
                                                      masked_blit(carta[n3], buffer, 0, 0, x4, y4, 150, 201);
                                                      masked_blit(carta[n4], buffer, 0, 0, x4+50, y4, 150, 201);
                                                       textprintf(buffer, font, 700, 40, palette_color[11], "%d P", puntaje);
                                                textprintf(buffer, font, 0, 10, palette_color[5], "Dolares: %ld", apuesta);
                                                      blit(buffer, screen, 0, 0, 0, 0, width, height);
                                                      textprintf(screen, font, 150, 400, palette_color[6], "PERDISTE");
                                                      apuesta-=100;
                                                      textprintf(screen, font, 150, 500, palette_color[12], "-100");
                                                      rest(3000);
                                                      bj=1;m=1;ac=1;dc=1;
                                                      break;
                                                  }
                                           }
                                        else if (c[n3].valor==1 || c[n4].valor==1)
                                           {
                                                puntaje=puntaje+10;
                                                if (puntaje > puntajec)
                                                  {
                                                      masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                                      masked_blit(atras, buffer, 0, 0, x2, y2, 150, 201);
                                                      masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                                      masked_blit(atras, buffer, 0, 0, x3+10, y3+10, 150, 201);
                                                      masked_blit(carta[n1], buffer, 0, 0, x3, y3, 150, 201);
                                                      masked_blit(carta[n3], buffer, 0, 0, x4, y4, 150, 201);
                                                      masked_blit(carta[n4], buffer, 0, 0, x4+50, y4, 150, 201);
                                                    textprintf(buffer, font, 700, 40, palette_color[11], "%d P", puntaje);
                                                textprintf(buffer, font, 0, 10, palette_color[5], "Dolares: %ld", apuesta);;
                                                      blit(buffer, screen, 0, 0, 0, 0, width, height);
                                                      textprintf(screen, font, 150, 400, palette_color[6], "GANASTE");
                                                      apuesta+=100;
                                                      textprintf(screen, font, 150, 500, palette_color[10], "+100");
                                                      rest(3000);
                                                      bj=1;m=1;ac=1;dc=1;
                                                      break;
                                                  }
                                                if (puntaje <= puntajec)
                                                  {
                                                      masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                                      masked_blit(atras, buffer, 0, 0, x2, y2, 150, 201);
                                                      masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                                      masked_blit(atras, buffer, 0, 0, x3+10, y3+10, 150, 201);
                                                      masked_blit(carta[n1], buffer, 0, 0, x3, y3, 150, 201);
                                                      masked_blit(carta[n3], buffer, 0, 0, x4, y4, 150, 201);
                                                      masked_blit(carta[n4], buffer, 0, 0, x4+50, y4, 150, 201);
                                                     textprintf(buffer, font, 700, 40, palette_color[11], "%d P", puntaje);
                                                textprintf(buffer, font, 0, 10, palette_color[5], "Dolares: %ld", apuesta);
                                                      blit(buffer, screen, 0, 0, 0, 0, width, height);
                                                      textprintf(screen, font, 150, 400, palette_color[6], "PERDISTE");
                                                      apuesta-=100;
                                                      textprintf(screen, font, 150, 500, palette_color[12], "-100");
                                                      rest(3000);
                                                      bj=1;m=1;ac=1;dc=1;
                                                      break;
                                                  }
                                           }
                                       else
                                        {
                                            if (puntaje > puntajec)
                                              {
                                                  masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                                  masked_blit(atras, buffer, 0, 0, x2, y2, 150, 201);
                                                  masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                                  masked_blit(atras, buffer, 0, 0, x3+10, y3+10, 150, 201);
                                                  masked_blit(carta[n1], buffer, 0, 0, x3, y3, 150, 201);
                                                  masked_blit(carta[n3], buffer, 0, 0, x4, y4, 150, 201);
                                                  masked_blit(carta[n4], buffer, 0, 0, x4+50, y4, 150, 201);
                                                  textprintf(buffer, font, 700, 40, palette_color[11], "%d P", puntaje);
                                                textprintf(buffer, font, 0, 10, palette_color[5], "Dolares: %ld", apuesta);
                                                  blit(buffer, screen, 0, 0, 0, 0, width, height);
                                                  textprintf(screen, font, 150, 400, palette_color[6], "GANASTE");
                                                  apuesta+=100;
                                                  textprintf(screen, font, 150, 500, palette_color[10], "+100");
                                                  rest(3000);
                                                  bj=1;m=1;ac=1;dc=1;
                                                  break;
                                              }
                                       else if (puntaje <= puntajec)
                                              {
                                                  masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                                  masked_blit(atras, buffer, 0, 0, x2, y2, 150, 201);
                                                  masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                                  masked_blit(atras, buffer, 0, 0, x3+10, y3+10, 150, 201);
                                                  masked_blit(carta[n1], buffer, 0, 0, x3, y3, 150, 201);
                                                  masked_blit(carta[n3], buffer, 0, 0, x4, y4, 150, 201);
                                                  masked_blit(carta[n4], buffer, 0, 0, x4+50, y4, 150, 201);
                                                  textprintf(buffer, font, 700, 40, palette_color[11], "%d P", puntaje);
                                                textprintf(buffer, font, 0, 10, palette_color[5], "Dolares: %ld", apuesta);
                                                  blit(buffer, screen, 0, 0, 0, 0, width, height);
                                                  textprintf(screen, font, 150, 400, palette_color[6], "PERDISTE");
                                                  apuesta-=100;
                                                  textprintf(screen, font, 150, 500, palette_color[12], "-100");
                                                  rest(3000);
                                                  bj=1;m=1;ac=1;dc=1;
                                                  break;
                                              }
                                        }
                                     }
                                   if (j==2)
                                     {
                                         if (c[n5].valor==1)
                                           {
                                                if (puntaje2 == 21)
                                                  {
                                                      masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                                      masked_blit(atras, buffer, 0, 0, x2, y2, 150, 201);
                                                      masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                                      masked_blit(atras, buffer, 0, 0, x3+10, y3+10, 150, 201);
                                                      masked_blit(carta[n1], buffer, 0, 0, x3, y3, 150, 201);
                                                      masked_blit(carta[n5], buffer, 0, 0, x3+50, y3, 150, 201);
                                                      masked_blit(carta[n3], buffer, 0, 0, x4, y4, 150, 201);
                                                      masked_blit(carta[n4], buffer, 0, 0, x4+50, y4, 150, 201);
                                                      masked_blit(carta[n6], buffer, 0, 0, x4+100, y4, 150, 201);
                                                    textprintf(buffer, font, 700, 40, palette_color[11], "%d P", puntaje2);
                                                textprintf(buffer, font, 0, 10, palette_color[5], "Dolares: %ld", apuesta);
                                                      blit(buffer, screen, 0, 0, 0, 0, width, height);
                                                      textprintf(screen, font, 150, 400, palette_color[6], "GANASTE");
                                                      apuesta+=100;
                                                      textprintf(screen, font, 150, 500, palette_color[10], "+100");
                                                      rest(3000);
                                                      bj=1;m=1;ac=1;dc=1;
                                                      break;
                                                  }
                                                puntajec2=puntajec2+10;
                                                if (puntaje2 > puntajec2)
                                                  {
                                                      masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                                      masked_blit(atras, buffer, 0, 0, x2, y2, 150, 201);
                                                      masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                                      masked_blit(atras, buffer, 0, 0, x3+10, y3+10, 150, 201);
                                                      masked_blit(carta[n1], buffer, 0, 0, x3, y3, 150, 201);
                                                      masked_blit(carta[n5], buffer, 0, 0, x3+50, y3, 150, 201);
                                                      masked_blit(carta[n3], buffer, 0, 0, x4, y4, 150, 201);
                                                      masked_blit(carta[n4], buffer, 0, 0, x4+50, y4, 150, 201);
                                                      masked_blit(carta[n6], buffer, 0, 0, x4+100, y4, 150, 201);
                                               textprintf(buffer, font, 700, 40, palette_color[11], "%d P", puntaje2);
                                                textprintf(buffer, font, 0, 10, palette_color[5], "Dolares: %ld", apuesta);
                                                      blit(buffer, screen, 0, 0, 0, 0, width, height);
                                                      textprintf(screen, font, 150, 400, palette_color[6], "GANASTE");
                                                      apuesta+=100;
                                                      textprintf(screen, font, 150, 500, palette_color[10], "+100");
                                                      rest(3000);
                                                      bj=1;m=1;ac=1;dc=1;
                                                      break;
                                                  }
                                                if (puntaje2 <= puntajec2)
                                                  {
                                                      if (puntajec2 > 21)
                                                        {
                                                            textprintf(screen, font, 150, 400, palette_color[6], "SU NUMERO ES MAYOR A 21, GANASTE");
                                                            apuesta+=100;
                                                            textprintf(screen, font, 150, 500, palette_color[10], "+100");
                                                            rest(3000);
                                                            bj=1;m=1;ac=1;dc=1;
                                                            break;
                                                        }
                                                       else
                                                        {
                                                            masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                                            masked_blit(atras, buffer, 0, 0, x2, y2, 150, 201);
                                                            masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                                            masked_blit(atras, buffer, 0, 0, x3+10, y3+10, 150, 201);
                                                            masked_blit(carta[n1], buffer, 0, 0, x3, y3, 150, 201);
                                                            masked_blit(carta[n5], buffer, 0, 0, x3+50, y3, 150, 201);
                                                            masked_blit(carta[n3], buffer, 0, 0, x4, y4, 150, 201);
                                                            masked_blit(carta[n4], buffer, 0, 0, x4+50, y4, 150, 201);
                                                            masked_blit(carta[n6], buffer, 0, 0, x4+100, y4, 150, 201);
                                                         textprintf(buffer, font, 700, 40, palette_color[11], "%d P", puntaje2);
                                                textprintf(buffer, font, 0, 10, palette_color[5], "Dolares: %ld", apuesta);
                                                            blit(buffer, screen, 0, 0, 0, 0, width, height);
                                                            textprintf(screen, font, 150, 400, palette_color[6], "PERDISTE");
                                                            apuesta-=100;
                                                            textprintf(screen, font, 150, 500, palette_color[12], "-100");
                                                            rest(3000);
                                                            bj=1;m=1;ac=1;dc=1;
                                                            break;
                                                        }
                                                  }
                                           }
                                        else if (c[n6].valor==1)
                                           {
                                                if (puntajec2 == 21)
                                                  {
                                                      masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                                      masked_blit(atras, buffer, 0, 0, x2, y2, 150, 201);
                                                      masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                                      masked_blit(atras, buffer, 0, 0, x3+10, y3+10, 150, 201);
                                                      masked_blit(carta[n1], buffer, 0, 0, x3, y3, 150, 201);
                                                      masked_blit(carta[n5], buffer, 0, 0, x3+50, y3, 150, 201);
                                                      masked_blit(carta[n3], buffer, 0, 0, x4, y4, 150, 201);
                                                      masked_blit(carta[n4], buffer, 0, 0, x4+50, y4, 150, 201);
                                                      masked_blit(carta[n6], buffer, 0, 0, x4+100, y4, 150, 201);
                                                      textprintf(buffer, font, 700, 40, palette_color[11], "%d P", puntaje2);
                                                textprintf(buffer, font, 0, 10, palette_color[5], "Dolares: %ld", apuesta);
                                                      blit(buffer, screen, 0, 0, 0, 0, width, height);
                                                      textprintf(screen, font, 150, 400, palette_color[6], "PERDISTE");
                                                      apuesta-=100;
                                                      textprintf(screen, font, 150, 500, palette_color[12], "-100");
                                                      rest(3000);
                                                      bj=1;m=1;ac=1;dc=1;
                                                      break;
                                                  }
                                                puntaje2=puntaje2+10;
                                                if (puntaje2 > puntajec2)
                                                  {
                                                      if (puntaje2 > 21)
                                                        {
                                                            textprintf(screen, font, 150, 400, palette_color[6], "TU NUMERO ES MAYOR A 21, PERDISTE");
                                                            apuesta-=100;
                                                            textprintf(screen, font, 150, 500, palette_color[12], "-100");
                                                            rest(3000);
                                                            bj=1;m=1;ac=1;dc=1;
                                                            break;
                                                        }
                                                       else
                                                        {
                                                            masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                                            masked_blit(atras, buffer, 0, 0, x2, y2, 150, 201);
                                                            masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                                            masked_blit(atras, buffer, 0, 0, x3+10, y3+10, 150, 201);
                                                            masked_blit(carta[n1], buffer, 0, 0, x3, y3, 150, 201);
                                                            masked_blit(carta[n5], buffer, 0, 0, x3+50, y3, 150, 201);
                                                            masked_blit(carta[n3], buffer, 0, 0, x4, y4, 150, 201);
                                                            masked_blit(carta[n4], buffer, 0, 0, x4+50, y4, 150, 201);
                                                            masked_blit(carta[n6], buffer, 0, 0, x4+100, y4, 150, 201);
                                                            textprintf(buffer, font, 700, 40, palette_color[11], "%d P", puntaje2);
                                                            textprintf(buffer, font, 0, 10, palette_color[5], "Dolares: %ld", apuesta);
                                                            blit(buffer, screen, 0, 0, 0, 0, width, height);
                                                            textprintf(screen, font, 150, 400, palette_color[6], "GANASTE");
                                                            apuesta+=100;
                                                            textprintf(screen, font, 150, 500, palette_color[12], "+100");
                                                            rest(3000);
                                                            bj=1;m=1;ac=1;dc=1;
                                                            break;
                                                        }
                                                  }
                                                if (puntaje2 <= puntajec2)
                                                  {
                                                      masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                                      masked_blit(atras, buffer, 0, 0, x2, y2, 150, 201);
                                                      masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                                      masked_blit(atras, buffer, 0, 0, x3+10, y3+10, 150, 201);
                                                      masked_blit(carta[n1], buffer, 0, 0, x3, y3, 150, 201);
                                                      masked_blit(carta[n5], buffer, 0, 0, x3+50, y3, 150, 201);
                                                      masked_blit(carta[n3], buffer, 0, 0, x4, y4, 150, 201);
                                                      masked_blit(carta[n4], buffer, 0, 0, x4+50, y4, 150, 201);
                                                      masked_blit(carta[n6], buffer, 0, 0, x4+100, y4, 150, 201);
                                                   textprintf(buffer, font, 700, 40, palette_color[11], "%d P", puntaje2);
                                                textprintf(buffer, font, 0, 10, palette_color[5], "Dolares: %ld", apuesta);
                                                      blit(buffer, screen, 0, 0, 0, 0, width, height);
                                                      textprintf(screen, font, 150, 400, palette_color[6], "PERDISTE");
                                                      apuesta-=100;
                                                      textprintf(screen, font, 150, 500, palette_color[12], "-100");
                                                      rest(3000);
                                                      bj=1;m=1;ac=1;dc=1;
                                                      break;
                                                  }
                                           }
                                       else
                                        {
                                            if (puntaje2 > puntajec2)
                                              {
                                                  masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                                  masked_blit(atras, buffer, 0, 0, x2, y2, 150, 201);
                                                  masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                                  masked_blit(atras, buffer, 0, 0, x3+10, y3+10, 150, 201);
                                                  masked_blit(carta[n1], buffer, 0, 0, x3, y3, 150, 201);
                                                  masked_blit(carta[n5], buffer, 0, 0, x3+50, y3, 150, 201);
                                                  masked_blit(carta[n3], buffer, 0, 0, x4, y4, 150, 201);
                                                  masked_blit(carta[n4], buffer, 0, 0, x4+50, y4, 150, 201);
                                                  masked_blit(carta[n6], buffer, 0, 0, x4+100, y4, 150, 201);
                                                 textprintf(buffer, font, 700, 40, palette_color[11], "%d P", puntaje2);
                                                  blit(buffer, screen, 0, 0, 0, 0, width, height);
                                                  textprintf(screen, font, 150, 400, palette_color[6], "GANASTE");
                                                 textprintf(buffer, font, 0, 550, palette_color[5], "Dolares: %ld", apuesta);
                                                  apuesta+=100;
                                                  textprintf(screen, font, 150, 500, palette_color[10], "+100");
                                                  rest(3000);
                                                  bj=1;m=1;ac=1;dc=1;
                                                  break;
                                              }
                                       else if (puntaje2 <= puntajec2)
                                              {
                                                  if (puntajec2 > 21)
                                                    {
                                                        textprintf(screen, font, 150, 400, palette_color[6], "SU NUMERO ES MAYOR A 21, GANASTE");
                                                        apuesta+=100;
                                                        textprintf(screen, font, 150, 500, palette_color[10], "+100");
                                                        rest(3000);
                                                        bj=1;m=1;ac=1;dc=1;
                                                        break;
                                                    }
                                                   else
                                                    {
                                                        masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                                        masked_blit(atras, buffer, 0, 0, x2, y2, 150, 201);
                                                        masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                                        masked_blit(atras, buffer, 0, 0, x3+10, y3+10, 150, 201);
                                                        masked_blit(carta[n1], buffer, 0, 0, x3, y3, 150, 201);
                                                        masked_blit(carta[n5], buffer, 0, 0, x3+50, y3, 150, 201);
                                                        masked_blit(carta[n3], buffer, 0, 0, x4, y4, 150, 201);
                                                        masked_blit(carta[n4], buffer, 0, 0, x4+50, y4, 150, 201);
                                                        masked_blit(carta[n6], buffer, 0, 0, x4+100, y4, 150, 201);
                                                     textprintf(buffer, font, 700, 40, palette_color[11], "%d P", puntaje2);
                                                textprintf(buffer, font, 0, 10, palette_color[5], "Dolares: %ld", apuesta);
                                                        blit(buffer, screen, 0, 0, 0, 0, width, height);
                                                        textprintf(screen, font, 150, 400, palette_color[6], "PERDISTE");
                                                        apuesta-=100;
                                                        textprintf(screen, font, 150, 500, palette_color[12], "-100");
                                                        rest(3000);
                                                        bj=1;m=1;ac=1;dc=1;
                                                        break;
                                                    }
                                              }
                                        }
                                     }//AQUI TERMINA EL j==2
                                   if (j==3)
                                     {
                                        if (puntaje3 == 21)
                                          {
                                                masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                                masked_blit(atras, buffer, 0, 0, x2, y2, 150, 201);
                                                masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                                masked_blit(atras, buffer, 0, 0, x3+10, y3+10, 150, 201);
                                                masked_blit(carta[n1], buffer, 0, 0, x3, y3, 150, 201);
                                                masked_blit(carta[n5], buffer, 0, 0, x3+50, y3, 150, 201);
                                                masked_blit(carta[n7], buffer, 0, 0, x3+100, y3, 150, 201);
                                                masked_blit(carta[n3], buffer, 0, 0, x4, y4, 150, 201);
                                                masked_blit(carta[n4], buffer, 0, 0, x4+50, y4, 150, 201);
                                                masked_blit(carta[n6], buffer, 0, 0, x4+100, y4, 150, 201);
                                                masked_blit(carta[n8], buffer, 0, 0, x4+150, y4, 150, 201);
                                             textprintf(buffer, font, 700, 40, palette_color[11], "%d P", puntaje3);
                                                textprintf(buffer, font, 0, 10, palette_color[5], "Dolares: %ld", apuesta);
                                                blit(buffer, screen, 0, 0, 0, 0, width, height);
                                                textprintf(screen, font, 150, 400, palette_color[6], "GANASTE");
                                                apuesta+=100;
                                                textprintf(screen, font, 150, 500, palette_color[10], "+100");
                                                rest(3000);
                                                bj=1;m=1;ac=1;dc=1;
                                                break;
                                          }
                                        if (puntaje3 > puntajec3)
                                          {
                                                masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                                masked_blit(atras, buffer, 0, 0, x2, y2, 150, 201);
                                                masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                                masked_blit(atras, buffer, 0, 0, x3+10, y3+10, 150, 201);
                                                masked_blit(carta[n1], buffer, 0, 0, x3, y3, 150, 201);
                                                masked_blit(carta[n5], buffer, 0, 0, x3+50, y3, 150, 201);
                                                masked_blit(carta[n7], buffer, 0, 0, x3+100, y3, 150, 201);
                                                masked_blit(carta[n3], buffer, 0, 0, x4, y4, 150, 201);
                                                masked_blit(carta[n4], buffer, 0, 0, x4+50, y4, 150, 201);
                                                masked_blit(carta[n6], buffer, 0, 0, x4+100, y4, 150, 201);
                                                masked_blit(carta[n8], buffer, 0, 0, x4+150, y4, 150, 201);
                                              textprintf(buffer, font, 700, 40, palette_color[11], "%d P", puntaje3);
                                                textprintf(buffer, font, 0, 10, palette_color[5], "Dolares: %ld", apuesta);
                                                blit(buffer, screen, 0, 0, 0, 0, width, height);
                                                textprintf(screen, font, 150, 400, palette_color[6], "GANASTE");
                                                apuesta+=100;
                                                textprintf(screen, font, 150, 500, palette_color[10], "+100");
                                                rest(3000);
                                                bj=1;m=1;ac=1;dc=1;
                                                break;
                                          }
                                        if (puntaje3 <= puntajec3)
                                          {
                                             if (puntajec3 > 21)
                                               {
                                                    textprintf(screen, font, 150, 400, palette_color[6], "SU NUMERO ES MAYO A 21, GANASTE");
                                                    apuesta+=100;
                                                    textprintf(screen, font, 150, 500, palette_color[10], "+100");
                                                    rest(3000);
                                                    bj=1;m=1;ac=1;dc=1;puntaje=0;puntajec=0;
                                                    break;
                                               }
                                              else
                                               {
                                                    masked_blit(fondo, buffer, 0, 0, 0, 0, width, height);
                                                    masked_blit(atras, buffer, 0, 0, x2, y2, 150, 201);
                                                    masked_blit(logo, buffer, 0, 0, x, y, 420, 150);
                                                    masked_blit(atras, buffer, 0, 0, x3+10, y3+10, 150, 201);
                                                    masked_blit(carta[n1], buffer, 0, 0, x3, y3, 150, 201);
                                                    masked_blit(carta[n5], buffer, 0, 0, x3+50, y3, 150, 201);
                                                    masked_blit(carta[n7], buffer, 0, 0, x3+100, y3, 150, 201);
                                                    masked_blit(carta[n3], buffer, 0, 0, x4, y4, 150, 201);
                                                    masked_blit(carta[n4], buffer, 0, 0, x4+50, y4, 150, 201);
                                                    masked_blit(carta[n6], buffer, 0, 0, x4+100, y4, 150, 201);
                                                    masked_blit(carta[n8], buffer, 0, 0, x4+150, y4, 150, 201);
                                                    textprintf(buffer, font, 700, 40, palette_color[11], "%d P", puntaje3);
                                                    textprintf(buffer, font, 0, 10, palette_color[5], "Dolares: %ld", apuesta);;
                                                    blit(buffer, screen, 0, 0, 0, 0, width, height);
                                                    textprintf(screen, font, 150, 400, palette_color[6], "PERDISTE");
                                                    apuesta-=100;
                                                    textprintf(screen, font, 150, 500, palette_color[12], "-100");
                                                    rest(3000);
                                                    bj=1;m=1;ac=1;dc=1;
                                                    break;
                                               }
                                          }
                                     }//AQUI TERMINA j==3
                               }
                     }
            }
        dolares = fopen("dolares.txt", "w+");
        fprintf(dolares, "%ld", apuesta);//SE GUARDA EL SALDO EN EL ARCHIVO
        fclose(dolares);
        stop_sample(blackjack);

        allegro_exit();
   }
   END_OF_MAIN();

void Push(Pila *pila, int n)
   {
    pNodo nuevo;
    nuevo = (pNodo)malloc(sizeof(cartas));
    nuevo->numero = n;
    nuevo->siguiente = *pila;
    *pila = nuevo;
   }

int Pop(Pila *pila)
   {
    int n;
    pNodo nodo;
    nodo = *pila;
    n=nodo->numero;
    *pila = nodo->siguiente;
    free(nodo);
    return n;
   }

