#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define LED_AZUL 11
#define LED_VERMELHO 12
#define LED_VERDE 13
#define BOTAO 5

#define TEMPORIZADOR 1000 // 1 segundo

bool botao_pressionado = false;
bool botao_liberado = true;

void ligar_leds() {
    gpio_put(LED_AZUL, 1);
    gpio_put(LED_VERMELHO, 1);
    gpio_put(LED_VERDE, 1);
}

void desligar_leds() {
    gpio_put(LED_AZUL, 0);
    gpio_put(LED_VERMELHO, 0);
    gpio_put(LED_VERDE, 0);
}

void turn_off_callback(repeating_timer_t *rt) {
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

void botao_callback() {
    if (!botao_pressionado && botao_liberado) {
        botao_pressionado = true;
        botao_liberado = false;
        ligar_leds();
        repeating_timer_t rt;
        add_repeating_timer_ms(TEMPORIZADOR, turn_off_callback, NULL, &rt);
    }
}

void configurar_gpio() {
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

int main() {
    stdio_init_all();
    configurar_gpio();

    desligar_leds();
    
    while (true) {
        if (gpio_get(BOTAO) == 0 && !botao_pressionado && botao_liberado) {
            botao_callback();
        }
        sleep_ms(100);
    }

    return 0;
}