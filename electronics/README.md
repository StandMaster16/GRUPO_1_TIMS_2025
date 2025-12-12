# Diretório de Eletrônica

## Como está organizado?

Em tese, tudo está na pasta `img/`, que contém um histórico de evolução do trabalho
de eletrônica do nosso mini sumô. Há um pequeno salto entre as semanas, por motivos
diversos, por exemplo: não tiramos foto de tudo. Porém, o que foi registrado e é 
pertinente, você com certeza vai encontrar lá.

## Um pouco sobre o circuito

O circuito do mini sumô "Sr. Batata" possui uma história interessante: Nasceu como um
simples arranjo de controlador, ponte H e motores, para uma máquina mortífera de 
controlador, ponte H, motores e algumas coisinhas.

## Como ele funciona?

### Componentes:

 - Dois motores n20 300 rpm
 - Uma ESP32
 - Uma ponte H TB6612FNG
 - Um buzzer passivo
 - Um controlador de tensão (AMS1117 ou o Buck Converter (ainda não foi decidido (11/12/25)))
 - Placa fenolite universal
 - Três KRE Borne
 - Barramento de pinos
 - Um switch alavanca

### Descrição:

A alimentação está ligada ao switch, a qual envia energia para a ponte H pela porta VM, que alimenta os motores A e B. A mesma alimentação é enviada ao regulador de tensão que converte 7.4v para 5v na porta VIM da ESP32. Os motores A e B estão ligados às respectivas portas OUT da ponte H, sendo as portas IN e PWM ligadas à ESP32. Por fim, o buzzer passivo conecta-se à ESP32

### Mural de conexões

- Positivo da Bateria -> L2 (switch)
- COM (switch) -> VM (TB6612FNG)
- A01 (TB6612FNG) -> Negativo do motor A
- A02 (TB6612FNG) -> Positivo do motor A
- B01 (TB6612FNG) -> Negativo do motor B
- B02 (TB6612FNG) -> Positivo do motor B
- D13 (ESP32) -> PWMA (TB6612FNG)
- D14 (ESP32) -> PWMB (TB6612FNG)
- D27 (ESP32) -> BI1 (TB6612FNG)
- D26 (ESP32) -> BI2 (TB6612FNG)
- D25 (ESP32) -> AI1 (TB6612FNG)
- D24 (ESP32) -> AI2 (TB6612FNG)

#### Para versão com AM1117 5V

- VIM (AMS1117) -> COM (switch)
- VOUT (AMS1117) -> VIM (ESP32)
- GND (AMS1117) -> GND (ESP32)
  
#### Para versão com Buck Converter

- IN+ -> COM (switch)
- IN- -> Negativo da Bateria
- OUT+ -> VIM (ESP32)
- OUT- -> GND (ESP32)

