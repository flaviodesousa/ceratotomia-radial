Program Ceratotomia_Radial;

uses crt, turbo3, graph3;

const Tabela_Zonas_Opticas : array [1..3,1..11] of Real =
  ((4.50, 4.25, 4.00, 3.75, 3.75, 3.50, 3.25, 3.25, 3.00, 3.00, 3.00),
   (4.75, 4.50, 4.25, 4.00, 4.00, 3.75, 3.50, 3.50, 3.25, 3.25, 3.00),
   (5.00, 4.75, 4.50, 4.25, 4.25, 4.00, 3.75, 3.75, 3.50, 3.50, 3.00));
      Tabela_Cortes : array [1..11] of Byte =
   (4, 4, 4, 4, 6, 6, 6, 8, 8, 12, 16);
      MASCULINO    = 'M';
      FEMININO     = 'F';
      ASTIGMATISMO = 'A';
      MIOPIA       = 'M';

var tipo_cirurgia      : Char;
    graus,
    eixo               : Real;
    sexo               : Char;
    idade              : Byte;
    pio,
    paquimetria,
    ceratometria,
    zona_optica,
    graus_reais,
    eixo_cortes,
    paquimetria_real,
    comprimento_lamina : Real;
    cortes             : Byte;
    paciente           : String[50];
    olho               : String[2];

procedure Circulo(diametro:Real;intensidade:Integer);

var xp,yp,i : Integer;
    raio    : Real;

begin
  raio := diametro / 2;
  for i := 0 to 360 do
    begin
      xp := Trunc(raio * cos(i/180*PI) * 340 / 13) + 470;
      yp := Trunc(raio * sin(i/180*PI) * 156 / 13) +  78;
      if i mod intensidade = 0 then Plot(xp,yp,1);
    end;
end;

procedure Tracar_Cortes(diametro_ZO,diametro_cornea:Real;cortes:Byte);

var angulo,
    raio_ZO, raio_cornea : Real;
    xi,yi,xf,yf,i : Integer;

begin
  angulo := 2 * PI / cortes;
  raio_ZO := diametro_ZO / 2;
  raio_cornea := diametro_cornea / 2;
  for i := 0 to Pred(cortes) do
    begin
      xi := Trunc(raio_ZO     * cos(i*angulo) * 340 / 13) + 470;
      yi := Trunc(raio_ZO     * sin(i*angulo) * 156 / 13) +  78;
      xf := Trunc(raio_cornea * cos(i*angulo) * 340 / 13) + 470;
      yf := Trunc(raio_cornea * sin(i*angulo) * 156 / 13) +  78;
      Draw(xi,yi,xf,yf,1);
    end;
end;

procedure Moldura;

begin
  Draw(300,0,300,153,1);
  Draw(301,0,301,153,1);
  Draw(300,153,639,153,1);
  Draw(639,153,639,0,1);
  Draw(638,153,638,0,1);
  Draw(639,0,300,0,1);
end;

procedure Obter_Dados_pelo_Teclado;

begin
  repeat
    Write('Tipo de cirurgia (A)stigmatismo ou (M)iopia? ');
    ReadLn(tipo_cirurgia); tipo_cirurgia := UpCase(tipo_cirurgia);
  until tipo_cirurgia in ['A','M'];
  repeat
    Write('Grau (D)? ');
    ReadLn(graus);
  until (graus <= -1.0) and (graus >= -8.0);
  graus_reais := graus;
  if (tipo_cirurgia = ASTIGMATISMO) then
    repeat
      Write('Eixo (entre 0ø e 180ø)? ');
      ReadLn(eixo);
    until (eixo >=0) and (eixo <=180);
  repeat
    Write('Sexo? ');
    ReadLn(sexo); sexo := UpCase(sexo);
  until sexo in ['M','F'];
  repeat
    Write('Idade (ò20 e ó55)? ');
    ReadLn(idade);
  until (idade >= 20) and (idade <= 55);
  repeat
    Write('PIO (ò10mmHg e ó24mmHg)? ');
    ReadLn(pio);
  until (pio >= 10) and (pio <= 24);
  repeat
    Write('Paquimetria (ò50æ e <75æ) ? ');
    ReadLn(paquimetria);
  until paquimetria >= 50;
  if tipo_cirurgia = MIOPIA then
    repeat
      Write('Ceratometria (ò41mm e ó47mm) ? ');
      ReadLn(ceratometria)
    until (ceratometria >= 41) and (ceratometria <= 47);
  Write('Paciente: '); ReadLn(paciente);
  Write('Olho: '); ReadLn(olho);
end;

procedure Ajustar_Lamina;

begin
  if (paquimetria >= 52) and (paquimetria < 56) then
    paquimetria_real := paquimetria + 0;
  if (paquimetria >= 56) and (paquimetria < 64) then
    paquimetria_real := paquimetria + 1;
  if (paquimetria >= 64) and (paquimetria < 68) then
    paquimetria_real := paquimetria + 2;
  if (paquimetria >= 68) and (paquimetria < 75) then
    paquimetria_real := paquimetria + 3;
  comprimento_lamina := paquimetria_real * 0.98;
end;

procedure Sobre_Corrigir;

begin
  if (graus_reais <= -1.50) and (graus_reais > -2.25) then graus_reais := graus_reais + (-0.00);
  if (graus_reais <= -2.25) and (graus_reais > -3.25) then graus_reais := graus_reais + (-0.25);
  if (graus_reais <= -3.25) and (graus_reais > -4.25) then graus_reais := graus_reais + (-0.50);
  if (graus_reais <= -4.25)                           then graus_reais := graus_reais + (-0.75);
end;

procedure Ajustar_por_Sexo_Idade;

begin
  case idade of
    20..29 : case sexo of
               MASCULINO : graus_reais := graus_reais + (-0.75);
               FEMININO  : graus_reais := graus_reais + (-1.00);
             end;
    30..34 : graus_reais := graus_reais + (-0.50);
    35..37 : graus_reais := graus_reais + (+0.00);
    38..40 : graus_reais := graus_reais + (+0.50);
    41..49 : graus_reais := graus_reais + (+1.00);
    50..55 : graus_reais := graus_reais + (+1.50);
  end;
end;

procedure Calcular_Miopia;

var linha, coluna : Byte;

begin
  Sobre_Corrigir; {ajuste de margem de seguranca}
  Ajustar_por_Sexo_Idade;
  if (pio > 17) then
    graus_reais := graus_reais + (+0.25);
  if (pio < 14) then
    graus_reais := graus_reais + (-0.25);
  if (paquimetria > 56) then
    graus_reais := graus_reais + Trunc((paquimetria - 56)/10) * (+0.25);
  if (paquimetria < 52) then
    graus_reais := graus_reais + Trunc((52 - paquimetria)/10) * (-0.25);
  if (ceratometria <= 43)                            then linha := 1;
  if (ceratometria >= 43.12) and (ceratometria <=45) then linha := 2;
  if (ceratometria >= 45.12) and (ceratometria <=47) then linha := 3;
  if (graus_reais >= -1.50)                            then coluna := 01;
  if (graus_reais <  -1.50) and (graus_reais >= -1.75) then coluna := 02;
  if (graus_reais <  -1.75) and (graus_reais >= -2.00) then coluna := 03;
  if (graus_reais <  -2.00) and (graus_reais >= -2.25) then coluna := 04;
  if (graus_reais <  -2.25) and (graus_reais >= -2.50) then coluna := 05;
  if (graus_reais <  -2.50) and (graus_reais >= -3.00) then coluna := 06;
  if (graus_reais <  -3.00) and (graus_reais >= -3.50) then coluna := 07;
  if (graus_reais <  -3.50) and (graus_reais >= -4.00) then coluna := 08;
  if (graus_reais <  -4.00) and (graus_reais >= -5.00) then coluna := 09;
  if (graus_reais <  -5.00) and (graus_reais >= -6.00) then coluna := 10;
  if (graus_reais <  -6.00) and (graus_reais >= -8.00) then coluna := 11;
  zona_optica := Tabela_Zonas_Opticas[linha,coluna];
  cortes      := Tabela_Cortes[coluna];
end;

procedure Exibir_Miopia;

begin
  if (graus_reais <= -8.25) then
    begin
      TextColor(WHITE+BLINK);
      WriteLn('Paciente fora dos parametros normais.');
      Sound(600); Delay(400); NoSound;
      TextColor(WHITE);
    end
  else
    begin
      HiRes;
      WriteLn('Miopia'); WriteLn;
      WriteLn('Graus : ',graus:5:2,' D');
      Write('Sexo : ');
      case sexo of
        MASCULINO : WriteLn('Masculino');
        FEMININO  : WriteLn('Feminino');
      end;
      WriteLn('Idade : ',idade,' anos');
      WriteLn('PIO : ',pio:4:1,' mmHg');
      WriteLn('Paquimetria : ',paquimetria:4:2,' M');
      WriteLn('Ceratometria : ',ceratometria:4:2,' D');
      WriteLn;
      WriteLn('Graus reais : ',graus_reais:5:2,' D');
      WriteLn('Zona optica : ',zona_optica:4:2,' mm');
      WriteLn('Cortes : ',cortes);
      WriteLn;
      WriteLn('Paquimetria real : ',paquimetria_real:4:2,' M');
      WriteLn('Comprimento da lamina : ',comprimento_lamina:4:2,' M');
      WriteLn; WriteLn; WriteLn; WriteLn; WriteLn;
      WriteLn(paciente);
      WriteLn('Ceratotomia do ',olho);
      Moldura;
      Circulo(12,3);
      Circulo(zona_optica,9);
      Tracar_Cortes(zona_optica,12,cortes);
      repeat until KeyPressed;
      TextMode(CO80);
    end;
end;

procedure Calcular_Astigmatismo;

begin
  Ajustar_por_Sexo_Idade;
  if (pio > 17) then
    graus_reais := graus_reais + (+0.25);
  if (pio < 14) then
    graus_reais := graus_reais + (-0.25);
  if (graus_reais <= -0.75) and (graus_reais >= -1.25) then zona_optica := 8.0;
  if (graus_reais <= -1.50) and (graus_reais >= -2.00) then zona_optica := 7.0;
  if (graus_reais <= -2.12) and (graus_reais >= -3.00) then zona_optica := 6.0;
  if (graus_reais <= -3.12) and (graus_reais >= -4.00) then zona_optica := 5.0;
  if (graus_reais <= -4.12) and (graus_reais >= -5.00) then zona_optica := 4.0;
  if (graus_reais <= -5.12) and (graus_reais >= -6.00) then zona_optica := 3.5;
  eixo_cortes := eixo - 90.0;
  if eixo_cortes < 0 then eixo_cortes := 180 + eixo_cortes;
  if (graus_reais <= -3.25) then
    cortes := 6
  else
    cortes := 4;
end;

procedure Exibir_Astigmatismo;

begin
  HiRes;
  WriteLn('Astigmatismo'); WriteLn;
  WriteLn('Graus : ',graus:5:2,' D');
  WriteLn('Eixo : ',eixo:6:1,' graus');
  Write('Sexo : ');
  case sexo of
    MASCULINO : WriteLn('Masculino');
    FEMININO  : WriteLn('Feminino');
  end;
  WriteLn('Idade : ',idade,' anos');
  WriteLn('PIO : ',pio:4:1,' mmHg');
  WriteLn('Paquimetria : ',paquimetria:4:2,' M');
  WriteLn;
  WriteLn('Graus reais : ',graus_reais:5:2,' D');
  WriteLn('Zona optica : ',zona_optica:4:2,' mm');
  WriteLn('Cortes : ',cortes);
  WriteLn('Eixo dos cortes : ',eixo_cortes:6:1,' M');
  WriteLn;
  WriteLn('Paquimetria real : ',paquimetria_real:4:2,' M');
  WriteLn('Comprimento da lamina : ',comprimento_lamina:4:2,' M');
  repeat until KeyPressed;
  TextMode(CO80);
end;

begin
  ClrScr;
  Obter_Dados_pelo_Teclado;
  Ajustar_Lamina;
  case tipo_cirurgia of
    ASTIGMATISMO : begin
                     Calcular_Astigmatismo;
                     Exibir_Astigmatismo;
                   end;
    MIOPIA       : begin
                     Calcular_Miopia;
                     Exibir_Miopia;
                   end;
  end;
end.
