/* Program Ceratotomia_Radial  */ 

#include <stdio.h>
#include <math.h>
#include <graphics.h>

#define FEMININO     0
#define MASCULINO    1

#define MIOPIA       0
#define ASTIGMATISMO 1

const float Tabela_Zonas_Opticas[3][11] =
 {
   {4.50,4.25,4.00,3.75,3.75,3.50,3.25,3.25,3.00,3.00,3.00},
   {4.75,4.50,4.25,4.00,4.00,3.75,3.50,3.50,3.25,3.25,3.00},
   {5.00,4.75,4.50,4.25,4.25,4.00,3.75,3.75,3.50,3.50,3.00}
 };
const int Tabela_Cortes[11] = {4, 4, 4, 4, 6, 6, 6, 8, 8, 12, 16};

int          tipo_cirurgia; 
float        graus, eixo; 
int          sexo; 
int          idade; 
float        pio,
             paquimetria,
             ceratometria,
             zona_optica,
             graus_reais,
             eixo_cortes,
             paquimetria_real,
             comprimento_lamina; 
int          cortes; 
char         paciente[51]; 
char         olho[3]; 


void Circulo(float diametro, int intensidade)

{ int xp, yp, i; 
  float raio; 


  raio = diametro / 2.0; 
  for (i = 0; i <= 360; i++) 
    { 
      xp = (int) (floor(raio * cos(i / 180 * M_PI) * 340.0 / 13.0) + 470L); 
      yp = (int) (floor(raio * sin(i / 180 * M_PI) * 156.0 / 13.0) + 78L); 
      if (i % intensidade == 0) putpixel(xp,yp,1); 
    } 
} 


void Tracar_Cortes(float         diametro_ZO,
                   float         diametro_cornea,
                   int           cortes)

{ float         angulo, raio_ZO, raio_cornea; 
    int      xi, yi, xf, yf, i; 


  angulo = (float) (2.0 * M_PI / cortes); 
  raio_ZO = diametro_ZO / 2.0; 
  raio_cornea = diametro_cornea / 2.0; 
  for (i = 0; i < cortes; i++) 
    { 
      xi = (int) (floor(raio_ZO * cos(i * angulo) * 340.0 / 13.0) + 470L); 
      yi = (int) (floor(raio_ZO * sin(i * angulo) * 156.0 / 13.0) + 78L); 
      xf = (int) (floor(raio_cornea * cos(i * angulo) * 340.0 / 13.0) + 470L); 
      yf = (int) (floor(raio_cornea * sin(i * angulo) * 156.0 / 13.0) + 78L); 
      line(xi,yi,xf,yf);
    } 
} 


void         Moldura(void)

{
  setcolor(WHITE);
  line(300,0,300,153); 
  line(301,0,301,153); 
  line(300,153,639,153); 
  line(639,153,639,0); 
  line(638,153,638,0); 
  line(639,0,300,0); 
} 


void         Obter_Dados_pelo_Teclado(void)

{ 
}


void         Ajustar_Lamina(void)

{ 
  if ((paquimetria >= 52.0) && (paquimetria < 56.0)) 
    paquimetria_float = paquimetria + 0.0; 
  if ((paquimetria >= 56.0) && (paquimetria < 64.0)) 
    paquimetria_float = paquimetria + 1.0; 
  if ((paquimetria >= 64.0) && (paquimetria < 68.0)) 
    paquimetria_float = paquimetria + 2.0; 
  if ((paquimetria >= 68.0) && (paquimetria < 75.0)) 
    paquimetria_float = paquimetria + 3.0; 
  comprimento_lamina = paquimetria_float * 0.98; 
} 


void         Sobre_Corrigir(void)

{ 
  if ((graus_reais <= -1.50) && (graus_reais > -2.25)) graus_reais = graus_reais + (-0.00); 
  if ((graus_reais <= -2.25) && (graus_reais > -3.25)) graus_reais = graus_reais + (-0.25); 
  if ((graus_reais <= -3.25) && (graus_reais > -4.25)) graus_reais = graus_reais + (-0.50); 
  if ((graus_reais <= -4.25)) graus_reais = graus_reais + (-0.75); 
} 


void         Ajustar_por_Sexo_Idade(void)

{ 
  switch (idade) {
    
    case 20:   
    case 21:   
    case 22:   
    case 23:   
    case 24:   
    case 25:   
    case 26:   
    case 27:   
    case 28:   
    case 29:   switch (sexo) {
               
               case MASCULINO:   graus_reais = graus_reais + (-0.75); 
               break; 
               
               case FEMININO:   graus_reais = graus_reais + (-1.00); 
             break; 
             } 
    break; 
    
    case 30.0:   
    case 301:   
    case 302:   
    case 303:   
    case 304:   
    case 305:   
    case 306:   
    case 307:   
    case 308:   
    case 309:   
    case 310:   
    case 311:   
    case 312:   
    case 313:   
    case 314:   
    case 315:   
    case 316:   
    case 317:   
    case 318:   
    case 319:   
    case 320:   
    case 321:   
    case 322:   
    case 323:   
    case 324:   
    case 325:   
    case 326:   
    case 327:   
    case 328:   
    case 329:   
    case 330:   
    case 331:   
    case 332:   
    case 333:   
    case 334:   
    case 335:   
    case 336:   
    case 337:   
    case 338:   
    case 339:   
    case 340:   graus_reais = graus_reais + (-0.50); 
    break; 
    
    case 35.0:   
    case 351:   
    case 352:   
    case 353:   
    case 354:   
    case 355:   
    case 356:   
    case 357:   
    case 358:   
    case 359:   
    case 360:   
    case 361:   
    case 362:   
    case 363:   
    case 364:   
    case 365:   
    case 366:   
    case 367:   
    case 368:   
    case 369:   
    case 370:   graus_reais = graus_reais + (0.00); 
    break; 
    
    case 38.0:   
    case 381:   
    case 382:   
    case 383:   
    case 384:   
    case 385:   
    case 386:   
    case 387:   
    case 388:   
    case 389:   
    case 390:   
    case 391:   
    case 392:   
    case 393:   
    case 394:   
    case 395:   
    case 396:   
    case 397:   
    case 398:   
    case 399:   
    case 400:   graus_reais = graus_reais + (0.50); 
    break; 
    
    case 41.0:   
    case 411:   
    case 412:   
    case 413:   
    case 414:   
    case 415:   
    case 416:   
    case 417:   
    case 418:   
    case 419:   
    case 420:   
    case 421:   
    case 422:   
    case 423:   
    case 424:   
    case 425:   
    case 426:   
    case 427:   
    case 428:   
    case 429:   
    case 430:   
    case 431:   
    case 432:   
    case 433:   
    case 434:   
    case 435:   
    case 436:   
    case 437:   
    case 438:   
    case 439:   
    case 440:   
    case 441:   
    case 442:   
    case 443:   
    case 444:   
    case 445:   
    case 446:   
    case 447:   
    case 448:   
    case 449:   
    case 450:   
    case 451:   
    case 452:   
    case 453:   
    case 454:   
    case 455:   
    case 456:   
    case 457:   
    case 458:   
    case 459:   
    case 460:   
    case 461:   
    case 462:   
    case 463:   
    case 464:   
    case 465:   
    case 466:   
    case 467:   
    case 468:   
    case 469:   
    case 470:   
    case 471:   
    case 472:   
    case 473:   
    case 474:   
    case 475:   
    case 476:   
    case 477:   
    case 478:   
    case 479:   
    case 480:   
    case 481:   
    case 482:   
    case 483:   
    case 484:   
    case 485:   
    case 486:   
    case 487:   
    case 488:   
    case 489:   
    case 490:   graus_reais = graus_reais + (1.00); 
    break; 
    
    case 50.0:   
    case 501:   
    case 502:   
    case 503:   
    case 504:   
    case 505:   
    case 506:   
    case 507:   
    case 508:   
    case 509:   
    case 510:   
    case 511:   
    case 512:   
    case 513:   
    case 514:   
    case 515:   
    case 516:   
    case 517:   
    case 518:   
    case 519:   
    case 520:   
    case 521:   
    case 522:   
    case 523:   
    case 524:   
    case 525:   
    case 526:   
    case 527:   
    case 528:   
    case 529:   
    case 530:   
    case 531:   
    case 532:   
    case 533:   
    case 534:   
    case 535:   
    case 536:   
    case 537:   
    case 538:   
    case 539:   
    case 540:   
    case 541:   
    case 542:   
    case 543:   
    case 544:   
    case 545:   
    case 546:   
    case 547:   
    case 548:   
    case 549:   
    case 550:   graus_reais = graus_reais + (1.50); 
  break; 
  } 
} 


void         Calcular_Miopia(void)

{ int         linha, coluna; 


  Sobre_Corrigir();   /* ajuste de margem de seguranca */ 
  Ajustar_por_Sexo_Idade(); 
  if ((pio > 17.0)) 
    graus_reais = graus_reais + (0.25); 
  if ((pio < 14.0)) 
    graus_reais = graus_reais + (-0.25); 
  if ((paquimetria > 56.0)) 
    graus_reais = graus_reais + floor((paquimetria - 56.0) / 10.0) * (0.25); 
  if ((paquimetria < 52.0)) 
    graus_reais = graus_reais + floor((52L - paquimetria) / 10.0) * (-0.25); 
  if ((ceratometria <= 43.0)) linha = 1; 
  if ((ceratometria >= 43.12) && (ceratometria <= 45.0)) linha = 2; 
  if ((ceratometria >= 45.12) && (ceratometria <= 47.0)) linha = 3; 
  if ((graus_reais >= -1.50)) coluna = 01; 
  if ((graus_reais < -1.50) && (graus_reais >= -1.75)) coluna = 02; 
  if ((graus_reais < -1.75) && (graus_reais >= -2.00)) coluna = 03; 
  if ((graus_reais < -2.00) && (graus_reais >= -2.25)) coluna = 04; 
  if ((graus_reais < -2.25) && (graus_reais >= -2.50)) coluna = 05; 
  if ((graus_reais < -2.50) && (graus_reais >= -3.00)) coluna = 06; 
  if ((graus_reais < -3.00) && (graus_reais >= -3.50)) coluna = 07; 
  if ((graus_reais < -3.50) && (graus_reais >= -4.00)) coluna = 08; 
  if ((graus_reais < -4.00) && (graus_reais >= -5.00)) coluna = 09; 
  if ((graus_reais < -5.00) && (graus_reais >= -6.00)) coluna = 10; 
  if ((graus_reais < -6.00) && (graus_reais >= -8.00)) coluna = 11; 
  zona_optica = Tabela_Zonas_Opticas[linha][coluna-1]; 
  cortes = Tabela_Cortes[coluna-10]; 
} 


void         Exibir_Miopia(void)

{ 
  if ((graus_reais <= -8.25)) 
    { 
      textcolor(White + Blink); 
      printf("Paciente fora dos parametros normais.\n"); 
      Sound(600); Delay(400); NoSound(); 
      textcolor(White); 
    } 
  else 
    { 
      HiRes(); 
      printf("Miopia\n"); printf("\n"); 
      printf("Graus : %5.2f D\n",graus); 
      printf("Sexo : "); 
      switch (sexo) {
        
        case MASCULINO:   printf("Masculino\n"); 
        break; 
        
        case FEMININO:   printf("Feminino\n"); 
      break; 
      } 
      printf("Idade : %d anos\n",idade); 
      printf("PIO : %4.1f mmHg\n",pio); 
      printf("Paquimetria : %4.2f M\n",paquimetria); 
      printf("Ceratometria : %4.2f D\n",ceratometria); 
      printf("\n"); 
      printf("Graus reais : %5.2f D\n",graus_reais); 
      printf("Zona optica : %4.2f mm\n",zona_optica); 
      printf("Cortes : %d\n",cortes); 
      printf("\n"); 
      printf("Paquimetria float : %4.2f M\n",paquimetria_float); 
      printf("Comprimento da lamina : %4.2f M\n",comprimento_lamina); 
      printf("\n"); printf("\n"); printf("\n"); printf("\n"); printf("\n"); 
      printf("%s\n",paciente); 
      printf("Ceratotomia do %s\n",olho); 
      Moldura(); 
      Circulo(12,3); 
      Circulo(zona_optica,9.0); 
      Tracar_Cortes(zona_optica,12.0,cortes); 
      do { }  while (!(keypressed())); 
      TextMode(CO80); 
    } 
} 


void         Calcular_Astigmatismo(void)

{ 
  Ajustar_por_Sexo_Idade(); 
  if ((pio > 17.0)) 
    graus_reais = graus_reais + (0.25); 
  if ((pio < 14.0)) 
    graus_reais = graus_reais + (-0.25); 
  if ((graus_reais <= -0.75) && (graus_reais >= -1.25)) zona_optica = 8.0; 
  if ((graus_reais <= -1.50) && (graus_reais >= -2.00)) zona_optica = 7.0; 
  if ((graus_reais <= -2.12) && (graus_reais >= -3.00)) zona_optica = 6.0; 
  if ((graus_reais <= -3.12) && (graus_reais >= -4.00)) zona_optica = 5.0; 
  if ((graus_reais <= -4.12) && (graus_reais >= -5.00)) zona_optica = 4.0; 
  if ((graus_reais <= -5.12) && (graus_reais >= -6.00)) zona_optica = 3.5; 
  eixo_cortes = eixo - 90.0; 
  if (eixo_cortes < 0.0) eixo_cortes = 180.0 + eixo_cortes; 
  if ((graus_reais <= -3.25)) 
    cortes = 6;
  else 
    cortes = 4; 
} 


void         Exibir_Astigmatismo(void)

{ 
  HiRes(); 
  printf("Astigmatismo\n"); printf("\n"); 
  printf("Graus : %5.2f D\n",graus); 
  printf("Eixo : %6.1f graus\n",eixo); 
  printf("Sexo : "); 
  switch (sexo) {
    
    case MASCULINO:   printf("Masculino\n"); 
    break; 
    
    case FEMININO:   printf("Feminino\n"); 
  break; 
  } 
  printf("Idade : %d anos\n",idade); 
  printf("PIO : %4.1f mmHg\n",pio); 
  printf("Paquimetria : %4.2f M\n",paquimetria); 
  printf("\n"); 
  printf("Graus reais : %5.2f D\n",graus_reais); 
  printf("Zona optica : %4.2f mm\n",zona_optica); 
  printf("Cortes : %d\n",cortes); 
  printf("Eixo dos cortes : %6.1f M\n",eixo_cortes); 
  printf("\n"); 
  printf("Paquimetria float : %4.2f M\n",paquimetria_float); 
  printf("Comprimento da lamina : %4.2f M\n",comprimento_lamina); 
  do { }  while (!(keypressed())); 
  TextMode(CO80); 
} 


void main(int argc, char **argv)
{
   tptcsys_init(argc,argv);
   crt_init();
   tp3_init();


  clrscr(); 
  Obter_Dados_pelo_Teclado(); 
  Ajustar_Lamina(); 
  switch (tipo_cirurgia) {
    
    case ASTIGMATISMO:   { 
                     Calcular_Astigmatismo(); 
                     Exibir_Astigmatismo(); 
                   } 
    break; 
    
    case MIOPIA:   { 
                     Calcular_Miopia(); 
                     Exibir_Miopia(); 
                   } 
  break; 
  } 
}



