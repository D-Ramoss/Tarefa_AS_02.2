// Inclui as bibliotecas necessárias
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

// Define as constantes para os LEDs e o botão
#define LED_AZUL 11
#define LED_VERMELHO 12
#define LED_VERDE 13
#define BOTAO 5

// Define o tempo de espera para o temporizador
#define TEMPORIZADOR 1000 // 1 segundo

// Variáveis para controlar o estado do botão
bool botao_pressionado = false;
bool botao_liberado = true;

// Função para ligar os LEDs
void ligar_leds() {
    // Liga os LEDs
    gpio_put(LED_AZUL, 1);
    gpio_put(LED_VERMELHO, 1);
    gpio_put(LED_VERDE, 1);
}

// Função para desligar os LEDs
void desligar_leds() {
    // Desliga os LEDs
    gpio_put(LED_AZUL, 0);
    gpio_put(LED_VERMELHO, 0);
    gpio_put(LED_VERDE, 0);
}

// Função de callback para o temporizador
void turn_off_callback(repeating_timer_t *rt) {
    // Desliga os LEDs em sequência
    static int estado = 0;
    switch (estado) {
        case 0:
            gpio_put(LED_AZUL, 0);
            estado = 1;
            break;
        case 1:
            gpio_put(LED_VERMELHO, 0);
            estado = 2;
            break;
        case 2:
            gpio_put(LED_VERDE, 0);
            estado = 0;
            cancel_repeating_timer(rt);
            botao_pressionado = false;
            botao_liberado = true;
            break;
    }
}

// Função para controlar o botão
void botao_callback() {
    // Liga os LEDs e inicia o temporizador
    if (!botao_pressionado && botao_liberado) {
        botao_pressionado = true;
        botao_liberado = false;
        ligar_leds();
        repeating_timer_t rt;
        add_repeating_timer_ms(TEMPORIZADOR, turn_off_callback, NULL, &rt);
    }
}

// Função para configurar os GPIOs
void configurar_gpio() {
    // Configura os GPIOs para os LEDs e o botão
    gpio_init(LED_AZUL);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_init(BOTAO);
    gpio_set_dir(BOTAO, GPIO_IN);
    gpio_pull_up(BOTAO);
}

// Função principal
int main() {
    // Inicializa a biblioteca stdio e configura os GPIOs
    stdio_init_all();
    configurar_gpio();

    // Desliga os LEDs
    desligar_leds();
    
    // Loop infinito
    while (true) {
        // Verifica se o botão está pressionado e liberado
        if (gpio_get(BOTAO) == 0 && !botao_pressionado && botao_liberado) {
            // Chama a função de callback do botão
            botao_callback();
        }
        // Espera 100ms
        sleep_ms(100);
    }

    return 0;
}