CONTROLE DE LED'S COM BOTÃO

Este programa controla três LEDs (azul, vermelho e verde) utilizando um botão. Quando o botão é pressionado, os LEDs são ligados e, após um tempo determinado, são desligados em sequência.

Instruções de Uso

Conecte os LEDs ao Raspberry Pi Pico, seguindo a seguinte configuração:
LED Azul: GPIO 11
LED Vermelho: GPIO 12
LED Verde: GPIO 13
Botão: GPIO 5

Pressione o botão para ligar os LEDs e, após um tempo determinado, eles serão desligados em sequência.
Funcionamento

O programa utiliza um temporizador para desligar os LEDs em sequência. Quando o botão é pressionado, os LEDs são ligados e o temporizador é iniciado. Após um tempo determinado, o temporizador desliga os LEDs em sequência.

Autor: Douglas Ramos

Obs:

O programa utiliza a biblioteca pico/stdlib.h para interagir com o Raspberry Pi Pico.
O programa utiliza a biblioteca hardware/gpio.h para controlar os LEDs e o botão.
O programa utiliza a função add_repeating_timer_ms para criar um temporizador que desliga os LEDs em sequência.